#pragma once
#include "Generator.h"

namespace miit::algebra
{
	/**
	 * @brief Генератор нулевых значений
	 */
	class ZeroGenerator : public Generator
	{
	public:
		/**
		 * @brief Конструктор генератора нулей по умолчанию
		 */
		ZeroGenerator() = default;

		/**
		 * @brief Получить нулевое значение
		 * @return Всегда возвращает 0
		 */
		int generate() const override;
	};
}
