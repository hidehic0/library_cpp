#pragma once
#include <bits/stdc++.h>

#include "geometry/templates.hpp"

namespace geometry {
constexpr Point projection(const Line &l, Point &p) {
  Real t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
  return l.a + (l.a - l.b) * t;
}
} // namespace geometry
