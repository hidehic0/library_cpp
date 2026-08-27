#define PROBLEM "https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum_fixed_root"

#include <bits/stdc++.h>
using namespace std;

#include "tree/static_top_tree.hpp"

constexpr int MOD = 998244353;

struct Mint {
  int v;
  Mint(long long x = 0) : v((x % MOD + MOD) % MOD) {}
  Mint &operator+=(const Mint &x) {
    v += x.v;
    if (v >= MOD) v -= MOD;
    return *this;
  }
  Mint &operator*=(const Mint &x) {
    v = (long long)v * x.v % MOD;
    return *this;
  }
  friend Mint operator+(Mint a, const Mint &b) { return a += b; }
  friend Mint operator*(Mint a, const Mint &b) { return a *= b; }
  friend ostream &operator<<(ostream &os, const Mint &x) { return os << x.v; }
};

struct Data {
  Mint a, b, cnt, ans;
};

using Path = pair<Data, Data>;
using Point = Data;

vector<Mint> A, B, C;
vector<int> parent, edge_id;

Data compose(const Data &l, const Data &r) {
  return {l.a * r.a,
          l.a * r.b + l.b,
          l.cnt + r.cnt,
          l.ans + l.a * r.ans + l.b * r.cnt};
}

Path vertex(int v) {
  if (parent[v] == -1) {
    Data root{1, 0, 1, A[v]};
    return {root, root};
  }

  int e = edge_id[v];
  Data up{B[e], C[e], 1, B[e] * A[v] + C[e]};
  Data down{B[e], C[e], 1, A[v]};
  return {up, down};
}

Path add_vertex(Point p, int v) {
  Path x = vertex(v);
  x.first.cnt += p.cnt;
  x.first.ans += x.first.a * p.ans + x.first.b * p.cnt;
  x.second.cnt += p.cnt;
  x.second.ans += p.ans;
  return x;
}

Path compress(Path l, Path r) {
  return {compose(l.first, r.first), compose(r.second, l.second)};
}

Point add_edge(Path p) { return p.first; }

Point rake(Point l, Point r) {
  l.cnt += r.cnt;
  l.ans += r.ans;
  return l;
}

using DP = StaticTopTreeDP<int, Point, Path, vertex, add_vertex, compress,
                           add_edge, rake>;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, Q;
  cin >> N >> Q;

  A.resize(N);
  for (auto &x : A) cin >> x.v;

  vector<vector<pair<int, int>>> G(N);
  B.resize(max(0, N - 1));
  C.resize(max(0, N - 1));
  for (int i = 0; i < N - 1; ++i) {
    int u, v;
    cin >> u >> v >> B[i].v >> C[i].v;
    G[u].emplace_back(v, i);
    G[v].emplace_back(u, i);
  }

  parent.assign(N, -1);
  edge_id.assign(N, -1);
  vector<int> child_of_edge(max(0, N - 1), -1);
  vector<int> order{0};
  for (int i = 0; i < (int)order.size(); ++i) {
    int v = order[i];
    for (auto [u, e] : G[v]) {
      if (u == parent[v]) continue;
      parent[u] = v;
      edge_id[u] = e;
      child_of_edge[e] = u;
      order.push_back(u);
    }
  }

  vector<vector<int>> tree(N);
  for (int v = 0; v < N; ++v)
    for (auto [u, _] : G[v]) tree[v].push_back(u);

  DP dp(tree, 0);
  while (Q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int w, x;
      cin >> w >> x;
      A[w] = x;
      dp.update(w);
    } else {
      int e, y, z;
      cin >> e >> y >> z;
      B[e] = y;
      C[e] = z;
      dp.update(child_of_edge[e]);
    }
    cout << dp.get().first.ans << '\n';
  }
}
