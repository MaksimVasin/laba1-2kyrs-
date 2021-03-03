#include "pch.h"
#include "CppUnitTest.h"
#include "../Drevo/RbTree.h"
#include "../Drevo/RbTree.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestRBTree
{
	TEST_CLASS(TestRBTree)
	{
	public:
		RBTree <float, char> TestRbTree;
		/////////////////////////////////////////////////////////////////////////////// Insert
		TEST_METHOD(insert_first)
		{
			TestRbTree.insert(2.5, 'A');
			Assert::AreEqual(TestRbTree.get_keys()[0], (float)2.5);
		}
		TEST_METHOD(insert_2)
		{
			// левый поворот для 3, правый поворот для 5 и перекрашивание
			TestRbTree.insert(5, 'A');///////// 5 /////////////
			TestRbTree.insert(3, 'B');///// 3 ////// nil /////
			TestRbTree.insert(4, 'C');//////// 4 ////////////
			float* arr = TestRbTree.get_keys();
			Assert::AreEqual(arr[0], (float)4);//////// 3 //////////
			Assert::AreEqual(arr[1], (float)3);//// 4 //// 5 //////
			Assert::AreEqual(arr[2], (float)5);///////////////////
		}
		TEST_METHOD(insert_3) // зеркальная проверка
		{
			TestRbTree.insert(5, 'A');
			TestRbTree.insert(7, 'B');
			TestRbTree.insert(6, 'C');
			float* arr = TestRbTree.get_keys();
			Assert::AreEqual(arr[0], (float)6);
			Assert::AreEqual(arr[1], (float)5);
			Assert::AreEqual(arr[2], (float)7);
		}
		TEST_METHOD(insert_4)
		{
			TestRbTree.insert(5, 'A');
			TestRbTree.insert(3, 'B');
			TestRbTree.insert(4, 'C');
			TestRbTree.insert(1, 'D');
			TestRbTree.insert(0, 'E');
			float* arr = TestRbTree.get_keys();
			Assert::AreEqual(arr[1], (float)1);
			Assert::AreEqual(arr[2], (float)0);
		}
		/////////////////////////////////////////////////////////////////////////////// find
		TEST_METHOD(find_test)
		{
			TestRbTree.insert(2, 'A');
			TestRbTree.insert(1, 'A');
			TestRbTree.insert(3, 'A');
			Assert::AreEqual(TestRbTree.find(2), true); // find root
			Assert::AreEqual(TestRbTree.find(1), true); // find node
			Assert::AreEqual(TestRbTree.find(999), false); // not find
		}
		/////////////////////////////////////////////////////////////////////////////// remove
		TEST_METHOD(remove_root)
		{
			TestRbTree.insert(5, 'A');
			TestRbTree.remove(5);
			float* arr = TestRbTree.get_keys();
			Assert::AreEqual(TestRbTree.get_sizeTree(), (size_t)0);
			TestRbTree.insert(4, 'B'); // проверка можно ли вновь добавить
			arr = TestRbTree.get_keys();
			Assert::AreEqual(arr[0], (float)4);
		}
		TEST_METHOD(remove_2nils)
		{
			TestRbTree.insert(2, 'A');
			TestRbTree.insert(1, 'A');
			TestRbTree.insert(3, 'A');
			TestRbTree.remove(3);
			Assert::AreEqual(TestRbTree.find(3), false);
		}
		TEST_METHOD(remove_1child_1nil)
		{
			TestRbTree.insert(5, 'A');
			TestRbTree.insert(10, 'A');
			TestRbTree.insert(3, 'A');
			TestRbTree.insert(15, 'A');
			TestRbTree.remove(10);
			Assert::AreEqual(TestRbTree.find(10), false);
		}
		TEST_METHOD(remove_2childs)
		{
			TestRbTree.insert(5, 'A');
			TestRbTree.insert(10, 'A');
			TestRbTree.insert(3, 'A');
			TestRbTree.insert(15, 'A');
			TestRbTree.insert(7, 'A');
			TestRbTree.remove(10);
			Assert::AreEqual(TestRbTree.find(10), false);
			Assert::AreEqual(TestRbTree.find(7), true);
			Assert::AreEqual(TestRbTree.find(15), true);

		}
		TEST_METHOD(remove_1)
		{
			TestRbTree.insert(20, 'A');
			TestRbTree.insert(10, 'A');
			TestRbTree.insert(30, 'A');
			TestRbTree.insert(0, 'A');
			TestRbTree.insert(40, 'A');
			TestRbTree.insert(35, 'A');
			TestRbTree.insert(5, 'A');
			TestRbTree.insert(15, 'A');
			TestRbTree.insert(25, 'A');
			TestRbTree.insert(32, 'A');
			TestRbTree.insert(7, 'A');
			TestRbTree.insert(6, 'A');
			TestRbTree.insert(33, 'A');
			// 20 5 0 10 7 6 15 35 30 25 32 33 40
			TestRbTree.remove(5);
			float* arr = TestRbTree.get_keys();
			Assert::AreEqual(arr[1], (float)6);
		}
		TEST_METHOD(remove_2)
		{
			TestRbTree.insert(20, 'A');
			TestRbTree.insert(10, 'A');
			TestRbTree.insert(30, 'A');
			TestRbTree.insert(0, 'A');
			TestRbTree.insert(40, 'A');
			TestRbTree.insert(35, 'A');
			TestRbTree.insert(5, 'A');
			TestRbTree.insert(15, 'A');
			TestRbTree.insert(25, 'A');
			TestRbTree.insert(32, 'A');
			TestRbTree.insert(7, 'A');
			TestRbTree.insert(6, 'A');
			TestRbTree.insert(33, 'A');
			// 20 5 0 10 7 6 15 35 30 25 32 33 40
			TestRbTree.remove(35);
			float* arr = TestRbTree.get_keys();
			Assert::AreEqual(arr[7], (float)30);
			Assert::AreEqual(arr[9], (float)33);
			Assert::AreEqual(arr[11], (float)40);
		}
		/////////////////////////////////////////////////////////////////////////////// clear
		TEST_METHOD(clear)
		{
			TestRbTree.insert(20, 'A');
			TestRbTree.insert(10, 'A');
			TestRbTree.insert(30, 'A');
			TestRbTree.insert(0, 'A');
			TestRbTree.insert(40, 'A');
			TestRbTree.clear();
			Assert::AreEqual(TestRbTree.get_sizeTree(), (size_t)0);
		}
	};
}
