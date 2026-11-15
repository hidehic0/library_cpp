#define PROBLEM                                                                \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A"

#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

#include "geometry/projection.hpp"

int main() {
  geometry::Point p1, p2;
  in(p1, p2);
  int Q;
  in(Q);

  cout << fixed << setprecision(10);

  while (Q--) {
    geometry::Point x;
    in(x);

    out(geometry::projection(geometry::Line(p1, p2), x));
  }
}
