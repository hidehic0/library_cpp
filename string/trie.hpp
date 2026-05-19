#pragma once
#include <bits/stdc++.h>

/*!
 * @struct Trie
 * Trie木構造体 使う文字は[margin,margin+char_size)の範囲でないといけない
 * @note
 * 参考: https://nyaannyaan.github.io/library/string/trie.hpp
 */
template <size_t char_size = 26, char margin = 'a'> struct Trie {
  struct Node {
    std::array<int, char_size> nxt;
    std::vector<int> accepts;

    char key;
    int child_accepts = 0;

    Node(char c) : key(c) { fill(nxt.begin(), nxt.end(), -1); };
  };

  std::vector<Node> nodes;

  Trie(char root = '$') { nodes.emplace_back(root); }

  inline int get_next(int i, int j) { return nodes[i].nxt[j]; }

  void add(std::string S, int id = -1) {
    int cur = 0;

    for (char s : S) {
      int k = s - margin;

      assert(0 <= k && k < char_size);

      if (~get_next(cur, k)) {
        cur = get_next(cur, k);
        continue;
      }

      int nxt = nodes.size();

      nodes[cur].nxt[k] = nxt;
      nodes.emplace_back(s);
      nodes[nxt].child_accepts++;

      cur = nxt;
    }

    nodes[cur].accepts.emplace_back(id == -1 ? nodes[0].child_accepts++ : id);
  }

  int size() { return nodes.size(); }
};

/*!
 * @file string/trie.hpp
 * @brief Trie Tree
 * @auther hidehic0
 */
