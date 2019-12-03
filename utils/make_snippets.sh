#! /bin/bash
git config --global user.name "shibh308"
git config --global user.email "s17097@tokyo.kosen-ac.jp"

git remote set-url origin https://shibh308:${GITHUB_TOKEN}@github.com/shibh308/library.git

git checkout -b master
git branch -a

cp utils/compro_library.xml utils/compro_library.xml.tmp
python3 utils/make_snippets.py

if ! diff utils/compro_library.xml utils/compro_library.xml.tmp  -q ; then
	git add utils/compro_library.xml
	git commit -m '[auto]update snippets'
	git push origin HEAD
fi
