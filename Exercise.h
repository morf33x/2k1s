#pragma once
#include "Matrix.h"
#include "Generator.h"

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

		/**
		 * @brief Ссылка на генератор элементов матрицы
		 */
		Generator& generator;

	public:
		/**
		 * @brief Конструктор базового класса задания
		 * @param mat Ссылка на исходную матрицу
		 * @param gen Ссылка на генератор значений
		 */
		Exercise(Matrix<int>& mat, Generator& gen);

		/**
		 * @brief Виртуальный деструктор по умолчанию
		 */
		virtual ~Exercise() = default;

		/**
		 * @brief Выполнить задание над матрицей
		 * @return Ссылка на результирующую матрицу
		 */
		virtual Matrix<int>& solve() = 0;
	};
}
