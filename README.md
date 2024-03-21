# s21_matrix+

Реализация библиотеки s21_matrix_oop.h

![s21_matrix](/images/logo.png)

## Содержание

1. [Краткое описание](#Краткое-описание) \
    1.1. [Операции над матрицами](#Операции-над-матрицами)
2. [Реализация функции библиотеки s21_matrix_oop.h](#Реализация-функции-библиотеки-s21-matrix-ooph) 
3. [Установка для пользователя](#Установка-для-пользователя) 

## Краткое описание

В данном проекте реализована библиотека для работы с матрицами, но на этот раз, используя объектно-ориентированный подход. Объектно-ориентированный подход позволяет реализовать библиотеку для работы с матрицами в виде отдельного класса, над объектами которого определены операции, представленные как методами, так и стандартными операторами +, -, * и т.д.

### Операции над матрицами

Ниже представлено краткое описание операций над матрицами, которые реализованы в разрабатываемой библиотеке. 

| Операция    | Описание   | Исключительные ситуации |
| ----------- | ----------- | ----------- |
| `bool EqMatrix(const S21Matrix& other)` | Проверяет матрицы на равенство между собой |  |
| `void SumMatrix(const S21Matrix& other)` | Прибавляет вторую матрицы к текущей | различная размерность матриц |
| `void SubMatrix(const S21Matrix& other)` | Вычитает из текущей матрицы другую | различная размерность матриц |
| `void MulNumber(const double num)` | Умножает текущую матрицу на число |  |
| `void MulMatrix(const S21Matrix& other)` | Умножает текущую матрицу на вторую | число столбцов первой матрицы не равно числу строк второй матрицы |
| `S21Matrix Transpose()` | Создает новую транспонированную матрицу из текущей и возвращает ее |  |
| `S21Matrix CalcComplements()` | Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее | матрица не является квадратной |
| `double Determinant()` | Вычисляет и возвращает определитель текущей матрицы | матрица не является квадратной |
| `S21Matrix InverseMatrix()` | Вычисляет и возвращает обратную матрицу | определитель матрицы равен 0 |

Помимо реализации данных операций, также реализованы конструкторы и деструкторы:

| Метод    | Описание   |
| ----------- | ----------- |
| `S21Matrix()` | Базовый конструктор, инициализирующий матрицу некоторой заранее заданной размерностью |  
| `S21Matrix(int rows, int cols)` | Параметризированный конструктор с количеством строк и столбцов | 
| `S21Matrix(const S21Matrix& other)` | Конструктор копирования |
| `S21Matrix(S21Matrix&& other)` | Конструктор переноса |
| `~S21Matrix()` | Деструктор |

А также перегружены следующие операторы, частично соответствующие операциям выше:

| Оператор    | Описание   | Исключительные ситуации |
| ----------- | ----------- | ----------- |
| `+`      | Сложение двух матриц  | различная размерность матриц |
| `-`   | Вычитание одной матрицы из другой | различная размерность матриц |
| `*`  | Умножение матриц и умножение матрицы на число | число столбцов первой матрицы не равно числу строк второй матрицы |
| `==`  | Проверка на равенство матриц (`EqMatrix`) | |
| `=`  | Присвоение матрице значений другой матрицы | |
| `+=`  | Присвоение сложения (`SumMatrix`)   | различная размерность матриц |
| `-=`  | Присвоение разности (`SubMatrix`) | различная размерность матриц |
| `*=`  | Присвоение умножения (`MulMatrix`/`MulNumber`) | число столбцов первой матрицы не равно числу строк второй матрицы |
| `(int i, int j)`  | Индексация по элементам матрицы (строка, колонка) | индекс за пределами матрицы |

## Реализация функции библиотеки s21_matrix_oop.h

- Программа разработана на языке C++ стандарта C++17 с использованием компилятора gcc
- Матрица реализована в виде класса `S21Matrix`
- Хранятся только приватные поля `matrix_`, `rows_` и `cols_`
- Реализован доступ к приватным полям `rows_` и `cols_` через accessor и mutator. При увеличении размера - матрица дополняется нулевыми элементами, при уменьшении - лишнее просто отбрасывается
- Решение оформлено как статическая библиотека (с заголовочным файлом s21_matrix_oop.h)
- Реализованы операции, описанные [выше](#операции-над-матрицами)
- Перегружены операторы в соответствии с таблицой в разделе [выше](#операции-над-матрицами).
- Подготовлено полное покрытие unit-тестами функций библиотеки c помощью библиотеки GTest
- Предусмотрен Makefile для сборки библиотеки и тестов (с целями all, clean, test, s21_matrix_oop.a)

## Установка для пользователя

Чтобы пользоваться программой, необходимо зайти в папку src и с помощью команд выполнить необходимые действия:

`make all` - Эта цель сначала очищает все исполняемые файлы, чтобы в дальнейшем создать новые, запускает цель `s21_matrix_oop.a` и цель `test`

`make test` - Эта цель компилирует и запускает тестовый файл test.c, который,содержит набор тестов для библиотеки s21_matrix_oop_a

`make s21_matrix_oop.a` - Эта команда создает статическую библиотеку из исходных файлов

`make gcov_report` - Эта команда создает отчет о том, как много кода покрыто тестами. Она компилирует файлы с опцией для сбора данных о покрытии кода. Затем она создает отчет, который вы можете просмотреть в веб-браузере.

`make check_style` - Эта команда проверяет на googlestyle

`make clean` - Эта команда удаляет временные файлы, созданные в процессе сборки программы.

`make clean_test` - Эта команда удаляет временные файлы после выполнения тестов.
