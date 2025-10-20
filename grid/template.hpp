#pragma once
#include <bits/stdc++.h>

bool coordinate_check(int x, int w, int H, int W) {
  return 0 <= x && x < H && 0 <= w && w < W;
}

constexpr std::array<std::pair<int, int>, 4> MOVES1 = {
    {{0, 1}, {1, 0}, {-1, 0}, {0, -1}}};
