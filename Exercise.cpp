#include "../include/Exercise.h"

namespace miit::algebra
{
	Exercise::Exercise(Matrix<int>& mat, Generator& gen)
		: matrix(mat), generator(gen)
	{
	}
}
