#include "pch.h"
#include "CppUnitTest.h"
#include "linked_list.hpp"
#include "crt_check_memory.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace data_structures;

namespace data_structures_tests
{
	TEST_CLASS(LinkedListTest)
	{
	public:

		LinkedList<int> MakeList(int n)
		{
			LinkedList<int> list;
			for (int i = 0; i < n; ++i)
			{
				list.Append(i);
			}
			return list;
		}
		TEST_METHOD(AppendEmptySizeFirstLast_Sunny)
		{
			const CrtCheckMemory check;

			//Arrange
			LinkedList<int> list;

			for (int i = 0; i < 10; ++i)
			{
				//Act
				list.Append(i);
			}

			//Assert
			Assert::IsFalse(list.IsEmpty());
			Assert::AreEqual<size_t>(10, list.Size());
			Assert::AreEqual(0, list.First());
			Assert::AreEqual(9, list.Last());
		}

		TEST_METHOD(ClearEmptiesTheList)
		{
			const CrtCheckMemory check;

			//Arrange
			auto list = MakeList(10);

			//Act
			list.Clear();

			//Arrange
			Assert::IsTrue(list.IsEmpty());
			Assert::AreEqual<size_t>(0, list.Size());
			Assert::IsNull(list.Head());
			Assert::IsNull(list.Tail());
		}

		TEST_METHOD(RemoveFirst_Sunny)
		{
			const CrtCheckMemory check;

			//Arrange
			auto list = MakeList(10);

			//Act
			list.RemoveFirst();

			//Assert
			Assert::AreEqual(1, list.First());
			Assert::AreEqual(1, list.Head()->Value());
		}

		TEST_METHOD(InsertAfter_SunnyAndRainy)
		{
			const CrtCheckMemory check;

			//Arrange
			auto list = MakeList(10);

			//Act
			list.InsertAfter(10, 9);

			//Assert
			Assert::AreEqual(11ull, list.Size(), L"Insert After Tail Size");
			Assert::AreEqual<size_t>(10, list.Last(), L"Insert After Tail Last");

			//Act
			list.InsertAfter(11, 0);
			int array[] = { 0,11,1,2,3,4,5,6,7,8,9,10 };
			int counter = 0;
			for (auto travel = list.Head(); travel; travel = travel->Next())
			{
				Assert::AreEqual(array[counter++], travel->Value(), L"Insert after Head Value");
			}

			//Act
			list.InsertAfter(12, 7);
			int array2[] = { 0,11,1,2,3,4,5,6,7,12,8,9,10 };
			counter = 0;
			for (auto travel = list.Head(); travel; travel = travel->Next())
			{
				Assert::AreEqual(array2[counter++], travel->Value(), L"Insert after Middle Value");
			}

			//bad inserts
			//Act & Assert
			Assert::ExpectException <AdtException>([&]
				{
					list.InsertAfter(44, 52);
				}, L"Throws Exception");
		}

		TEST_METHOD(Prepend_UpdatesHeadCorrectly)
		{
			const CrtCheckMemory check;

			LinkedList<int> list;
			list.Prepend(2);
			list.Prepend(1);
			list.Prepend(0);

			Assert::AreEqual<size_t>(3, list.Size());
			Assert::AreEqual(0, list.First());
			Assert::AreEqual(2, list.Last());

			int expected[] = { 0,1,2 };
			int i = 0;
			for (auto* node = list.Head(); node; node = node->Next())
				Assert::AreEqual(expected[i++], node->Value());
		}

		TEST_METHOD(RemoveLast_RemovesCorrectly)
		{
			const CrtCheckMemory check;

			auto list = MakeList(3); // 0,1,2
			list.RemoveLast();

			Assert::AreEqual<size_t>(2, list.Size());
			Assert::AreEqual(1, list.Last());

			list.RemoveLast();
			list.RemoveLast();

			Assert::IsTrue(list.IsEmpty());
			Assert::IsNull(list.Head());
			Assert::IsNull(list.Tail());

			Assert::ExpectException<AdtException>([&] { list.RemoveLast(); });
		}

		TEST_METHOD(Remove_RemovesMiddleCorrectly)
		{
			const CrtCheckMemory check;

			auto list = MakeList(5); // 0-4
			list.Remove(2);

			int expected[] = { 0,1,3,4 };
			int i = 0;
			for (auto* node = list.Head(); node; node = node->Next())
				Assert::AreEqual(expected[i++], node->Value());

			Assert::AreEqual<size_t>(4, list.Size());

			// Remove head
			list.Remove(0);
			Assert::AreEqual(1, list.First());

			// Remove tail
			list.Remove(4);
			Assert::AreEqual(3, list.Last());

			// Remove missing
			Assert::ExpectException<AdtException>([&] { list.Remove(99); });
		}

		TEST_METHOD(InsertBefore_SunnyAndRainy)
		{
			const CrtCheckMemory check;

			auto list = MakeList(5); // 0,1,2,3,4
			list.InsertBefore(100, 0); // before head
			Assert::AreEqual(100, list.First());

			list.InsertBefore(101, 2); // middle
			int expected[] = { 100,0,1,101,2,3,4 };
			int i = 0;
			for (auto* node = list.Head(); node; node = node->Next())
				Assert::AreEqual(expected[i++], node->Value());

			list.InsertBefore(102, 4); // before tail
			Assert::AreEqual(102, list.Tail()->Prev()->Value());

			Assert::ExpectException<AdtException>([&] { list.InsertBefore(500, 999); });
		}

		TEST_METHOD(FirstLast_Tests)
		{
			const CrtCheckMemory check;

			auto list = MakeList(3); // 0,1,2
			Assert::AreEqual(0, list.First());
			Assert::AreEqual(2, list.Last());

			list.Clear();
			Assert::ExpectException<AdtException>([&] { list.First(); });
			Assert::ExpectException<AdtException>([&] { list.Last(); });
		}

		TEST_METHOD(HeadTail_Tests)
		{
			const CrtCheckMemory check;

			LinkedList<int> list;
			Assert::IsNull(list.Head());
			Assert::IsNull(list.Tail());

			list.Append(5);
			Assert::IsNotNull(list.Head());
			Assert::IsNotNull(list.Tail());
			Assert::AreEqual(5, list.Head()->Value());
			Assert::AreEqual(5, list.Tail()->Value());
		}

		TEST_METHOD(EmptySize_Check)
		{
			const CrtCheckMemory check;

			LinkedList<int> list;
			Assert::IsTrue(list.IsEmpty());
			Assert::AreEqual<size_t>(0, list.Size());

			list.Append(42);
			Assert::IsFalse(list.IsEmpty());
			Assert::AreEqual<size_t>(1, list.Size());

			list.RemoveFirst();
			Assert::IsTrue(list.IsEmpty());
			Assert::AreEqual<size_t>(0, list.Size());
		}

	};
}
