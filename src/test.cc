#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

/* Конструкторы */
TEST(S21MatrixTestConstructor, BasicConstructor) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.AccessorRows(), 3);
  EXPECT_EQ(matrix.AccessorCols(), 3);
}

TEST(S21MatrixTestConstructor, ParameterizedConstructor1) {
  S21Matrix matrix(2, 3);
  ASSERT_EQ(matrix.AccessorRows(), 2);
  ASSERT_EQ(matrix.AccessorCols(), 3);
}

TEST(S21MatrixTestConstructor, ParameterizedConstructor2) {
  S21Matrix matrix(5, 5);
  ASSERT_EQ(matrix.AccessorRows(), 5);
  ASSERT_EQ(matrix.AccessorCols(), 5);
}

TEST(S21MatrixTestConstructor, ParameterizedConstructor3) {
  S21Matrix matrix(12, 4);
  ASSERT_EQ(matrix.AccessorRows(), 12);
  ASSERT_EQ(matrix.AccessorCols(), 4);
}

TEST(S21MatrixTestConstructor, CopyConstructor1) {
  S21Matrix original(2, 3);
  original(0, 0) = 1.345;
  original(0, 1) = 2.256;
  original(0, 2) = 3.124;
  original(1, 0) = 4.434;
  original(1, 1) = 5.444442;
  original(1, 2) = 6.55298;

  S21Matrix copy(original);

  ASSERT_EQ(copy.AccessorRows(), 2);
  ASSERT_EQ(copy.AccessorCols(), 3);

  for (int row = 0; row < copy.AccessorRows(); row++) {
    for (int col = 0; col < copy.AccessorCols(); col++) {
      ASSERT_DOUBLE_EQ(copy(row, col), original(row, col));
    }
  }
}

TEST(S21MatrixTestConstructor, CopyConstructor2) {
  S21Matrix original(4, 4);
  original(0, 0) = 42.5;
  original(0, 1) = 123.456;
  original(0, 2) = 3.141596;
  original(0, 3) = 42.51;

  original(1, 0) = -7.2;
  original(1, 1) = 1.6180;
  original(1, 2) = 123.456;
  original(1, 3) = 3.14159;

  original(2, 0) = -7.2;
  original(2, 1) = 0.01;
  original(2, 2) = 0.01;
  original(2, 3) = 299792458;

  original(3, 0) = -7.2;
  original(3, 1) = 123.456;
  original(3, 2) = 299792458;
  original(3, 3) = 1.6180;

  S21Matrix copy(original);

  ASSERT_EQ(copy.AccessorRows(), 4);
  ASSERT_EQ(copy.AccessorCols(), 4);

  for (int row = 0; row < copy.AccessorRows(); row++) {
    for (int col = 0; col < copy.AccessorCols(); col++) {
      ASSERT_DOUBLE_EQ(copy(row, col), original(row, col));
    }
  }
}

TEST(S21MatrixTestConstructor, MoveConstructor) {
  S21Matrix original(2, 3);
  original(0, 0) = 31.0;
  original(0, 1) = 22.34;
  original(0, 2) = 3.03;
  original(1, 0) = 4.0211;
  original(1, 1) = 5.2053;
  original(1, 2) = 6.0008;

  S21Matrix copy(std::move(original));

  ASSERT_EQ(original.AccessorRows(), 0);
  ASSERT_EQ(original.AccessorCols(), 0);

  ASSERT_EQ(copy.AccessorRows(), 2);
  ASSERT_EQ(copy.AccessorCols(), 3);

  ASSERT_DOUBLE_EQ(copy(0, 0), 31.0);
  ASSERT_DOUBLE_EQ(copy(0, 1), 22.34);
  ASSERT_DOUBLE_EQ(copy(0, 2), 3.03);
  ASSERT_DOUBLE_EQ(copy(1, 0), 4.0211);
  ASSERT_DOUBLE_EQ(copy(1, 1), 5.2053);
  ASSERT_DOUBLE_EQ(copy(1, 2), 6.0008);
}

