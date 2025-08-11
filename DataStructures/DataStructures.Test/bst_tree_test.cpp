#include "pch.h"
#include "CppUnitTest.h"
#include "bst_tree.hpp"
#include "crt_check_memory.hpp"
#include "vector"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace data_structures;

namespace data_structures_tests
{
	TEST_CLASS(BstTreeTest)
	{
	public:

		TEST_METHOD(Insert_At_find_Sunny)
		{
			const CrtCheckMemory check;

			//Arrange
			data_structures::BstTree<int, std::string> tree;

			auto result1 = tree.insert(10, "ten");
			auto& val1 = result1.first;
			bool inserted1 = result1.second;

			auto result2 = tree.insert(5, "five");
			auto& val2 = result2.first;
			bool inserted2 = result2.second;

			auto result3 = tree.insert(15, "fifteen");
			auto& val3 = result3.first;
			bool inserted3 = result3.second;

			//Assert
			Assert::IsTrue(inserted1);
			Assert::IsTrue(inserted2);
			Assert::IsTrue(inserted3);

			Assert::AreEqual(std::string("ten"), val1);
			Assert::AreEqual(std::string("five"), val2);
			Assert::AreEqual(std::string("fifteen"), val3);

			Assert::AreEqual(std::string("ten"), tree.at(10));
			Assert::AreEqual(std::string("five"), tree.at(5));
			Assert::AreEqual(std::string("fifteen"), tree.at(15));

			std::string* found = tree.find(5);
			Assert::IsNotNull(found);
			Assert::AreEqual(std::string("five"), *found);

			Assert::IsNull(tree.find(100));

			tree[10] = "TEN";

			Assert::AreEqual(std::string("TEN"), tree.at(10));
		}

		TEST_METHOD(IsEmpty_Height_Clear_Sunny)
		{
			const CrtCheckMemory check;

			//Arrange
			BstTree<int, int> tree;
			Assert::IsTrue(tree.Empty());
			Assert::AreEqual(0ull, tree.Height());

			//Act
			tree.insert(10, 100);
			tree.insert(5, 50);
			tree.insert(15, 150);

			//Assert
			Assert::IsFalse(tree.Empty());
			Assert::AreEqual(2ull, tree.Height()); // Height should be 2 with 3 nodes in balanced-ish tree

			//clear
			tree.Clear();

			//Assert
			Assert::IsTrue(tree.Empty());
			Assert::AreEqual(0ull, tree.Height());
		}

		TEST_METHOD(Lookup_Rainy)
		{
			const CrtCheckMemory check;

			//Arrange
			BstTree<std::string, int> tree;
			tree.insert("alpha", 1);
			tree.insert("bravo", 2);

			//Act & Assert
			Assert::ExpectException<AdtException>([&] {tree.at("charlie"); });

			//find() returns nullptr and **does not** throw
			int* pointer = tree.find("charlie");
			Assert::IsNull(pointer);

			//After clear, at() throws when looking for old data
			tree.Clear();
			Assert::ExpectException<AdtException>([&] {tree.at("alpha"); });
			Assert::IsNull(tree.find("alpha"));
		}

		TEST_METHOD(Erase_Sunny)
		{
			const CrtCheckMemory check;

			// Arrange
			BstTree<int, std::string> tree;
			tree.insert(10, "ten");
			tree.insert(5, "five");
			tree.insert(15, "fifteen");
			tree.insert(12, "twelve");
			tree.insert(20, "twenty");

			// Pre-assert: all inserted nodes are present
			Assert::AreEqual(std::string("ten"), tree.at(10));
			Assert::AreEqual(std::string("five"), tree.at(5));
			Assert::AreEqual(std::string("fifteen"), tree.at(15));
			Assert::AreEqual(std::string("twelve"), tree.at(12));
			Assert::AreEqual(std::string("twenty"), tree.at(20));

			// Act: erase leaf node
			tree.erase(20);
			Assert::IsNull(tree.find(20));
			Assert::AreEqual(std::string("ten"), tree.at(10));

			// Act: erase node with one child
			tree.erase(15);
			Assert::IsNull(tree.find(15));
			Assert::AreEqual(std::string("twelve"), tree.at(12));

			// Act: erase node with two children (root)
			tree.erase(10);
			Assert::IsNull(tree.find(10));
			Assert::IsNotNull(tree.find(5));
			Assert::IsNotNull(tree.find(12));

			// Act: erase remaining nodes
			tree.erase(5);
			tree.erase(12);

			// Assert tree is empty now
			Assert::IsTrue(tree.Empty());
			Assert::AreEqual(0ull, tree.Height());
		}

		TEST_METHOD(Traversals_Sunny)
		{
			const CrtCheckMemory check;

			//Arrange
			BstTree<int, int> tree;
			for (int i : {4, 2, 6, 1, 3, 5, 7})
				tree.insert(i, i * 10);

			std::vector<int> visited;

			//Act

			//InOrder: 1,2,3,4,5,6,7
			visited.clear();
			tree.VisitFunction([&](const PairNode<int, int>* p)
			{
				visited.push_back(p->Key());
			});
			tree.InOrder();
			Assert::AreEqual(7ull, visited.size());
			Assert::IsTrue(std::is_sorted(visited.begin(), visited.end()));

			//PreOrder: 4,2,1,3,6,5,7
			visited.clear();
			tree.VisitFunction([&](auto p) {visited.push_back(p->Key()); });
			tree.PreOrder();
			std::vector<int> expPre = { 4, 2, 1, 3, 6, 5, 7 };
			Assert::IsTrue(visited == expPre);

			// PostOrder: 1, 3, 2, 5, 7, 6, 4
			visited.clear();
			tree.VisitFunction([&](auto p) { visited.push_back(p->Key()); });
			tree.PostOrder();
			std::vector<int> expPost = { 1, 3, 2, 5, 7, 6, 4 };
			Assert::IsTrue(visited == expPost);

			// BreadthFirst: 4, 2, 6, 1, 3, 5, 7
			visited.clear();
			tree.VisitFunction([&](auto p) { visited.push_back(p->Key()); });
			tree.BreadthFirst();
			std::vector<int> expBre = { 4, 2, 6, 1, 3, 5, 7 };
			Assert::IsTrue(visited == expBre);
		}

		TEST_METHOD(Sunny_Day_Equality)
		{
			const CrtCheckMemory check;

			// Arrange
			BstTree<int, std::string> tree1;
			BstTree<int, std::string> tree2;

			tree1.insert(10, "ten");
			tree1.insert(5, "five");
			tree1.insert(15, "fifteen");

			tree2.insert(10, "ten");
			tree2.insert(5, "five");
			tree2.insert(15, "fifteen");

			// Act & Assert
			Assert::IsTrue(tree1 == tree2);

			tree2[5] = "FIVE"; 

			Assert::IsFalse(tree1 == tree2);
			Assert::IsTrue(tree1 != tree2);
		}

		TEST_METHOD(Indexer_sunny_default_check_intIs0)
		{
			const CrtCheckMemory check;

			// Arrange
			BstTree<int, int> tree;

			// Act & Assert
			//default int value 0
			int& val = tree[42];
			Assert::AreEqual(0, val);

			val = 123;
			Assert::AreEqual(123, tree.at(42));
		}

	};
}
