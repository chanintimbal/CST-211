#ifndef CRTCHECKMEMORY_H
#define CRTCHECKMEMORY_H

#include "pch.h"
#include "CppUnitTest.h"
#include "crtdbg.h"

#define _CRTDBG_MAP_ALLOC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace data_structures_tests
{
	struct CrtCheckMemory
	{
		_CrtMemState state1{};
		_CrtMemState state2{};
		_CrtMemState state3{};
		CrtCheckMemory()
		{
			_CrtMemCheckpoint(&state1);
		}

		CrtCheckMemory(const CrtCheckMemory& copy) = delete;
		CrtCheckMemory& operator=(const CrtCheckMemory& copy) = delete;
		CrtCheckMemory(CrtCheckMemory&& copy) = delete;
		CrtCheckMemory& operator=(CrtCheckMemory&& copy) = delete;

		~CrtCheckMemory()
		{
			_CrtMemCheckpoint(&state2);

			if (_CrtMemDifference(&state3, &state1, &state2) != 0)
			{
				Assert::Fail(L"Detected memory leaks!");
			}
		}
	};
}

#endif