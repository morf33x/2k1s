#pragma once
#include "Matrix.h"

namespace miit::algebra
{
	/**
	 * @brief Базовый класс для выполнения заданий над матрицей
	 */
	class Exercise
	{
	protected:
		/**
		 * @brief Ссылка на обрабатываемую матрицу
		 */
		Matrix<int>& matrix;

	public:
		/**
		 * @brief Конструктор базового класса задания
		 * @param mat Ссылка на исходную матрицу
		 */
		explicit Exercise(Matrix<int>& mat);

		/**
		 * @brief Виртуальный деструктор по умолчанию
		 */
		virtual ~Exercise() = default;

		/**
		 * @brief Выполнить задание над матрицей
		 * @return Ссылка на результирующую матрицу
		 */
		virtual Matrix<int>& Solve() = 0;
	};
}
