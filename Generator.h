#pragma once

namespace miit::algebra
{
	/**
	 * @brief Базовый интерфейс для генераторов элементов матрицы
	 */
	class Generator
	{
	public:
		/**
		 * @brief Чисто виртуальный деструктор
		 */
		virtual ~Generator() = 0 {};

		/**
		 * @brief Сгенерировать очередное целочисленное значение
		 * @return Сгенерированное число
		 */
		virtual int generate() = 0;
	};
}
