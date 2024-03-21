#include "s21_matrix_oop.h"

/* Конструкторы и деструктор */
S21Matrix::S21Matrix() : rows_(3), cols_(3) { CreateMatrix(rows_, cols_); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  CreateMatrix(rows_, cols_);
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  CreateMatrix(other.rows_, other.cols_);
  CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.ResetMatrix();
}

S21Matrix::~S21Matrix() { DeleteMatrix(); }

/* Accessor и mutator */
int S21Matrix::AccessorRows() const { return rows_; }

int S21Matrix::AccessorCols() const { return cols_; }

void S21Matrix::MutatorRows(int new_rows) {
  if (new_rows < rows_) {
    S21Matrix new_matrix(new_rows, cols_);
    for (int row = 0; row < new_rows; row++) {
      for (int col = 0; col < cols_; col++) {
        new_matrix.matrix_[row][col] = matrix_[row][col];
      }
    }
    *this = new_matrix;
    new_matrix.DeleteMatrix();
  } else if (new_rows > rows_) {
    S21Matrix new_matrix(new_rows, cols_);
    for (int row = 0; row < rows_; row++) {
      for (int col = 0; col < cols_; col++) {
        new_matrix.matrix_[row][col] = matrix_[row][col];
      }
    }
    for (int row = rows_; row < new_rows; row++) {
      for (int col = 0; col < cols_; col++) {
        new_matrix.matrix_[row][col] = 0;
      }
    }
    *this = new_matrix;
    new_matrix.DeleteMatrix();
  }
}

void S21Matrix::MutatorCols(int new_cols) {
  if (new_cols < cols_) {
    S21Matrix new_matrix(rows_, new_cols);
    for (int row = 0; row < rows_; row++) {
      for (int col = 0; col < new_cols; col++) {
        new_matrix.matrix_[row][col] = matrix_[row][col];
      }
    }
    *this = new_matrix;
    new_matrix.DeleteMatrix();
  } else if (new_cols > cols_) {
    S21Matrix new_matrix(rows_, new_cols);
    for (int row = 0; row < rows_; row++) {
      for (int col = 0; col < cols_; col++) {
        new_matrix.matrix_[row][col] = matrix_[row][col];
      }
    }
    for (int col = cols_; col < new_cols; col++) {
      for (int row = 0; row < rows_; row++) {
        new_matrix.matrix_[row][col] = 0;
      }
    }
    *this = new_matrix;
    new_matrix.DeleteMatrix();
  }
}

/* Основные операции */
bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool equality = true;
  if (CheckEqWithOther(other)) {
    for (int row = 0; row < rows_; row++) {
      for (int col = 0; col < cols_; col++) {
        if (fabs(matrix_[row][col] - other.matrix_[row][col]) > s21_EPSILON) {
          equality = false;
        }
      }
    }
  } else
    equality = false;
  return equality;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (!CheckEqWithOther(other)) {
    throw std::invalid_argument("Различная размерность матриц");
  }
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      matrix_[row][col] += other.matrix_[row][col];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (!CheckEqWithOther(other)) {
    throw std::invalid_argument("Различная размерность матриц");
  }
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      matrix_[row][col] -= other.matrix_[row][col];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      matrix_[row][col] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Число столбцов первой матрицы должно быть равно числу строк второй "
        "матрицы");
  }
  S21Matrix result_mul_matrix(rows_, other.cols_);
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < other.cols_; col++) {
      for (int dop_index = 0; dop_index < cols_; dop_index++) {
        result_mul_matrix.matrix_[row][col] +=
            matrix_[row][dop_index] * other.matrix_[dop_index][col];
      }
    }
  }
  *this = result_mul_matrix;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result_transpose(cols_, rows_);
  for (int row = 0; row < cols_; row++) {
    for (int col = 0; col < rows_; col++) {
      result_transpose.matrix_[row][col] = matrix_[col][row];
    }
  }
  return result_transpose;
}

