#define PROBLEM "https://judge.yosupo.jp/problem/stern_brocot_tree"

#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

#include "math/stern-brocot-tree.hpp"

void solve() {
  string tp;
  in(tp);

  if (tp == "ENCODE_PATH") {
    ll a, b;
    in(a, b);

    SternBrocotTreeNode sbt(a, b);
    cout << sbt.dir.size() << " ";
    for (auto &d : sbt.dir)
      cout << (d < 0 ? 'L' : 'R') << " " << llabs(d) << " ";

    cout << "\n";
  } else if (tp == "DECODE_PATH") {
    int K;
    in(K);
    SternBrocotTreeNode sbt;

    rep(_, K) {
      char c;
      ll n;

      in(c, n);

      if (c == 'L')
        sbt.go_left(n);
      else
        sbt.go_right(n);
    }

    out(sbt.p + sbt.r, sbt.q + sbt.s);
  } else if (tp == "LCA") {
    ll a, b, c, d;
    in(a, b, c, d);

    SternBrocotTreeNode A(a, b), B(c, d);

    auto sbt = SternBrocotTreeNode::lca(A, B);

    out(sbt.p + sbt.r, sbt.q + sbt.s);
  } else if (tp == "ANCESTOR") {
    ll k, a, b;
    in(k, a, b);

    SternBrocotTreeNode sbt(a, b);
    ll d = sbt.depth() - k;

    if (d < 0) {
      out(-1);
      return;
    }

    bool t = sbt.go_parent(d);
    assert(t);

    out(sbt.p + sbt.r, sbt.q + sbt.s);
  } else {
    ll a, b;
    in(a, b);

    SternBrocotTreeNode sbt(a, b);

    out(sbt.p, sbt.q, sbt.r, sbt.s);
  }
}

int main() {
  int T;
  in(T);

  while (T--)
    solve();
}
