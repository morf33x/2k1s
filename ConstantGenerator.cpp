#include "../include/ConstantGenerator.h"

namespace miit::algebra
{
	ConstantGenerator::ConstantGenerator(const int val)
		: value(val)
	{
	}

	int ConstantGenerator::generate() const
	{
		return value;
	}
}
