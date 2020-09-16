---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/tangent_lines.test.cpp
    title: verify/tangent_lines.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/geometry.cpp\"\nnamespace geometry{\n    using D = long\
    \ double;\n    constexpr D eps =1e-9;\n\n    struct Point;\n    bool near_eq(Point,\
    \ Point);\n    D norm(Point);\n\n    struct Point{\n        D x, y;\n        Point(D\
    \ x = 0.0, D y = 0.0) : x(x), y(y){}\n        friend bool operator<(const Point&\
    \ a, const Point& b){\n            return a.x == b.x ? a.y < b.y : a.x < b.x;\n\
    \        }\n        Point& operator+=(Point a){x += a.x, y += a.y; return *this;}\n\
    \        Point& operator-=(Point a){x -= a.x, y -= a.y; return *this;}\n     \
    \   Point& operator*=(D p){x *= p, y *= p; return *this;}\n        Point& operator*=(Point\
    \ b){return *this = *this * b;}\n        Point& operator/=(D p){x /= p, y /= p;\
    \ return *this;}\n        Point& operator/=(Point b){return *this = *this / b;}\n\
    \        friend Point operator+(Point a, Point b){return Point(a) += b;}\n   \
    \     friend Point operator-(Point a, Point b){return Point(a) -= b;}\n      \
    \  friend Point operator*(Point a, D p){return Point(a) *= p;}\n        friend\
    \ Point operator*(Point a, Point b){return Point(a.x * b.x - a.y * b.y, a.x *\
    \ b.y + b.x * a.y);}\n        friend Point operator/(Point a, D b){return Point(a)\
    \ /= b;}\n        friend Point operator/(Point a, Point b){return Point(a.x *\
    \ b.x + a.y * b.y, b.x * a.y - a.x * b.y) / norm(b);}\n    };\n    using P = Point;\n\
    \n    struct Circle : public Point{\n        D r;\n        Circle(Point p = Point(),\
    \ D r = 1) : Point(p), r(r){}\n        Circle(D x = 0.0, D y = 0.0, D r = 1) :\
    \ Point(x, y), r(r){}\n    };\n    using C = Circle;\n\n    bool near_eq(D a,\
    \ D b = 0.0){return abs(a - b) < eps;}\n    bool near_eq(P a, P b = Point()){return\
    \ near_eq(a.x, b.x) && near_eq(a.y, b.y);}\n    D diag(P a){\n        assert(!near_eq(a));\n\
    \        return atan2(a.y, a.x);\n    }\n    D norm(P a){return a.x * a.x + a.y\
    \ * a.y;}\n    D abs(P a){return sqrt(norm(a));}\n    D dist(P a, P b){return\
    \ abs(a - b);}\n    D dot(P a, P b){return a.x * b.x + a.y * b.y;}\n    D cross(P\
    \ a, P b){return a.x * b.y - a.y * b.x;}\n    int ccw(P a, P b, P c){\n      \
    \  b -= a;\n        c -= a;\n        if(cross(b, c) > eps)return 1;\n        if(cross(b,\
    \ c) < -eps)return -1;\n        if(dot(b, c) < -eps)return 2;\n        if(norm(b)\
    \ < norm(c))return -2;\n        return 0;\n    }\n    bool is_on_line(P a1, P\
    \ a2, P b){return abs(ccw(a1, a2, b)) != -1;}\n    bool is_on_segment(P a1, P\
    \ a2, P b){return !ccw(a1, a2, b);}\n    P proj(P a1, P a2, P b){return a1 + dot(a2\
    \ - a1, b - a1) / norm(a2 - a1) * (a2 - a1);} // \u76F4\u7DDA\u3078\u306E\u5C04\
    \u5F71\u70B9\n    D dist(P a1, P a2, P b){return dist(proj(a1, a2, b), b);}\n\
    \    bool intersect(P a1, P a2, P b1, P b2){\n        return ccw(a1, a2, b1) *\
    \ ccw(a1, a2, b2) <= 0 &&\n               ccw(b1, b2, a1) * ccw(b1, b2, a2) <=\
    \ 0;\n    }\n    P cross_point(P a1, P a2, P b1, P b2){\n        D d1 = cross(b2\
    \ - b1, b1 - a1);\n        D d2 = cross(b2 - b1, a2 - a1);\n        if(near_eq(d1)\
    \ && near_eq(d2))return a1;\n        assert(!near_eq(d2));\n        return a1\
    \ + d1 / d2 * (a2 - a1);\n    }\n    vector<Point> cross_point(C c1, C c2){\n\
    \        vector<Point> cross;\n        P diff = c2 - c1;\n        D d = abs(diff);\n\
    \        D crl = (norm(diff) + c1.r * c1.r - c2.r * c2.r) / (2 * d);\n       \
    \ if(near_eq(d) || c1.r < abs(crl))\n            return cross;\n        P abn\
    \ = diff * P(0, sqrt(c1.r * c1.r - crl * crl) / d);\n        P cp = c1 + crl /\
    \ d * diff;\n        cross.push_back(cp + abn);\n        if(!near_eq(abn))\n \
    \           cross.push_back(cp - abn);\n        return cross;\n    }\n    vector<pair<P,\
    \ P>> tangent_lines(C c1, C c2){ // \u5171\u901A\u63A5\u7DDA\u3001\u63A5\u7DDA\
    \u306E\u4E21\u7AEF\u306F\u5186\u3068\u306E\u63A5\u70B9\n        vector<pair<P,\
    \ P>> lines;\n        D d = dist(c1, c2);\n        for(int i = 0; i < 2; ++i){\n\
    \            D sin =(c1.r - (1 - i * 2) * c2.r) / d;\n            if(!(sin * sin\
    \ < 1 + eps))\n                break;\n            D cos = sqrt(max(1 - sin *\
    \ sin, D(0)));\n            for(int j = 0; j < 2; ++j){\n                P n =\
    \ (c2 - c1) * P(sin, (1 - j * 2) * cos) / d;\n                lines.emplace_back(c1\
    \ + c1.r * n, c2 + (1 - i * 2)  * c2.r * n);\n                if(cos < eps)\n\
    \                    break;\n            }\n        }\n        return lines;\n\
    \    }\n}\n"
  code: "namespace geometry{\n    using D = long double;\n    constexpr D eps =1e-9;\n\
    \n    struct Point;\n    bool near_eq(Point, Point);\n    D norm(Point);\n\n \
    \   struct Point{\n        D x, y;\n        Point(D x = 0.0, D y = 0.0) : x(x),\
    \ y(y){}\n        friend bool operator<(const Point& a, const Point& b){\n   \
    \         return a.x == b.x ? a.y < b.y : a.x < b.x;\n        }\n        Point&\
    \ operator+=(Point a){x += a.x, y += a.y; return *this;}\n        Point& operator-=(Point\
    \ a){x -= a.x, y -= a.y; return *this;}\n        Point& operator*=(D p){x *= p,\
    \ y *= p; return *this;}\n        Point& operator*=(Point b){return *this = *this\
    \ * b;}\n        Point& operator/=(D p){x /= p, y /= p; return *this;}\n     \
    \   Point& operator/=(Point b){return *this = *this / b;}\n        friend Point\
    \ operator+(Point a, Point b){return Point(a) += b;}\n        friend Point operator-(Point\
    \ a, Point b){return Point(a) -= b;}\n        friend Point operator*(Point a,\
    \ D p){return Point(a) *= p;}\n        friend Point operator*(Point a, Point b){return\
    \ Point(a.x * b.x - a.y * b.y, a.x * b.y + b.x * a.y);}\n        friend Point\
    \ operator/(Point a, D b){return Point(a) /= b;}\n        friend Point operator/(Point\
    \ a, Point b){return Point(a.x * b.x + a.y * b.y, b.x * a.y - a.x * b.y) / norm(b);}\n\
    \    };\n    using P = Point;\n\n    struct Circle : public Point{\n        D\
    \ r;\n        Circle(Point p = Point(), D r = 1) : Point(p), r(r){}\n        Circle(D\
    \ x = 0.0, D y = 0.0, D r = 1) : Point(x, y), r(r){}\n    };\n    using C = Circle;\n\
    \n    bool near_eq(D a, D b = 0.0){return abs(a - b) < eps;}\n    bool near_eq(P\
    \ a, P b = Point()){return near_eq(a.x, b.x) && near_eq(a.y, b.y);}\n    D diag(P\
    \ a){\n        assert(!near_eq(a));\n        return atan2(a.y, a.x);\n    }\n\
    \    D norm(P a){return a.x * a.x + a.y * a.y;}\n    D abs(P a){return sqrt(norm(a));}\n\
    \    D dist(P a, P b){return abs(a - b);}\n    D dot(P a, P b){return a.x * b.x\
    \ + a.y * b.y;}\n    D cross(P a, P b){return a.x * b.y - a.y * b.x;}\n    int\
    \ ccw(P a, P b, P c){\n        b -= a;\n        c -= a;\n        if(cross(b, c)\
    \ > eps)return 1;\n        if(cross(b, c) < -eps)return -1;\n        if(dot(b,\
    \ c) < -eps)return 2;\n        if(norm(b) < norm(c))return -2;\n        return\
    \ 0;\n    }\n    bool is_on_line(P a1, P a2, P b){return abs(ccw(a1, a2, b)) !=\
    \ -1;}\n    bool is_on_segment(P a1, P a2, P b){return !ccw(a1, a2, b);}\n   \
    \ P proj(P a1, P a2, P b){return a1 + dot(a2 - a1, b - a1) / norm(a2 - a1) * (a2\
    \ - a1);} // \u76F4\u7DDA\u3078\u306E\u5C04\u5F71\u70B9\n    D dist(P a1, P a2,\
    \ P b){return dist(proj(a1, a2, b), b);}\n    bool intersect(P a1, P a2, P b1,\
    \ P b2){\n        return ccw(a1, a2, b1) * ccw(a1, a2, b2) <= 0 &&\n         \
    \      ccw(b1, b2, a1) * ccw(b1, b2, a2) <= 0;\n    }\n    P cross_point(P a1,\
    \ P a2, P b1, P b2){\n        D d1 = cross(b2 - b1, b1 - a1);\n        D d2 =\
    \ cross(b2 - b1, a2 - a1);\n        if(near_eq(d1) && near_eq(d2))return a1;\n\
    \        assert(!near_eq(d2));\n        return a1 + d1 / d2 * (a2 - a1);\n   \
    \ }\n    vector<Point> cross_point(C c1, C c2){\n        vector<Point> cross;\n\
    \        P diff = c2 - c1;\n        D d = abs(diff);\n        D crl = (norm(diff)\
    \ + c1.r * c1.r - c2.r * c2.r) / (2 * d);\n        if(near_eq(d) || c1.r < abs(crl))\n\
    \            return cross;\n        P abn = diff * P(0, sqrt(c1.r * c1.r - crl\
    \ * crl) / d);\n        P cp = c1 + crl / d * diff;\n        cross.push_back(cp\
    \ + abn);\n        if(!near_eq(abn))\n            cross.push_back(cp - abn);\n\
    \        return cross;\n    }\n    vector<pair<P, P>> tangent_lines(C c1, C c2){\
    \ // \u5171\u901A\u63A5\u7DDA\u3001\u63A5\u7DDA\u306E\u4E21\u7AEF\u306F\u5186\u3068\
    \u306E\u63A5\u70B9\n        vector<pair<P, P>> lines;\n        D d = dist(c1,\
    \ c2);\n        for(int i = 0; i < 2; ++i){\n            D sin =(c1.r - (1 - i\
    \ * 2) * c2.r) / d;\n            if(!(sin * sin < 1 + eps))\n                break;\n\
    \            D cos = sqrt(max(1 - sin * sin, D(0)));\n            for(int j =\
    \ 0; j < 2; ++j){\n                P n = (c2 - c1) * P(sin, (1 - j * 2) * cos)\
    \ / d;\n                lines.emplace_back(c1 + c1.r * n, c2 + (1 - i * 2)  *\
    \ c2.r * n);\n                if(cos < eps)\n                    break;\n    \
    \        }\n        }\n        return lines;\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/geometry.cpp
  requiredBy: []
  timestamp: '2020-02-25 16:29:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/tangent_lines.test.cpp
documentation_of: lib/geometry.cpp
layout: document
redirect_from:
- /library/lib/geometry.cpp
- /library/lib/geometry.cpp.html
title: lib/geometry.cpp
---
