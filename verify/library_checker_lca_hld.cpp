// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/lca

#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

#include "tree/heavy_light_decomposition.hpp"

int main() {
  ll N, Q;
  in(N, Q);
  vvi G(N);

  vi P(N - 1);
  in(P);

  rep(i, N - 1) G[P[i]].emplace_back(i + 1);

  HeavyLightDecomposition<ll> hld(G);

  while (Q--) {
    ll u, v;
    in(u, v);

    out(hld.lca(u, v));
  }
}
