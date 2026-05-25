#pragma once

#include <bits/stdc++.h>

#include "templates/alias.hpp"
#include "templates/macro.hpp"

template <std::integral T> struct LcaWithDoubling {
  VC<VC<T>> G, P;
  VC<T> D;
  T N, K;

  LcaWithDoubling(VC<VC<T>> G, T st = 0) : G{G}, N{G.size()} {
    assert(N > 0);
    assert(st < N);

    K = std::bit_width((unsigned)N);
    P.resize(K, VC<T>(N, -1));
    D.resize(N);

    auto dfs = [&](const auto &self, T cur, T par, T d) -> void {
      P[0][cur] = par;
      D[cur] = d;

      for (auto nxt : G[cur]) {
        if (nxt == par)
          continue;

        self(self, nxt, cur, d + 1);
      }
    };

    dfs(dfs, st, st, 0);

    rep(b, K - 1) rep(i, N) P[b + 1][i] = P[b][P[b][i]];
  }

  T lca(T u, T v) {
    if (D[u] < D[v])
      std::swap(u, v);

    rep(k, K) {
      if ((D[u] - D[v]) >> k & 1) {
        u = P[k][u];
      }
    }

    if (u == v) {
      return u;
    }

    rrep(k, K) {
      if (P[k][u] != P[k][v]) {
        u = P[k][u], v = P[k][v];
      }
    }

    return P[0][u];
  }
};
