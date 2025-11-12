#pragma once
#include <iostream>
#include <vector>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rrep(i, n) for (int i = n - 1; i >= 0; i--)
#define REP(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define RREP(i, a, b) for (int i = (int)(b - 1); i >= (int)(a); i--)
#define all(a) (a).begin(), (a).end()

template <typename T> bool chmin(T &a, T b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}
template <typename T> bool chmax(T &a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

inline void input() {}
template <class H, class... T> void input(H &h, T &...t) {
  std::cin >> h;
  input(t...);
}
template <typename T> void input(std::vector<T> &v) {
  for (int i = 0; i < v.size(); i++) {
    std::cin >> v[i];
  }
}

inline void out() { std::cout << "\n"; }
template <class H, class... T> void out(H &h, T &...t) {
  std::cout << h << " ";
  out(t...);
}

template <typename T> void out(std::vector<T> v) {
  for (int i = 0; i < v.size(); i++) {
    std::cout << v[i] << (i + 1 == v.size() ? "\n" : " ");
  }
}

template <typename T> inline T ceil_div(T a, T b) { return (a + b - 1) / b; }
template <typename T> inline T mod_pow(T a, T n, T mod) {
  T res = 1;
  while (n) {
    if (n % 2 != 0) {
      res *= a;
      res %= mod;
    }

    a *= a;
    a %= mod;

    n >>= 1;
  }

  return res;
}
