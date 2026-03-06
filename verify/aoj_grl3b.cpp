#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B"

#include <bits/stdc++.h>
using namespace std;
#include "graph/lowlink.hpp"
#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M;
  in(N, M);
  VC<VC<int>> G(N);
  rep(_, M) {
    int a, b;
    in(a, b);
    G[a].emplace_back(b), G[b].emplace_back(a);
  }

  LowLink LG(G);
  sort(all(LG.bridges));

  set<pii> S;

  for (auto [a, b] : LG.bridges) {
    if (a > b)
      swap(a, b);
    S.emplace(a, b);
  }

  for (auto [a, b] : S)
    out(a, b);
}
