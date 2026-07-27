#pragma once
#include <bits/stdc++.h>

template <class T> using VC = std::vector<T>;
template <class T>
using rpriority_queue = std::priority_queue<T, VC<T>, std::greater<T>>;
using ll = long long;
using ld = long double;
using u64 = uint64_t;
using u32 = uint32_t;

using pii = std::pair<ll, ll>;

using vi = VC<ll>;
using vvi = VC<vi>;
using vvvi = VC<vvi>;
using vb = VC<bool>;
using vvb = VC<vb>;
using vf = VC<ld>;
using vvf = VC<vf>;
using vpii = VC<pii>;
using vvpii = VC<vpii>;
using si = std::set<ll>;
using spii = std::set<pii>;
using mii = std::map<ll, ll>;
using str = std::string;
const std::string upperlist = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string lowerlist = "abcdefghijklmnopqrstuvwxyz";

#define mp make_pair

constexpr int MOD998 = 998244353;
