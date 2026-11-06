#include "../include/Task1.h"

namespace miit::algebra
{
	Task1::Task1(Matrix<int>& mat)
		: Exercise(mat)
	{
	}

	Matrix<int>& Task1::Solve()
	{
		result = matrix;

		const int rows = result.rowsCount();
		const int cols = result.columnsCount();

		if (rows == 0 || cols == 0)
		{
			return result;
		}

		const int maxAbs = matrix.maxAbsolute();

		for (int j = 0; j < cols; j++)
		{
			for (int i = 0; i < rows; i++)
			{
				if (result[i][j] == 0)
				{
					result[i][j] = maxAbs;
				}
			}
		}

		return result;
	}
}
