#pragma once
#include <chrono>
#include <cstdint>
#include <optional>

struct Xorshift32 {
  std::uint32_t prv;

  Xorshift32(std::optional<uint32_t> seed = std::nullopt) {
    if (seed) {
      prv = seed.value();
    } else {
      auto now = std::chrono::system_clock::now();
      prv = now.time_since_epoch().count();
    }
  }

  std::uint32_t rand() {
    uint32_t x = prv;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;

    return prv = x;
  }

  // [l,r)の乱数を取得する
  std::uint32_t randrange(int l, int r) { return rand() % (r - l) + l; }
  double randouble() { return (double)rand() / 4294967296.0; }
};

struct Xorshift64 {
  std::uint64_t prv;

  Xorshift64(std::optional<uint64_t> seed = std::nullopt) {
    if (seed) {
      prv = seed.value();
    } else {
      auto now = std::chrono::system_clock::now();
      prv = now.time_since_epoch().count();
    }
  }

  std::uint64_t rand() {
    uint64_t x = prv;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;

    return prv = x;
  }

  // [l,r)の乱数を取得する
  std::uint64_t randrange(long long l, long long r) {
    return rand() % (r - l) + l;
  }

  double randouble() { return (double)(rand() >> 11) * (1.0 / (1ULL << 53)); }
};
