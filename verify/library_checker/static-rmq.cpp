// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/staticrmq
#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

#include "data-structure/disjoint-sparsetable.hpp"

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);

  int N, Q;
  in(N, Q);
  VC<int> A(N);
  in(A);

  DisjointSparseTable<int, [](int a, int b) { return min(a, b); }> dst(A);

  while (Q--) {
    int l, r;
    in(l, r);

    out(dst.prod(l, r));
  }
}
