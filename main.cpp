#include <iostream>
#include <memory>
#include "Matrix.h"
#include "Generator.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "ConstantGenerator.h"
#include "ZeroGenerator.h"
#include "Task1.h"
#include "Task2.h"

using namespace miit::algebra;

enum GeneratorType
{
	Random = 1,
	Keyboard,
	Constant,
	Zero
};

/**
 * @brief Отобразить диалог выбора генератора и создать соответствующий объект
 * @return Умный указатель std::unique_ptr на созданный генератор
 * @throw std::invalid_argument В случае некорректного выбора или недопустимого диапазона
 */
std::unique_ptr<Generator> chooseGenerator()
{
	int choice = 0;
	std::cout << "\nВыберите способ заполнения матрицы:\n";
	std::cout << Random << " - Случайными числами\n";
	std::cout << Keyboard << " - Вводом с клавиатуры\n";
	std::cout << Constant << " - Одним конкретным числом\n";
	std::cout << Zero << " - Нулями\n";
	std::cout << "Ваш выбор: ";
	std::cin >> choice;

	switch (choice)
	{
	case Random:
	{
		int min = 0, max = 0;
		std::cout << "Введите минимальное значение: ";
		std::cin >> min;
		std::cout << "Введите максимальное значение: ";
		std::cin >> max;

		if (min > max)
		{
			throw std::invalid_argument("Минимум не может быть больше максимума");
		}

		return std::make_unique<RandomGenerator>(min, max);
	}

	case Keyboard:
	{
		std::cout << "Введите элементы матрицы через пробел:\n";
		return std::make_unique<IStreamGenerator>(std::cin);
	}

	case Constant:
	{
		int value = 0;
		std::cout << "Введите число: ";
		std::cin >> value;
		return std::make_unique<ConstantGenerator>(value);
	}

	case Zero:
	{
		return std::make_unique<ZeroGenerator>();
	}

	default:
		throw std::invalid_argument("Неверный пункт меню");
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	try
	{
		int n = 0, m = 0;
		std::cout << "=== Вариант 10 ===\n";
		std::cout << "Введите число строк (n): ";
		std::cin >> n;
		std::cout << "Введите число столбцов (m): ";
		std::cin >> m;

		Matrix<int> mat(n, m);
		auto generator = chooseGenerator();
		mat.fill(*generator);

		std::cout << "\nИсходная матрица:\n" << mat;
		std::cout << "Максимальный по модулю элемент: " << mat.maxAbsolute() << "\n";

		// Задание 1
		Task1 task1(mat, *generator);
		const Matrix<int>& res1 = task1.solve();
		std::cout << "\nПосле задания 1 (замена нулевых элементов каждого столбца):\n" << res1;

		// Задание 2
		Task2 task2(mat, *generator);
		const Matrix<int>& res2 = task2.solve();
		std::cout << "\nПосле задания 2 (вставка столбца из нулей после максимума по модулю):\n" << res2;
	}
	catch (const std::exception& e)
	{
		std::cout << "Ошибка: " << e.what() << "\n";
		return 1;
	}

	return 0;
}