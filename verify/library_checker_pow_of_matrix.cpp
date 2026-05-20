// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/pow_of_matrix
#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;
#include "templates/alias.hpp"
#include "templates/macro.hpp"

#include "matrix/matrix.hpp"

inline ll op(ll a, ll b) { return (a * b) % 998244353; }
inline ll add(ll a, ll b) { return (a + b) % 998244353; }
inline ll e() { return 0; }
inline ll id() { return 1; }

int main() {
  ll N, K;
  in(N, K);
  vvi A(N, vi(N));
  in(A);

  Matrix<ll, add, op, e, id> mat(A);
  mat ^= K;

  rep(i, N) rep(k, N) cout << mat[i][k] << (k + 1 == N ? "\n" : " ");
}
