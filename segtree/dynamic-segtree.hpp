#pragma once
#include <bits/stdc++.h>

template <class S, auto op, auto e> struct DynamicSegtree {
  static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                "op must work as S(S, S)");
  static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                "e must work as S()");

public:
  long long _n;

  DynamicSegtree(long long n) : _n(n), root(nullptr) {}

  void set(long long p, const S &x) {
    assert(0 <= p && p < _n);
    set(root, 0, _n, p, x);
  }

  std::optional<S> get(long long p) {
    assert(0 <= p && p < _n);
    return get(root, 0, _n, p);
  }

  S prod(long long l, long long r) {
    assert(0 <= l && l <= r && r <= _n);

    return prod(root, 0, _n, l, r);
  }

private:
  struct Node;
  using node_ptr = std::unique_ptr<Node>;

  struct Node {
    S value;

    node_ptr left, right;

    Node(S value) : value(value), left(nullptr), right(nullptr) {}
  };

  node_ptr root;

  void set(node_ptr &node, long long a, long long b, long long p, const S &x) {
    if (!node)
      node = std::make_unique<Node>(e());

    if (b - a == 1) {
      node->value = x;
      return;
    }

    long long mid = (a + b) >> 1LL;

    if (p < mid)
      set(node->left, a, mid, p, x);
    else
      set(node->right, mid, b, p, x);

    node->value = e();

    if (node->left)
      node->value = op(node->value, node->left->value);
    if (node->right)
      node->value = op(node->value, node->right->value);
  }

  std::optional<S> get(const node_ptr &node, long long a, long long b,
                       long long p) {
    if (!node)
      return std::nullopt;
    if (b - a == 1)
      return node->value;

    long long mid = (a + b) >> 1LL;

    if (p < mid)
      return get(node->left, a, mid, p);
    else
      return get(node->right, mid, b, p);
  }

  S prod(const node_ptr &node, long long a, long long b, long long l,
         long long r) {
    if (!node || b <= l || r <= a)
      return e();

    if (l <= a && b <= r)
      return node->value;

    long long mid = (a + b) >> 1;

    return op(prod(node->left, a, mid, l, r), prod(node->right, mid, b, l, r));
  }
};
