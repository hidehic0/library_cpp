#pragma once
#include <algorithm>
#include <stack>
#include <vector>

template <class T>
std::vector<T> rerooting(std::vector<std::vector<int>> G, T (*merge)(T, T),
                         T (*add_root)(T, int), T e) {
  int n = G.size();
  std::vector<T> down(n, e), up(n, e), res(n, e);

  // 順序を決定
  std::vector<int> parent(n, -1), order;
  std::vector<bool> used(n, false);
  std::stack<int> ST;
  used[0] = true;
  ST.emplace(0);

  while (!ST.empty()) {
    int cur = ST.top();
    ST.pop();
    order.emplace_back(cur);

    for (const int &nxt : G[cur]) {
      if (used[nxt])
        continue;

      used[nxt] = true;
      parent[nxt] = cur;
      ST.emplace(nxt);
    }
  }

  // 0を根とした木dp
  for (int i = n - 1; i >= 1; i--) {
    int cur = order[i];
    down[cur] = add_root(down[cur], cur);
    down[parent[cur]] = merge(down[parent[cur]], down[cur]);
  }
  down[0] = add_root(down[0], 0);

  // 全方位部分
  for (const int &cur : order) {
    int deg = G[cur].size();
    std::vector<T> dp_r(deg + 1, e);

    for (int i = deg - 1; i >= 0; i--) {
      int nxt = G[cur][i];
      dp_r[i] = merge(dp_r[i + 1], nxt == parent[cur] ? up[cur] : down[nxt]);
    }

    T l_cur = e;

    for (int i = 0; i < deg; i++) {
      int nxt = G[cur][i];
      up[nxt] = add_root(merge(l_cur, dp_r[i + 1]), cur);

      l_cur = merge(l_cur, nxt == parent[cur] ? up[cur] : down[nxt]);
    }
    res[cur] = add_root(l_cur, cur);
  }

  return res;
}