/* Основные операции */
TEST(S21MatrixTestOperations, EqMatrix1) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 67.02;
  matrix1(0, 1) = 32.044;
  matrix1(1, 0) = 113.02;
  matrix1(1, 1) = 42.03;

  matrix2(0, 0) = 67.02;
  matrix2(0, 1) = 32.044;
  matrix2(1, 0) = 113.02;
  matrix2(1, 1) = 42.03;

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));

  matrix2(1, 1) = 5.0;
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));

  matrix2.MutatorCols(3);
  matrix2(0, 2) = 3.0;
  matrix2(1, 2) = 6.0;

  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(S21MatrixTestOperations, SumMatrix1) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 0.5;
  matrix2(0, 1) = 1.5;
  matrix2(1, 0) = 2.5;
  matrix2(1, 1) = 3.5;

  matrix1.SumMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 1.5);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 3.5);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 5.5);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 7.5);
}

TEST(S21MatrixTestOperations, SumMatrix2) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  matrix1(0, 0) = -98.0;
  matrix1(0, 1) = -22.203;
  matrix1(0, 2) = 3.00004;
  matrix1(1, 0) = 41.012;
  matrix1(1, 1) = 53.03;
  matrix1(1, 2) = 61.03;
  matrix1(2, 0) = 7.0;
  matrix1(2, 1) = 8.022;
  matrix1(2, 2) = 9.1;

  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(0, 2) = 3.55553;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.2221111;
  matrix2(1, 2) = 6.0;
  matrix2(2, 0) = 7.5;
  matrix2(2, 1) = 8.0;
  matrix2(2, 2) = 9.0;

  matrix1.SumMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix1(0, 0), -97.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), -20.203);
  EXPECT_DOUBLE_EQ(matrix1(0, 2), 6.55557);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 45.012);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 58.2521111);
  EXPECT_DOUBLE_EQ(matrix1(1, 2), 67.03);
  EXPECT_DOUBLE_EQ(matrix1(2, 0), 14.5);
  EXPECT_DOUBLE_EQ(matrix1(2, 1), 16.022);
  EXPECT_DOUBLE_EQ(matrix1(2, 2), 18.1);
}

TEST(S21MatrixTestOperations, IncorrectSumMatrix) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);

  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::invalid_argument);
}

TEST(S21MatrixTestOperations, SubMatrix) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 21.18;
  matrix1(0, 1) = 12.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 45.56;

  matrix2(0, 0) = 0.51;
  matrix2(0, 1) = 1.5;
  matrix2(1, 0) = 2.5;
  matrix2(1, 1) = 3.5;

  matrix1.SubMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 20.67);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 10.5);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 0.5);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 42.06);

  matrix1.MutatorRows(1);
  matrix2.MutatorRows(1);

  matrix1.SubMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 20.16);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 9.0);
}

TEST(S21MatrixTestOperations, IncorrectSubMatrix) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);
  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}

TEST(S21MatrixTestOperations, MulNumber) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 11.00003;
  matrix(0, 1) = 2.1234567;
  matrix(0, 2) = 3.99;
  matrix(1, 0) = 4.12;
  matrix(1, 1) = 5.02;
  matrix(1, 2) = 6.011;

  double num = 2.1;
  matrix.MulNumber(num);

  ASSERT_DOUBLE_EQ(matrix(0, 0), 23.100063);
  ASSERT_DOUBLE_EQ(matrix(0, 1), 4.45925907);
  ASSERT_DOUBLE_EQ(matrix(0, 2), 8.379);
  ASSERT_DOUBLE_EQ(matrix(1, 0), 8.652);
  ASSERT_DOUBLE_EQ(matrix(1, 1), 10.542);
  ASSERT_DOUBLE_EQ(matrix(1, 2), 12.6231);

  matrix.MutatorRows(3);
  matrix(2, 0) = 41.2;
  matrix(2, 1) = 5.2;
  matrix(2, 2) = 6.1;

  matrix.MulNumber(num);

  ASSERT_DOUBLE_EQ(matrix(0, 0), 48.5101323);
  ASSERT_DOUBLE_EQ(matrix(0, 1), 9.364444047);
  ASSERT_DOUBLE_EQ(matrix(0, 2), 17.5959);
  ASSERT_DOUBLE_EQ(matrix(1, 0), 18.1692);
  ASSERT_DOUBLE_EQ(matrix(1, 1), 22.1382);
  ASSERT_DOUBLE_EQ(matrix(1, 2), 26.50851);
  ASSERT_DOUBLE_EQ(matrix(2, 0), 86.52);
  ASSERT_DOUBLE_EQ(matrix(2, 1), 10.92);
  ASSERT_DOUBLE_EQ(matrix(2, 2), 12.81);
}

