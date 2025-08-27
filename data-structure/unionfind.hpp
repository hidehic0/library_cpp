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

struct UnionFind2D {
public:
  int _h, _w;
  UnionFind internal_uf;

  UnionFind2D(int h, int w) : _h(h), _w(w), internal_uf(h * w) {}

  int leader(int h, int w) { return internal_uf.leader(get_id(h, w)); };
  bool merge(int ah, int aw, int bh, int bw) {
    return internal_uf.merge(get_id(ah, aw), get_id(bh, bw));
  }
  int size(int h, int w) { return internal_uf.size(get_id(h, w)); }
  bool same(int ah, int aw, int bh, int bw) {
    return internal_uf.same(get_id(ah, aw), get_id(bh, bw));
  }

private:
  int get_id(int h, int w) {
    assert(0 <= h && 0 < _h && 0 <= w && w < _w);
    return h * _w + w;
  }
};
