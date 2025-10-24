#pragma once
#include <algorithm>
#include <vector>

template <typename T> void warshall_floyd(std::vector<std::vector<T>> &G) {
  int n = G.size();

  for (int k = 0; k < n; k++) {
    for (int u = 0; u < n; u++) {
      for (int v = 0; v < n; v++)
        G[u][v] = std::min(G[u][v], G[u][k] + G[k][v]);
    }
  }
}
