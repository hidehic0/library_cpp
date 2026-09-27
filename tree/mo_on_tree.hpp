#pragma once
#include <bits/stdc++.h>

#include "tree/offline_lca.hpp"

template <std::integral T> struct MoTreeVertex {
  int width;

  std::vector<std::vector<T>> G;
  std::vector<std::pair<T, T>> ql;
  std::vector<int> order, in, vs;

  MoTreeVertex(std::vector<std::vector<T>> G, std::vector<std::pair<T, T>> ql)
      : G(G), ql(ql) {}

  void run(auto add, auto del, auto save) {
    static_assert(
        std::is_convertible_v<decltype(add), std::function<void(int)>>);
    static_assert(
        std::is_convertible_v<decltype(del), std::function<void(int)>>);
    static_assert(
        std::is_convertible_v<decltype(save), std::function<void(int)>>);

    width =
        (G.size() * 2 - 1) / std::min<int>(G.size() * 2 - 1, sqrt(ql.size()));

    order.resize(ql.size());
    std::ranges::iota(order, 0);
    in.resize(G.size());

    dfs(0);

    std::vector<std::pair<int, int>> lr;
    lr.reserve(ql.size());

    for (auto &[l, r] : ql)
      lr.emplace_back(std::minmax(in[l] + 1, in[r] + 1));

    std::ranges::sort(order, [&](int a, int b) {
      int ablock = lr[a].first / width, bblock = lr[b].first / width;

      if (ablock != bblock)
        return ablock < bblock;
      return (ablock & 1) ? lr[a].second > lr[b].second
                          : lr[a].second < lr[b].second;
    });

    int l = 0, r = 0;

    std::vector<int> flip(G.size(), 0);

    auto f = [&](int v) {
      flip[v] ^= 1;

      if (flip[v])
        add(v);
      else
        del(v);
    };

    auto lca = offline_lca(G, ql);

    for (auto &ind : order) {
      while (l > lr[ind].first)
        f(vs[--l]);
      while (r < lr[ind].second)
        f(vs[r++]);
      while (l < lr[ind].first)
        f(vs[l++]);
      while (r > lr[ind].second)
        f(vs[--r]);

      f(lca[ind]);
      save(ind);
      f(lca[ind]);
    }
  }

private:
  void dfs(int cur, int par = -1) {
    in[cur] = vs.size();
    vs.emplace_back(cur);

    for (auto &nxt : G[cur]) {
      if (nxt != par)
        dfs(nxt, cur), vs.emplace_back(nxt);
    }
  }
};
