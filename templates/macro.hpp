#pragma once
#include <iostream>
#include <vector>

// 引数の長さで内容が変わるrep 参考: https://trap.jp/post/1224
#define overload4(a, b, c, d, ...) d
#define _rep(i, n) for (int i = 0; i < (int)(n); i++)
#define REP(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define rep(...) overload4(__VA_ARGS__, REP, _rep)(__VA_ARGS__)
#define _rrep(i, n) for (int i = n - 1; i >= 0; i--)
#define RREP(i, a, b) for (int i = (int)(b - 1); i >= (int)(a); i--)
#define rrep(...) overload4(__VA_ARGS__, RREP, _rrep)(__VA_ARGS__)

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

template <typename T1, typename T2>
std::istream &operator>>(std::istream &is, std::pair<T1, T2> &p) {
  is >> p.first >> p.second;
  return is;
}

template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
  for (T &in : v)
    is >> in;
  return is;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
  for (int i = 0; i < (int)v.size(); i++) {
    os << v[i] << (i + 1 == v.size() ? "" : " ");
  }
  return os;
}

// pythonのprintライクな関数 参考:
// https://nyaannyaan.github.io/library/template/inout.hpp
inline void out() { std::cout << std::endl; }
template <typename T, typename... U, char sep = ' '>
void out(const T &t, const U &...u) {
  std::cout << t;

  if (sizeof...(u))
    std::cout << sep;

  out(u...);
}

// cinの短縮関数 参考: https://nyaannyaan.github.io/library/template/inout.hpp
inline void in() {}
template <typename T, class... U> void in(T &t, U &...u) {
  std::cin >> t;
  in(u...);
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
template <typename T> inline T minus_mod(T a, T b) { return ((a % b) + b) % b; }

template <typename T> void apply_vec(std::vector<T> &v, T (*fn)(T)) {
  for (int i = 0; i < v.size(); i++)
    v[i] = fn(v[i]);
}
