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


# :warning: utils/make_snippets.py

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#2b3583e6e17721c54496bd04e57a0c15">utils</a>
* <a href="{{ site.github.repository_url }}/blob/master/utils/make_snippets.py">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
import os
import glob
from xml.sax.saxutils import escape
from jinja2 import Environment

save_path = os.path.join(os.path.dirname(__file__), "compro_library.xml")
template = '  <template name="{{ name }}" value="{{ code }}" discription="" toReformat="false" toShortenFQNames="true">\n    <context>\n      <option name="cpp" value="true" />\n    </context>\n  </template>\n\n'


def create():
    dics = []
    pathes = sorted(glob.glob("lib/functions/*.cpp")) + sorted(glob.glob("lib/classes/*.cpp")) + sorted(glob.glob("lib/*.cpp"))
    for load_path in pathes:
        with open(load_path, 'r') as f:
            name = os.path.splitext(load_path.split('/')[-1])[0]
            s = '// doc: https://shibh308.github.io/library/library/{}.html\n'.format(load_path) + f.read()
            dics.append({"name": escape(name), "code": escape(s).replace('\n', '&#10;').replace('"', '&quot;')})
    
    with open(save_path, 'w') as f:
        f.write('<templateSet group="compro_library">\n')
        for dic in dics:
            f.write(Environment().from_string(template).render(**dic))
        f.write('</templateSet>')


if __name__ == '__main__':
    create()

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 349, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/python.py", line 84, in bundle
    raise NotImplementedError
NotImplementedError

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

