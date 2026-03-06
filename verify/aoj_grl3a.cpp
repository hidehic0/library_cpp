#define PROBLEM                                                                \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A"

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
  sort(all(LG.articulation_points));
  rep(i, LG.articulation_points.size()) out(LG.articulation_points[i]);
}
