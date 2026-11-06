#include "../include/IStreamGenerator.h"

namespace miit::algebra
{
	IStreamGenerator::IStreamGenerator(std::istream& stream)
		: in(stream)
	{
	}

	int IStreamGenerator::generate() const
	{
		int val = 0;
		in >> val;
		return val;
	}
}
