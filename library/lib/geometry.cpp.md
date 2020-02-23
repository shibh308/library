---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: lib/geometry.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8acc63b1e238f3255c900eed37254b8">lib</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/geometry.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-20 20:31:58+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
namespace geometry{
    using D = long double;
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

    struct Circle : public Point{
        D r;
        Circle(Point p = Point(), D r = 1) : Point(p), r(r){}
        Circle(D x = 0.0, D y = 0.0, D r = 1) : Point(x, y), r(r){}
    };
    using C = Circle;

    bool near_eq(D a, D b = 0.0){return abs(a - b) < eps;}
    bool near_eq(P a, P b = Point()){return near_eq(a.x, b.x) && near_eq(a.y, b.y);}
    D diag(P a){
        assert(!near_eq(a));
        return atan2(a.y, a.x);
    }
    D norm(P a){return a.x * a.x + a.y * a.y;}
    D abs(P a){return sqrt(norm(a));}
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
        if(near_eq(d1) && near_eq(d2))return a1;
        assert(!near_eq(d2));
        return a1 + d1 / d2 * (a2 - a1);
    }

    vector<Point> cross_point(C c1, C c2){
        vector<Point> cross;
        P diff = c2 - c1;
        D d = abs(diff);
        D crl = (norm(diff) + c1.r * c1.r - c2.r * c2.r) / (2 * d);
        if(near_eq(d) || c1.r < abs(crl))
            return cross;
        P abn = diff * P(0, sqrt(c1.r * c1.r - crl * crl) / d);
        P cp = c1 + crl / d * diff;
        cross.push_back(cp + abn);
        if(!near_eq(abn))
            cross.push_back(cp - abn);
        return cross;
    }
}


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/geometry.cpp"
namespace geometry{
    using D = long double;
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

    struct Circle : public Point{
        D r;
        Circle(Point p = Point(), D r = 1) : Point(p), r(r){}
        Circle(D x = 0.0, D y = 0.0, D r = 1) : Point(x, y), r(r){}
    };
    using C = Circle;

    bool near_eq(D a, D b = 0.0){return abs(a - b) < eps;}
    bool near_eq(P a, P b = Point()){return near_eq(a.x, b.x) && near_eq(a.y, b.y);}
    D diag(P a){
        assert(!near_eq(a));
        return atan2(a.y, a.x);
    }
    D norm(P a){return a.x * a.x + a.y * a.y;}
    D abs(P a){return sqrt(norm(a));}
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
        if(near_eq(d1) && near_eq(d2))return a1;
        assert(!near_eq(d2));
        return a1 + d1 / d2 * (a2 - a1);
    }

    vector<Point> cross_point(C c1, C c2){
        vector<Point> cross;
        P diff = c2 - c1;
        D d = abs(diff);
        D crl = (norm(diff) + c1.r * c1.r - c2.r * c2.r) / (2 * d);
        if(near_eq(d) || c1.r < abs(crl))
            return cross;
        P abn = diff * P(0, sqrt(c1.r * c1.r - crl * crl) / d);
        P cp = c1 + crl / d * diff;
        cross.push_back(cp + abn);
        if(!near_eq(abn))
            cross.push_back(cp - abn);
        return cross;
    }
}


```
{% endraw %}

<a href="../../index.html">Back to top page</a>

