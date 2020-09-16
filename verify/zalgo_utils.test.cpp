#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include <bits/stdc++.h>

using namespace std;


#include "../lib/classes/stringutils.cpp"


signed main(){
    string s;
    cin >> s;
    StringUtils su(s);
    for(int i = 0; i < s.size(); ++i){
        cout << su.get_lcp(su.sa_inv[0], su.sa_inv[i]) << " \n"[i == s.size() - 1];
    }
}

