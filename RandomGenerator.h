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
		 * @brief Генератор псевдослучайных чисел на основе вихря Мерсенна
		 */
		mutable std::mt19937 gen;

		/**
		 * @brief Равномерное целочисленное распределение
		 */
		mutable std::uniform_int_distribution<int> dist;

	public:
		/**
		 * @brief Конструктор генератора случайных чисел
		 * @param min Нижняя граница диапазона (включительно)
		 * @param max Верхняя граница диапазона (включительно)
		 * @throw std::invalid_argument Если min > max
		 */
		RandomGenerator(const int min, const int max);

		/**
		 * @brief Сгенерировать случайное целое число из заданного диапазона
		 * @return Случайное число в диапазоне [min, max]
		 */
		int generate() const override;
	};
}
