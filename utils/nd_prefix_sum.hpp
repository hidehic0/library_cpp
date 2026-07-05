#pragma once
#include <bits/stdc++.h>

template <class S, auto op, auto minus, auto e> struct NdPrefixSum {
  static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                "op must work as S(S, S)");
  static_assert(std::is_convertible_v<decltype(minus), std::function<S(S)>>,
                "minus must work as S(S)");
  static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                "e must work as S()");

  std::vector<S> data;
  bool built;
  std::vector<int> X;
  int _n, _m;

  NdPrefixSum(const std::vector<int> &X)
      : X(X), built(false), _n(1), _m(X.size()) {
    for (int x : X) {
      assert(0 <= x);
      _n *= x + 1;
    }

    data.resize(_n, e());
  }

  inline void add(const std::vector<int> &Y, const S &v) {
    assert(!built);
    assert(Y.size() == _m);

    int cur = 0;

    for (auto [i, x] : Y | std::views::enumerate) {
      assert(x < X[i]);
      cur *= X[i] + 1;
      cur += x + 1;
    }

    data[cur] = op(data[cur], v);
  }

  inline void build() {
    assert(!built);

    built = true;

    int div = 1;

    for (int k = 0; k < _m; k++) {
      for (int i = 0; i < _n; i++) {
        if ((i / div) % (X[k] + 1) < X[k])
          data[i + div] = op(data[i + div], data[i]);
      }

      div *= X[k] + 1;
    }
  }

  inline S prod(const std::vector<int> &L, const std::vector<int> &R) {
    assert(built);
    assert(L.size() == R.size() && R.size() == _m);

    for (int i = 0; i < _m; i++) {
      if (!(0 <= L[i] && L[i] <= R[i] && R[i] <= X[i]))
        return e();
    }

    S res = e();

    for (int bit = 0; bit < 1 << _m; bit++) {
      int cur = 0;

      for (int k = 0; k < _m; k++)
        cur *= X[k] + 1, cur += ((bit >> k) & 1 ? L[k] : R[k]);

      res = op(res,
               std::popcount(uint32_t(bit)) & 1 ? minus(data[cur]) : data[cur]);
    }

    return res;
  }
};
