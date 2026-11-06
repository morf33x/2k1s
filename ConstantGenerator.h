#pragma once
#include "Generator.h"

namespace miit::algebra
{
	/**
	 * @brief Генератор, возвращающий заданное константное значение
	 */
	class ConstantGenerator : public Generator
	{
	private:
		/**
		 * @brief Фиксированное значение для генерации
		 */
		int value;

	public:
		/**
		 * @brief Конструктор генератора константы
		 * @param val Число, которое будет возвращаться генератором
		 */
		explicit ConstantGenerator(const int val);

		/**
		 * @brief Получить сохраненное константное значение
		 * @return Фиксированное число
		 */
		int generate() const override;
	};
}
