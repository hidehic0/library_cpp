#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

#include "tree/heavy_light_decomposition.hpp"

int main() {
  ll N, Q;
  in(N, Q);
  vi A(N);
  in(A);

  vvi G(N);

  rep(_, N - 1) {
    ll u, v;
    in(u, v);

    G[u].emplace_back(v), G[v].emplace_back(u);
  }

  HeavyLightDecomposition<ll> hld(G);

  auto e = [&]() { return 0; };
  auto op = [](ll a, ll b) { return a + b; };

  vi seg(N * 2, e());

  rep(i, N) seg[hld.in[i] + N] = A[i];
  rrep(i, 1, N) { seg[i] = op(seg[i << 1], seg[i << 1 | 1]); }

  auto prod = [&](ll l, ll r) {
    // out(l, r);
    ll res = e();

    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        res = op(res, seg[l++]);
      if (r & 1)
        res = op(res, seg[--r]);
    }
    // out(res);

    return res;
  };
  auto seg_set = [&](ll x, ll a) {
    x += N;
    seg[x] += a;

    while (x >>= 1) {
      seg[x] = op(seg[x << 1], seg[x << 1 | 1]);
    }
  };

  while (Q--) {
    ll t;
    in(t);

    if (t == 0) {
      ll p, x;
      in(p, x);

      seg_set(hld.in[p], x);
    } else {
      ll u, v;
      in(u, v);

      out(hld.query<ll>(u, v, e, prod, op));
    }
  }
}
