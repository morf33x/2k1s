#pragma once
#include "Generator.h"
#include <random>

namespace miit::algebra
{
	/**
	 * @brief Генератор псевдослучайных целых чисел в заданном диапазоне
	 */
	class RandomGenerator : public Generator
	{
	private:
		/**
		 * @brief Равномерное целочисленное распределение
		 */
		std::uniform_int_distribution<int> distribution;

		/**
		 * @brief Генератор псевдослучайных чисел на основе вихря Мерсенна
		 */
		std::mt19937 generator;

	public:
		/**
		 * @brief Конструктор генератора случайных чисел
		 * @param min Нижняя граница диапазона (включительно)
		 * @param max Верхняя граница диапазона (включительно)
		 */
		RandomGenerator(const int min, const int max);

		/**
		 * @brief Сгенерировать случайное целое число из заданного диапазона
		 * @return Случайное число в диапазоне [min, max]
		 */
		int generate() override;
	};
}
