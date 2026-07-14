#pragma once

#include <bits/stdc++.h>

// 参考:ㅤhttps://nyaannyaan.github.io/library/math/stern-brocot-tree-binary-search.hpp

struct SternBrocotTreeNode {
  using ll = long long;

  ll p, q, r, s;
  std::vector<ll> dir;

  SternBrocotTreeNode() : p(0), q(1), r(1), s(0) {}
  SternBrocotTreeNode(ll X, ll Y) : p(0), q(1), r(1), s(0) {
    assert(1 <= X && 1 <= Y);

    ll g = std::gcd<ll>(X, Y);

    X /= g, Y /= g;

    while (std::min(X, Y) > 0LL) {
      if (X > Y) {
        ll d = X / Y;
        X -= d * Y;
        go_right(d - ll(X == 0 ? 1 : 0));
      } else {
        ll d = Y / X;
        Y -= d * X;
        go_left(d - ll(Y == 0 ? 1 : 0));
      }
    }
  }

  void go_left(ll d = 1) {
    if (d <= 0)
      return;
    if (dir.empty() || dir.back() > 0)
      dir.emplace_back(0);

    dir.back() -= d;
    r += p * d, s += q * d;
  }
  void go_right(ll d = 1) {
    if (d <= 0)
      return;

    if (dir.empty() || dir.back() < 0)
      dir.emplace_back(0);

    dir.back() += d;
    p += r * d, q += s * d;
  }
  bool go_parent(ll d = 1) {
    if (d <= 0)
      return true;

    while (d != 0) {
      if (dir.empty())
        return false;

      ll m = std::min(d, std::llabs(dir.back()));

      if (dir.back() > 0)
        p -= r * m, q -= s * m, dir.back() -= m;
      else
        r -= p * m, s -= q * m, dir.back() += m;

      if (dir.back() == 0)
        dir.pop_back();

      d -= m;
      if (m == 0)
        break;
    }

    return true;
  }

  inline ll depth() {
    ll res = 0;

    for (auto &d : dir)
      res += std::llabs(d);

    return res;
  }

  static SternBrocotTreeNode lca(const SternBrocotTreeNode &lhs,
                                 const SternBrocotTreeNode &rhs) {
    SternBrocotTreeNode n;

    for (int i = 0; i < std::min<int>(lhs.dir.size(), rhs.dir.size()); i++) {
      ll val1 = lhs.dir[i], val2 = rhs.dir[i];
      if ((val1 < 0) != (val2 < 0))
        break;
      if (val1 < 0)
        n.go_left(std::min(-val1, -val2));
      if (val1 > 0)
        n.go_right(std::min(val1, val2));

      if (val1 != val2)
        break;
    }

    return n;
  }
};

// 分子と分母がINF以下である非負分数のうち以下のものを返す
// fisrt->check(x)がfalseである最大の非負分数
// second->check(x)がtrueである最小の非負分数
// check(0)=trueの場合は、(0/1,0/1)を返す
// trueになる分数が存在しない場合は(?,1/0)を返す
// INF=0の場合は、(0/1,1/0)を返す
std::pair<std::pair<long long, long long>, std::pair<long long, long long>>
stern_brocot_tree_binary_search(auto check, const long long &INF) {
  static_assert(
      std::is_convertible_v<decltype(check),
                            std::function<bool(long long, long long)>>,
      "check must work as bool(ll, ll)");
  assert(0 <= INF);

  SternBrocotTreeNode sbt;

  if (INF == 0)
    return {{0, 1}, {1, 0}};

  if (check(0, 1))
    return {{0, 1}, {0, 1}};

  auto over = [&](bool return_value) {
    return std::max(sbt.p + sbt.r, sbt.q + sbt.s) > INF ||
           check(sbt.p + sbt.r, sbt.q + sbt.s) == return_value;
  };

  bool go_left = over(true);

  for (; true; go_left ^= 1) {
    long long a = 1;

    if (go_left) {
      // 左に進むだけ進んで、ちょうどcheck(x)がfalseになる、またはINFが超えるところまで移動

      for (; true; a <<= 1) {
        sbt.go_left(a);

        if (over(false)) {
          sbt.go_parent(a);
          break;
        }
      }

      for (a >>= 1; a; a >>= 1) {
        sbt.go_left(a);

        if (over(false))
          sbt.go_parent(a);
      }

      sbt.go_left(1);
      if (std::max(sbt.p + sbt.r, sbt.q + sbt.s) > INF)
        return {{sbt.p, sbt.q}, {sbt.r, sbt.s}};
    } else {
      // 右に進むだけ進んで、ちょうどcheck(x)がtrueになる、またはINFが超えるところまで移動

      for (; true; a <<= 1) {
        sbt.go_right(a);

        if (over(true)) {
          sbt.go_parent(a);
          break;
        }
      }

      for (a >>= 1; a; a >>= 1) {
        sbt.go_right(a);

        if (over(true))
          sbt.go_parent(a);
      }

      sbt.go_right(1);
      if (std::max(sbt.p + sbt.r, sbt.q + sbt.s) > INF)
        return {{sbt.p, sbt.q}, {sbt.r, sbt.s}};
    }
  }
}
