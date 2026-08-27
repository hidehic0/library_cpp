#pragma once
#include <bits/stdc++.h>

enum Type { Vertex, AddVertex, Compress, AddEdge, Rake };

template <std::integral Tp> struct StaticTopTree {
  std::vector<int> P, L, R; // parent, left child, right child
  std::vector<Type> T;      // segment type
  std::vector<std::vector<int>> G;
  std::vector<int> S;
  int tree_root, root;

  StaticTopTree(std::vector<std::vector<Tp>> _G, int _root = 0)
      : tree_root{_root} {
    int _n = _G.size();
    T.resize(_n), P.resize(_n, -1), L.resize(_n, -1), R.resize(_n, -1),
        G.resize(_n), S.resize(_n);

    hl_dfs(_G, tree_root);
    root = build();
  }

private:
  void hl_dfs(const std::vector<std::vector<Tp>> &_G, int cur, int par = -1) {
    int &sz = S[cur];
    sz++;

    for (auto nxt : _G[cur]) {
      if (nxt == par)
        continue;

      hl_dfs(_G, nxt, cur);
      G[cur].emplace_back(nxt);
      sz += S[nxt];

      if (S[G[cur][0]] < S[nxt])
        std::swap(G[cur][0], G[cur].back());
    }
  }

  int build() { return compress(tree_root).first; }

  int add(int p, int l, int r, Type t) {
    if (p == -1) {
      p = P.size();
      P.emplace_back(-1), L.emplace_back(-1), R.emplace_back(-1),
          T.emplace_back();
    }

    T[p] = t, L[p] = l, R[p] = r;

    if (l != -1)
      P[l] = p;
    if (r != -1)
      P[r] = p;

    return p;
  }
  std::pair<int, int> merge(const std::vector<std::pair<int, int>> &vl,
                            Type t) {
    if (vl.size() == 1)
      return vl[0];

    int sz = 0;
    for (auto [_, s] : vl)
      sz += s;

    std::vector<std::pair<int, int>> al, bl;

    for (auto [u, s] : vl)
      (s < sz ? al : bl).emplace_back(u, s), sz -= s * 2;

    auto [a, sa] = merge(al, t);
    auto [b, sb] = merge(bl, t);

    return {add(-1, a, b, t), sa + sb};
  }

  std::pair<int, int> add_edge(int cur) {
    auto [a, s] = compress(cur);

    return {add(-1, a, -1, Type::AddEdge), s};
  }

  std::pair<int, int> rake(int cur) {
    std::vector<std::pair<int, int>> cl;

    for (auto nxt : G[cur] | std::views::drop(1))
      cl.emplace_back(add_edge(nxt));

    return (cl.empty() ? std::make_pair(-1, 0) : merge(cl, Type::Rake));
  }

  std::pair<int, int> compress(int cur) {
    std::vector<std::pair<int, int>> hp;

    hp.emplace_back(add_vertex(cur));

    while (!G[cur].empty())
      hp.emplace_back(add_vertex(cur = G[cur][0]));

    return merge(hp, Type::Compress);
  }

  std::pair<int, int> add_vertex(int cur) {
    auto [i, s] = rake(cur);

    return {add(cur, i, -1, i == -1 ? Type::Vertex : Type::AddVertex), s + 1};
  }
};

template <std::integral Tp, class Point, class Path, auto vertex,
          auto add_vertex, auto compress, auto add_edge, auto rake>
struct StaticTopTreeDP {
  static_assert(
      std::is_convertible_v<decltype(vertex), std::function<Path(Tp)>>,
      "vertex must work as Path(Tp)");
  static_assert(std::is_convertible_v<decltype(add_vertex),
                                      std::function<Path(Point, Tp)>>,
                "add_vertex must work as Path(Point, Tp)");
  static_assert(std::is_convertible_v<decltype(compress),
                                      std::function<Path(Path, Path)>>,
                "compress must work as Path(Path, Path)");
  static_assert(
      std::is_convertible_v<decltype(add_edge), std::function<Point(Path)>>,
      "add_edge must work as Point(Path)");
  static_assert(
      std::is_convertible_v<decltype(rake), std::function<Point(Point, Point)>>,
      "rake must work as Point(Point, Point)");

  StaticTopTree<Tp> stt;

  std::vector<Path> Pa;
  std::vector<Point> Po;

  StaticTopTreeDP(std::vector<std::vector<Tp>> G, int root = 0) : stt{G, root} {
    Pa.resize(stt.P.size()), Po.resize(stt.P.size());

    for (int i = 0; i < G.size(); i++)
      update(i);
  }

  void update(Tp u) {
    const auto &T = stt.T, &L = stt.L, &R = stt.R, &P = stt.P;

    if (Type::Vertex == T[u]) {
      Pa[u] = vertex(u);
    } else if (Type::AddVertex == T[u]) {
      Pa[u] = add_vertex(Po[L[u]], u);
    } else if (Type::Compress == T[u]) {
      Pa[u] = compress(Pa[L[u]], Pa[R[u]]);
    } else if (Type::AddEdge == T[u]) {
      Po[u] = add_edge(Pa[L[u]]);
    } else if (Type::Rake == T[u]) {
      Po[u] = rake(Po[L[u]], Po[R[u]]);
    }

    if (P[u] != -1)
      update(P[u]);
  }

  Path get() { return Pa[stt.root]; }
};
