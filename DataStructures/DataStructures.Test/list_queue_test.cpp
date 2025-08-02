#include "pch.h"
#include "CppUnitTest.h"
#include "crt_check_memory.hpp"
#include "list_queue.hpp"
#include "adt_exception.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace data_structures;

namespace data_structures_tests
{
	TEST_CLASS(ListQueueTest)
	{
	public:

		TEST_METHOD(Sunny_EnqueueDequeueOrder)
		{
			const CrtCheckMemory check;
			ListQueue<int> q;
			q.Enqueue(10);
			q.Enqueue(20);
			q.Enqueue(30);

			Assert::AreEqual(10, q.Dequeue());
			Assert::AreEqual(20, q.Dequeue());
			Assert::AreEqual(30, q.Dequeue());
			Assert::IsTrue(q.IsEmpty());
		}

		TEST_METHOD(Sunny_FrontReturnsCorrectElement)
		{
			const CrtCheckMemory check;
			ListQueue<int> q;
			q.Enqueue(100);
			Assert::AreEqual(100, q.Front());
			q.Enqueue(200);
			Assert::AreEqual(100, q.Front());
		}

		TEST_METHOD(Sunny_SizeAfterOperations)
		{
			const CrtCheckMemory check;
			ListQueue<int> q;
			Assert::AreEqual<size_t>(0, q.Size());

			q.Enqueue(1);
			q.Enqueue(2);
			Assert::AreEqual<size_t>(2, q.Size());

			q.Dequeue();
			Assert::AreEqual<size_t>(1, q.Size());
		}

		TEST_METHOD(Rainy_DequeueOnEmptyThrows)
		{
			const CrtCheckMemory check;
			ListQueue<int> q;
			Assert::ExpectException<AdtException>([&]() { q.Dequeue(); });
		}

		TEST_METHOD(Rainy_FrontOnEmptyThrows)
		{
			const CrtCheckMemory check;
			ListQueue<int> q;
			Assert::ExpectException<AdtException>([&]() { q.Front(); });
		}

		TEST_METHOD(Sunny_ClearEmptiesQueue)
		{
			const CrtCheckMemory check;
			ListQueue<int> q;
			q.Enqueue(1);
			q.Enqueue(2);
			q.Clear();
			Assert::IsTrue(q.IsEmpty());
			Assert::AreEqual<size_t>(0, q.Size());
		}

		TEST_METHOD(Sunny_CopyConstructorCopiesElements)
		{
			const CrtCheckMemory check;
			ListQueue<int> q1;
			q1.Enqueue(5);
			q1.Enqueue(10);

			ListQueue<int> q2(q1);
			Assert::AreEqual(5, q2.Dequeue());
			Assert::AreEqual(10, q2.Dequeue());
		}
	};
}