TEST(S21MatrixTestOperations, MulMatrix) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 7.0;
  matrix2(0, 1) = 8.0;
  matrix2(1, 0) = 9.0;
  matrix2(1, 1) = 10.0;
  matrix2(2, 0) = 11.0;
  matrix2(2, 1) = 12.0;

  S21Matrix result(2, 2);
  result(0, 0) = 58.0;
  result(0, 1) = 64.0;
  result(1, 0) = 139.0;
  result(1, 1) = 154.0;

  matrix1.MulMatrix(matrix2);

  ASSERT_TRUE(matrix1.EqMatrix(result));
}

TEST(S21MatrixTestOperations, IncorrectMulMatrix) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix matrix2(2, 2);

  ASSERT_THROW(matrix1.MulMatrix(matrix2), std::invalid_argument);
}

TEST(S21MatrixTestOperations, Transpose) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 32.0;
  matrix(0, 2) = 3.04;
  matrix(1, 0) = 4.03331;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 16.01;

  S21Matrix transposedMatrix = matrix.Transpose();

  S21Matrix result(3, 2);
  result(0, 0) = 1.0;
  result(0, 1) = 4.03331;
  result(1, 0) = 32.0;
  result(1, 1) = 5.0;
  result(2, 0) = 3.04;
  result(2, 1) = 16.01;

  ASSERT_TRUE(transposedMatrix.EqMatrix(result));

  matrix.MutatorCols(2);
  S21Matrix transposedMatrix2 = matrix.Transpose();
  S21Matrix result2(2, 2);

  result2(0, 0) = 1.0;
  result2(0, 1) = 4.03331;
  result2(1, 0) = 32.0;
  result2(1, 1) = 5.0;

  ASSERT_TRUE(transposedMatrix2.EqMatrix(result2));
}

TEST(S21MatrixTestOperations, Determinant1) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 2.0;
  matrix1(0, 1) = 3.0;
  matrix1(1, 0) = 1.0;
  matrix1(1, 1) = 4.0;

  ASSERT_DOUBLE_EQ(matrix1.Determinant(), 5.0);
}

TEST(S21MatrixTestOperations, Determinant2) {
  S21Matrix matrix2(3, 3);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(0, 2) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;
  matrix2(1, 2) = 6.0;
  matrix2(2, 0) = 7.0;
  matrix2(2, 1) = 8.0;
  matrix2(2, 2) = 9.0;

  ASSERT_DOUBLE_EQ(matrix2.Determinant(), 0.0);
}

TEST(S21MatrixTestOperations, Determinant3) {
  S21Matrix matrix2(1, 1);
  matrix2(0, 0) = 5.0;
  ASSERT_DOUBLE_EQ(matrix2.Determinant(), 5.0);
}

TEST(S21MatrixTestOperations, IncorrectDeterminant) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;
  ASSERT_THROW(matrix1.Determinant(), std::invalid_argument);
}

TEST(S21MatrixTestOperations, CalcComplements1) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 2.0;
  matrix1(0, 1) = 3.0;
  matrix1(1, 0) = 1.0;
  matrix1(1, 1) = 4.0;

  S21Matrix complementsMatrix = matrix1.CalcComplements();

  ASSERT_DOUBLE_EQ(complementsMatrix(0, 0), 4.0);
  ASSERT_DOUBLE_EQ(complementsMatrix(0, 1), -1.0);
  ASSERT_DOUBLE_EQ(complementsMatrix(1, 0), -3.0);
  ASSERT_DOUBLE_EQ(complementsMatrix(1, 1), 2.0);
}

TEST(S21MatrixTestOperations, CalcComplements2) {
  S21Matrix matrix2(3, 3);
  matrix2(0, 0) = 0.0;
  matrix2(0, 1) = 1.0;
  matrix2(0, 2) = -0.75;
  matrix2(1, 0) = -0.5;
  matrix2(1, 1) = 3.0;
  matrix2(1, 2) = -2.0;
  matrix2(2, 0) = 0.5;
  matrix2(2, 1) = -3.5;
  matrix2(2, 2) = 2.5;

  S21Matrix complementsMatrix = matrix2.CalcComplements();

  ASSERT_DOUBLE_EQ(complementsMatrix(0, 0), 0.5);
  ASSERT_DOUBLE_EQ(complementsMatrix(0, 1), 0.25);
  ASSERT_DOUBLE_EQ(complementsMatrix(0, 2), 0.25);
  ASSERT_DOUBLE_EQ(complementsMatrix(1, 0), 0.125);
  ASSERT_DOUBLE_EQ(complementsMatrix(1, 1), 0.375);
  ASSERT_DOUBLE_EQ(complementsMatrix(1, 2), 0.5);
  ASSERT_DOUBLE_EQ(complementsMatrix(2, 0), 0.25);
  ASSERT_DOUBLE_EQ(complementsMatrix(2, 1), 0.375);
  ASSERT_DOUBLE_EQ(complementsMatrix(2, 2), 0.5);
}

