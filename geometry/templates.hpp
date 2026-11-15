#pragma once
#include <bits/stdc++.h>
#include <cassert>

namespace geometry {
using Real = double;
constexpr Real EPS = 1e-8;

constexpr int sign(const Real &t) {
  if (t <= -EPS)
    return -1;
  else if (t >= EPS)
    return 1;
  else
    return 0;
}
constexpr bool equals(const Real &a, const Real &b) { return sign(a - b) == 0; }

struct Point {
  Real x, y;

  constexpr Point() : x(0), y(0) {}
  constexpr Point(Real x, Real y) : x(x), y(y) {}

  // operators
  constexpr Point operator+() const { return Point(*this); }
  constexpr Point operator-() const { return Point(-x, -y); }

  constexpr Point operator+(const Point &rhs) const {
    return Point(*this) += rhs;
  }
  constexpr Point operator-(const Point &rhs) const {
    return Point(*this) -= rhs;
  }
  constexpr Point operator*(Real rhs) const { return Point(*this) *= rhs; }
  constexpr Point operator/(Real rhs) const { return Point(*this) /= rhs; }

  constexpr Point &operator+=(const Point &rhs) {
    x += rhs.x, y += rhs.y;
    return *this;
  }
  constexpr Point &operator-=(const Point &rhs) {
    *this += -rhs;
    return *this;
  }
  constexpr Point &operator*=(Real rhs) {
    x *= rhs, y *= rhs;
    return *this;
  }
  constexpr Point &operator/=(Real rhs) {
    x /= rhs, y /= rhs;
    return *this;
  }

  friend std::istream &operator>>(std::istream &is, Point &p) {
    is >> p.x >> p.y;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const Point &p) {
    os << p.x << " " << p.y;
    return os;
  }
};

constexpr Real dot(const Point &a, const Point &b) {
  return a.x * b.x + a.y * b.y;
}
constexpr Real cross(const Point &a, const Point &b) {
  return a.x * b.y - a.y * b.x;
}
constexpr Real norm(const Point &a) { return dot(a, a); }

struct Line {
  Point a, b;

  constexpr Line() = default;
  constexpr Line(const Point &a, const Point &b) : a(a), b(b) {}

  constexpr Line(const Real &A, const Real &B, const Real &C) { // Ax + By = C
    if (equals(A, 0)) {
      assert(!equals(B, 0));

      a = Point(0, C / B);
      b = Point(1, C / B);
    } else if (equals(B, 0)) {
      a = Point(C / A, 0);
      b = Point(C / A, 1);
    } else if (equals(C, 0)) {
      a = Point(0, C / B);
      b = Point(1, (C - A) / B);
    } else {
      a = Point(0, C / B);
      b = Point(C / A, 0);
    }
  }
};
} // namespace geometry
