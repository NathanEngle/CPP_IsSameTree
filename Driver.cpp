/*
Nathan Engle
8/25/2021
Program Description: Implements binary tree data structure. Within the data structure is a function called bool isSameTree(Tree *) that takes an argument of a tree.  It returns true if the argument is the equivalent tree. Structure is ignored
*/

#include <iostream>
#include <string>
#include "BinarySearchTree.h"
#include "BinaryNodeTree.h"
#include <vector>

using namespace std;

int main()
{
	//
	//EXAMPLE 1
	// 	   binary node tree of strings
	// 	   example lifted from eLearn
	//
	BinaryNodeTree<string> theTree;
	theTree.add("abc");
	theTree.add("def");
	theTree.add("ghi");

	BinaryNodeTree<string> otherTree;
	otherTree.add("def");
	otherTree.add("abc");
	otherTree.add("ghi");

	BinaryNodeTree<string>* otherTreePtr = &otherTree;

	cout << "Example 1:" << endl;
	if (theTree.isSameTree(otherTreePtr))
	{
		cout << "Trees are equal" << endl;
	}
	else
	{
		cout << "Trees are NOT equal" << endl;
	}

	theTree.clear();
	otherTree.clear();
	cout << endl;

	//
	//EXAMPLE 2
	// 	   shared elements, but not exactly matched
	//

	theTree.add("abc");
	theTree.add("ghi");

	otherTree.add("abc");
	otherTree.add("def");
	otherTree.add("ghi");

	cout << "Example 2:" << endl;
	if (theTree.isSameTree(otherTreePtr))
	{
		cout << "Trees are equal" << endl;
	}
	else
	{
		cout << "Trees are NOT equal" << endl;
	}

	theTree.clear();
	otherTree.clear();
	cout << endl;

	//
	//EXAMPLE 3
	// 	   first example, but using a binary search tree instead
	//

	BinarySearchTree<string> theBSTree;
	BinarySearchTree<string> theOtherBSTree;

	BinarySearchTree<string>* otherBSTPtr = &theOtherBSTree;

	theBSTree.add("abc");
	theBSTree.add("def");
	theBSTree.add("ghi");

	theOtherBSTree.add("def");
	theOtherBSTree.add("abc");
	theOtherBSTree.add("ghi");

	cout << "Example 3:" << endl;
	if (theBSTree.isSameTree(otherBSTPtr))
	{
		cout << "Trees are equal" << endl;
	}
	else
	{
		cout << "Trees are NOT equal" << endl;
	}

	theBSTree.clear();
	theOtherBSTree.clear();
	cout << endl;

	//
	//EXAMPLE 4
	// 	   second example, but using a binary search tree instead
	//

	theBSTree.add("abc");
	theBSTree.add("ghi");

	theOtherBSTree.add("abc");
	theOtherBSTree.add("def");
	theOtherBSTree.add("ghi");

	cout << "Example 4:" << endl;
	if (theBSTree.isSameTree(otherBSTPtr))
	{
		cout << "Trees are equal" << endl;
	}
	else
	{
		cout << "Trees are NOT equal" << endl;
	}

	theBSTree.clear();
	theOtherBSTree.clear();
	cout << endl;

	//
	//EXAMPLE 5
	// 	   demonstrating desired behavior with numerical data types
	// 	   in this case, double
	//
	BinaryNodeTree<double> numTree;
	BinaryNodeTree<double> otNumTree;
	BinaryNodeTree<double>* numPtr = &otNumTree;

	numTree.add(38.4);
	numTree.add(50.048);
	numTree.add(11.0001);
	numTree.add(160);

	otNumTree.add(160);
	otNumTree.add(11.0001);
	otNumTree.add(50.048);
	otNumTree.add(38.4);

	cout << "Example 5:" << endl;
	if (numTree.isSameTree(numPtr))
	{
		cout << "Trees are equal" << endl;
	}
	else
	{
		cout << "Trees are NOT equal" << endl;
	}

	//
	//EXAMPLE 6
	// 	   repeat of example 5, with one more number added to the other tree
	// 	   now it returns false
	//

	otNumTree.add(682);
	cout << endl;

	cout << "Example 6:" << endl;
	if (numTree.isSameTree(numPtr))
	{
		cout << "Trees are equal" << endl;
	}
	else
	{
		cout << "Trees are NOT equal" << endl;
	}


	cout << endl << endl;
	system("pause");
	return 0;
}