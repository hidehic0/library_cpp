#pragma once
#include "templates/macro.hpp"
#include <cassert>
#include <vector>

template <class T> std::vector<T> factorial_list(int N) {
  std::vector<T> P(N + 1, 1);
  for (int i = 1; i <= N; i++) {
    P[i] = P[i - 1] * T{i};
  }

  return P;
}

template <class T> struct Fact {
  std::vector<T> F, FINV;
  int _n;

  Fact(int n) : F(n + 1, 1), FINV(n + 1, 0), _n(n) {
    rep(i, 1, n + 1) {
      F[i] = F[i - 1] * (T)i;
      FINV[i] = (T)1 / F[i];
    }
  }

  T *begin() { return F.begin(); }
  T *end() { return F.end(); }
  T *rbegin() { return F.rbegin(); }
  T *rend() { return F.rend(); }

  T operator[](size_t ind) { return F[ind]; }

  T getinv(int i) {
    assert(0 <= i && i <= _n);
    return FINV[i];
  }
  T nCr(int n, int k) { return F[n] * F[n - k] * F[k]; }
};
