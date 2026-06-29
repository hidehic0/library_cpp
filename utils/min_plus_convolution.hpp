#pragma once
#include <bits/stdc++.h>

template <class T>
concept AddCompType = requires(T a, T b) {
  { a + b } -> std::same_as<T>;
  { a - b } -> std::same_as<T>;
} && std::totally_ordered<T>;

template <AddCompType T, class Comp = std::less<T>>
std::vector<T> min_plus_convolution(const std::vector<T> &A,
                                    const std::vector<T> &B) {
  if (A.empty() || B.empty())
    return {};

  int N = A.size(), M = B.size();
  T cur = A[0] + B[0];

  std::vector<T> res = {cur};

  for (int a = 0, b = 0; a < N - 1 || b < M - 1;) {
    if (a != N - 1 &&
        (b == M - 1 || Comp{}(A[a + 1] - A[a], B[b + 1] - B[b]))) {
      cur += A[a + 1] - A[a];
      a++;
      res.emplace_back(cur);
    } else {
      cur += B[b + 1] - B[b];
      b++;
      res.emplace_back(cur);
    }
  }

  return res;
}
template <AddCompType T>
std::vector<T> max_plus_convolution(const std::vector<T> &A,
                                    const std::vector<T> &B) {
  return min_plus_convolution<T, std::greater<T>>(A, B);
}
