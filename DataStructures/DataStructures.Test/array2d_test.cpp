#include "pch.h"
#include "CppUnitTest.h"
#include "Array2d.hpp"
#include "crt_check_memory.hpp"

using namespace data_structures;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace data_structures_tests
{
	TEST_CLASS(Array2DTest)
	{
		static Array2D<int> IntFactory(size_t rows = 4, size_t columns = 4)
		{
			Array2D<int> array(rows, columns);
			int counter = 0;

			for (size_t i = 0; i < array.Rows(); ++i)
			{
				for (size_t j = 0; j < array.Columns(); ++j)
					array[i][j] = counter++;
			}

			return array;
		}


	public:
		TEST_METHOD(SelectAndOpIndex_SunnyDay)
		{
			const CrtCheckMemory check;

			// Arrange
			auto array = IntFactory();

			int sumSelect = 0, sumIndex = 0;

			// Act: sum via Select() and sum via operator[][]
			for (size_t i = 0; i < 4ull; ++i)
			{
				for (size_t j = 0; j < 4ull; ++j)
				{
					sumSelect += array.Select(i, j);
					sumIndex += array[i][j];
				}
			}

			// Assert
			Assert::AreEqual(120, sumSelect, L"Sum via Select()");
			Assert::AreEqual(120, sumIndex, L"Sum via operator[][]");
		}

		TEST_METHOD(ResizeRowd_ShrinkAndGrow_PreservesAndValueInits_SunnyAndRainy)
		{
			const CrtCheckMemory check;

			// Arrange
			Array2D<int> array(2ull, 3ull);

			// Fill
			array[0][0] = 10; array[0][1] = 11; array[0][2] = 12;
			array[1][0] = 20; array[1][1] = 21; array[1][2] = 22;

			// Act1: shrink to 1 row
			array.Rows(1ull);

			// Assert
			Assert::AreEqual(1ull, array.Rows(), L"Rows after shrink to 1");
			Assert::AreEqual(3ull, array.Columns(), L"Columns remain 3");
			Assert::AreEqual(10, array[0][0], L"Retained[0][0]");
			Assert::AreEqual(11, array[0][1], L"Retained[0][1]");
			Assert::AreEqual(12, array[0][2], L"Retained[0][2]");
			Assert::ExpectException<AdtException>([&]() {array.Select(1ull, 0); });
			Assert::ExpectException<AdtException>([&]() {array.Select(2ull, 0); });

			// Act 2: Grow to 3 rows
			array.Rows(3ull);

			//Assert grow
			Assert::AreEqual(3ull, array.Rows(), L"Rows after grow to 3");
			Assert::AreEqual(10, array[0][0], L"Retained[0][0]");
			Assert::AreEqual(11, array[0][1], L"Retained[0][1]");
			Assert::AreEqual(12, array[0][2], L"Retained[0][2]");
			Assert::AreEqual(0, array[1][0], L"New rows default to 0");
			Assert::AreEqual(0, array[1][1], L"New rows default to 0");
			Assert::AreEqual(0, array[1][2], L"New rows default to 0");
			Assert::AreEqual(0, array[2][0], L"New rows default to 0");
			Assert::AreEqual(0, array[2][1], L"New rows default to 0");
			Assert::AreEqual(0, array[2][2], L"New rows default to 0");
		}

		TEST_METHOD(OperatorEqualsAndNotEquals)
		{
			const CrtCheckMemory check;

			// Arrange
			auto array1 = IntFactory();
			auto array2 = IntFactory();

			// Act and Assert
			Assert::IsTrue(array1 == array2, L"Two identical factories compare equal");
			array2[2][3] = -1;
			Assert::IsTrue(array1 != array2, L"After mutation, the arrays differ");
		}
	};
}
