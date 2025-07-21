#pragma once
#include <iostream>

#define rep(i, n) for (ll i = 0; i < (int)(n); i++)
#define REP(i, a, b) for (ll i = (int)(a); i < (int)(b); ++i)
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

void YN(bool b) { std::cout << (b ? "Yes" : "No") << std::endl; }
void YE(bool b) {
  if (b) {
    std::cout << "Yes" << std::endl;
    exit(1);
  }
}
void NE(bool b) {
  if (b) {
    std::cout << "No" << std::endl;
    exit(1);
  }
}
