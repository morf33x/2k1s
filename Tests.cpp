#include "CppUnitTest.h"
#include <sstream>
#include <stdexcept>
#include "../include/Matrix.h"
#include "../include/ConstantGenerator.h"
#include "../include/ZeroGenerator.h"
#include "../include/IStreamGenerator.h"
#include "../include/RandomGenerator.h"
#include "../include/Task1.h"
#include "../include/Task2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace miit::algebra;

namespace UnitTests
{
	TEST_CLASS(ConstantGeneratorTests)
	{
	public:
		TEST_METHOD(ReturnsConstant)
		{
			ConstantGenerator gen(25);
			Assert::AreEqual(25, gen.generate());
			Assert::AreEqual(25, gen.generate());
		}

		TEST_METHOD(ReturnsNegativeConstant)
		{
			ConstantGenerator gen(-10);
			Assert::AreEqual(-10, gen.generate());
		}
	};

	TEST_CLASS(ZeroGeneratorTests)
	{
	public:
		TEST_METHOD(ReturnsZero)
		{
			ZeroGenerator gen;
			Assert::AreEqual(0, gen.generate());
		}
	};

	TEST_CLASS(IStreamGeneratorTests)
	{
	public:
		TEST_METHOD(ReadsFromStream)
		{
			std::istringstream input("5 -8 14");
			IStreamGenerator gen(input);

			Assert::AreEqual(5, gen.generate());
			Assert::AreEqual(-8, gen.generate());
			Assert::AreEqual(14, gen.generate());
		}
	};

	TEST_CLASS(RandomGeneratorTests)
	{
	public:
		TEST_METHOD(GeneratesInRange)
		{
			RandomGenerator gen(1, 10);
			for (int i = 0; i < 30; i++)
			{
				int val = gen.generate();
				Assert::IsTrue(val >= 1 && val <= 10);
			}
		}

		TEST_METHOD(ThrowsWhenMinGreaterThanMax)
		{
			Assert::ExpectException<std::invalid_argument>([]() {
				RandomGenerator(15, 2);
			});
		}
	};

