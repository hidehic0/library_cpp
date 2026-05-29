// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/cartesian_tree
#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

#include "tree/cartesian_tree.hpp"

int main() {
  ll N;
  in(N);
  vi A(N);
  in(A);

  CartesianTree<ll> ct(A);

  vi res(N);

  rep(i, N) { res[i] = ct.par[i] == -1 ? i : ct.par[i]; }
  out(res);
}
