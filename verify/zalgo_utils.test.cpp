#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include <bits/stdc++.h>

using namespace std;


#include "../lib/classes/stringutils.cpp"


signed main(){
    string s;
    cin >> s;
    StringUtils su(s);
    for(int i = 0; i < s.size(); ++i){
        cout << su.get_lcp(0, i) << " \n"[i == s.size() - 1];
    }
}

