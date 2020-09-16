#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/stringutils.cpp"


signed main() {
	string s;
	cin >> s;
	StringUtils st(s);
	int n = s.size();
	for(int i = 0; i < n; ++i)
		cout << st.sa[i + 1] << " \n"[i == n - 1];
}
