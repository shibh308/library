#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1327"

#include "bits/stdc++.h"

using namespace std;

using i64 = long long;

struct ModInt{
    static i64 mod;
    i64 p;

    ModInt() : p(0){}
    ModInt(i64 x){p = x >= 0 ? x % mod : x + (-x + mod - 1) / mod * mod;}

    ModInt& operator+=(const ModInt& y){p = p + *y - ((p + *y) >= mod ? mod : 0); return *this;}
    ModInt& operator-=(const ModInt& y){p = p - *y + (p - *y < 0 ? mod : 0); return *this;}
    ModInt& operator*=(const ModInt& y){p = (p * *y) % mod; return *this;}

    ModInt operator+(const ModInt& y) const{ModInt x = *this; return x += y;}
    ModInt operator-(const ModInt& y) const{ModInt x = *this; return x -= y;}
    ModInt operator*(const ModInt& y) const{ModInt x = *this; return x *= y;}

    ModInt& operator++(){p = (p + 1) % mod; return *this;}
    ModInt& operator--(){p = (p - 1 + mod) % mod; return *this;}

    bool operator==(const ModInt& y) const{return p == *y;}
    bool operator!=(const ModInt& y) const{return p != *y;}

    const i64& operator*() const{return p;}
    i64& operator*(){return p;}

};

using mint = ModInt;
i64 mint::mod = 0;


#include "../lib/classes/matrix.cpp"

bool solve(){
    int n, m, a, b, c, t;
    cin >> n >> m >> a >> b >> c >> t;
    if(!n)
        return false;

    mint::mod = m;

    Matrix<mint> mat(n, n);
    for(int i = 0; i < n; ++i){
        if(i)
            mat.at(i - 1, i) = a;
        mat.at(i, i) = b;
        if(i != n - 1)
            mat.at(i + 1, i) = c;
    }
    Matrix<mint> st(1, n);
    for(int i = 0; i < n; ++i){
        int s;
        cin >> s;
        st.at(0, i) = s;
    }
    auto res = st * mat.pow(t);
    for(int i = 0; i < n; ++i){
        cout << *res.at(0, i) << " \n"[i == n - 1];
    }

    return true;
}

signed main(){
    while(solve());
}
