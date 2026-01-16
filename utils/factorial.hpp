#pragma once
#include <vector>

template <class T> std::vector<T> factorial_list(int N) {
  std::vector<T> P(N + 1, 1);
  for (int i = 1; i <= N; i++) {
    P[i] = P[i - 1] * T{i};
  }

  return P;
}
