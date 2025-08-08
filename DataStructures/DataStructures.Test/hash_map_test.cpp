#include "pch.h"
#include "CppUnitTest.h"
#include "adt_exception.hpp"
#include "hash_map.hpp"  
#include "crt_check_memory.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace data_structures;

namespace data_structures_tests
{
	TEST_CLASS(HashMapTest)
	{
	public:

		TEST_METHOD(SUNNY_AddAndRetrieve)
		{
			const CrtCheckMemory check;

			auto hashFn = [](const int& key) { return std::hash<int>{}(key); };
			HashMap<int, std::string> map(5, hashFn);

			Assert::IsTrue(map.TryAdd(1, "one"));
			Assert::IsTrue(map.TryAdd(2, "two"));
			Assert::IsFalse(map.TryAdd(1, "uno"));  // duplicate key

			map.Put(2, "deux");  // overwrite

			std::string value;
			Assert::IsTrue(map.TryGetValue(1, value));
			Assert::AreEqual(std::string("one"), value);

			Assert::IsTrue(map.TryGetValue(2, value));
			Assert::AreEqual(std::string("deux"), value);

			Assert::AreEqual(size_t(2), map.Count());

			// operator[] non-const inserts default if missing
			Assert::AreEqual(std::string(""), map[3]);
			Assert::AreEqual(size_t(3), map.Count());

			map[3] = "three";
			Assert::AreEqual(std::string("three"), map[3]);
		}

		TEST_METHOD(RAINY_AccessMissingKeyThrows)
		{
			const CrtCheckMemory check;

			auto hashFn = [](const int& key) { return std::hash<int>{}(key); };
			HashMap<int, std::string> map(3, hashFn);

			map.Put(1, "one");

			const auto& const_map = map;

			auto func = [&const_map]()
				{
					auto val = const_map[42]; 
				};

			Assert::ExpectException<AdtException>(func);
		}

		TEST_METHOD(RAINY_RemoveMissingKeyReturnsFalse)
		{
			const CrtCheckMemory check;

			auto hashFn = [](const int& key) { return std::hash<int>{}(key); };
			HashMap<int, std::string> map(3, hashFn);

			map.Put(1, "one");

			Assert::IsFalse(map.Remove(999));
		}

		TEST_METHOD(SUNNY_RemoveExistingKey)
		{
			const CrtCheckMemory check;

			auto hashFn = [](const int& key) { return std::hash<int>{}(key); };

			HashMap<int, std::string> map(3, hashFn);

			map.Put(1, "one");
			map.Put(2, "two");

			Assert::IsTrue(map.Remove(1));
			Assert::AreEqual(size_t(1), map.Count());

			std::string removedVal;
			Assert::IsTrue(map.Remove(2, &removedVal));
			Assert::AreEqual(std::string("two"), removedVal);
			Assert::AreEqual(size_t(0), map.Count());
		}
	};
}
