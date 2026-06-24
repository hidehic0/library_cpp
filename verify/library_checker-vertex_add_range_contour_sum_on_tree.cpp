#define PROBLEM                                                                \
  "https://judge.yosupo.jp/problem/vertex_add_range_contour_sum_on_tree"

#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define dump(...)
#define CPP_DUMP_SET_OPTION(...)
#define CPP_DUMP_SET_OPTION_GLOBAL(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#define CPP_DUMP_DEFINE_EXPORT_ENUM(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT_GENERIC(...)
#define export_command
#elif __has_include(<cpp-dump/cpp-dump.hpp>)
#include <cpp-dump/cpp-dump.hpp>
#define dump(...) cpp_dump(__VA_ARGS__)
#else
#define dump(...)
#define CPP_DUMP_SET_OPTION(...)
#define CPP_DUMP_SET_OPTION_GLOBAL(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#define CPP_DUMP_DEFINE_EXPORT_ENUM(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT_GENERIC(...)
#define export_command
#endif

#include "tree/point_set_range_contour_sum.hpp"

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, Q;
  in(N, Q);

  vi A(N);
  in(A);

  vvi G(N);

  rep(_, N - 1) {
    ll u, v;
    in(u, v);

    G[u].emplace_back(v), G[v].emplace_back(u);
  }

  PointSetRangeContourSum<ll, [](ll a, ll b) { return a + b; },
                          []() { return 0; }, ll>
      psrcs(G, A);

  while (Q--) {
    ll t;
    in(t);

    if (t == 0) {
      ll p, x;
      in(p, x);

      psrcs.set(p, psrcs.get(p) + x);
    } else {
      ll p, l, r;
      in(p, l, r);

      out(psrcs.prod(p, l, r));
    }
  }
}
