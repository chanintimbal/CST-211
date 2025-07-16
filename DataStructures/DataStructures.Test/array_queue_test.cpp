#include "pch.h"
#include "CppUnitTest.h"
#include "array_queue.hpp"
#include "crt_check_memory.hpp"

using namespace data_structures;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace data_structures_tests
{
	TEST_CLASS(ArrayQueueTest)
	{
	public:

		static ArrayQueue<string> MakeFilledStringQueue()
		{
			ArrayQueue<string> queue(5);
			for (int i = 0; i < 5; ++i)
			{
				queue.Enqueue("Item " + std::to_string(i));
			}
			return queue;
		}

		static ArrayQueue<int> MakeFilledIntQueue()
		{
			ArrayQueue<int> queue(5);
			for (int i = 0; i < 5; ++i)
			{
				queue.Enqueue(i);
			}
			return queue;
		}

		TEST_METHOD(EnqueueIsValid)
		{
			const CrtCheckMemory check;

			ArrayQueue<int> queue(4);

			queue.Enqueue(1);
			queue.Enqueue(2);
			queue.Enqueue(3);
			queue.Enqueue(4);

			Assert::AreEqual(1, queue.Dequeue());
			Assert::AreEqual(2, queue.Dequeue());
			Assert::AreEqual(3, queue.Dequeue());
			Assert::AreEqual(4, queue.Dequeue());
		}

		TEST_METHOD(IsFullandIsEmptyCorrectlyReturnsWhenNotFull_Sunny)
		{
			const CrtCheckMemory check;

			ArrayQueue<int> queue(4);

			queue.Enqueue(1);
			Assert::IsFalse(queue.IsEmpty());
			Assert::IsFalse(queue.IsFull());

			queue.Enqueue(2);
			queue.Enqueue(3);
			queue.Enqueue(4);

			Assert::IsTrue(queue.IsFull());

		}

		TEST_METHOD(IsFullCorrectlyThrowsWhenNotFull_Rainy)
		{
			const CrtCheckMemory check;

			ArrayQueue<int> queue(4);

			queue.Enqueue(1);
			queue.Enqueue(2);
			queue.Enqueue(3);
			queue.Enqueue(4);

			Assert::ExpectException<AdtException>([&] { queue.Enqueue(5); });

		}

		TEST_METHOD(IsEmptyCorrectlyThrowsWhenEmptyOnDequeue_Rainy)
		{
			const CrtCheckMemory check;

			ArrayQueue<int> queue(4);
			Assert::ExpectException<AdtException>([&] { queue.Dequeue(); });


			queue.Enqueue(1);
			queue.Enqueue(2);
			queue.Enqueue(3);
			queue.Enqueue(4);

			queue.Dequeue();
			queue.Dequeue();
			queue.Dequeue();
			queue.Dequeue();

			Assert::ExpectException<AdtException>([&] { queue.Dequeue(); });

		}
	};
}
