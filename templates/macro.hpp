#pragma once
#include <iostream>

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

constexpr void YN(bool b) { std::cout << (b ? "Yes" : "No") << std::endl; }
