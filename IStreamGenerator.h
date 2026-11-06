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
		 * @param stream Входной поток (по умолчанию std::cin)
		 */
		explicit IStreamGenerator(std::istream& stream = std::cin);

		/**
		 * @brief Считать очередное число из потока
		 * @return Считанное целочисленное значение
		 * @throw std::runtime_error В случае ошибки чтения из потока
		 */
		int generate() const override;
	};
}
