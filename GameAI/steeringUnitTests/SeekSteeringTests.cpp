#include "stdafx.h"
#include "CppUnitTest.h"

#include "SeekSteering.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace steeringUnitTests
{
	TEST_CLASS(Seek_Steering_Tests)
	{
	public:

		TEST_METHOD(testME_expect_argument)
		{
			SeekSteering testClass = SeekSteering(1, Vector2D(1.0f, 1.0f), 1);
			//int value = testClass.testMe(7);
			//Assert::AreEqual(7, value);
		}

	};
}