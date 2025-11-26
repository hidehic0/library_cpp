#pragma once
#include <algorithm>
#include <map>
#include <vector>

template <class T> std::map<T, int> compress_1d(std::vector<T> V) {
  sort(V.begin(), V.end());
  V.erase(std::unique(V.begin(), V.end()), V.end());

  std::map<T, int> res;

  for (int i = 0; i < V.size(); i++) {
    res[V[i]] = i;
  }

  return res;
}
