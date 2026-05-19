#pragma once
#include "trie.hpp"
#include <bits/stdc++.h>
#include <queue>

/*!
 * @struct AhoCorasick
 * string/trie.hppのTrie構造体を継承している
 * trieの各ノードに対して、存在しない子ノードから、子を連結した文字列のprefixの中で長さが最大のノードに繋ぐオートマトンを作成する
 * テンプレート引数のheavyをtrueにすると、各ノードに対してマッチする文字列の列を管理できる
 * falseにすると個数のみ
 * build関数でオートマトンを作成する O(S)
 */

template <size_t char_size = 26, int margin = 'a', bool heavy = true>
struct AhoCorasick : Trie<char_size + 1, margin> {
  using TRIE = Trie<char_size + 1, margin>;
  using TRIE::get_next;

  std::vector<int> correct;

  /*!
   * @fn
   * trieの各ノードに対して、存在しない子ノードから、子を連結した文字列のprefixの中で長さが最大のノードに繋ぐオートマトンを作成する
   * 計算量は追加された文字列の長さの和をSとしてO(S)
   */
  void build() {
    correct.resize(this->nodes.size());

    for (int i = 0; i < this->size(); i++) {
      correct[i] = this->nodes[i].accepts.size();
    }

    std::queue<int> que;

    for (int k = 0; k < char_size; k++) {
      if (~get_next(0, k)) {
        this->nodes[get_next(0, k)].nxt[char_size] = 0;
        que.emplace(get_next(0, k));
      } else {
        this->nodes[0].nxt[k] = 0;
      }
    }

    while (!que.empty()) {
      auto &x = this->nodes[que.front()];
      int fail = x.nxt[char_size];

      correct[que.front()] += correct[fail];

      que.pop();

      for (int k = 0; k < char_size; k++) {
        int &nxt = x.nxt[k];

        if (nxt < 0) {
          nxt = get_next(fail, k);
          continue;
        }

        que.emplace(nxt);
        this->nodes[nxt].nxt[char_size] = get_next(fail, k);

        if (heavy) {
          auto &accept_x = this->nodes[nxt].accepts;
          auto &accept_y = this->nodes[get_next(fail, k)].accepts;

          std::vector<int> accept;

          set_union(accept_x.begin(), accept_x.end(), accept_y.begin(),
                    accept_y.end(), std::back_inserter(accept));

          accept_x = accept;
        }
      }
    }
  }

  std::pair<int, int> move(const char &c, int now = 0) {
    now = get_next(now, c - margin);

    return {correct[now], now};
  }
  std::pair<int, int> move(const std::string &s, int now = 0) {
    int res = 0;

    for (auto &c : s) {
      auto [cnt, nxt] = move(c, now);
      res += cnt, now = nxt;
    }

    return {res, now};
  }
};

/*!
 * @file string/aho-corasick.hpp
 * @brief AhoCorasick法
 * @auther hidehic0
 * @date 2026-05-19
 */
