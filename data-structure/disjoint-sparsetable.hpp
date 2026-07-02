#pragma once
#include <bits/stdc++.h>

template <typename S, auto op> struct DisjointSparseTable {
  static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                "op must work as S(S, S)");

  std::vector<std::vector<S>> table;
  std::vector<S> A;
  std::vector<int> log_table;
  int _N;

  DisjointSparseTable(std::vector<S> A) : A(A) {
    int K = 0;
    _N = A.size();

    while ((1 << K) < _N)
      K++;

    table.resize(K);
    log_table.resize(1 << K);

    for (int i = 0; i < K; i++) {
      table[i] = A;

      int w = 1 << i;

      for (int l = 0; l + w < _N; l += 2 * w) {
        int r = std::min(l + w * 2, _N), m = l + w;

        for (int k = m - 2; k >= l; k--) {
          table[i][k] = op(table[i][k], table[i][k + 1]);
        }
        for (int k = m + 1; k < r; k++) {
          table[i][k] = op(table[i][k - 1], table[i][k]);
        }
      }

      for (int k = 1 << i; k < (1 << (i + 1)); k++)
        log_table[k] = i;
    }
  }

  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= _N);
    if (l + 1 == r)
      return A[l];

    int k = log_table[l ^ (r - 1)];

    return op(table[k][l], table[k][r - 1]);
  }
};
