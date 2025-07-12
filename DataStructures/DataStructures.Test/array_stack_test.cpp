#include "pch.h"
#include "CppUnitTest.h"
#include "array_stack.hpp"
#include "crt_check_memory.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace data_structures;

namespace data_structures_tests
{
	TEST_CLASS(ArrayStackTest)
	{
	public:

		static ArrayStack<std::string> ArrayStackStringFactory()
		{
			ArrayStack<string> my_array = ArrayStack<string>(10);

			for (auto i = 0ull; i < my_array.Capacity(); ++i)
			{
				my_array.Push(std::to_string(i));
			}
			return my_array;
		}

		static ArrayStack<int> ArrayStackintFactory()
		{
			ArrayStack<int> my_array = ArrayStack<int>(10);

			for (auto i = 0ull; i < static_cast<int>(my_array.Capacity()); ++i)
			{
				my_array.Push(i);
			}
			return my_array;
		}

		TEST_METHOD(PopPeekTest_WithStrings)
		{
			const CrtCheckMemory check;

			auto stack = ArrayStackStringFactory();

			for (auto i = stack.Capacity() -1; i > 0; i--)
			{
				Assert::AreEqual(std::to_string(i), stack.Peek());
				stack.Pop();
			}

		}
	};
}
