// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/lca

#include <bits/stdc++.h>
using namespace std;

#include "../tree/lca.hpp"

#include "../templates/alias.hpp"
#include "../templates/macro.hpp"

int main() {
  ll N, Q;
  in(N, Q);
  vvi G(N);

  vi P(N - 1);
  in(P);

  rep(i, N - 1) G[P[i]].emplace_back(i + 1);

  LcaWithDoubling<ll> LCA(G);

  while (Q--) {
    ll u, v;
    in(u, v);

    out(LCA.lca(u, v));
  }
}
