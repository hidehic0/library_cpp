# AGENTS.md

競プロ用のライブラリのrepoです

## verify/以下にコードを書くときの規則

c++で書いて指示されたライブラリを用いて書いてください

```c++
#define PROBLEM "問題のURL"
```
を書いてください

なおincludeのパスはライブラリが例えば、string/aho-corasick.hppといった場合は
```c++
#include "string/aho-corasick.hpp"
```
のように書いてください

### コードのテスト

コンパイルコマンドは
```
g++ [filename] -I[repoのroot] -Wall
```
としてください

サンプルも実行してください

またコンパイルが通らない場合は、原因を特定して、その内容を出力してください
