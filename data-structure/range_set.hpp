#pragma once
#include "templates/alias.hpp"
#include "templates/macro.hpp"
#include <cassert>
#include <climits>
#include <iterator>
#include <set>
#include <utility>

struct RangeSet {
  std::set<std::pair<int, int>> s;

  RangeSet() {
    s.emplace(INT_MIN, INT_MIN);
    s.emplace(INT_MAX, INT_MAX);
  }

  bool insert(int x) {
    auto it = s.lower_bound({x + 1, x + 1});
    auto prev_it = std::prev(it);

    auto [l, r] = *prev_it;
    auto [nl, nr] = *it;

    if (l <= x && x <= r) {
      return false;
    }

    int al = x, ar = x;

    if (r == x - 1) {
      al = l;
      s.erase(prev_it);
    }

    if (nl == x + 1) {
      ar = nr;
      s.erase(it);
    }

    s.emplace(al, ar);
    return true;
  }

  // verify: https://atcoder.jp/contests/abc435/submissions/74579141
  void insert_range(int l, int r) {
    assert(l <= r);
    auto it = std::prev(s.lower_bound({l, l}));

    if (it->second < l) {
      it++;
    }

    auto nit = it;

    VC<pii> D;
    ll nl = l, nr = r;

    while (nit != s.end() && nit->first <= r) {
      D.emplace_back(*nit);
      chmin(nl, (ll)nit->first), chmax(nr, (ll)nit->second);

      nit++;
    }

    for (auto [dl, dr] : D)
      s.erase({dl, dr});

    s.emplace(nl, nr);
  }

  void erase(int x) {
    auto it = std::prev(s.lower_bound({x + 1, x + 1}));
    auto [l, r] = *it;

    s.erase(it);
    if (l == x && r == x) {
      return;
    }

    if (l == x) {
      s.emplace(x + 1, r);
    } else if (r == x) {
      s.emplace(l, x - 1);
    } else {
      s.emplace(l, x - 1);
      s.emplace(x + 1, r);
    }
  }

  int mex(int x = 0) {
    auto [l, r] = *std::prev(s.lower_bound(std::make_pair(x + 1, x + 1)));

    if (l <= x && x <= r) {
      return r + 1;
    } else {
      return x;
    }
  }
};
