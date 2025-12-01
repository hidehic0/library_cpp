#pragma once
#include <cassert>
#include <functional>
#include <type_traits>

template <class S, auto op, auto e> struct DualSegmentTree {
  static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                "op must work as S(S, S)");
  static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                "e must work as S()");

  int _n, size = 0;
  std::vector<S> data;

  DualSegmentTree(int n) {
    _n = n;
    int tmp = n - 1;

    while (tmp) {
      size++;
      tmp >>= 1;
    }

    size = 1 << size;

    data = std::vector(size * 2, e());
  }

  void apply(int l, int r, S x) {
    assert(0 <= l && l <= r && r <= _n);
    l += size;
    r += size;

    while (l < r) {
      if (l & 1) {
        data[l] = op(data[l], x);
        l++;
      }

      if (r & 1)
        data[r - 1] = op(data[r - 1], x);

      l >>= 1;
      r >>= 1;
    }
  }

  S get(int p) {
    assert(0 <= p && p < _n);
    S res = e();
    p += size;

    while (p) {
      res = op(res, data[p]);
      p >>= 1;
    }

    return res;
  }
};
