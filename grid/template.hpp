#pragma once

bool coordinate_check(int x, int w, int H, int W) {
  return 0 <= x && x < H && 0 <= w && w < W;
}
