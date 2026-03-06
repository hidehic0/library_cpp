#pragma once
#include "templates/macro.hpp"
#include <vector>

// 参考: https://algo-logic.info/bridge-lowlink/
struct LowLink {
  std::vector<int> ord, low, parents, articulation_points;
  std::vector<std::vector<int>> G;
  std::vector<bool> used;
  std::vector<std::pair<int, int>> bridges;
  LowLink(const std::vector<std::vector<int>> &_G) : G(_G) {
    ord.resize(_G.size(), 0), low.resize(_G.size(), 0),
        used.resize(_G.size(), false), parents.resize(_G.size(), -1);
    int d = 0;
    rep(i, _G.size()) {
      if (!used[i])
        d = dfs(i, d, -1);
    }
  }

  int dfs(int cur, int d, int par = -1) {
    used[cur] = true, ord[cur] = low[cur] = d++, parents[cur] = par;
    bool is_articulation_point = false;
    int child_cnt = 0;

    for (const auto &nxt : G[cur]) {
      if (!used[nxt]) {
        child_cnt++, d = dfs(nxt, d, cur);
        chmin(low[cur], low[nxt]);
        if (par != -1 && ord[cur] <= low[nxt])
          is_articulation_point = true;
        if (ord[cur] < low[nxt])
          bridges.emplace_back(cur, nxt);
      } else if (nxt != par) {
        chmin(low[cur], ord[nxt]);
      }
    }

    if (par == -1 && child_cnt >= 2)
      is_articulation_point = true;
    if (is_articulation_point)
      articulation_points.emplace_back(cur);

    return d;
  }
};
