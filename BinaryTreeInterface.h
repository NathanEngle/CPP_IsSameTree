/*
Nathan Engle
8/25/2021
Program Description: Implements binary tree data structure. Within the data structure is a function called bool isSameTree(Tree *) that takes an argument of a tree.  It returns true if the argument is the equivalent tree. Structure is ignored
*/

#pragma once
#include "NotFoundException.h"
template<class ItemType>
class BinaryTreeInterface
{
public:
	virtual bool isEmpty() const = 0;
	virtual int getHeight() const = 0;
	virtual int getNumberOfNodes() const = 0;
	virtual ItemType getRootData() const = 0;
	virtual void setRootData(const ItemType& newData) = 0;
	virtual bool add(const ItemType& data) = 0;
	virtual bool remove(const ItemType& data) = 0;
	virtual void clear() = 0;
	virtual ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException) = 0;
	virtual bool contains(const ItemType& anEntry) const = 0;

	/** Traverses this binary tree in preorder (inorder, postorder) and
	calls the function visit once for each node.
	@param visit A client-defined function that performs an operation on
	or with the data in each visited node. */
	virtual void preorderTraverse(void visit(ItemType&)) const = 0;
	virtual void inorderTraverse(void visit(ItemType&)) const = 0;
	virtual void postorderTraverse(void visit(ItemType&)) const = 0;

	//Destructor
	virtual ~BinaryTreeInterface() {  }
};