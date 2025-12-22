#pragma once
#include <cassert>
#include <climits>
#include <iterator>
#include <set>
#include <utility>
#include <vector>

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

  void insert_range(int l, int r) {
    assert(l <= r);
    auto it = prev(s.lower_bound(std::make_pair(l + 1, l + 1)));
    if (it->second)
      it++;

    // 重複要素を消す
    int nl = l, nr = r;
    std::vector<std::pair<int, int>> T;

    while (it->first <= r) {
      int tl, tr;
      std::tie(tl, tr) = *it;

      if (tl <= l) {
        nl = tl;
      }
      if (tr >= r)
        nr = tr;

      T.emplace_back(*it);
      it++;
    }

    for (auto [tl, tr] : T)
      s.erase(std::make_pair(tl, tr));

    s.emplace(nl, nr);

    // 隣接要素を削除
    it = s.lower_bound(std::make_pair(nl, nl));

    if (prev(it)->second + 1 == nl) {
      int tmp = nl;
      nl = prev(it)->first;
      s.erase(*prev(it));
      s.erase(std::make_pair(tmp, nr));
      s.emplace(nl, nr);
    }

    it = s.lower_bound(std::make_pair(nl, nl));

    if (nr + 1 == next(it)->first) {
      int tmp = nr;
      nr = next(it)->second;
      s.erase(*next(it));
      s.erase(std::make_pair(nl, tmp));
      s.emplace(nl, nr);
    }
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
