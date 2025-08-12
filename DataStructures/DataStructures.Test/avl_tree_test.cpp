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
			auto [refB, wasNewB] = tree.insert("banana", 2);
			auto [refA2, wasNewA2] = tree.insert("apple", 42); //duplicate

			//Assert
			Assert::IsTrue(wasNewA, L"First insert of apple should be new");
			Assert::IsTrue(wasNewB, L"First insert of banana should be new");
			Assert::IsFalse(wasNewA2, L"second insert of apple must not be new");
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
			const int* cpApple = ctree.find("apple");

			//Assert
			Assert::IsNotNull(cpApple, L"const find ('apple') should succeed");
			Assert::AreEqual(1, *cpApple, L"const find('apple') should return 1");
		}

		TEST_METHOD(Empty_Height_Clear_Sunny)
		{
			const CrtCheckMemory check;

			//Arrange
			AvlTree<int, int> tree;

			//Assert
			Assert::IsTrue(tree.Empty(), L"New tree should be empty");
			Assert::AreEqual(0ull, tree.Height(), L"Height of empty tree should be 0");

			
			//Act
			tree.insert(10, 100);
			tree.insert(5, 50);
			tree.insert(15, 150);


			//Assert
			Assert::IsFalse(tree.Empty(), L"Tree should not be empty after inserts");
			Assert::AreEqual(2ull, tree.Height(), L"Height after inserts should be 2");

			//Act
			tree.Clear();

			//Assert
			Assert::IsTrue(tree.Empty(), L"Tree should be empty after Clear");
			Assert::AreEqual(0ull, tree.Height(), L"Height after Clear should be 0");
		}

		TEST_METHOD(Lookup_Rainy)
		{
			const CrtCheckMemory check;

			//Arrange
			AvlTree <std::string, int> tree;

			//Act
			tree.InsertImpl("aloha", 1);
			tree.InsertImpl("bravo", 2);

			//Assert
			Assert::ExpectException<AdtException>([&] {tree.at("charlie"); });

			int* pointer = tree.find("charlie");
			Assert::IsNull(pointer);

			tree.Clear();
			Assert::ExpectException<AdtException>([&] {tree.at("alpha");  });
			Assert::IsNull(tree.find("alpha"));
		}

		TEST_METHOD(Traversals_Sunny)
		{
			const CrtCheckMemory check;

			//Arrange
			AvlTree<int, int> tree;
			for (int i : {4, 2, 6, 1, 3, 5, 7})
				tree.insert(i, i * 10);

			std::vector<int> visited;

			//Act
			// InOrder
			visited.clear();
			tree.VisitFunction([&](const PairNode<int, int>* p) { visited.push_back(p->Key()); });
			tree.InOrder();
			Assert::AreEqual(7ull, visited.size());
			Assert::IsTrue(std::is_sorted(visited.begin(), visited.end()));

			// PreOrder
			visited.clear();
			tree.VisitFunction([&](auto p) { visited.push_back(p->Key()); });
			tree.PreOrder();
			std::vector expectedPreOrder = { 4, 2, 1, 3, 6, 5, 7 };
			Assert::IsTrue(visited == expectedPreOrder);

			// PostOrder
			visited.clear();
			tree.VisitFunction([&](auto p) { visited.push_back(p->Key()); });
			tree.PostOrder();
			std::vector expectedPostOrder = { 1, 3, 2, 5, 7, 6, 4 };
			Assert::IsTrue(visited == expectedPostOrder); 
			
			// BreadthFirst
			visited.clear();
			tree.VisitFunction([&](auto p) { visited.push_back(p->Key()); });
			tree.BreadthFirst();
			std::vector expectedBreadthFirst = { 4, 2, 6, 1, 3, 5, 7 };
			Assert::IsTrue(visited == expectedBreadthFirst);
		}
		
		TEST_METHOD(Indexer_Sunny)
		{
			const CrtCheckMemory check;

			data_structures::AvlTree<std::string, int> tree;
			tree.InsertImpl("one", 1);
			tree.InsertImpl("two", 2);

			Assert::AreEqual(1, tree["one"]);
			Assert::AreEqual(2, tree["two"]);
			Assert::AreEqual(0, tree["three"]);

			tree["three"] = 3;
			Assert::AreEqual(3, tree["three"]);
		}

		TEST_METHOD(RotateRight_Sunny)
		{
			const CrtCheckMemory check;

			AvlTree<int, int> tree;


			tree.insert(3, 30);
			tree.insert(2, 20);
			tree.insert(1, 10); 

			std::vector<int> visited;
			visited.clear();
			tree.VisitFunction([&](auto p) {visited.push_back(p->Key());  });
			tree.BreadthFirst();
			std::vector expBre = { 2, 1, 3 };
			Assert::IsTrue(visited == expBre);
		}
	};
}
