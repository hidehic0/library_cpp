#define PROBLEM                                                                \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D"

#include <bits/stdc++.h>
using namespace std;
#include "templates/alias.hpp"
#include "templates/macro.hpp"
#include "utils/slide_minmax.hpp"

int main() {
  ll N, L;
  in(N, L);
  vi A(N);
  in(A);

  out(slide_min(A, L));
}
