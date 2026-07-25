#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <iostream>
using namespace std;

#include "data-structure/implicit_treap.hpp"

using S = long long;
auto op = [](S a, S b) { return a + b; };
auto e = []() { return 0LL; };

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  ImplicitTreap<S, op, e> treap;
  for (int i = 0; i < n; ++i) {
    S x;
    cin >> x;
    treap.insert(x, i);
  }
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int p;
      S x;
      cin >> p >> x;
      S cur = treap.prod(p, p + 1);
      treap.erase(p);
      treap.insert(cur + x, p);
    } else {
      int l, r;
      cin >> l >> r;
      cout << treap.prod(l, r) << '\n';
    }
  }
  return 0;
}
