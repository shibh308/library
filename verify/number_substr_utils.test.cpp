#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/stringutils.cpp"


signed main(){
    string s;
    cin >> s;
    StringUtils su(s);
    int n = s.size();
    cout << (1LL * n * (n + 1)) / 2 - accumulate(su.lcp.begin(), su.lcp.end(), 0LL) << endl;
}

