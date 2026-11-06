#pragma once
#include "Generator.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <stdexcept>

namespace miit::algebra
{
	/**
	 * @brief Шаблонный класс двумерной матрицы
	 * @tparam T Тип элементов матрицы (по умолчанию int)
	 */
	template <typename T = int>
	class Matrix
	{
	private:
		/**
		 * @brief Количество строк матрицы
		 */
		int rows;

		/**
		 * @brief Количество столбцов матрицы
		 */
		int cols;

		/**
		 * @brief Двумерный массив данных матрицы
		 */
		std::vector<std::vector<T>> data;

	public:
		/**
		 * @brief Конструктор по умолчанию (создает пустую матрицу 0x0)
		 */
		Matrix()
			: rows(0), cols(0)
		{
		}

		/**
		 * @brief Конструктор матрицы заданного размера, заполненной значениями по умолчанию
		 * @param r Количество строк матрицы
		 * @param c Количество столбцов матрицы
		 * @throw std::invalid_argument Если r <= 0 или c <= 0
		 */
		Matrix(const int r, const int c)
		{
			if (r <= 0 || c <= 0)
			{
				throw std::invalid_argument("Размеры матрицы должны быть больше нуля");
			}
			rows = r;
			cols = c;
			data.resize(r, std::vector<T>(c, T{}));
		}

		/**
		 * @brief Конструктор копирования
		 * @param other Матрица для копирования
		 */
		Matrix(const Matrix& other) = default;

		/**
		 * @brief Конструктор перемещения
		 * @param other Перемещаемая матрица
		 */
		Matrix(Matrix&& other) noexcept = default;

		/**
		 * @brief Деструктор матрицы
		 */
		~Matrix() = default;

		/**
		 * @brief Оператор копирующего присваивания
		 * @param other Матрица для копирования
		 * @return Ссылка на текущий объект матрицы
		 */
		Matrix& operator=(const Matrix& other) = default;

		/**
		 * @brief Оператор перемещающего присваивания
		 * @param other Перемещаемая матрица
		 * @return Ссылка на текущий объект матрицы
		 */
		Matrix& operator=(Matrix&& other) noexcept = default;

		/**
		 * @brief Оператор проверки двух матриц на поэлементное равенство
		 * @param other Матрица для сравнения
		 * @return true, если размеры и все соответствующие элементы совпадают, иначе false
		 */
		bool operator==(const Matrix& other) const
		{
			return data == other.data;
		}

		/**
		 * @brief Оператор проверки двух матриц на неравенство
		 * @param other Матрица для сравнения
		 * @return true, если матрицы различаются, иначе false
		 */
		bool operator!=(const Matrix& other) const
		{
			return !(*this == other);
		}

		/**
		 * @brief Неконстантный оператор доступа к строке матрицы по индексу
		 * @param row Индекс строки (поддерживаются отрицательные индексы с конца)
		 * @return Ссылка на вектор элементов строки
		 * @throw std::invalid_argument Если индекс выходит за границы матрицы
		 */
		std::vector<T>& operator[](const int row)
		{
			int actualRow = row;
			if (actualRow < 0)
			{
				actualRow += rows;
			}
			if (actualRow < 0 || actualRow >= rows)
			{
				throw std::invalid_argument("Индекс строки вне диапазона");
			}
			return data[actualRow];
		}

		/**
		 * @brief Константный оператор доступа к строке матрицы по индексу
		 * @param row Индекс строки (поддерживаются отрицательные индексы с конца)
		 * @return Константная ссылка на вектор элементов строки
		 * @throw std::invalid_argument Если индекс выходит за границы матрицы
		 */
		const std::vector<T>& operator[](const int row) const
		{
			int actualRow = row;
			if (actualRow < 0)
			{
				actualRow += rows;
			}
			if (actualRow < 0 || actualRow >= rows)
			{
				throw std::invalid_argument("Индекс строки вне диапазона");
			}
			return data[actualRow];
		}

		/**
		 * @brief Получить количество строк матрицы
		 * @return Число строк матрицы
		 */
		int rowsCount() const
		{
			return rows;
		}

		/**
		 * @brief Получить количество столбцов матрицы
		 * @return Число столбцов матрицы
		 */
		int columnsCount() const
		{
			return cols;
		}

		/**
		 * @brief Найти минимальный элемент матрицы
		 * @return Константная ссылка на минимальный элемент матрицы
		 * @throw std::invalid_argument Если матрица пустая
		 */
		const T& minimum() const
		{
			if (rows == 0 || cols == 0)
			{
				throw std::invalid_argument("Матрица пустая");
			}
			int minR = 0;
			int minC = 0;
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					if (data[i][j] < data[minR][minC])
					{
						minR = i;
						minC = j;
					}
				}
			}
			return data[minR][minC];
		}

		/**
		 * @brief Найти максимальный элемент матрицы
		 * @return Константная ссылка на максимальный элемент матрицы
		 * @throw std::invalid_argument Если матрица пустая
		 */
		const T& maximum() const
		{
			if (rows == 0 || cols == 0)
			{
				throw std::invalid_argument("Матрица пустая");
			}
			int maxR = 0;
			int maxC = 0;
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					if (data[i][j] > data[maxR][maxC])
					{
						maxR = i;
						maxC = j;
					}
				}
			}
			return data[maxR][maxC];
		}

		/**
		 * @brief Найти максимальный по модулю элемент матрицы
		 * @return Константная ссылка на элемент матрицы с наибольшим значением модуля (|x|)
		 * @throw std::invalid_argument Если матрица пустая
		 */
		const T& maxAbsolute() const
		{
			if (rows == 0 || cols == 0)
			{
				throw std::invalid_argument("Матрица пустая");
			}
			int maxR = 0;
			int maxC = 0;
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					if (std::abs(data[i][j]) > std::abs(data[maxR][maxC]))
					{
						maxR = i;
						maxC = j;
					}
				}
			}
			return data[maxR][maxC];
		}

		/**
		 * @brief Заполнить все элементы матрицы с помощью переданного генератора
		 * @param generator Объект генератора чисел
		 */
		void fill(const Generator& generator)
		{
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					data[i][j] = (T)generator.generate();
				}
			}
		}

		/**
		 * @brief Преобразовать матрицу в строку
		 * @return Строка с элементами матрицы, разделенными табуляцией
		 */
		std::string toString() const
		{
			std::ostringstream ss;
			ss << *this;
			return ss.str();
		}

		/**
		 * @brief Дружественный оператор вывода матрицы в поток
		 * @param out Выходной поток
		 * @param mat Матрица для вывода
		 * @return Ссылка на выходной поток
		 */
		friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& mat)
		{
			for (int i = 0; i < mat.rows; i++)
			{
				for (int j = 0; j < mat.cols; j++)
				{
					out << mat.data[i][j];
					if (j + 1 < mat.cols)
					{
						out << "\t";
					}
				}
				out << "\n";
			}
			return out;
		}

		/**
		 * @brief Дружественный оператор ввода элементов матрицы из потока
		 * @param in Входной поток
		 * @param mat Матрица, в которую считываются элементы
		 * @return Ссылка на входной поток
		 */
		friend std::istream& operator>>(std::istream& in, Matrix<T>& mat)
		{
			for (int i = 0; i < mat.rows; i++)
			{
				for (int j = 0; j < mat.cols; j++)
				{
					in >> mat.data[i][j];
				}
			}
			return in;
		}
	};

	// Руководства по дедукции аргументов шаблона (CTAD)
	Matrix() -> Matrix<int>;
	Matrix(int, int) -> Matrix<int>;
}
