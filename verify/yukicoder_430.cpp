// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/430

#include <bits/stdc++.h>
using namespace std;
#include "templates/alias.hpp"
#include "templates/macro.hpp"

#include "string/aho-corasick.hpp"

int main() {
  string S;
  ll N;
  in(S, N);

  AhoCorasick<26, 'A'> AH;

  rep(i, N) {
    string T;
    in(T);

    AH.add(T, i);
  }
  AH.build();

  cout << AH.move(S, 0).first << "\n";
}
