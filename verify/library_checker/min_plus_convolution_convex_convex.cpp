#define PROBLEM                                                                \
  "https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex"

#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

#include "utils/min_plus_convolution.hpp"

int main() {
  ll N, M;
  in(N, M);

  vi A(N), B(M);
  in(A, B);

  out(min_plus_convolution(A, B));
}
