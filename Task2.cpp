#include "../include/Task2.h"
#include <cmath>

namespace miit::algebra
{
	Task2::Task2(Matrix<int>& mat)
		: Exercise(mat)
	{
	}

	bool Task2::columnHasMaxAbs(const Matrix<int>& mat, const int col, const int maxAbs) const
	{
		const int rows = mat.rowsCount();
		for (int i = 0; i < rows; i++)
		{
			if (std::abs(mat[i][col]) == std::abs(maxAbs))
			{
				return true;
			}
		}
		return false;
	}

	Matrix<int>& Task2::Solve()
	{
		const int rows = matrix.rowsCount();
		const int cols = matrix.columnsCount();

		if (rows == 0 || cols == 0)
		{
			result = Matrix<int>();
			return result;
		}

		const int maxAbs = matrix.maxAbsolute();

		int extraCols = 0;
		for (int j = 0; j < cols; j++)
		{
			if (columnHasMaxAbs(matrix, j, maxAbs))
			{
				extraCols++;
			}
		}

		result = Matrix<int>(rows, cols + extraCols);

		int targetCol = 0;
		for (int j = 0; j < cols; j++)
		{
			for (int i = 0; i < rows; i++)
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
