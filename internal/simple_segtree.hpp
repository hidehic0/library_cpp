#pragma once
#include <bits/stdc++.h>

namespace hidehic0_internal {
template <typename S, auto op, auto e> struct SimpleSegtree {
  static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                "op must work as S(S, S)");
  static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                "e must work as S()");

  int n;
  std::vector<S> data;

  SimpleSegtree() = default;
  SimpleSegtree(int n) : n(n), data(n * 2, e()) {}
  SimpleSegtree(const std::vector<S> &v) : n(v.size()), data(n * 2, e()) {
    for (int i = 0; i < n; i++)
      set(i, v[i]);
  }

  inline S get(int p) { return data[p + n]; }

  void set(int p, S x) {
    p += n;
    data[p] = x;

    while (p >>= 1) {
      data[p] = op(data[p << 1], data[p << 1 | 1]);
    }
  }

  S prod(int l, int r) {
    S left = e(), right = e();
    l += n, r += n;

    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        left = op(left, data[l++]);
      if (r & 1)
        right = op(data[--r], right);
    }

    return op(left, right);
  }
};
} // namespace hidehic0_internal
