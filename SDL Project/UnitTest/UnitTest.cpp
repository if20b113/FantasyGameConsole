#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int integer1 = 1;
			int integer2 = 2;
			Assert::AreNotEqual(integer1, integer2);
		}
	};
}
