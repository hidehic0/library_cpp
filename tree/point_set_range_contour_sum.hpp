#pragma once
#include "internal/simple_segtree.hpp"
#include <bits/stdc++.h>

template <typename S, auto op, auto e, std::integral T>
struct PointSetRangeContourSum {
  static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                "op must work as S(S, S)");
  static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                "e must work as S()");

  using SegTree = hidehic0_internal::SimpleSegtree<S, op, e>;

  struct Node {
    SegTree seg;
    std::vector<int> sep, depth;

    Node() = default;
    Node(const std::vector<int> &roots, int ind, const std::vector<S> &D,
         const std::vector<std::vector<T>> &G, const std::vector<bool> &used,
         std::vector<std::vector<std::pair<int, int>>> &info) {
      std::deque<std::tuple<int, int, int>> dq; // current,parrent,depth
      std::vector<S> data;

      for (auto u : roots) {
        dq.emplace_back(u, -1, 0);
      }

      int cnt = 0, cd = 0;

      while (!dq.empty()) {
        auto [cur, par, d] = dq.front();
        dq.pop_front();

        data.emplace_back(D[cur]);
        info[cur].emplace_back(ind, cnt);
        depth.emplace_back(d);

        if (d == cd)
          sep.emplace_back(cnt), cd++;

        cnt++;

        for (auto nxt : G[cur]) {
          if (nxt == par || used[nxt])
            continue;

          dq.emplace_back(nxt, cur, d + 1);
        }
      }

      sep.emplace_back(cnt);
      seg = SegTree(data);
    }

    S prod(int dl, int du) {
      dl = std::max(dl, 0);
      du = std::min<int>(du, sep.size() - 1);

      return (dl < du ? seg.prod(sep[dl], sep[du]) : e());
    }
  };

  int n;
  std::vector<std::vector<T>> G;
  std::vector<bool> used;
  std::vector<std::vector<std::pair<int, int>>> info;
  std::vector<Node> nodes;
  std::vector<int> L, R, P, sub_size;
  std::vector<std::vector<int>> ch;
  std::vector<S> dat;

  PointSetRangeContourSum(std::vector<std::vector<T>> G, std::vector<S> D)
      : n(G.size()), G(G), used(n, false), info(n), sub_size(n, 0), L(n, -1),
        R(n, -1), P(n, -1), nodes(n), ch(n), dat(D) {

    auto rec = [&](const auto &rec, int r, int sz) -> int {
      int c = -1;

      auto get_centroid = [&](const auto &get_centroid, int cur,
                              int par) -> void {
        sub_size[cur] = 1;

        for (auto nxt : G[cur]) {
          if (nxt == par || used[nxt])
            continue;

          get_centroid(get_centroid, nxt, cur);

          if (nxt == c) {
            sub_size[cur] = sz - sub_size[nxt];
            break;
          }

          sub_size[cur] += sub_size[nxt];
        }

        if (c < 0 && sub_size[cur] * 2 > sz)
          c = cur;
      };

      get_centroid(get_centroid, r, -1);

      used[c] = true;

      auto cmp = [&](int a, int b) { return sub_size[a] > sub_size[b]; };

      std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);

      for (auto v : G[c]) {
        if (used[v])
          continue;

        int tmp = v;
        int tmp_sz = sub_size[v];

        v = rec(rec, tmp, tmp_sz);

        ch[v] = {tmp};
        sub_size[tmp] = tmp_sz;

        pq.emplace(v);
      }

      while (pq.size() >= 2) {
        auto u = pq.top();
        pq.pop();
        auto v = pq.top();
        pq.pop();

        if (pq.empty()) {
          P[u] = P[v] = c;
          L[c] = u;
          R[c] = v;

          nodes[u] = Node{ch[u], u, D, G, used, info};
          nodes[v] = Node{ch[v], v, D, G, used, info};

          break;
        }

        const int ind = nodes.size();
        sub_size.emplace_back(sub_size[u] + sub_size[v]);
        L.emplace_back(u), R.emplace_back(v), P.emplace_back(-1);
        ch.emplace_back();
        nodes[u] = Node{ch[u], u, D, G, used, info};
        nodes[v] = Node{ch[v], v, D, G, used, info};

        P[u] = P[v] = ind;

        if (ch[u].size() > ch[v].size())
          swap(u, v);

        for (auto k : ch[u])
          ch[v].emplace_back(k);

        swap(ch[v], ch[ind]);

        ch[u].clear(), ch[v].clear();

        nodes.emplace_back();
        pq.emplace(ind);
      }

      if (!pq.empty()) {
        int u = pq.top();
        P[u] = c;
        L[c] = u;

        nodes[u] = {ch[u], u, D, G, used, info};
      }

      used[c] = false;
      return c;
    };

    rec(rec, 0, n);
  }

  inline S get(int p) { return dat[p]; }

  void set(int p, S x) {
    dat[p] = x;

    for (auto [v, pt] : info[p])
      nodes[v].seg.set(pt, x);
  }

  //! [dl, du)
  S prod(int u, int dl, int du) {
    S res = dl <= 0 && 0 < du ? dat[u] : e();

    if (L[u] != -1)
      res = op(res, nodes[L[u]].prod(dl - 1, du - 1));
    if (R[u] != -1)
      res = op(res, nodes[R[u]].prod(dl - 1, du - 1));

    int v = P[u];

    for (auto [p, ind] : info[u]) {
      int ql = dl - nodes[p].depth[ind] - 2, qu = du - nodes[p].depth[ind] - 2;

      if (v < n and ql <= -1 and -1 < qu)
        res = op(res, dat[v]);

      if (L[v] == p && R[v] != -1)
        res = op(res, nodes[R[v]].prod(ql, qu));
      if (R[v] == p)
        res = op(res, nodes[L[v]].prod(ql, qu));

      v = P[v];
    }

    return res;
  }
};

/*!
 * @file tree/point_set_range_contour_sum.hpp
 * @brief PointSetRangeContourSum
 * @author hidehic0
 * @date 2026-06-23
 */
