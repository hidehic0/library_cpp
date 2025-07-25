#pragma once
#include <climits>
#include <iterator>
#include <set>
#include <utility>

struct RangeSet {
private:
  std::set<std::pair<int, int>> s;

public:
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

  int mex(int x = 0) {
    auto [l, r] = *std::prev(s.lower_bound(std::make_pair(x + 1, x + 1)));

    if (l <= x && x <= r) {
      return r + 1;
    } else {
      return x;
    }
  }
};