	TEST_CLASS(MatrixTests)
	{
	public:
		TEST_METHOD(DefaultConstructorIsEmpty)
		{
			Matrix<int> m;
			Assert::AreEqual(0, m.rowsCount());
			Assert::AreEqual(0, m.columnsCount());
		}

		TEST_METHOD(ConstructorCreatesZeroMatrix)
		{
			Matrix<int> m(2, 3);
			Assert::AreEqual(2, m.rowsCount());
			Assert::AreEqual(3, m.columnsCount());
			Assert::AreEqual(0, m[0][0]);
			Assert::AreEqual(0, m[1][2]);
		}

		TEST_METHOD(ConstructorThrowsOnInvalidSize)
		{
			Assert::ExpectException<std::invalid_argument>([]() {
				Matrix<int>(0, 2);
			});
			Assert::ExpectException<std::invalid_argument>([]() {
				Matrix<int>(-1, 3);
			});
		}

		TEST_METHOD(CopyConstructorWorks)
		{
			Matrix<int> a(2, 2);
			a[0][0] = 5;
			a[0][1] = 6;

			Matrix<int> b(a);
			b[0][0] = 99;

			Assert::AreEqual(5, a[0][0]);
			Assert::AreEqual(99, b[0][0]);
			Assert::AreEqual(6, b[0][1]);
		}

		TEST_METHOD(AssignmentOperatorWorks)
		{
			Matrix<int> a(1, 2);
			a[0][0] = 3;
			a[0][1] = 7;

			Matrix<int> b;
			b = a;

			Assert::AreEqual(3, b[0][0]);
			Assert::AreEqual(7, b[0][1]);
		}

		TEST_METHOD(EqualityOperators)
		{
			Matrix<int> a(2, 2);
			Matrix<int> b(2, 2);
			a[0][0] = 1;
			b[0][0] = 1;

			Assert::IsTrue(a == b);
			Assert::IsFalse(a != b);

			b[0][1] = 2;
			Assert::IsTrue(a != b);
		}

		TEST_METHOD(IndexOperatorThrowsOutOfRange)
		{
			Matrix<int> m(2, 2);
			Assert::ExpectException<std::invalid_argument>([&]() {
				(void)m[2][0];
			});
			Assert::ExpectException<std::invalid_argument>([&]() {
				(void)m[5][0];
			});
		}

		TEST_METHOD(NegativeIndexSupport)
		{
			Matrix<int> m(2, 2);
			m[0][0] = 1; m[0][1] = 2;
			m[1][0] = 3; m[1][1] = 4;

			Assert::AreEqual(3, m[-1][0]);
			Assert::AreEqual(4, m[-1][1]);
			Assert::AreEqual(1, m[-2][0]);

			Assert::ExpectException<std::invalid_argument>([&]() {
				(void)m[-3][0];
			});
		}

		TEST_METHOD(MinimumAndMaximum)
		{
			Matrix<int> m(2, 2);
			m[0][0] = -15; m[0][1] = 4;
			m[1][0] = 8;   m[1][1] = 30;

			Assert::AreEqual(-15, m.minimum());
			Assert::AreEqual(30, m.maximum());
		}

		TEST_METHOD(MaxAbsoluteNegative)
		{
			Matrix<int> m(2, 2);
			m[0][0] = -50; m[0][1] = 10;
			m[1][0] = 20;  m[1][1] = -5;

			Assert::AreEqual(-50, m.maxAbsolute());
		}

		TEST_METHOD(MaxAbsolutePositive)
		{
			Matrix<int> m(2, 2);
			m[0][0] = -20; m[0][1] = 60;
			m[1][0] = 15;  m[1][1] = -40;

			Assert::AreEqual(60, m.maxAbsolute());
		}

		TEST_METHOD(EmptyMatrixThrowsOnExtremum)
		{
			Matrix<int> m;
			Assert::ExpectException<std::invalid_argument>([&]() { (void)m.minimum(); });
			Assert::ExpectException<std::invalid_argument>([&]() { (void)m.maximum(); });
			Assert::ExpectException<std::invalid_argument>([&]() { (void)m.maxAbsolute(); });
		}

		TEST_METHOD(FillWithGenerator)
		{
			Matrix<int> m(2, 2);
			ConstantGenerator gen(7);
			m.fill(gen);

			Assert::AreEqual(7, m[0][0]);
			Assert::AreEqual(7, m[0][1]);
			Assert::AreEqual(7, m[1][0]);
			Assert::AreEqual(7, m[1][1]);
		}

		TEST_METHOD(ToStringAndOutputOperator)
		{
			Matrix<int> m(2, 2);
			m[0][0] = 1; m[0][1] = 2;
			m[1][0] = 3; m[1][1] = 4;

			std::string expected = "1\t2\n3\t4\n";
			Assert::AreEqual(expected.c_str(), m.toString().c_str());

			std::ostringstream ss;
			ss << m;
			Assert::AreEqual(expected.c_str(), ss.str().c_str());
		}

		TEST_METHOD(InputOperator)
		{
			Matrix<int> m(1, 2);
			std::istringstream ss("10 20");
			ss >> m;

			Assert::AreEqual(10, m[0][0]);
			Assert::AreEqual(20, m[0][1]);
		}

		TEST_METHOD(TemplateWorksWithDouble)
		{
			Matrix<double> md(2, 2);
			md[0][0] = 1.5;
			md[0][1] = -4.2;
			md[1][0] = 3.1;
			md[1][1] = 2.0;

			Assert::AreEqual(2, md.rowsCount());
			Assert::AreEqual(2, md.columnsCount());
			Assert::AreEqual(-4.2, md.maxAbsolute());
			Assert::AreEqual(-4.2, md.minimum());
			Assert::AreEqual(3.1, md.maximum());
		}

		TEST_METHOD(ConstMatrixMethodsWork)
		{
			Matrix<int> m(2, 2);
			m[0][0] = -12; m[0][1] = 5;
			m[1][0] = 7;   m[1][1] = 0;

			const Matrix<int>& constRef = m;
			Assert::AreEqual(2, constRef.rowsCount());
			Assert::AreEqual(2, constRef.columnsCount());
			Assert::AreEqual(-12, constRef[0][0]);
			Assert::AreEqual(0, constRef[1][1]);
			Assert::AreEqual(-12, constRef.minimum());
			Assert::AreEqual(7, constRef.maximum());
			Assert::AreEqual(-12, constRef.maxAbsolute());
			std::string expected = "-12\t5\n7\t0\n";
			Assert::AreEqual(expected.c_str(), constRef.toString().c_str());
		}
	};

