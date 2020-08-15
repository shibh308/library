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


# :warning: utils/include_expand.py

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#2b3583e6e17721c54496bd04e57a0c15">utils</a>
* <a href="{{ site.github.repository_url }}/blob/master/utils/include_expand.py">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#!/usr/bin/python3
import os
import sys

def expand(origin_path, lines):
    out_lines = []
    for line in lines:
        if line.startswith('#include'):
            path = (line.split('"'))
            if len(path) == 1:
                path = line.split('<')[1].split('>')[0]
            else:
                path = path[-2]
            if path.endswith('.cpp'):
                path = os.path.join(os.path.dirname(origin_path), path)
                with open(path, 'r') as f:
                    out_lines += f.readlines()
                continue
        out_lines.append(line)

    write_path = os.path.join('expand', os.path.basename(origin_path))
    with open(write_path, 'w') as f:
        for line in out_lines:
            f.write(line)
    print('expand:  {}  =>  {}'.format(origin_path, write_path))


def run():
    assert len(sys.argv) >= 2, 'a number of arguments is not match'
    pathes = sys.argv[1:]
    for path in pathes:
        with open(path, 'r') as f:
            expand(path, f.readlines())


if __name__ == '__main__':
    run()

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