TEST(S21MatrixTestOperations, CalcComplements4) {
  S21Matrix matrix(4, 4);
  matrix(0, 0) = 6.2838;
  matrix(0, 1) = 71.8;
  matrix(0, 2) = 23.0001;
  matrix(0, 3) = 0.123;
  matrix(1, 0) = 1.234;
  matrix(1, 1) = 5.678;
  matrix(1, 2) = 9.876;
  matrix(1, 3) = 3.1415;
  matrix(2, 0) = 2.718;
  matrix(2, 1) = 0.999;
  matrix(2, 2) = 0.001;
  matrix(2, 3) = 8.88;
  matrix(3, 0) = 11.11;
  matrix(3, 1) = 22.22;
  matrix(3, 2) = 33.33;
  matrix(3, 3) = 44.44;

  S21Matrix expectedComplements(4, 4);
  expectedComplements(0, 0) = -65.517353165000031;
  expectedComplements(0, 1) = 299.18303981499992;
  expectedComplements(0, 2) = -159.50089831499997;
  expectedComplements(0, 3) = -13.586507879999999;
  expectedComplements(1, 0) = 17726.260958846;
  expectedComplements(1, 1) = -2357.41620147;
  expectedComplements(1, 2) = 2543.8575021419983;
  expectedComplements(1, 3) = -5160.7502655829985;
  expectedComplements(2, 0) = 19792.522139840999;
  expectedComplements(2, 1) = -1632.9531400215003;
  expectedComplements(2, 2) = -288.89754957800005;
  expectedComplements(2, 3) = -3914.9808027660001;
  expectedComplements(3, 0) = -5207.8439867138504;
  expectedComplements(3, 1) = 492.11627737200001;
  expectedComplements(3, 2) = -121.65840441569992;
  expectedComplements(3, 3) = 1538.6731366214001;

  S21Matrix complementsMatrix = matrix.CalcComplements();

  for (int row = 0; row < complementsMatrix.AccessorRows(); row++) {
    for (int col = 0; col < complementsMatrix.AccessorCols(); col++) {
      EXPECT_DOUBLE_EQ(complementsMatrix(row, col),
                       expectedComplements(row, col));
    }
  }
}

TEST(S21MatrixTestOperations, IncorrectCalcComplements) {
  S21Matrix matrix(3, 2);
  ASSERT_THROW(matrix.CalcComplements(), std::invalid_argument);
}

TEST(S21MatrixTestOperations, InverseMatrix1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 2.0;

  S21Matrix inverseMatrix = matrix.InverseMatrix();

  ASSERT_DOUBLE_EQ(inverseMatrix(0, 0), 0.5);
}

TEST(S21MatrixTestOperations, InverseMatrix2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;

  S21Matrix inverseMatrix = matrix.InverseMatrix();

  ASSERT_DOUBLE_EQ(inverseMatrix(0, 0), -2.5);
  ASSERT_DOUBLE_EQ(inverseMatrix(0, 1), 1.5);
  ASSERT_DOUBLE_EQ(inverseMatrix(1, 0), 2.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(1, 1), -1.0);
}

TEST(S21MatrixTestOperations, InverseMatrix3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = -2.0;
  matrix(0, 2) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 1.0;
  matrix(1, 2) = -1.0;
  matrix(2, 0) = 3.0;
  matrix(2, 1) = 2.0;
  matrix(2, 2) = -2;

  S21Matrix inverseMatrix = matrix.InverseMatrix();

  ASSERT_DOUBLE_EQ(inverseMatrix(0, 0), 0.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(0, 1), 2.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(0, 2), -1.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(1, 0), -1.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(1, 1), 5.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(1, 2), -3.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(2, 0), -1.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(2, 1), 8.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(2, 2), -5.0);
}

