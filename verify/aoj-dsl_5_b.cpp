#define PROBLEM                                                                \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_5_B"

#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

#include "data-structure/2d-segtree.hpp"

int main() {
  ll N;
  in(N);

  SegmentTree2D<ll, [](ll a, ll b) { return a + b; }, []() { return 0; }> seg(
      vvi(1003, vi(1003)));

  rep(_, N) {
    ll x1, x2, y1, y2;
    in(x1, y1, x2, y2);

    seg.set(x1, y1, seg.get(x1, y1) + 1);
    seg.set(x2, y2, seg.get(x2, y2) + 1);
    seg.set(x1, y2, seg.get(x1, y2) - 1);
    seg.set(x2, y1, seg.get(x2, y1) - 1);
  }

  ll ans = 0;

  rep(i, 1000) rep(k, 1000) chmax(ans, seg.prod(0, i + 1, 0, k + 1));

  out(ans);
}
