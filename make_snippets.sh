#! /bin/bash
git config --global user.name "shibh308"
git config --global user.email "s17097@tokyo.kosen-ac.jp"

git remote set-url origin https://shibh308:${GITHUB_TOKEN}@github.com/shibh308/library.git

git checkout -b master
git branch -a

python3 make_snippets.py

if ! diff $1 $2 -q >/dev/null ; then
	git add compro_library.xml
	git commit -m '[auto]update snippets'
	git push origin HEAD
fi
