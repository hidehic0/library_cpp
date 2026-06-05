#pragma once
#include <bits/stdc++.h>

struct BitVector {
  using u64 = uint64_t;

  int n;
  std::vector<u64> bit;
  std::vector<u64> cnt;

  BitVector() {};
  BitVector(int N) {
    n = (N + 63) / (64);
    bit.resize(n + 1, 0), cnt.resize(n + 1, 0);
  }
  void set(int i) { bit[i / 64] |= 1LL << (i & 63); }
  void build() {
    for (int i = 0; i < n; i++)
      cnt[i + 1] += cnt[i] + std::popcount(bit[i]);
  }
  int rank(int i) {
    return cnt[i / 64] + std::popcount(bit[i / 64] & ((1ull << (i & 63)) - 1));
  }
};

template <std::integral Tp, int H = 64> struct WaveletMatrix {
  int N;
  std::array<BitVector, H> dir;

  WaveletMatrix(std::vector<Tp> A) : N{A.size()} {
    for (int b = H - 1; b >= 0; --b) {
      BitVector bv(N);

      std::vector<Tp> left, right;

      for (int i = 0; i < N; i++) {
        if ((A[i] >> b) & 1) {
          right.emplace_back(A[i]);
          bv.set(i);
        } else
          left.emplace_back(A[i]);
      }

      for (int i = 0; i < left.size(); i++)
        A[i] = left[i];
      for (int i = 0; i < right.size(); i++)
        A[i + left.size()] = right[i];

      bv.build();
      dir[b] = bv;
    }
  }

  //! [left,right)の区間で、xより大きい値の個数を求める
  int upper_cnt(int left, int right, Tp x) {
    int res = 0;

    for (int b = H - 1; b >= 0; b--) {
      int lc = dir[b].rank(left), rc = dir[b].rank(right), nl, nr;

      if ((x >> b) & 1) {
        if (lc == rc)
          break;

        nl = N - dir[b].rank(N) + lc, nr = nl + rc - lc;
      } else {
        res += rc - lc;

        if ((right - left) == (rc - lc))
          break;

        nl = left - lc, nr = right - rc;
      }

      std::swap(left, nl), std::swap(right, nr);
    }

    return res;
  }

  //! [left,right)の区間で、x未満の値の個数を求める
  int lower_cnt(int left, int right, Tp x) {
    int res = 0;

    for (int b = H - 1; b >= 0; b--) {
      int lc = dir[b].rank(left), rc = dir[b].rank(right), nl, nr;

      if ((x >> b) & 1) {
        res += (right - left) - (rc - lc);

        if (lc == rc)
          break;

        nl = N - dir[b].rank(N) + lc, nr = nl + rc - lc;
      } else {
        if ((right - left) == (rc - lc))
          break;

        nl = left - lc, nr = right - rc;
      }

      std::swap(left, nl), std::swap(right, nr);
    }

    return res;
  }

  //! [left,right)のなかでk番目(0-indexed)に大きい値を求める
  Tp kth_largest(int left, int right, int k) {
    Tp res = 0;

    for (int b = H - 1; b >= 0; b--) {
      int lc = dir[b].rank(left), rc = dir[b].rank(right), nl, nr;

      if (rc - lc > k) {
        res += Tp(1) << b;
        nl = N - dir[b].rank(N) + lc, nr = nl + rc - lc;
      } else {
        k -= rc - lc;
        nl = left - lc, nr = right - rc;
      }

      std::swap(left, nl), std::swap(right, nr);
    }

    return res;
  }

  //! [left,right)のなかでk番目(0-indexed)に小さい値を求める
  Tp kth_smallest(int left, int right, int k) {
    return kth_largest(left, right, (right - left) - k - 1);
  }
};
