#pragma once
#include <bits/stdc++.h>

template <class Tp, class Comp = std::less<Tp>> struct CartesianTree {
  int root, n;
  std::vector<int> par, left, right;

  CartesianTree(const std::vector<Tp> &v)
      : root(-1), n{(int)v.size()}, par(n, -1), left(n, -1), right(n, -1) {
    std::stack<int> st;

    for (int i = 0; i < n; i++) {
      int top = -1;
      while (!st.empty() && Comp{}(v[i], v[st.top()])) {
        top = st.top();
        st.pop();
      }

      if (top != -1)
        left[i] = top, par[top] = i;

      if (!st.empty())
        top = st.top(), par[i] = top, right[top] = i;
      else
        root = i;

      st.emplace(i);
    }
  }
};

/**
 * @file cartesian_tree
 * @brief CartesianTree
 * @author hidehic0
 * @date 2026-05-29
 */
