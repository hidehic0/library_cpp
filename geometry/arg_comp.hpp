#pragma once
template <typename T> bool arg_comp(T ax, T ay, T bx, T by) {
  auto gettp = [](T x, T y) -> int {
    if (x >= 0 && y >= 0)
      return 0;
    if (x >= 0 && y < 0)
      return 1;
    if (x < 0 && y < 0)
      return 2;
    if (x < 0 && y >= 0)
      return 3;
  };

  int a = gettp(ax, ay), b = gettp(bx, by);

  if (a != b)
    return a < b;

  return ax * by < bx * ay;
}
