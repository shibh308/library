# library
競技プログラミング用の自作ライブラリ群
  
[![GitHub Pages](https://img.shields.io/static/v1?label=GitHub+Pages&message=+&color=brightgreen&logo=github)](https://shibh308.github.io/library/)
[![Actions Status](https://github.com/shibh308/library/workflows/verify/badge.svg)](https://github.com/shibh308/library/actions)

<br><br>  
## 機能について
* ライブラリの自動verify ([online-judge-verify-helper](https://github.com/kmyk/online-judge-verify-helper)を使っています)
  * cppファイルが変更されてpushされるのに合わせて走らせています
  * verify用のコードはhttps://github.com/shibh308/library/tree/master/verify 以下にあります

* clion用のxmlファイルの自動生成
  * 上と同様、cppの変更に合わせて再生成して、内容が変わってたら自動pushさせています
  * [変換するスクリプト](https://github.com/shibh308/library/blob/master/utils/make_snippets.py)
