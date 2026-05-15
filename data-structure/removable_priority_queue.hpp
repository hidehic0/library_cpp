#pragma once
#include <bits/stdc++.h>

template <typename T, typename Compare = std::less<T>>
struct RemovablePriorityQueue {
  std::priority_queue<T, std::vector<T>, Compare> PQ, RPQ;

  void m_remove() {
    if (PQ.empty())
      return;

    while (true) {
      if (PQ.empty() || RPQ.empty())
        return;

      if (PQ.top() == RPQ.top())
        PQ.pop(), RPQ.pop();
      else
        return;
    }
  }

  void push(T v) { PQ.push(v); }

  void remove(T v) { RPQ.push(v); }

  bool empty() {
    m_remove();

    return PQ.empty();
  }

  T top() {
    assert(!empty());
    return PQ.top();
  }

  void pop() {
    assert(!empty());
    PQ.pop();
  }
};
