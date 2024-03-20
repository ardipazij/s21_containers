#ifndef __S21MATRIX_OOP_H__
#define __S21MATRIX_OOP_H__

#include <cmath>
#include <iostream>

namespace s21 {
class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  void set_rows(int new_rows);
  void set_cols(int new_cols);

  int get_rows() const noexcept;
  int get_cols() const noexcept;

  S21Matrix& operator=(const S21Matrix& other);
  bool operator==(const S21Matrix& other) const noexcept;

  double& operator()(int row, int col);

  bool EqMatrix(const S21Matrix& other) const noexcept;

 private:
  int rows_, cols_;
  double** matrix_;

  void SetDimensions(int rows, int cols);
  void CreateMatrix();
  void RemoveMatrix();
  void CopyMatrix(const S21Matrix& other);
};
}  // namespace s21

#endif  // __S21MATRIX_OOP_H__
