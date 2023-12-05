#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB_11.2.B/lab_11.2.B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            const char* testFilename = "test.bin";

            ofstream testFile(testFilename, ios::binary);
            if (!testFile.is_open()) {
                Assert::Fail(L"Failed to create test file");
            }

            Student testData[] = {
                {"Surname1", 1,  Õ, 5, 4, 5},
                {"Surname2", 2, ≤Õ‘, 4, 5, 3},
                {"Surname3", 3, Ã“≈, 3, 5, 5},
                {"Surname4", 4, ‘“≤, 5, 5, 5},
                {"Surname5", 5, “Õ, 5, 5, 4}
            };

            testFile.write(reinterpret_cast<const char*>(testData), sizeof(testData));
            testFile.close();

            int countPhysics5 = 0, countMath5 = 0, countProg5 = 0, countChuslo = 0, countPed = 0;
            CountMarks(const_cast<char*>(testFilename), countPhysics5, countMath5, countProg5, countChuslo, countPed);
            
            Assert::AreEqual(3, countPhysics5);
            Assert::AreEqual(4, countMath5);

		}
	};
}
