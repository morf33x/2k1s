#pragma once
#include "Exercise.h"

namespace miit::algebra
{
	/**
	 * @brief Задание 1 (Вариант 10): Заменить нулевой элемент каждого столбца максимальным по модулю элементом массива
	 */
	class Task1 : public Exercise
	{
	private:
		/**
		 * @brief Результирующая матрица после преобразования
		 */
		Matrix<int> result;

	public:
		/**
		 * @brief Конструктор Задания 1
		 * @param mat Ссылка на исходную матрицу
		 * @param gen Ссылка на генератор значений
		 */
		Task1(Matrix<int>& mat, Generator& gen);

		/**
		 * @brief Заменить нули в каждом столбце на максимальный по модулю элемент матрицы
		 * @return Ссылка на результирующую матрицу
		 */
		Matrix<int>& solve() override;
	};
}
