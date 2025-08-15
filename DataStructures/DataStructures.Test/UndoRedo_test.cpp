#include "pch.h"
#include "CppUnitTest.h"
#include "UndoRedo.hpp"
#include "crt_check_memory.hpp"
#include "adt_exception.hpp"
using namespace data_structures;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace data_structures_tests
{
    TEST_CLASS(UndoRedoUnitTests)
    {
    public:

        TEST_METHOD(Sunny_Initialization)
        {
            UndoRedo<int> ur(5);
            Assert::AreEqual<size_t>(5, ur.MaxHistory());
            Assert::IsFalse(ur.CanUndo());
            Assert::IsFalse(ur.CanRedo());
            Assert::AreEqual<size_t>(0, ur.UndoSize());
            Assert::AreEqual<size_t>(0, ur.RedoSize());
        }

        TEST_METHOD(Sunny_DoOperation)
        {
            UndoRedo<int> ur(3);
            ur.Do(1);
            ur.Do(2);
            Assert::IsTrue(ur.CanUndo());
            Assert::IsFalse(ur.CanRedo());
            Assert::AreEqual<size_t>(2, ur.UndoSize());
        }

        TEST_METHOD(Sunny_UndoRedoOperations)
        {
            UndoRedo<int> ur(3);
            ur.Do(10);
            ur.Do(20);
            ur.Do(30);

            Assert::AreEqual(30, ur.Undo());
            Assert::AreEqual<size_t>(1, ur.RedoSize());
            Assert::AreEqual<size_t>(2, ur.UndoSize());

            Assert::AreEqual(30, ur.Redo());
            Assert::AreEqual<size_t>(2, ur.UndoSize());
            Assert::AreEqual<size_t>(0, ur.RedoSize());
        }

        TEST_METHOD(Sunny_BoundedHistory)
        {
            UndoRedo<int> ur(2);
            ur.Do(1);
            ur.Do(2);
            ur.Do(3);

            Assert::AreEqual<size_t>(2, ur.UndoSize());
            Assert::AreEqual(3, ur.Undo());
            Assert::AreEqual(2, ur.Undo());
            Assert::IsFalse(ur.CanUndo());
        }

        TEST_METHOD(Sunny_ClearHistory)
        {
            UndoRedo<int> ur(3);
            ur.Do(1);
            ur.Do(2);
            ur.Clear();
            Assert::IsFalse(ur.CanUndo());
            Assert::IsFalse(ur.CanRedo());
            Assert::AreEqual<size_t>(0, ur.UndoSize());
            Assert::AreEqual<size_t>(0, ur.RedoSize());
        }

        TEST_METHOD(Rainy_ExceptionOnInvalidUndoRedo)
        {
            UndoRedo<int> ur(2);
            auto undoLambda = [&]() { ur.Undo(); };
            auto redoLambda = [&]() { ur.Redo(); };
            Assert::ExpectException<AdtException>(undoLambda);
            Assert::ExpectException<AdtException>(redoLambda);

            ur.Do(5);
            ur.Undo();
            ur.Redo();
            Assert::ExpectException<AdtException>([&]() { ur.Redo(); });
        }

        TEST_METHOD(Sunny_CopyConstructor)
        {
            UndoRedo<int> ur1(3);
            ur1.Do(1);
            ur1.Do(2);

            UndoRedo<int> ur2(ur1);
            Assert::AreEqual<size_t>(2, ur2.UndoSize());
            Assert::AreEqual(2, ur2.Undo());
            Assert::AreEqual(1, ur2.Undo());
        }

        TEST_METHOD(Sunny_CopyAssignment)
        {
            UndoRedo<int> ur1(3);
            ur1.Do(1);
            ur1.Do(2);

            UndoRedo<int> ur2(3);
            ur2 = ur1;
            Assert::AreEqual<size_t>(2, ur2.UndoSize());
            Assert::AreEqual(2, ur2.Undo());
            Assert::AreEqual(1, ur2.Undo());
        }

        TEST_METHOD(Sunny_MoveConstructor)
        {
            UndoRedo<int> ur1(3);
            ur1.Do(1);
            ur1.Do(2);

            UndoRedo<int> ur2(std::move(ur1));
            Assert::AreEqual<size_t>(2, ur2.UndoSize());
            Assert::AreEqual(2, ur2.Undo());
            Assert::AreEqual(1, ur2.Undo());
        }

        TEST_METHOD(Sunny_MoveAssignment)
        {
            UndoRedo<int> ur1(3);
            ur1.Do(1);
            ur1.Do(2);

            UndoRedo<int> ur2(3);
            ur2 = std::move(ur1);
            Assert::AreEqual<size_t>(2, ur2.UndoSize());
            Assert::AreEqual(2, ur2.Undo());
            Assert::AreEqual(1, ur2.Undo());
        }
    };
}
