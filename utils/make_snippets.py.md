---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: py
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://shibh308.github.io/library/library/{}.html\n'.format(load_path)
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 70, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 84, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "import os\nimport glob\nfrom xml.sax.saxutils import escape\nfrom jinja2\
    \ import Environment\n\nsave_path = os.path.join(os.path.dirname(__file__), \"\
    compro_library.xml\")\ntemplate = '  <template name=\"{{ name }}\" value=\"{{\
    \ code }}\" discription=\"\" toReformat=\"false\" toShortenFQNames=\"true\">\\\
    n    <context>\\n      <option name=\"cpp\" value=\"true\" />\\n    </context>\\\
    n  </template>\\n\\n'\n\n\ndef create():\n    dics = []\n    pathes = sorted(glob.glob(\"\
    lib/functions/*.cpp\")) + sorted(glob.glob(\"lib/classes/*.cpp\")) + sorted(glob.glob(\"\
    lib/*.cpp\"))\n    for load_path in pathes:\n        with open(load_path, 'r')\
    \ as f:\n            name = os.path.splitext(load_path.split('/')[-1])[0]\n  \
    \          s = '// doc: https://shibh308.github.io/library/library/{}.html\\n'.format(load_path)\
    \ + f.read()\n            dics.append({\"name\": escape(name), \"code\": escape(s).replace('\\\
    n', '&#10;').replace('\"', '&quot;')})\n    \n    with open(save_path, 'w') as\
    \ f:\n        f.write('<templateSet group=\"compro_library\">\\n')\n        for\
    \ dic in dics:\n            f.write(Environment().from_string(template).render(**dic))\n\
    \        f.write('</templateSet>')\n\n\nif __name__ == '__main__':\n    create()\n"
  dependsOn: []
  isVerificationFile: false
  path: utils/make_snippets.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utils/make_snippets.py
layout: document
redirect_from:
- /library/utils/make_snippets.py
- /library/utils/make_snippets.py.html
title: utils/make_snippets.py
---
