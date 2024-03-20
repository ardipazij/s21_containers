#include "matrix_oop.h"

namespace s21 {
S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix();
  CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix();
  CopyMatrix(other);
  other.RemoveMatrix();
}

S21Matrix::~S21Matrix() { RemoveMatrix(); }

void S21Matrix::CreateMatrix() {
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::RemoveMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      if (matrix_[i] != nullptr) {
        delete[] matrix_[i];
      }
    }
    if (matrix_ != nullptr) {
      delete[] matrix_;
      matrix_ = nullptr;
    }
  }
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::CopyMatrix(const S21Matrix &other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::set_rows(int new_rows) { SetDimensions(new_rows, cols_); }

void S21Matrix::set_cols(int new_cols) { SetDimensions(rows_, new_cols); }

int S21Matrix::get_rows() const noexcept { return rows_; }

int S21Matrix::get_cols() const noexcept { return cols_; }

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (*this == other) return *this;
  RemoveMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  CreateMatrix();
  CopyMatrix(other);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) const noexcept {
  return EqMatrix(other);
}

double &S21Matrix::operator()(int row, int col) { return matrix_[row][col]; }

bool S21Matrix::EqMatrix(const S21Matrix &other) const noexcept {
  bool result = true;
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    result = false;
  }
  for (int i = 0; i < other.get_rows(); i++) {
    for (int j = 0; j < other.get_cols(); j++) {
      if (result && fabs(this->matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
        result = false;
      }
    }
  }
  return result;
}

void S21Matrix::SetDimensions(int rows, int cols) {
  int rows_limit = std::min(rows_, rows);
  int cols_limit = std::min(cols_, cols);
  S21Matrix temp(rows, cols);
  for (int i = 0; i < rows_limit; i++) {
    for (int j = 0; j < cols_limit; j++) {
      temp.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = temp;
}

}  // namespace s21