TEST(S21MatrixTestOperations, InverseMatrix4) {
  S21Matrix matrix(4, 4);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = -2.0;
  matrix(0, 2) = 1.0;
  matrix(0, 3) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 1.0;
  matrix(1, 2) = -1.0;
  matrix(1, 3) = -1.0;
  matrix(2, 0) = 3.0;
  matrix(2, 1) = 2.0;
  matrix(2, 2) = -2;
  matrix(2, 3) = -2;
  matrix(3, 0) = 3.0;
  matrix(3, 1) = 2.0;
  matrix(3, 2) = -2;
  matrix(3, 3) = -4;

  S21Matrix inverseMatrix = matrix.InverseMatrix();

  ASSERT_DOUBLE_EQ(inverseMatrix(0, 0), 0.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(0, 1), 2.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(0, 2), -1.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(0, 3), 0.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(1, 0), -1.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(1, 1), 5.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(1, 2), -3.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(1, 3), 0.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(2, 0), -1.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(2, 1), 8.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(2, 2), -5.5);
  ASSERT_DOUBLE_EQ(inverseMatrix(2, 3), 0.5);
  ASSERT_DOUBLE_EQ(inverseMatrix(3, 0), 0.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(3, 1), 0.0);
  ASSERT_DOUBLE_EQ(inverseMatrix(3, 2), 0.5);
  ASSERT_DOUBLE_EQ(inverseMatrix(3, 3), -0.5);
}

TEST(S21MatrixTestOperations, InverseMatrix5) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(1, 0) = 1.0;
  matrix(1, 1) = 2.0;

  S21Matrix expectedInverse(2, 2);
  expectedInverse(0, 0) = 0.6666666;
  expectedInverse(0, 1) = -0.3333333;
  expectedInverse(1, 0) = -0.3333333;
  expectedInverse(1, 1) = 0.6666666;

  S21Matrix inverseMatrix = matrix.InverseMatrix();
  EXPECT_EQ(inverseMatrix, expectedInverse);
}

TEST(S21MatrixTestOperations, IncorrectInverseMatrix1) {
  S21Matrix matrix(3, 2);
  ASSERT_THROW(matrix.InverseMatrix(), std::invalid_argument);
}

TEST(S21MatrixTestOperations, IncorrectInverseMatrix2) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 0.0;

  ASSERT_THROW(matrix.InverseMatrix(), std::invalid_argument);
}

TEST(S21MatrixTestOperations, IncorrectInverseMatrix3) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 4.0;  // определитель равен нулю

  ASSERT_THROW(matrix.InverseMatrix(), std::invalid_argument);
}

/* Перегрузка операторов */
TEST(S21MatrixTestOperator, SumOperator) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 0.5;
  matrix2(0, 1) = 1.5;
  matrix2(1, 0) = 2.5;
  matrix2(1, 1) = 3.5;

  S21Matrix result = matrix1 + matrix2;

  EXPECT_DOUBLE_EQ(result(0, 0), 1.5);
  EXPECT_DOUBLE_EQ(result(0, 1), 3.5);
  EXPECT_DOUBLE_EQ(result(1, 0), 5.5);
  EXPECT_DOUBLE_EQ(result(1, 1), 7.5);
}

TEST(S21MatrixTestOperator, SubOperator) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.11;
  matrix1(0, 1) = 12.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 45.56;

  matrix2(0, 0) = 0.5;
  matrix2(0, 1) = 1.5;
  matrix2(1, 0) = 2.5;
  matrix2(1, 1) = 3.5;

  S21Matrix result = matrix1 - matrix2;

  EXPECT_DOUBLE_EQ(result(0, 0), 0.61);
  EXPECT_DOUBLE_EQ(result(0, 1), 10.5);
  EXPECT_DOUBLE_EQ(result(1, 0), 0.5);
  EXPECT_DOUBLE_EQ(result(1, 1), 42.06);
}

TEST(S21MatrixTestOperator, MulOperator) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 7.0;
  matrix2(0, 1) = 8.0;
  matrix2(1, 0) = 9.0;
  matrix2(1, 1) = 10.0;
  matrix2(2, 0) = 11.0;
  matrix2(2, 1) = 12.0;

  S21Matrix result = matrix1 * matrix2;

  EXPECT_DOUBLE_EQ(result(0, 0), 58.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 64.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 139.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 154.0);
}

