#pragma once
#include <bits/stdc++.h>

#include "utils/xorshift.hpp"

struct SortedList {
public:
  SortedList() : rnd(), root(nullptr) {}

  void insert(int x) {
    auto [l, r] = split_by_key(root, x);

    auto node = new Node{x};
    root = merge(merge(l, node), r);
  }
  void erase(int x) {
    if (!contains(x))
      return;

    auto [left, right] = split_by_key(root, x);
    auto y = split_by_size(right, 1);

    delete y.first;
    root = merge(left, y.second);
  }
  void pop(int p = -1) {
    assert(root);

    if (p < 0) {
      assert(-p <= root->sub_size);
      p = root->sub_size + p;
    } else
      assert(0 <= p && p < root->sub_size);

    auto x = split_by_size(root, p);
    auto y = split_by_size(x.second, 1);
    delete y.first;
    root = merge(x.first, y.second);
  }

  inline int operator[](int n) { return get(root, n); }

  inline int size() { return sub_size(root); }
  inline bool empty() { return root == nullptr; }

  inline int bisect_left(int x) { return bisect_left(root, x); }
  inline int bisect_right(int x) { return bisect_right(root, x); }

  bool contains(int x) {
    int i = bisect_left(x);
    return i < size() && (*this)[i] == x;
  }

private:
  struct Node;
  Xorshift64 rnd;

  using node_ptr = Node *;

  node_ptr root;

  struct Node {
    int key;
    int sub_size;

    node_ptr left, right;

    Node(int k) : key(k), sub_size(1), left(nullptr), right(nullptr) {};
  };

  inline int sub_size(node_ptr node) { return (!node ? 0 : node->sub_size); }

  node_ptr update(node_ptr t) {
    assert(t);
    t->sub_size = sub_size(t->left) + sub_size(t->right) + 1;
    return t;
  }

  node_ptr merge(node_ptr left, node_ptr right) {
    if (!left || !right)
      return !left ? right : left;

    if (rnd.rand() % std::uint64_t(left->sub_size + right->sub_size) <
        left->sub_size) {
      left->right = merge(left->right, right);
      return update(left);
    } else {
      right->left = merge(left, right->left);
      return update(right);
    }
  }

  std::pair<node_ptr, node_ptr> split_by_key(node_ptr node, int key) {
    if (!node)
      return {nullptr, nullptr};

    if (key <= node->key) {
      auto [left, right] = split_by_key(node->left, key);
      node->left = right;
      update(node);

      return {left, node};
    } else {
      auto [left, right] = split_by_key(node->right, key);
      node->right = left;
      update(node);

      return {node, right};
    }
  }

  std::pair<node_ptr, node_ptr> split_by_size(node_ptr node, int sz) {
    if (!node)
      return {nullptr, nullptr};

    if (sz <= sub_size(node->left)) {
      auto [left, right] = split_by_size(node->left, sz);
      node->left = right;
      update(node);

      return {left, node};
    } else {
      auto [left, right] =
          split_by_size(node->right, sz - sub_size(node->left) - 1);
      node->right = left;
      update(node);

      return {node, right};
    }
  }

  int get(node_ptr node, int n) {
    assert(0 <= n && n < sub_size(node));

    if (sub_size(node->left) == n)
      return node->key;
    if (n < sub_size(node->left)) {
      return get(node->left, n);
    } else {
      return get(node->right, n - sub_size(node->left) - 1);
    }
  }

  int bisect_left(node_ptr node, int x) {
    if (!node)
      return 0;

    if (x <= node->key) {
      return bisect_left(node->left, x);
    } else {
      return sub_size(node->left) + 1 + bisect_left(node->right, x);
    }
  }
  int bisect_right(node_ptr node, int x) {
    if (!node)
      return 0;

    if (x < node->key)
      return bisect_right(node->left, x);
    else
      return sub_size(node->left) + 1 + bisect_right(node->right, x);
  }
};