double S21Matrix::Determinant() const {
  if (!CheckEqRowsCols()) {
    throw std::invalid_argument("Матрица должна быть квадратной");
  }
  int sign = 1;
  double determinant = 0.0;
  if (rows_ == 1) {  // det(A) = a
    determinant = matrix_[0][0];
  } else if (rows_ == 2) {  // det(A) = a00*a11 - a01*a10
    determinant = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {  // det(A) = a00 * det(minor00) - a10 * det(minor10) + a20 *
    // det(minor20) - ... + (-1)^(n+1) * an0 * det(minor n0)
    for (int row = 0; row < rows_; row++) {
      S21Matrix minor_matrix = GenerateMinorMatrix(
          row, 0);  // Разложение определителя по первому столбцу
      determinant += sign * matrix_[row][0] * minor_matrix.Determinant();
      sign = -sign;
    }
  }
  return determinant;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (!CheckEqRowsCols()) {
    throw std::invalid_argument("Матрица должна быть квадратной");
  }
  S21Matrix result_сalc_сomplements(rows_, cols_);
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {  // значение минора каждого элемента
      // матрицы умноженное на -1^(i+j)
      S21Matrix minor_matrix = GenerateMinorMatrix(row, col);
      double determinant_minor_matrix = minor_matrix.Determinant();
      int sign = (row + col) % 2 == 0 ? 1 : -1;
      result_сalc_сomplements(row, col) = sign * determinant_minor_matrix;
    }
  }
  return result_сalc_сomplements;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Матрица должна быть квадратной");
  }
  S21Matrix result_inverse_matrix;
  if (rows_ == 1) {
    if (fabs(matrix_[0][0]) < s21_EPSILON) {
      throw std::invalid_argument(
          "Обратной матрицы не существует (определитель равен нулю)");
    }
    matrix_[0][0] = 1.0 / matrix_[0][0];
    result_inverse_matrix = *this;
  } else {  // 1/|A| * M^T. (|A| - определитель, M^T. - транспонированная
    // матрица алгебраических дополнений)
    double determinant = Determinant();
    if (fabs(determinant) < s21_EPSILON) {
      throw std::invalid_argument(
          "Обратной матрицы не существует (определитель равен нулю)");
    }
    S21Matrix matrix_calc_complements = CalcComplements();
    result_inverse_matrix = matrix_calc_complements.Transpose();
    result_inverse_matrix.MulNumber(1.0 / determinant);
  }
  return result_inverse_matrix;
}

/* Перегрузка операторов */
S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    DeleteMatrix();
    CreateMatrix(other.rows_, other.cols_);
    CopyMatrix(other);
  }
  return *this;
}

void S21Matrix::operator+=(const S21Matrix &other) { SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix &other) { SubMatrix(other); }

void S21Matrix::operator*=(const S21Matrix &other) { MulMatrix(other); }

void S21Matrix::operator*=(const double num) { MulNumber(num); }

double &S21Matrix::operator()(int row, int col) {
  if (!CheckValidIndex(row, col)) {
    throw std::out_of_range("Индекс за пределами матрицы");
  }
  return matrix_[row][col];
}

/* Доп функции */
void S21Matrix::CreateMatrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument(
        "Количество столбцов и строк в матрице не может быть меньше 1");
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double *[rows_];
  for (int row = 0; row < rows_; row++) {
    matrix_[row] = new double[cols_];
    for (int col = 0; col < cols_; col++) {
      matrix_[row][col] = 0.0;
    }
  }
}

void S21Matrix::CopyMatrix(const S21Matrix &other) {
  for (int row = 0; row < rows_; row++) {
    for (int col = 0; col < cols_; col++) {
      matrix_[row][col] = other.matrix_[row][col];
    }
  }
}

void S21Matrix::DeleteMatrix() {
  if (matrix_) {
    for (int row = 0; row < rows_; row++) {
      delete[] matrix_[row];
    }
    delete[] matrix_;
  }
  ResetMatrix();
}

void S21Matrix::ResetMatrix() {
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

bool S21Matrix::CheckValidIndex(int row, int col) const {
  return row >= 0 && row < rows_ && col >= 0 && col < cols_;
}

bool S21Matrix::CheckEqWithOther(const S21Matrix &other) const {
  return rows_ == other.rows_ && cols_ == other.cols_;
}

bool S21Matrix::CheckEqRowsCols() const { return rows_ == cols_; }

S21Matrix S21Matrix::GenerateMinorMatrix(int row, int col) const {
  if (!CheckValidIndex(row, col)) {
    throw std::out_of_range("Недопустимые индексы строки и/или столбца");
  }
  S21Matrix minor_matrix(rows_ - 1, cols_ - 1);
  int minor_row = 0;
  int minor_col = 0;
  for (int current_row = 0; current_row < rows_; current_row++) {
    for (int current_col = 0; current_col < cols_; current_col++) {
      if (current_row != row && current_col != col) {
        minor_matrix(minor_row, minor_col) = matrix_[current_row][current_col];
        minor_col++;
        if (minor_col == minor_matrix.cols_) {  // пока столбцы не закончились
          minor_row++;
          minor_col = 0;
        }
      }
    }
  }
  return minor_matrix;
}