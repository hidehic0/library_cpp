#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <bits/stdc++.h>
using namespace std;

#include "tree/offline_lca.hpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, Q;
  cin >> N >> Q;

  vector<vector<int>> G(N);
  for (int v = 1; v < N; ++v) {
    int p;
    cin >> p;
    G[p].push_back(v);
    G[v].push_back(p);
  }

  vector<pair<int, int>> queries(Q);
  for (int i = 0; i < Q; ++i) {
    int u, v;
    cin >> u >> v;
    queries[i] = {u, v};
  }

  for (int ans : offline_lca(G, queries))
    cout << ans << '\n';
}
