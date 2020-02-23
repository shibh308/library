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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :warning: lib/functions/calc_fact.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#abc4d0f7246596dc1cbcc6b77896a2fc">lib/functions</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/functions/calc_fact.cpp">View this file on GitHub</a>
    - Last commit date: 2019-11-30 20:08:52+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
auto calc_fact = [mpow]{
	constexpr int N = 2e6;
	vector<mint> fact(N + 1, 1);
	vector<mint> inv(N + 1, 1);
	for(int i = 1; i < N; ++i){
		fact[i + 1] = fact[i] * (i + 1);
		inv[i + 1] = mpow(fact[i + 1], MOD - 2);
	}
	return make_pair(fact, inv);
};
vector<mint> fact, inv;
tie(fact, inv) = calc_fact();


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/functions/calc_fact.cpp"
auto calc_fact = [mpow]{
	constexpr int N = 2e6;
	vector<mint> fact(N + 1, 1);
	vector<mint> inv(N + 1, 1);
	for(int i = 1; i < N; ++i){
		fact[i + 1] = fact[i] * (i + 1);
		inv[i + 1] = mpow(fact[i + 1], MOD - 2);
	}
	return make_pair(fact, inv);
};
vector<mint> fact, inv;
tie(fact, inv) = calc_fact();


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

