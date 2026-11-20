#pragma once
#include "Generator.h"
#include <iostream>

namespace miit::algebra
{
	/**
	* @brief
	*/
	class IStreamGenerator : public Generator
	{
		private:
			std::istream& in;

		public:
			/**
			* @brief
			* @param in
			*/
			IStreamGenerator(std::istream& in = std::cin);

			/**
			* @brief
			*/
			int generate() override;
	};
}