TEST(S21MatrixTestOperator, MulOperatorNum) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  double num = 3.2;
  S21Matrix result = matrix1 * num;

  EXPECT_DOUBLE_EQ(result(0, 0), 3.2);
  EXPECT_DOUBLE_EQ(result(0, 1), 6.4);
  EXPECT_DOUBLE_EQ(result(1, 0), 9.6);
  EXPECT_DOUBLE_EQ(result(1, 1), 12.8);
}

TEST(S21MatrixTestOperator, EqualityOperator) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 11.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.065;
  matrix1(1, 1) = 4.0001;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 11.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.065;
  matrix2(1, 1) = 4.0001;

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(S21MatrixTestOperator, AssignmentOperator) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 12.0;
  matrix1(0, 1) = 2.032;
  matrix1(1, 0) = 312.0;
  matrix1(1, 1) = 4.033;

  S21Matrix matrix2(3, 3);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(0, 2) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;
  matrix2(1, 2) = 8.0;
  matrix2(2, 0) = 7.0;
  matrix2(2, 1) = 8.0;
  matrix2(2, 2) = 8.0;

  matrix1 = matrix2;

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(S21MatrixTestOperator, OperatorTransfer) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 12.0;
  matrix1(0, 1) = 2.032;
  matrix1(0, 2) = 2.12;
  matrix1(1, 0) = 312.0;
  matrix1(1, 1) = 4.033;
  matrix1(1, 2) = 4.033;
  matrix1(2, 0) = 312.0;
  matrix1(2, 1) = 45.3;
  matrix1(2, 2) = 4.3;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  matrix1 = matrix2;

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(S21MatrixTestOperator, SumAssignmentOperator) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 0.5;
  matrix2(0, 1) = 1.5;
  matrix2(1, 0) = 2.5;
  matrix2(1, 1) = 3.5;

  matrix1 += matrix2;

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 1.5);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 3.5);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 5.5);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 7.5);
}

TEST(S21MatrixTestOperator, SubAssignmentOperator) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.11;
  matrix1(0, 1) = 12.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 45.56;

  matrix2(0, 0) = 0.5;
  matrix2(0, 1) = 1.5;
  matrix2(1, 0) = 2.5;
  matrix2(1, 1) = 3.5;

  matrix1 -= matrix2;

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 0.61);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 10.5);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 0.5);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 42.06);
}

TEST(S21MatrixTestOperator, MulAssignmentOperator) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 7.0;
  matrix2(0, 1) = 8.0;
  matrix2(1, 0) = 9.0;
  matrix2(1, 1) = 10.0;
  matrix2(2, 0) = 11.0;
  matrix2(2, 1) = 12.0;

  matrix1 *= matrix2;

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 58.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 64.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 139.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 154.0);
}

TEST(S21MatrixTestOperator, MulNumAssignmentOperator) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix1 *= 3.2;

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 3.2);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 6.4);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 9.6);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 12.8);
}

TEST(S21MatrixTestOperator, IndexingOperator) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  double &element = matrix(0, 1);

  EXPECT_EQ(element, 2.0);
  element = 5.0;
  EXPECT_EQ(matrix(0, 1), 5.0);
}

/* Доп функции */
TEST(S21MatrixTestDop, IncorrectGenerateMinorMatrix) {
  S21Matrix matrix(3, 3);
  ASSERT_THROW(matrix.GenerateMinorMatrix(3, 3), std::out_of_range);
}

TEST(S21MatrixTestDop, IncorrectIndexing) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  EXPECT_THROW(matrix(2, 2), std::out_of_range);
  EXPECT_THROW(matrix(-1, 0), std::out_of_range);
  EXPECT_THROW(matrix(0, 3), std::out_of_range);
}

TEST(S21MatrixTestDop, IncorrectGetElement) {
  S21Matrix matrix(3, 3);
  ASSERT_THROW(matrix(4, 3), std::out_of_range);
}

TEST(S21MatrixTestDop, IncorrectMutatorElement) {
  S21Matrix matrix(3, 3);
  ASSERT_THROW(matrix(3, 3) = 42.0, std::out_of_range);
}

TEST(S21MatrixTestDop, IncorrectRowsCols) {
  EXPECT_THROW(S21Matrix matrix(-1, 2), std::invalid_argument);
  EXPECT_THROW(S21Matrix matrix(2, 0), std::invalid_argument);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}