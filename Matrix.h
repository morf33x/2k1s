#pragma once
#include "Generator.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <cstddef>
#include <utility>

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
		size_t rows;

		/**
		 * @brief Количество столбцов матрицы
		 */
		size_t cols;

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
		 * @throw std::invalid_argument Если r == 0 или c == 0
		 */
		Matrix(const size_t r, const size_t c)
		{
			if (r == 0 || c == 0)
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
		Matrix(Matrix&& other) noexcept
			: rows(other.rows), cols(other.cols), data(std::move(other.data))
		{
			other.rows = 0;
			other.cols = 0;
		}

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
		Matrix& operator=(Matrix&& other) noexcept
		{
			if (this != &other)
			{
				rows = other.rows;
				cols = other.cols;
				data = std::move(other.data);
				other.rows = 0;
				other.cols = 0;
			}
			return *this;
		}

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
		 * @param row Индекс строки
		 * @return Ссылка на вектор элементов строки
		 * @throw std::out_of_range Если индекс выходит за границы матрицы
		 */
		std::vector<T>& operator[](const size_t row)
		{
			if (row >= rows)
			{
				throw std::out_of_range("Индекс строки вне диапазона");
			}
			return data[row];
		}

		/**
		 * @brief Константный оператор доступа к строке матрицы по индексу
		 * @param row Индекс строки
		 * @return Константная ссылка на вектор элементов строки
		 * @throw std::out_of_range Если индекс выходит за границы матрицы
		 */
		const std::vector<T>& operator[](const size_t row) const
		{
			if (row >= rows)
			{
				throw std::out_of_range("Индекс строки вне диапазона");
			}
			return data[row];
		}

		/**
		 * @brief Получить количество строк матрицы
		 * @return Число строк матрицы
		 */
		size_t rowsCount() const
		{
			return rows;
		}

		/**
		 * @brief Получить количество столбцов матрицы
		 * @return Число столбцов матрицы
		 */
		size_t columnsCount() const
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
			size_t minR = 0;
			size_t minC = 0;
			for (size_t i = 0; i < rows; i++)
			{
				for (size_t j = 0; j < cols; j++)
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
			size_t maxR = 0;
			size_t maxC = 0;
			for (size_t i = 0; i < rows; i++)
			{
				for (size_t j = 0; j < cols; j++)
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
			size_t maxR = 0;
			size_t maxC = 0;
			for (size_t i = 0; i < rows; i++)
			{
				for (size_t j = 0; j < cols; j++)
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
		void fill(Generator& generator)
		{
			for (size_t i = 0; i < rows; i++)
			{
				for (size_t j = 0; j < cols; j++)
				{
					data[i][j] = static_cast<T>(generator.generate());
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
			for (size_t i = 0; i < mat.rows; i++)
			{
				for (size_t j = 0; j < mat.cols; j++)
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
			for (size_t i = 0; i < mat.rows; i++)
			{
				for (size_t j = 0; j < mat.cols; j++)
				{
					in >> mat.data[i][j];
				}
			}
			return in;
		}
	};
}
