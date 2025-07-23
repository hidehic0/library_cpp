#pragma once
#include <algorithm>
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
    auto bis = s.lower_bound(std::make_pair(x + 1, x + 1));
    auto it = std::prev(bis);

    auto [l, r] = *it;
    auto [nl, nr] = *it;

    int al = x, ar = x;

    if (l <= x && x <= r) {
      return false;
    }

    if (r == x - 1) {
      al = l;

      if (nl == x + 1) {
        s.erase(it);
        s.erase(bis);
        ar = nr;
      } else {
        s.erase(it);
      }
    } else {
      if (nl == x + 1) {
        ar = nr;
        s.erase(bis);
      }
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
