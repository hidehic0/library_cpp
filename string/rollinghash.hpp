#pragma once
#include <vector>

/**
 * @class RollingHash
 * stringを渡すのではなく文字をintに変換したvectorを使う事
 * @brief rollinghash
 * @author hidehic0
 */
template <typename CT = int, class HT = long long> class RollingHash {
private:
  std::vector<HT> hash, pow;
  HT mod;

public:
  RollingHash(std::vector<CT> s, HT base, HT mod) {
    assert(base > 0);
    assert(mod > 0);
    this->mod = mod;
    hash.resize(s.size() + 1, 0);
    pow.resize(s.size() + 1, 1);

    for (int i = 0; i < s.size(); i++)
      hash[i + 1] = (hash[i] * base + s[i]) % mod;
    for (int i = 1; i <= s.size(); i++)
      pow[i] = (pow[i - 1] * base) % mod;
  }

  //! [left,right)のhash値を取得する
  HT gethash(int left, int right) {
    return ((hash[right] - ((hash[left] * pow[right - left]) % mod)) % mod +
            mod) %
           mod;
  }
};
