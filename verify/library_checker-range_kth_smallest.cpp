#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

#include "data-structure/wavelet_matrix.hpp"

int main() {
  ll N, Q;
  in(N, Q);

  vi A(N);
  in(A);

  WaveletMatrix<ll, 30> wm(A);

  while (Q--) {
    ll l, r, k;
    in(l, r, k);

    cout << wm.kth_smallest(l, r, k) << "\n";
  }
}
