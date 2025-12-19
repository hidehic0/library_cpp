#pragma once
#include <cassert>
#include <deque>

/**
 * @class ConvexHullTrick
 * @brief
 * aとbとxが与えられたときa_i×x+b_iの最大/最小値を各xに対して求めるアルゴリズム
 * テンプレートのismaxを使って最大値または最小値を求めるかを制御する
 * 最大値の場合はaは単調増加 最小値の場合はaは単調減少
 */
template <bool ismax, class T> class ConvexHullTrick {
private:
  std::deque<std::pair<T, T>> dq;
  bool is_get_query = false, is_get_func = false;
  T prev_x, prev_a;

  // どちらのcheckもpopするかの判定

  bool check_with_three_funcs(std::pair<T, T> f1, std::pair<T, T> f2,
                              std::pair<T, T> f3) {
    T a = (f3.second - f1.second) * (f1.first - f2.first),
      b = (f2.second - f1.second) * (f1.first - f3.first);

    if (ismax)
      return a <= b;
    else
      return a >= b;
  }

  bool check_with_x(std::pair<T, T> f1, std::pair<T, T> f2, T x) {
    T a = f1.first * x + f1.second, b = f2.first * x + f2.second;
    if (ismax)
      return a <= b;
    else
      return a >= b;
  }

public:
  void add_func(T a, T b) {
    if (is_get_func) {
      if (ismax)
        assert(a >= prev_a);
      else
        assert(a <= prev_a);
    }

    std::pair<T, T> p = {a, b};
    while (dq.size() >= 2 &&
           check_with_three_funcs(dq[dq.size() - 2], dq[dq.size() - 1], p)) {
      dq.pop_back();
    }
    dq.emplace_back(p);
    is_get_func = true;
    prev_a = a;
  }

  T query(T x) {
    if (is_get_query)
      assert(x >= prev_x);

    while (dq.size() >= 2 && check_with_x(dq[0], dq[1], x)) {
      dq.pop_front();
    }

    is_get_query = true;
    prev_x = x;

    return dq.front().first * x + dq.front().second;
  }
};
