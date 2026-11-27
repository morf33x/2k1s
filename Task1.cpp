#include "Task1.h"

namespace miit::algebra
{
	Task1::Task1(Matrix<int>& mat, Generator& gen)
		: Exercise(mat, gen)
	{
	}

	Matrix<int>& Task1::solve()
	{
		result = matrix;

		const size_t rows = result.rowsCount();
		const size_t cols = result.columnsCount();

		if (rows == 0 || cols == 0)
		{
			return result;
		}

		const int maxAbs = matrix.maxAbsolute();

		for (size_t j = 0; j < cols; j++)
		{
			for (size_t i = 0; i < rows; i++)
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
