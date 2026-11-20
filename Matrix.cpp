#include "../include/Matrix.h"
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace miit::algebra
{
	template <typename T>
	Matrix<T>::Matrix()
		: rows(0), cols(0)
	{
	}

	template <typename T>
	Matrix<T>::Matrix(const size_t r, const size_t c)
	{
		if (r == 0 || c == 0)
		{
			throw std::invalid_argument("Размеры матрицы должны быть больше нуля");
		}
		rows = r;
		cols = c;
		data.resize(r, std::vector<T>(c, T{}));
	}

	template <typename T>
	Matrix<T>::Matrix(const Matrix& other)
		: rows(other.rows), cols(other.cols), data(other.data)
	{
	}

	template <typename T>
	Matrix<T>::Matrix(Matrix&& other) noexcept
		: rows(other.rows), cols(other.cols), data(std::move(other.data))
	{
		other.rows = 0;
		other.cols = 0;
	}

	template <typename T>
	Matrix<T>& Matrix<T>::operator=(const Matrix& other)
	{
		if (this != &other)
		{
			rows = other.rows;
			cols = other.cols;
			data = other.data;
		}
		return *this;
	}

	template <typename T>
	Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept
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

	template <typename T>
	bool Matrix<T>::operator==(const Matrix& other) const
	{
		return data == other.data;
	}

	template <typename T>
	bool Matrix<T>::operator!=(const Matrix& other) const
	{
		return !(*this == other);
	}

	template <typename T>
	std::vector<T>& Matrix<T>::operator[](const size_t row)
	{
		if (row >= rows)
		{
			throw std::out_of_range("Индекс строки вне диапазона");
		}
		return data[row];
	}

	template <typename T>
	const std::vector<T>& Matrix<T>::operator[](const size_t row) const
	{
		if (row >= rows)
		{
			throw std::out_of_range("Индекс строки вне диапазона");
		}
		return data[row];
	}

	template <typename T>
	size_t Matrix<T>::rowsCount() const
	{
		return rows;
	}

	template <typename T>
	size_t Matrix<T>::columnsCount() const
	{
		return cols;
	}

	template <typename T>
	const T& Matrix<T>::minimum() const
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

	template <typename T>
	const T& Matrix<T>::maximum() const
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

	template <typename T>
	const T& Matrix<T>::maxAbsolute() const
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

	template <typename T>
	void Matrix<T>::fill(Generator& generator)
	{
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
			{
				data[i][j] = static_cast<T>(generator.generate());
			}
		}
	}

	template <typename T>
	std::string Matrix<T>::toString() const
	{
		std::ostringstream ss;
		ss << *this;
		return ss.str();
	}

	template class Matrix<int>;
	template class Matrix<double>;
}
