#pragma once
#include "templates/alias.hpp"
#include "templates/macro.hpp"
#include <deque>

template <class T> VC<T> slide_min(const VC<T> &v, int k) {
  assert(k <= v.size());
  std::deque<int> Q;

  rep(i, k - 1) {
    while (!Q.empty() && v[Q.back()] >= v[i])
      Q.pop_back();
    Q.emplace_back(i);
  }

  VC<T> res(v.size() - k + 1);

  rep(i, k - 1, v.size()) {
    while (!Q.empty() && v[Q.back()] >= v[i])
      Q.pop_back();
    Q.emplace_back(i);
    res[i - k + 1] = v[Q.front()];

    while (!Q.empty() && Q.front() <= i - k + 1) {
      Q.pop_front();
    }
  }

  return res;
}

template <class T> VC<T> slide_max(const VC<T> &v, int k) {
  assert(k <= v.size());
  std::deque<int> Q;

  rep(i, k - 1) {
    while (!Q.empty() && v[Q.back()] <= v[i])
      Q.pop_back();
    Q.emplace_back(i);
  }

  VC<T> res(v.size() - k + 1);

  rep(i, k - 1, v.size()) {
    while (!Q.empty() && v[Q.back()] <= v[i])
      Q.pop_back();
    Q.emplace_back(i);
    res[i - k + 1] = v[Q.front()];

    while (!Q.empty() && Q.front() <= i - k + 1)
      Q.pop_front();
  }

  return res;
}
