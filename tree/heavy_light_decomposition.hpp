#pragma once
#include <bits/stdc++.h>

template <std::integral T> struct HeavyLightDecomposition {
public:
  std::vector<std::vector<T>> G;
  T n;
  std::vector<T> size, par, in, out, head, depth, rev;

  HeavyLightDecomposition(std::vector<std::vector<T>> G, T root = 0)
      : G{G}, n(static_cast<T>(G.size())), size(n, 0), par(n, -1), in(n, 0),
        out(n, 0), head(n, root), depth(n, 0), rev(n, -1), d{0}, o{0} {

    dfs_sz(root);
    dfs_hld(root);
  }

  T lca(T u, T v) {
    assert(0 <= u && u < n && 0 <= v && v < n);

    for (;; u = par[head[u]]) {
      if (in[u] < in[v])
        std::swap(u, v);

      if (head[u] == head[v])
        return v;
    }
  }

  template <typename S>
  S query(T u, T v, const auto &e, const auto &q, const auto &op,
          bool edge = false) {
    assert(0 <= u && u < n && 0 <= v && v < n);

    static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                  "op must work as S(S, S)");
    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                  "e must work as S()");
    static_assert(std::is_convertible_v<decltype(q), std::function<S(T, T)>>,
                  "q must work as S(T, T)");

    S l = e(), r = e();

    for (;; u = par[head[u]]) {
      if (in[u] < in[v])
        std::swap(u, v), std::swap(l, r);
      if (head[u] == head[v])
        break;

      l = op(q(in[head[u]], in[u] + 1), l);
    }

    return op(op(q(in[v] + edge, in[u] + 1), l), r);
  }

private:
  T d, o;

  void dfs_sz(T cur) {
    size[cur] = 1;

    if (G[cur].size() >= 2 && G[cur][0] == par[cur])
      swap(G[cur][0], G[cur][1]);

    for (auto &nxt : G[cur]) {
      if (par[cur] == nxt)
        continue;

      par[nxt] = cur;
      dfs_sz(nxt);
      size[cur] += size[nxt];

      if (size[G[cur][0]] < size[nxt])
        swap(G[cur][0], nxt);
    }
  }

  void dfs_hld(T cur) {
    in[cur] = o++, rev[in[cur]] = cur;
    depth[cur] = d;

    for (auto nxt : G[cur]) {
      if (nxt == par[cur])
        continue;

      head[nxt] = (nxt == G[cur][0] ? head[cur] : nxt);
      ++d, dfs_hld(nxt), --d;
    }

    out[cur] = o;
  }
};

/**
 * @file tree/heavy_light_decomposition.hpp
 * @brief HeavyLightDecomposition
 * @auther hidehic0
 * @date 2026-05-31
 */