	TEST_CLASS(Task1Tests)
	{
	public:
		TEST_METHOD(ReplacesZeroWithMaxAbs)
		{
			// Матрица 2x3. Максимум по модулю = 30.
			// Столбец 0: 0, 5 -> 0 заменяется на 30
			// Столбец 1: 10, 0 -> 0 заменяется на 30
			// Столбец 2: 30, 2 -> нулей нет
			Matrix<int> m(2, 3);
			m[0][0] = 0;  m[0][1] = 10; m[0][2] = 30;
			m[1][0] = 5;  m[1][1] = 0;  m[1][2] = 2;

			Task1 task(m);
			Matrix<int> res = task.Solve();

			Assert::AreEqual(30, res[0][0]);
			Assert::AreEqual(10, res[0][1]);
			Assert::AreEqual(30, res[0][2]);
			Assert::AreEqual(5,  res[1][0]);
			Assert::AreEqual(30, res[1][1]);
			Assert::AreEqual(2,  res[1][2]);
		}

		TEST_METHOD(ReplacesZeroWithNegativeMaxAbs)
		{
			// Максимум по модулю = -40 (| -40 | = 40)
			Matrix<int> m(2, 2);
			m[0][0] = -40; m[0][1] = 0;
			m[1][0] = 0;   m[1][1] = 15;

			Task1 task(m);
			Matrix<int> res = task.Solve();

			Assert::AreEqual(-40, res[0][0]);
			Assert::AreEqual(-40, res[0][1]);
			Assert::AreEqual(-40, res[1][0]);
			Assert::AreEqual(15,  res[1][1]);
		}

		TEST_METHOD(NoZeroesMatrixUnchanged)
		{
			Matrix<int> m(2, 2);
			m[0][0] = 1; m[0][1] = 2;
			m[1][0] = 3; m[1][1] = 4;

			Task1 task(m);
			Matrix<int> res = task.Solve();

			Assert::AreEqual(1, res[0][0]);
			Assert::AreEqual(2, res[0][1]);
			Assert::AreEqual(3, res[1][0]);
			Assert::AreEqual(4, res[1][1]);
		}

		TEST_METHOD(EntireColumnOfZeroes)
		{
			Matrix<int> m(3, 2);
			m[0][0] = 0; m[0][1] = 8;
			m[1][0] = 0; m[1][1] = 2;
			m[2][0] = 0; m[2][1] = 3;

			Task1 task(m);
			Matrix<int> res = task.Solve();

			Assert::AreEqual(8, res[0][0]);
			Assert::AreEqual(8, res[1][0]);
			Assert::AreEqual(8, res[2][0]);
			Assert::AreEqual(8, res[0][1]);
		}
	};

	TEST_CLASS(Task2Tests)
	{
	public:
		TEST_METHOD(InsertsZeroColumnAfterColumnsWithMaxAbs)
		{
			// Матрица 2x3. Максимум по модулю = 20.
			// Присутствует в столбце 0 и столбце 2.
			Matrix<int> m(2, 3);
			m[0][0] = 20; m[0][1] = 5; m[0][2] = 20;
			m[1][0] = 1;  m[1][1] = 7; m[1][2] = 3;

			Task2 task(m);
			Matrix<int> res = task.Solve();

			// 3 исходных + 2 добавленных = 5 столбцов
			Assert::AreEqual(5, res.columnsCount());

			// Столбец 0
			Assert::AreEqual(20, res[0][0]);
			Assert::AreEqual(1,  res[1][0]);
			// Нулевой столбец
			Assert::AreEqual(0, res[0][1]);
			Assert::AreEqual(0, res[1][1]);
			// Столбец 1
			Assert::AreEqual(5, res[0][2]);
			Assert::AreEqual(7, res[1][2]);
			// Столбец 2
			Assert::AreEqual(20, res[0][3]);
			Assert::AreEqual(3,  res[1][3]);
			// Нулевой столбец
			Assert::AreEqual(0, res[0][4]);
			Assert::AreEqual(0, res[1][4]);
		}

		TEST_METHOD(InsertsZeroColumnForNegativeMaxAbs)
		{
			// Максимум по модулю = -30 (| -30 | = 30) в столбце 0 и 30 в столбце 1
			Matrix<int> m(2, 3);
			m[0][0] = -30; m[0][1] = 30; m[0][2] = 5;
			m[1][0] = 2;   m[1][1] = 1;  m[1][2] = 4;

			Task2 task(m);
			Matrix<int> res = task.Solve();

			Assert::AreEqual(5, res.columnsCount());

			// Столбец 0 (-30, 2)
			Assert::AreEqual(-30, res[0][0]);
			Assert::AreEqual(2,   res[1][0]);
			// Нулевой
			Assert::AreEqual(0, res[0][1]);
			Assert::AreEqual(0, res[1][1]);
			// Столбец 1 (30, 1)
			Assert::AreEqual(30, res[0][2]);
			Assert::AreEqual(1,  res[1][2]);
			// Нулевой
			Assert::AreEqual(0, res[0][3]);
			Assert::AreEqual(0, res[1][3]);
			// Столбец 2 (5, 4)
			Assert::AreEqual(5, res[0][4]);
			Assert::AreEqual(4, res[1][4]);
		}

		TEST_METHOD(EmptyMatrix)
		{
			Matrix<int> m;
			Task2 task(m);
			Matrix<int> res = task.Solve();

			Assert::AreEqual(0, res.rowsCount());
			Assert::AreEqual(0, res.columnsCount());
		}
	};
}
