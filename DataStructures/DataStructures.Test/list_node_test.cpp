#include "pch.h"
#include "CppUnitTest.h"
#include "list_node.hpp"
#include "crt_check_memory.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace data_structures;

namespace data_structures_tests
{
	TEST_CLASS(ListNodeTest)
	{
	public:

		static ListNode<int>* MakeIntNodePtr(int value)
		{
			return new ListNode<int>(value);
		}

		TEST_METHOD(NextPrev_SettersAndGettersRoundTrip)
		{
			const CrtCheckMemory check;

			//Arrange
			auto mid = MakeIntNodePtr(0);
			auto tail = MakeIntNodePtr(1);

			//Act
			mid->Next(tail);
			tail->Prev(mid);

			//Asserts
			Assert::AreEqual(static_cast<void*>(tail), static_cast<void*>(mid->Next()), L"Next pointer stored");
			Assert::AreEqual(static_cast<void*>(mid), static_cast<void*>(tail->Prev()), L"Prev pointer stored");

			delete mid;
			delete tail;
		}
	};
}
