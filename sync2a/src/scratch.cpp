//============================================================================
// Name        : scratch.cpp
// Author      : Homer Huang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
using namespace std;

int foo(int a)
{
	a += 1;
	cout << "I'm in foo" << endl;
	return a;
}

int main()
{
	int a = 1;
	int b = foo(a);

	cout << "!!!Hello World!!!" << b << endl; // prints !!!Hello World!!!
	return 0;
}
