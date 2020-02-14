namespace geometry{
    using D = long double;
    using C = complex<D>;
    constexpr D eps =1e-9;

    struct Point;
    bool near_eq(Point, Point);

    struct Point{
        D x, y;
        Point(D x = 0.0, D y = 0.0) : x(x), y(y){}
        friend bool operator<(const Point& a, const Point& b){
            return a.x == b.x ? a.y < b.y : a.x < b.x;
        }
        Point& operator+=(Point a){x += a.x, y += a.y; return *this;}
        Point& operator-=(Point a){x -= a.x, y -= a.y; return *this;}
        Point& operator*=(D p){x *= p, y *= p; return *this;}
        friend Point operator+(Point a, Point b){return Point(a) += b;}
        friend Point operator-(Point a, Point b){return Point(a) -= b;}
        friend Point operator*(Point a, Point b){return Point(a.x * b.x - a.y * b.y, a.x * b.y + b.x * a.y);}
        friend Point operator*(Point a, D p){return Point(a) *= p;}
    };
    using P = Point;
    bool near_eq(D a, D b){return abs(a - b) < eps;}
    bool near_eq(P a, P b){return near_eq(a.x, b.x) && near_eq(a.y, b.y);}
    D diag(P a){
        assert(!near_eq(a, P()));
        return atan2(a.y, a.x);
    }
    D abs_square(P a){return a.x * a.x + a.y * a.y;}
    D abs(P a){return sqrt(abs_square(a));}
    P conj(P a){return P(a.x, -a.y);}
    P norm(P a){return a * conj(a);}
    D dist(P a, P b){return abs(a - b);}
    D dot(P a, P b){return a.x * b.x + a.y * b.y;}
    D cross(P a, P b){return a.x * b.y - a.y * b.x;}
    int ccw(P a, P b, P c){
        b -= a;
        c -= a;
        if(cross(b, c) > eps)return 1;
        if(cross(b, c) < -eps)return -1;
        if(dot(b, c) < -eps)return 2;
        if(norm(b) < norm(c))return -2;
        return 0;
    }
    bool is_on_line(P a1, P a2, P b){return abs(ccw(a1, a2, b)) != -1;}
    bool is_on_segment(P a1, P a2, P b){return !ccw(a1, a2, b);}
    bool intersect(P a1, P a2, P b1, P b2){
        return ccw(a1, a2, b1) * ccw(a1, a2, b2) <= 0 &&
               ccw(b1, b2, a1) * ccw(b1, b2, a2) <= 0;
    }
    P cross_point(P a1, P a2, P b1, P b2){
        D d1 = cross(b2 - b1, b1 - a1);
        D d2 = cross(b2 - b1, a2 - a1);
        if(near_eq(d1, 0) && near_eq(d2, 0))return a1;
        assert(!near_eq(d2, 0));
        return a1 + d1 / d2 * (a2 - a1);
    }
}
