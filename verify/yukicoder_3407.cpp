// competitive-verifier: PROBLEM https://yukicoder.me/problems/3407
#include <bits/stdc++.h>
using namespace std;
#include "templates/alias.hpp"
#include "templates/macro.hpp"

#include "tree/auxiliary_tree.hpp"

int main() {
  ll N;
  in(N);

  vi D(N, 0);

  vvi VG(N);
  vvpii G(N);

  rep(_, N - 1) {
    ll u, v, w;
    in(u, v, w);

    G[u].emplace_back(v, w), G[v].emplace_back(u, w);
    VG[u].emplace_back(v), VG[v].emplace_back(u);
  }

  AuxiliaryTree<ll> AT(VG);

  auto dfs = [&](ll cur, ll par, ll d, const auto &self) -> void {
    D[cur] = d;
    for (auto [nxt, w] : G[cur]) {
      if (nxt == par)
        continue;

      self(nxt, cur, d + w, self);
    }
  };

  dfs(0, -1, 0, dfs);
  ll Q;
  in(Q);

  vvi AG(N);

  while (Q--) {
    ll K;
    in(K);
    vi X(K);
    in(X);

    ll root = AT.build(X, AG), res = 0;

    auto dfs = [&](ll cur, const auto &self) -> void {
      for (auto nxt : AG[cur]) {
        res += D[nxt] - D[cur];

        self(nxt, self);
      }
    };

    dfs(root, dfs);

    out(res);

    for (auto x : X)
      AG[x].clear();
  }
}
