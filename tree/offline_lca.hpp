#pragma once
#include <bits/stdc++.h>

#include "data-structure/unionfind.hpp"

// 参考: https://tjkendev.github.io/procon-library/python/graph/lca-tarjan.html
// 参考: https://ei1333.github.io/library/graph/tree/offline-lca.hpp
template <std::integral T>
std::vector<T> offline_lca(const std::vector<std::vector<T>> &G,
                           const std::vector<std::pair<T, T>> &ql,
                           int root = 0) {

  std::vector<std::vector<std::pair<int, int>>> queries(G.size());
  std::vector<T> res(ql.size(), -1);

  for (auto [i, ab] : ql | std::views::enumerate) {
    auto [a, b] = ab;

    if (a == b) {
      res[i] = a;
      continue;
    }

    queries[a].emplace_back(b, i), queries[b].emplace_back(a, i);
  }

  UnionFind UF(G.size());

  std::stack<int> S;
  S.emplace(root);

  std::vector<int> it(G.size());
  for (int i = 0; i < static_cast<int>(G.size()); i++)
    it[i] = G[i].size();

  std::vector<int> anc(G.size(), -1);

  while (!S.empty()) {
    int cur = S.top();

    if (anc[cur] == -1)
      anc[cur] = cur;
    else
      UF.merge(cur, G[cur][it[cur]]), anc[UF.leader(cur)] = cur;

    bool flag = false;

    while (it[cur]) {
      it[cur]--;

      int nxt = G[cur][it[cur]];

      if (anc[nxt] == -1) { // nxtが未訪問ならnxtに行く
        S.emplace(nxt);
        flag = true;
        break;
      }
    }

    if (!flag) { // curから繋がるところがすべて訪問済みなら、クエリを処理する
      for (auto &&[v, ind] : queries[cur]) {
        if (anc[v] != -1 && res[ind] == -1)
          res[ind] = anc[UF.leader(v)];
      }

      S.pop();
    }
  }

  return res;
}
