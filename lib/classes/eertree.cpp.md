---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://yukicoder.me/submissions/518134
  bundledCode: "#line 1 \"lib/classes/eertree.cpp\"\n// verify: https://yukicoder.me/submissions/518134\n\
    struct EerTree{\n    struct Node{\n        Node(int len) : len(len), sdep(0),\
    \ slink(nullptr){}\n        int len, sdep;\n        map<char, Node*> ch;\n   \
    \     Node* slink;\n    };\n    pair<Node*, Node*> root;\n    Node* active_point;\n\
    \    string s;\n    EerTree(){\n        root.second = new Node(0);\n        root.second->slink\
    \ = root.first = active_point = new Node(-1);\n        root.first->slink = root.first;\n\
    \    }\n    EerTree(string inp) : EerTree(){\n        for(auto c : inp)\n    \
    \        add(c);\n    }\n    Node* make(Node* par, char c){\n        if(par->ch.find(c)\
    \ == par->ch.end()){\n            par->ch[c] = new Node(par->len + 2);\n     \
    \       Node* sl = par->slink;\n            if(par->len == -1)\n             \
    \   sl = root.second;\n            else{\n                while(1){\n        \
    \            if(s[s.size() - sl->len - 2] == c){\n                        sl =\
    \ sl->ch[c];\n                        break;\n                    }else if(sl->len\
    \ < 0){\n                        sl = root.second;\n                        break;\n\
    \                    }else\n                        sl = sl->slink;\n        \
    \        }\n            }\n            par->ch[c]->slink = sl;\n            par->ch[c]->sdep\
    \ = sl->sdep + 1;\n        }\n        return par->ch[c];\n    }\n    void add(char\
    \ c){\n        for(s += c; int(s.size()) - active_point->len - 2 < 0 || s[s.size()\
    \ - active_point->len - 2] != c; active_point = active_point->slink);\n      \
    \  active_point = make(active_point, c);\n    }\n};\n"
  code: "// verify: https://yukicoder.me/submissions/518134\nstruct EerTree{\n   \
    \ struct Node{\n        Node(int len) : len(len), sdep(0), slink(nullptr){}\n\
    \        int len, sdep;\n        map<char, Node*> ch;\n        Node* slink;\n\
    \    };\n    pair<Node*, Node*> root;\n    Node* active_point;\n    string s;\n\
    \    EerTree(){\n        root.second = new Node(0);\n        root.second->slink\
    \ = root.first = active_point = new Node(-1);\n        root.first->slink = root.first;\n\
    \    }\n    EerTree(string inp) : EerTree(){\n        for(auto c : inp)\n    \
    \        add(c);\n    }\n    Node* make(Node* par, char c){\n        if(par->ch.find(c)\
    \ == par->ch.end()){\n            par->ch[c] = new Node(par->len + 2);\n     \
    \       Node* sl = par->slink;\n            if(par->len == -1)\n             \
    \   sl = root.second;\n            else{\n                while(1){\n        \
    \            if(s[s.size() - sl->len - 2] == c){\n                        sl =\
    \ sl->ch[c];\n                        break;\n                    }else if(sl->len\
    \ < 0){\n                        sl = root.second;\n                        break;\n\
    \                    }else\n                        sl = sl->slink;\n        \
    \        }\n            }\n            par->ch[c]->slink = sl;\n            par->ch[c]->sdep\
    \ = sl->sdep + 1;\n        }\n        return par->ch[c];\n    }\n    void add(char\
    \ c){\n        for(s += c; int(s.size()) - active_point->len - 2 < 0 || s[s.size()\
    \ - active_point->len - 2] != c; active_point = active_point->slink);\n      \
    \  active_point = make(active_point, c);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/eertree.cpp
  requiredBy: []
  timestamp: '2020-08-15 20:44:23+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/classes/eertree.cpp
layout: document
redirect_from:
- /library/lib/classes/eertree.cpp
- /library/lib/classes/eertree.cpp.html
title: lib/classes/eertree.cpp
---
