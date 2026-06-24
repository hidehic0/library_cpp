#pragma once
#include <bits/stdc++.h>

template <typename S, auto op, auto e> struct SegmentTree2D {
  static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                "op must work as S(S, S)");
  static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                "e must work as S()");

public:
  int _h, _w;
  std::vector<S> seg;

  explicit SegmentTree2D() = default;
  SegmentTree2D(std::vector<std::vector<S>> dat) {
    assert(!dat.empty() && !dat[0].empty());
    _h = dat.size(), _w = dat[0].size();

    seg.resize(_h * _w * 4, e());

    for (int x = 0; x < _h; x++)
      for (int y = 0; y < _w; y++)
        seg[id(x + _h, y + _w)] = dat[x][y];

    for (int x = 1; x < _h * 2; x++)
      for (int y = _w - 1; y; y--)
        seg[id(x, y)] = op(seg[id(x, y << 1)], seg[id(x, y << 1 | 1)]);

    for (int y = 1; y < _w * 2; y++)
      for (int x = _h - 1; x; x--)
        seg[id(x, y)] = op(seg[id(x << 1, y)], seg[id(x << 1 | 1, y)]);
  }

  inline S get(int x, int y) { return seg[id(x + _h, y + _w)]; }

  void set(int h, int w, S x) {
    h += _h, w += _w;

    seg[id(h, w)] = x;

    for (int i = w >> 1; i; i >>= 1)
      seg[id(h, i)] = op(seg[id(h, i << 1)], seg[id(h, i << 1 | 1)]);

    while (h >>= 1)
      for (int i = w; i; i >>= 1)
        seg[id(h, i)] = op(seg[id(h << 1, i)], seg[id(h << 1 | 1, i)]);
  }

  //! [h1,h2)[w1,w2)の総積を求める
  S prod(int h1, int h2, int w1, int w2) {
    S top = e(), bottom = e();

    for (h1 += _h, h2 += _h; h1 < h2; h1 >>= 1, h2 >>= 1) {
      if (h1 & 1)
        top = op(top, _inner_prod(h1++, w1, w2));
      if (h2 & 1)
        bottom = op(_inner_prod(--h2, w1, w2), bottom);
    }

    return op(top, bottom);
  }

private:
  inline int id(int h, int w) { return h * _w * 2 + w; }

  inline S _inner_prod(int h, int l, int r) {
    S left = e(), right = e();

    for (l += _w, r += _w; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        left = op(left, seg[id(h, l++)]);
      if (r & 1)
        right = op(seg[id(h, --r)], right);
    }

    return op(left, right);
  }
};

/*!
 * @file data-structure/2d-segtree.hpp
 * @brief 2DSegmentTree
 * @date 2026-06-24
 */
