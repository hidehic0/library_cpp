#define PROBLEM "https://yukicoder.me/problems/no/789"
#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

#include "segtree/dynamic-segtree.hpp"

int main() {
  ll Q;
  in(Q);

  DynamicSegtree<ll, [](ll a, ll b) { return a + b; }, []() { return 0; }> seg(
      1e9 + 10);

  ll ans = 0;

  while (Q--) {
    ll t;
    in(t);

    if (t == 0) {
      ll x, y;
      in(x, y);

      auto t = seg.get(x);

      if (!t)
        seg.set(x, y);
      else
        seg.set(x, *t + y);
    } else {
      ll l, r;
      in(l, r);

      ans += seg.prod(l, r + 1);
    }
  }

  out(ans);
}
