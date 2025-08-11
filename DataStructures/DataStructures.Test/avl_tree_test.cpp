#include "pch.h"
#include "CppUnitTest.h"
#include "avl_tree.hpp"
#include "crt_check_memory.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace data_structures;

namespace data_structures_tests
{
	TEST_CLASS(AvlTreeTest)
	{
	public:

		TEST_METHOD(Insert_At_Find_Sunny)
		{
			const CrtCheckMemory check;

			//Arrange
			AvlTree <std::string, int> tree;

			//Act
			auto [refA, wasNewA] = tree.insert("apple", 1);
			auto [refB, wasNewB] = tree.insert("banana", 1);
			auto [refA2, wasNewA2] = tree.insert("apple", 42); //duplicate

			//Assert
			Assert::IsTrue(wasNewA, L"First insert of apple should be new");
			Assert::IsTrue(wasNewB, L"First insert of banana should be new");
			Assert::IsTrue(wasNewA2, L"second insert of apple must not be new");
			Assert::AreEqual(1, refA, L"value return for first apple insert must be 1");

			//Act and Assert
			Assert::AreEqual(1, tree.at("apple"), L"at ('apple') should be 1");
			Assert::AreEqual(2, tree.at("banana"), L"at ('banana') should be 2");

			//Act
			int* pBanana = tree.find("banana");

			//Assert
			Assert::IsNotNull(pBanana, L"find('banana') should succeed");
			Assert::AreEqual(2, *pBanana, L"find('banana') should return pointer value to 2");

			//Arrange
			const AvlTree <std::string, int>& ctree = tree;

			//Act
			const int* cpApple = ctree.find("Apple");

			//Assert
			Assert::IsNotNull(cpApple, L"const find ('apple') should succeed");
			Assert::AreEqual(1, *cpApple, L"const find('apple') should return 1");

		}
	};
}
