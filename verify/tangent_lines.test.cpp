#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2201"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;

template <typename T>
bool chmax(T& x, T y){
    if(x < y){
        x = y;
        return true;
    }
    return false;
}


#include "../lib/geometry.cpp"

bool solve(){
    int n;
    cin >> n;
    if(!n)
        return false;
    vector<int> x(n);
    vector<int> y(n);
    vector<int> r(n);
    vector<int> m(n);
    for(int i = 0; i < n; ++i)
        cin >> x[i] >> y[i] >> r[i] >> m[i];
    if(n == 1){
        cout << 1 << endl;
        return true;
    }
    using namespace geometry;
    vector<C> circles, power;
    for(int i = 0; i < n; ++i){
        circles.emplace_back(x[i], y[i], r[i]);
        power.emplace_back(x[i], y[i], r[i] + m[i]);
    }

    vector<pair<P,P>> vs;
    for(int i = 0; i < n; ++i){
        for(int j = i + 1; j < n; ++j){
            auto res = tangent_lines(circles[i], circles[j]);
            for(auto p : res)
                vs.push_back(p);
            res = tangent_lines(circles[i], power[j]);
            for(auto p : res)
                vs.push_back(p);
            res = tangent_lines(power[i], circles[j]);
            for(auto p : res)
                vs.push_back(p);
            res = tangent_lines(power[i], power[j]);
            for(auto p : res)
                vs.push_back(p);
        }
    }
    int ans = 0;
    for(auto& p : vs){
        P p1, p2;
        tie(p1, p2) = p;
        int cnt = 0;
        for(int i = 0; i < n; ++i){
            D d = dist(p1, p2, circles[i]);
            if(r[i] < d + eps && d < r[i] + m[i] + eps)
                ++cnt;
        }
        chmax(ans, cnt);
    }
    cout << ans << endl;
    return true;
}

signed main(){
    while(solve());
}
