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


# :warning: lib/functions/factoring.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#abc4d0f7246596dc1cbcc6b77896a2fc">lib/functions</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/functions/factoring.cpp">View this file on GitHub</a>
    - Last commit date: 2019-11-30 20:08:52+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
auto factoring = [](i64 x){
	int sq = sqrt(x) + 1;
	vector<int> ret;
	if(x == 1){
		ret.emplace_back(1);
		return ret;
	}
	for(i64 i = 2; i < sq; ++i)
		while(x % i == 0){
			ret.emplace_back(i);
			x /= i;
		}
	if(x != 1)
		ret.emplace_back(x);
	return ret;
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/functions/factoring.cpp"
auto factoring = [](i64 x){
	int sq = sqrt(x) + 1;
	vector<int> ret;
	if(x == 1){
		ret.emplace_back(1);
		return ret;
	}
	for(i64 i = 2; i < sq; ++i)
		while(x % i == 0){
			ret.emplace_back(i);
			x /= i;
		}
	if(x != 1)
		ret.emplace_back(x);
	return ret;
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

