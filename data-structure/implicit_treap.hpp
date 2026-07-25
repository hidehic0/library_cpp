#pragma once
#include <bits/stdc++.h>

#include "utils/xorshift.hpp"

template <class S, auto op, auto e> struct ImplicitTreap {
  static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                "op must work as S(S, S)");
  static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                "e must work as S()");

public:
  ImplicitTreap() : rnd(), root(nullptr) {}

  void insert(const S &x, int k) {
    auto [l, r] = split(root, k);
    root = merge(merge(l, new Node(x, rnd)), r);
  }
  void erase(int k) {
    assert(k < count(root));
    auto [left, right] = split(root, k);
    auto y = split(right, 1);
    delete y.first;
    root = merge(left, y.second);
  }
  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= count(root));

    auto [left, right] = split(root, r);
    auto [a, b] = split(left, l);
    S res = data(b);
    root = merge(merge(a, b), right);

    return res;
  }

  inline S operator[](int k) { return get(root, k); }

private:
  Xorshift64 rnd;

  struct Node;

  using Ptr = Node *;

  struct Node {
    int cnt;
    long long priority;
    S key, data;
    Ptr l, r;

    Node(const S &k, Xorshift64 &rnd)
        : cnt(1), priority(rnd.rand()), key(k), data(k), l(nullptr),
          r(nullptr) {}
  };

  inline static int count(Ptr p) { return p ? p->cnt : 0; }
  inline static S data(Ptr p) { return p ? p->data : e(); }

  Ptr update(Ptr p) {
    if (!p)
      return nullptr;

    p->cnt = count(p->l) + count(p->r) + 1;
    p->data = op(op(data(p->l), p->key), data(p->r));

    return p;
  }

  Ptr root;

  Ptr merge(Ptr l, Ptr r) {
    if (!l)
      return r;
    if (!r)
      return l;

    if (l->priority > r->priority) {
      l->r = merge(l->r, r);
      return update(l);
    } else {
      r->l = merge(l, r->l);
      return update(r);
    }
  }

  std::pair<Ptr, Ptr> split(Ptr p, int k) {
    if (!p)
      return {nullptr, nullptr};

    if (k <= count(p->l)) {
      auto x = split(p->l, k);
      p->l = x.second;
      return {x.first, update(p)};
    } else {
      auto x = split(p->r, k - count(p->l) - 1);
      p->r = x.first;
      return {update(p), x.second};
    }
  }

  S get(Ptr p, int k) {
    assert(p);
    assert(0 <= k && k < count(p));

    if (count(p->l) == k)
      return p->key;

    if (k < count(p->l))
      return get(p->l, k);
    else
      return get(p->r, k - count(p->l) - 1);
  }
};
