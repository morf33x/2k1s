#pragma once
#include "Generator.h"
#include <iostream>

namespace miit::algebra
{
	/**
	 * @brief Генератор элементов, считываемых из входного потока
	 */
	class IStreamGenerator : public Generator
	{
	private:
		/**
		 * @brief Ссылка на входной поток данных
		 */
		std::istream& in;

	public:
		/**
		 * @brief Конструктор генератора из входного потока
		 * @param in Входной поток (по умолчанию std::cin)
		 */
		IStreamGenerator(std::istream& in = std::cin);

		/**
		 * @brief Считать очередное число из потока
		 * @return Считанное целочисленное значение
		 */
		int generate() override;
	};
}
