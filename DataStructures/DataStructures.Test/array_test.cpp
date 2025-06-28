#include "pch.h"
#include "CppUnitTest.h"
#include "array.hpp"
#include "crt_check_memory.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace data_structures;

namespace data_structures_tests
{
    TEST_CLASS(ArrayTest)
    {
    public:

        // Helper factories for creating test arrays.
        static Array<size_t> ArrayFactory()
        {
            auto array = Array<size_t>{ 10 };
            for (size_t i = 0; i < 10; ++i)
            {
                array[i] = i;
            }
            return array;
        }

        static Array<size_t> ArrayFactory(size_t length)
        {
            auto array = Array<size_t>{ length };
            for (size_t i = 0; i < length; ++i)
            {
                array[i] = i;
            }
            return array;
        }

        static Array<string> ArrayStringFactory(size_t length)
        {
            auto array = Array<string>{ length };
            for (size_t i = 0; i < length; ++i)
            {
                // Create a string like "012" for index 0, "111" for index 1, etc.
                array[i] = std::to_string(i) + std::to_string(i) + std::to_string(i);
            }
            return array;
        }

        // --- Constructor Tests ---

        // Verify that the default constructor creates an array with no storage.
        TEST_METHOD(DefaultConstructor_ShouldYieldFalseBool)
        {
            const CrtCheckMemory check;
            Array<int> array;
            Assert::IsFalse(static_cast<bool>(array));
            Assert::AreEqual(static_cast<size_t>(0), array.size());
        }

        // Test that a constructor with a length initializes the array with default values.
        TEST_METHOD(ConstructorWithLength_DefaultInitialization)
        {
            const CrtCheckMemory check;
            Array<int> array(5);
            Assert::IsTrue(static_cast<bool>(array));
            Assert::AreEqual(static_cast<size_t>(5), array.size());
            for (size_t i = 0; i < array.size(); ++i)
            {
                // For ints, default initialization should give 0.
                Assert::AreEqual(0, array[i]);
            }
        }

        // Test the constructor that takes an external storage pointer.
        TEST_METHOD(ConstructorWithStorage_ShouldCopyData)
        {
            const CrtCheckMemory check;
            int data[5] = { 10, 20, 30, 40, 50 };
            Array<int> array(data, 5);
            Assert::AreEqual(static_cast<size_t>(5), array.size());
            for (size_t i = 0; i < 5; ++i)
            {
                Assert::AreEqual(data[i], array[i]);
            }
        }

        // --- Copy and Move Semantics Tests ---

        // Verify the copy constructor produces a deep copy.
        TEST_METHOD(CopyConstructor_ShouldCreateDeepCopy)
        {
            const CrtCheckMemory check;
            auto original = ArrayFactory();
            auto copy = Array<size_t>(original); // Copy constructor
            // Check that the arrays are equal.
            Assert::IsTrue(original == copy);
            // Modify original and verify that copy remains unchanged.
            original[0] = 999;
            Assert::AreNotEqual(original[0], copy[0]);
        }

        // Verify the copy assignment operator produces a deep copy.
        TEST_METHOD(CopyAssignmentOperator_ShouldDeepCopy)
        {
            const CrtCheckMemory check;
            auto original = ArrayFactory();
            auto copy = ArrayFactory(10);
            copy = original;
            Assert::IsTrue(original == copy);
            // Change one element in the copy and confirm the original is unaffected.
            copy[5] = 12345;
            Assert::AreNotEqual(original[5], copy[5]);
        }

        // Test the move constructor transfers ownership.
        TEST_METHOD(MoveConstructor_ShouldTransferOwnership)
        {
            const CrtCheckMemory check;
            auto temp = ArrayFactory();
            auto moved = std::move(temp);
            Assert::AreEqual(10ull, moved.size());
            // The moved-from array should now be in a safe empty state.
        }

        // Test the move assignment operator transfers ownership.
        TEST_METHOD(MoveAssignmentOperator_ShouldTransferOwnership)
        {
            const CrtCheckMemory check;
            auto array1 = ArrayFactory();
            auto array2 = ArrayFactory(10);
            array2 = std::move(array1);
            Assert::AreEqual(10ull, array2.size());
            // Since array1 was moved-from, its operator bool should return false.
            Assert::IsFalse(static_cast<bool>(array1));
        }

        // --- Operator[] Tests ---

        // Test non-const subscript operator for out-of-bounds access.
        TEST_METHOD(BracketOperatorOutofBounds_Greater_ShouldThrowEx)
        {
            const CrtCheckMemory check;
            auto should_throw = []() -> void
                {
                    auto array = Array<int>(10);
                    array[10] = 5; // Index 10 is out of bounds (valid indices: 0-9).
                };
            Assert::ExpectException<AdtException>(should_throw);
        }

        // Test const subscript operator for out-of-bounds access.
        TEST_METHOD(ConstBracketOperatorOutofBounds_ShouldThrowEx)
        {
            const CrtCheckMemory check;
            auto array = ArrayFactory();
            auto const_array = array; // Create a const copy.
            auto should_throw = [&]() -> void
                {
                    int value = const_array[10];
                    (void)value;
                };
            Assert::ExpectException<AdtException>(should_throw);
        }

        // --- Equality Operator Tests ---

        // Verify that identical arrays are considered equal.
        TEST_METHOD(EqualityOperator_ShouldReturnTrueForIdenticalArrays)
        {
            const CrtCheckMemory check;
            auto array1 = ArrayFactory();
            auto array2 = ArrayFactory();
            Assert::IsTrue(array1 == array2);
        }

        // Verify that arrays with different elements are not equal.
        TEST_METHOD(EqualityOperator_ShouldReturnFalseForDifferentArrays)
        {
            const CrtCheckMemory check;
            auto array1 = ArrayFactory();
            auto array2 = ArrayFactory();
            array2[0] = 999;
            Assert::IsFalse(array1 == array2);
        }

        // Verify that arrays with different lengths are not equal.
        TEST_METHOD(EqualityOperator_ShouldReturnFalseForDifferentLengths)
        {
            const CrtCheckMemory check;
            auto array1 = ArrayFactory(5);
            auto array2 = ArrayFactory(7);
            Assert::IsFalse(array1 == array2);
        }

        // --- Resizing Tests ---

        // Test reducing the length preserves the initial segment of data.
        TEST_METHOD(Length_ShouldResizeAndPersistData_Decrease)
        {
            const CrtCheckMemory check;
            auto array = ArrayFactory(10);
            array.resize(5);
            Assert::AreEqual(5ull, array.size());
            for (size_t i = 0; i < 5; ++i)
            {
                Assert::AreEqual(i, array[i]);
            }
        }

        // Test increasing the length preserves existing data and default initializes new elements.
        TEST_METHOD(Length_ShouldResizeAndPersistData_Increase)
        {
            const CrtCheckMemory check;
            auto array = ArrayFactory(5);
            array.resize(10);
            Assert::AreEqual(10ull, array.size());
            for (auto i = 0ull; i < 5; ++i)
            {
                Assert::AreEqual(i, array[i]);
            }
            // For ints, the new elements should be default initialized to 0.
            for (auto i = 5ull; i < 10; ++i)
            {
                Assert::AreEqual(0ull, array[i]);
            }
        }

        // --- Operator bool Tests ---

        // Verify that an array with allocated storage converts to true.
        TEST_METHOD(OperatorBool_ShouldReturnTrueForNonNullArray)
        {
            const CrtCheckMemory check;
            auto array = ArrayFactory();
            Assert::IsTrue(static_cast<bool>(array));
        }

        // Verify that a default-constructed array (with no storage) converts to false.
        TEST_METHOD(OperatorBool_ShouldReturnFalseForNullArray)
        {
            const CrtCheckMemory check;
            Array<int> array;
            Assert::IsFalse(static_cast<bool>(array));
        }
    };
}
