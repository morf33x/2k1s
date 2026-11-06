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
		 * @brief Виртуальный деструктор по умолчанию
		 */
		virtual ~Generator() = default;

		/**
		 * @brief Сгенерировать очередное целочисленное значение
		 * @return Сгенерированное число
		 */
		virtual int generate() const = 0;
	};
}
