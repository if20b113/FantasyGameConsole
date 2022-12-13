#include "pch.h"
#include "CppUnitTest.h"
#include <ctime>
#include <iostream>
#include <Windows.h>
#include <string>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	void adjustTimer(const int& minutes, const int& seconds, std::string* time)
	{
		//system("cls");
		time->clear(); // trash old
		(*time) = "";
		if (minutes >= 10)
		{
			time->append(std::to_string(minutes));
			time->append(":"); // 13: (example with 13 mins)
		}
		else
		{
			time->append("0");
			time->append(std::to_string(minutes));
			time->append(":"); // 03: (example with 3 mins)
		}

		if (seconds >= 10)
		{
			time->append(std::to_string(seconds));
		}
		else
		{
			time->append("0");
			time->append(std::to_string(seconds));
		}
	};

	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int integer1 = 1;
			int integer2 = 2;
			Assert::AreNotEqual(integer1, integer2);
		}

		TEST_METHOD(Timer)
		{
			// Warning, this test takes 2 minutes
			int minutes = 0;
			int seconds = 0;
			std::string timeStr = "00:00";
			bool run = true;
			std::cout << timeStr << std::endl;
			while (run)
			{
				seconds++;
				Sleep(1000); // use unistd for usleep if not windows.
				if (seconds == 60)
				{
					minutes++;
					seconds = 0;
				}
				adjustTimer(minutes, seconds, &timeStr);
				std::cout << timeStr << std::endl;
				if (minutes >= 2)
				{
					run = false;
				}
			}
			Assert::AreEqual(minutes, 2);
		}
	};
}
