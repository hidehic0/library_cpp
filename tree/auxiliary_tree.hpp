#pragma once
#include <bits/stdc++.h>

#include "tree/lca.hpp"

template <std::integral T> struct AuxiliaryTree {
  LcaWithDoubling<T> lca;
  std::vector<int> order;
  int n;

  AuxiliaryTree(std::vector<std::vector<T>> G) : lca{G} {
    n = G.size();
    order.resize(n);

    int cnt = 0;
    auto dfs = [&](int cur, int par, const auto &self) -> void {
      order[cur] = cnt++;
      for (auto nxt : G[cur]) {
        if (nxt == par)
          continue;
        self(nxt, cur, self);
      }
    };

    dfs(0, -1, dfs);
  }

  /**
   * @fn build
   * @brief AuxiliaryTreeを構築します
   * @param V 頂点のリスト 後で補助に使われた頂点も追加される
   */
  T build(std::vector<T> &V, std::vector<std::vector<T>> &G) {
    int m = V.size();

    assert(n == G.size());
    assert(m > 0);

    std::ranges::sort(V, [&](int a, int b) { return order[a] < order[b]; });
    std::vector<T> st = {V[0]};

    for (int i = 0; i < m - 1; i++) {
      T w = lca.lca(V[i], V[i + 1]);

      if (w != V[i]) {
        T last = st.back();
        st.pop_back();
        while (!st.empty() && lca.D[w] < lca.D[st.back()]) {
          int tp = st.back();
          st.pop_back();
          G[tp].emplace_back(last);
          last = tp;
        }
        if (st.empty() || st.back() != w) {
          st.emplace_back(w), V.emplace_back(w);
          G[w] = {last};
        } else {
          G[w].emplace_back(last);
        }
      }

      st.emplace_back(V[i + 1]);
    }

    for (int i = 0; i < st.size() - 1; i++) {
      G[st[i]].emplace_back(st[i + 1]);
    }

    return st[0];
  }
};

/**
 * @file tree/auxiliary_tree.hpp
 * @brief AuxiliaryTree
 * @auther hidehic0
 * @date 2026-05-29
 * verify: https://atcoder.jp/contests/abc340/submissions/76203724
 */
