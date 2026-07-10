#pragma once
#include <bits/stdc++.h>

/**
 * @fn extgcd
 * ax + by = gcd(a, b)となるx,yを求める
 */
template <std::integral T> std::pair<T, T> extgcd(T a, T b) {
  std::pair<T, T> x{1, 0}, y{0, 1};

  while (b) {
    T u = a / b;
    a -= u * b;
    x.first -= y.first * u;
    x.second -= y.second * u;

    swap(a, b), swap(x, y);
  }

  return x;
}
