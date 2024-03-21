#ifndef CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H
#define CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>

class S21Matrix {
 public:
  const double s21_EPSILON = 1e-7;
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);

  /* перегруженные операторы */
  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix operator*(double num) const;
  bool operator==(const S21Matrix &other) const;
  S21Matrix &operator=(const S21Matrix &other);
  void operator+=(const S21Matrix &other);
  void operator-=(const S21Matrix &other);
  void operator*=(const S21Matrix &other);
  void operator*=(double num);
  double &operator()(int row, int col);

  ~S21Matrix();

  /* accessor и mutator */
  int AccessorRows() const;  // для получения значений без изменения
  int AccessorCols() const;
  void MutatorRows(int newRows);  // для изменения значений
  void MutatorCols(int new_cols);

  /* основные операции */
  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;
  S21Matrix GenerateMinorMatrix(int row, int col) const;

 private:
  int rows_, cols_;
  double **matrix_;

  /* доп функции */
  void CreateMatrix(int rows, int cols);
  void CopyMatrix(const S21Matrix &other);
  void DeleteMatrix();
  void ResetMatrix();
  bool CheckValidIndex(int row, int col) const;
  bool CheckEqWithOther(const S21Matrix &other) const;
  bool CheckEqRowsCols() const;
};

#endif  // CPP1_S21_MATRIXPLUS_SRC_S21_MATRIX_OOP_H