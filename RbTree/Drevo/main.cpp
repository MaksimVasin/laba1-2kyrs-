#include <iostream>
#include "RbTree.cpp"
using namespace std;

int main()
{
	RBTree <float, char> TestRbTree;
	TestRbTree.insert(20, 'H');
	TestRbTree.insert(10, 'L');
	TestRbTree.insert(30, 'R');
	TestRbTree.insert(0, 'L');
	TestRbTree.insert(40, 'E');
	TestRbTree.insert(35, 'W');
	TestRbTree.insert(5, 'G');
	TestRbTree.insert(15, 'O');
	TestRbTree.insert(25, 'J');
	TestRbTree.insert(32, 'O');
	TestRbTree.insert(7, 'L');
	TestRbTree.insert(6, 'E');
	TestRbTree.insert(33, 'L');
	TestRbTree.insert(100, 'D');

	TestRbTree.print_to_console();

	TestRbTree.remove(25);
	TestRbTree.remove(40);
	TestRbTree.remove(5);
	TestRbTree.remove(7);

	TestRbTree.print_to_console();

	cout << endl << " Keys: ";
	float* keys = TestRbTree.get_keys();
	//cout << endl << " Size: " << _msize(keys) / sizeof(float);
	for (int i = 0; i < TestRbTree.get_sizeTree(); i++)
	{
		cout << keys[i] << " ";
	}

	cout << endl << " Values: ";
	char* values = TestRbTree.get_values();
	for (int i = 0; i < TestRbTree.get_sizeTree(); i++)
	{
		cout << values[i] << " ";
	}

	TestRbTree.clear();
	cout << endl << " The end. ";
}