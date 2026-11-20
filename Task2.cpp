#include "../include/Task2.h"
#include <cmath>

namespace miit::algebra
{
	Task2::Task2(Matrix<int>& mat, Generator& gen)
		: Exercise(mat, gen)
	{
	}

	bool Task2::columnHasMaxAbs(const Matrix<int>& mat, const size_t col, const int maxAbs) const
	{
		const size_t rows = mat.rowsCount();
		for (size_t i = 0; i < rows; i++)
		{
			if (std::abs(mat[i][col]) == std::abs(maxAbs))
			{
				return true;
			}
		}
		return false;
	}

	Matrix<int>& Task2::solve()
	{
		const size_t rows = matrix.rowsCount();
		const size_t cols = matrix.columnsCount();

		if (rows == 0 || cols == 0)
		{
			result = Matrix<int>();
			return result;
		}

		const int maxAbs = matrix.maxAbsolute();

		size_t extraCols = 0;
		for (size_t j = 0; j < cols; j++)
		{
			if (columnHasMaxAbs(matrix, j, maxAbs))
			{
				extraCols++;
			}
		}

		result = Matrix<int>(rows, cols + extraCols);

		size_t targetCol = 0;
		for (size_t j = 0; j < cols; j++)
		{
			for (size_t i = 0; i < rows; i++)
			{
				result[i][targetCol] = matrix[i][j];
			}
			targetCol++;

			if (columnHasMaxAbs(matrix, j, maxAbs))
			{
				targetCol++;
			}
		}

		return result;
	}
}
