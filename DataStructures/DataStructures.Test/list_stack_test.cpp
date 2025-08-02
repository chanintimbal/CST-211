#include "pch.h"
#include "CppUnitTest.h"
#include "crt_check_memory.hpp"
#include "list_stack.hpp"
#include "adt_exception.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace data_structures;

namespace data_structures_tests
{
	TEST_CLASS(ListStackTest)
	{
	public:

		TEST_METHOD(PushPop_Sunny_ShouldBeLikeStack)
		{
			const CrtCheckMemory check;

			ListStack<int> stack;
			stack.Push(10);
			stack.Push(20);
			stack.Push(30);

			Assert::AreEqual(30, stack.Pop());
			Assert::AreEqual(20, stack.Pop());
			Assert::AreEqual(10, stack.Pop());

			Assert::IsTrue(stack.IsEmpty());
		}

		TEST_METHOD(Peek_Sunny_ShouldReturnTop)
		{
			const CrtCheckMemory check;

			ListStack<std::string> stack;
			stack.Push("A");
			stack.Push("B");

			Assert::AreEqual(std::string("B"), stack.Peek());
			Assert::AreEqual(std::string("B"), stack.Peek());  // still B
			Assert::AreEqual(std::string("B"), stack.Pop());
			Assert::AreEqual(std::string("A"), stack.Pop());
		}

		TEST_METHOD(Pop_Rainy_EmptyStackShouldThrow)
		{
			const CrtCheckMemory check;

			ListStack<int> stack;

			try
			{
				stack.Pop();
				Assert::Fail(L"Expected AdtException when popping from empty stack.");
			}
			catch (const AdtException& ex)
			{
				Assert::AreEqual("Stack is empty, nothing to pop", ex.what());
			}
			catch (...)
			{
				Assert::Fail(L"Unexpected exception type thrown.");
			}
		}

		TEST_METHOD(Peek_Rainy_EmptyStackShouldThrow)
		{
			const CrtCheckMemory check;

			ListStack<char> stack;

			try
			{
				stack.Peek();
				Assert::Fail(L"Expected AdtException when peeking into empty stack.");
			}
			catch (const AdtException& ex)
			{
				Assert::AreEqual("Stack is empty, nothing to peek", ex.what());
			}
			catch (...)
			{
				Assert::Fail(L"Unexpected exception type thrown.");
			}
		}

		TEST_METHOD(Clear_Sunny_ShouldEmptyStack)
		{
			const CrtCheckMemory check;

			ListStack<int> stack;
			stack.Push(1);
			stack.Push(2);
			stack.Push(3);

			stack.Clear();
			Assert::IsTrue(stack.IsEmpty());

			try
			{
				stack.Peek();
				Assert::Fail(L"Expected AdtException after clearing stack and peeking.");
			}
			catch (const AdtException&) {}
		}
	};
}
