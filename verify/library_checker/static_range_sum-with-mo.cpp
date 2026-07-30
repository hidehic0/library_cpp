#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include <bits/stdc++.h>
using namespace std;

#include "utils/mo.hpp"

struct Query {
  int l, r;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<long long> a(n);
  for (auto &x : a)
    cin >> x;

  vector<Query> queries(q);
  for (auto &[l, r] : queries)
    cin >> l >> r;

  vector<long long> ans(q);
  long long sum = 0;
  Mo mo(n, queries);
  mo.run(
      [&](int i) { sum += a[i]; }, [&](int i) { sum += a[i]; },
      [&](int i) { sum -= a[i]; }, [&](int i) { sum -= a[i]; },
      [&](int i) { ans[i] = sum; });

  for (auto x : ans)
    cout << x << '\n';
}
