#pragma once
#include <bits/stdc++.h>

template <class T, auto add, auto op, auto e, auto id> struct Matrix {
  static_assert(std::is_invocable_r_v<T, decltype(op), T, T>,
                "op must work as T(T, T)");

  static_assert(std::is_invocable_r_v<T, decltype(add), T, T>,
                "add must work as T(T, T)");

  static_assert(std::is_invocable_r_v<T, decltype(e)>, "e must work as T()");

  static_assert(std::is_invocable_r_v<T, decltype(id)>, "id must work as T()");

  std::vector<std::vector<T>> A;

  Matrix() = default;
  Matrix(int n) : A(n, std::vector<T>(n, e())) {}
  Matrix(int n, int m) : A(n, std::vector<T>(m, e())) {}
  Matrix(std::vector<std::vector<T>> A) : A(A) {}

  const inline std::vector<T> &operator[](int k) const { return A[k]; };

  inline std::vector<T> &operator[](int k) { return A[k]; };

  static Matrix<T, add, op, e, id> I(int n) {
    Matrix<T, add, op, e, id> mat(n);
    for (int i = 0; i < n; i++)
      mat[i][i] = id();

    return (mat);
  }

  Matrix &operator*=(const Matrix<T, add, op, e, id> &B) {
    int n = A.size();
    int m = B.A[0].size();
    int p = A[0].size();

    assert(n == B.A.size());
    std::vector<std::vector<T>> C(n, std::vector<T>(m, e()));

    for (int i = 0; i < n; i++) {
      for (int k = 0; k < p; k++) {
        for (int j = 0; j < m; j++) {
          C[i][j] = add(C[i][j], op((*this)[i][k], B[k][j]));
        }
      }
    }

    A.swap(C);

    return (*this);
  }

  Matrix &operator^=(long long k) {
    auto B = Matrix<T, add, op, e, id>::I(A.size());

    while (k > 0) {
      if (k & 1) {
        B *= *this;
      }

      *this *= *this;
      k >>= 1LL;
    }

    A.swap(B.A);

    return (*this);
  }

  Matrix operator*(const Matrix &B) const { return (Matrix(*this) *= B); }
  Matrix operator^(const long long k) const { return (Matrix(*this) ^= k); }
};
