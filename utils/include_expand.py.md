---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: py
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 85, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "#!/usr/bin/python3\nimport os\nimport sys\n\ndef expand(origin_path, lines):\n\
    \    out_lines = []\n    for line in lines:\n        if line.startswith('#include'):\n\
    \            path = (line.split('\"'))\n            if len(path) == 1:\n     \
    \           path = line.split('<')[1].split('>')[0]\n            else:\n     \
    \           path = path[-2]\n            if path.endswith('.cpp'):\n         \
    \       path = os.path.join(os.path.dirname(origin_path), path)\n            \
    \    with open(path, 'r') as f:\n                    out_lines += f.readlines()\n\
    \                continue\n        out_lines.append(line)\n\n    write_path =\
    \ os.path.join('expand', os.path.basename(origin_path))\n    with open(write_path,\
    \ 'w') as f:\n        for line in out_lines:\n            f.write(line)\n    print('expand:\
    \  {}  =>  {}'.format(origin_path, write_path))\n\n\ndef run():\n    assert len(sys.argv)\
    \ >= 2, 'a number of arguments is not match'\n    pathes = sys.argv[1:]\n    for\
    \ path in pathes:\n        with open(path, 'r') as f:\n            expand(path,\
    \ f.readlines())\n\n\nif __name__ == '__main__':\n    run()\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/include_expand.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/include_expand.py
layout: document
redirect_from:
- /library/utils/include_expand.py
- /library/utils/include_expand.py.html
title: utils/include_expand.py
---
