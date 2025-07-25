#pragma once
#include <cassert>
#include <vector>

struct UnionFind {
  std::vector<int> data;
  int _n;

  UnionFind(int n) : data(n, -1) { _n = n; }

  int leader(int x) { return data[x] < 0 ? x : data[x] = leader(data[x]); }

  bool merge(int a, int b) {
    // assert(0 <= a && a < _n && 0 <= b && b < _n);
    a = leader(a);
    b = leader(b);

    if (a == b) {
      return false;
    }

    if (data[a] > data[b]) {
      std::swap(a, b);
    }

    data[a] += data[b];
    data[b] = a;

    return true;
  }

  int size(int x) { return -data[leader(x)]; }

  bool same(int a, int b) { return leader(a) == leader(b); }
};
