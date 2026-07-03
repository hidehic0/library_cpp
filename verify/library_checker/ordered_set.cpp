#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

#include "data-structure/sorted-list.hpp"

int main() {
  ll N, Q;
  in(N, Q);
  vi A(N);
  in(A);

  SortedList S;

  for (auto a : A)
    S.insert(a);

  while (Q--) {
    ll t, x;
    in(t, x);

    // out(t, x, S.size());

    if (t == 0) {
      if (!S.contains(x))
        S.insert(x);
    } else if (t == 1) {
      S.erase(x);
    } else if (t == 2) {
      out(x <= S.size() ? S[x - 1] : -1);
    } else if (t == 3) {
      out(S.bisect_right(x));
    } else if (t == 4) {
      ll ind = S.bisect_right(x);
      out(ind ? S[ind - 1] : -1);
    } else {
      ll ind = S.bisect_left(x);
      out(ind < S.size() ? S[ind] : -1);
    }
  }
}
