#pragma once
#include <cassert>
#include <cmath>
#include <concepts>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

namespace hidehic0_internal {
template <typename T>
concept MoQuery = requires(T t) {
  { t.l } -> std::integral;
  { t.r } -> std::integral;
};
} // namespace hidehic0_internal

// 参考: https://nyaannyaan.github.io/library/misc/mo.hpp.html
template <hidehic0_internal::MoQuery Q> struct Mo {
  int width;
  std::vector<Q> queries;
  std::vector<int> order;

  Mo(int N, std::vector<Q> QL) : queries(QL), order(QL.size()) {
    width =
        max<int>(1, 1.0 * N / max<double>(1., std::sqrt(QL.size() * 2. / 3.)));
    std::iota(begin(order), end(order), 0);
  }

  void run(auto add_left, auto add_right, auto del_left, auto del_right,
           auto rem) {
    static_assert(
        std::is_convertible_v<decltype(add_left), std::function<void(int)>>);
    static_assert(
        std::is_convertible_v<decltype(add_right), std::function<void(int)>>);
    static_assert(
        std::is_convertible_v<decltype(del_left), std::function<void(int)>>);
    static_assert(
        std::is_convertible_v<decltype(del_right), std::function<void(int)>>);
    static_assert(
        std::is_convertible_v<decltype(rem), std::function<void(int)>>);

    std::cerr
        << "DEBUG: Queries must be in the range [l,r) and this isn't asserted"
        << "\n";

    std::sort(begin(order), end(order), [&](int a, int b) {
      int ablock = queries[a].l / width, bblock = queries[b].l / width;
      if (ablock != bblock)
        return ablock < bblock;
      if (ablock & 1)
        return queries[a].r < queries[b].r;
      return queries[a].r > queries[b].r;
    });

    int l = 0, r = 0;

    for (auto ind : order) {
      while (l > queries[ind].l)
        add_left(--l);
      while (r < queries[ind].r)
        add_right(r++);
      while (l < queries[ind].l)
        del_left(l++);
      while (r > queries[ind].r)
        del_right(--r);

      rem(ind);
    }
  }
};
