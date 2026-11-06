#pragma once
#include "Exercise.h"

namespace miit::algebra
{
	/**
	 * @brief Задание 2 (Вариант 10): Вставить после каждого столбца, содержащего максимальный по модулю элемент массива, столбец из нулей
	 */
	class Task2 : public Exercise
	{
	private:
		/**
		 * @brief Результирующая матрица с добавленными столбцами нулей
		 */
		Matrix<int> result;

		/**
		 * @brief Проверить, содержит ли столбец максимальный по модулю элемент
		 * @param mat Исходная матрица
		 * @param col Индекс проверяемого столбца
		 * @param maxAbs Максимальный по модулю элемент матрицы
		 * @return true, если столбец содержит максимальный по модулю элемент, иначе false
		 */
		bool columnHasMaxAbs(const Matrix<int>& mat, const int col, const int maxAbs) const;

	public:
		/**
		 * @brief Конструктор Задания 2
		 * @param mat Ссылка на исходную матрицу
		 */
		explicit Task2(Matrix<int>& mat);

		/**
		 * @brief Вставить столбец из нулей после каждого столбца с максимальным по модулю элементом
		 * @return Ссылка на результирующую расширенную матрицу
		 */
		Matrix<int>& Solve() override;
	};
}
