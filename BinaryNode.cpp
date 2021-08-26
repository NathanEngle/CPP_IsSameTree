/*
Nathan Engle
8/25/2021
Program Description: Implements binary tree data structure. Within the data structure is a function called bool isSameTree(Tree *) that takes an argument of a tree.  It returns true if the argument is the equivalent tree. Structure is ignored
*/


#include "BinaryNode.h"

template<class ItemType>
BinaryNode<ItemType>::BinaryNode()
	: item(nullptr), leftChildPtr(nullptr), rightChildPtr(nullptr)
{}

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem)
	: item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr)
{}

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem,
	std::shared_ptr<BinaryNode<ItemType>> leftPtr,
	std::shared_ptr<BinaryNode<ItemType>> rightPtr)
	: item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr)
{}

template<class ItemType>
void BinaryNode<ItemType>::setItem(const ItemType& anItem)
{
	item = anItem;
}

template<class ItemType>
ItemType BinaryNode<ItemType>::getItem() const
{
	return item;
}

template<class ItemType>
bool BinaryNode<ItemType>::isLeaf() const
{
	return ((leftChildPtr == nullptr) && (rightChildPtr == nullptr));
}

template<class ItemType>
auto BinaryNode<ItemType>::getLeftChildPtr() const
{
	return leftChildPtr;
}

template<class ItemType>
auto BinaryNode<ItemType>::getRightChildPtr() const
{
	return rightChildPtr;
}

template<class ItemType>
void BinaryNode<ItemType>::setLeftChildPtr(std::shared_ptr<BinaryNode<ItemType>> leftPtr)
{
	leftChildPtr = leftPtr;
}

template<class ItemType>
void BinaryNode<ItemType>::setRightChildPtr(std::shared_ptr<BinaryNode<ItemType>> rightPtr)
{
	rightChildPtr = rightPtr;
}


template<class ItemType>
void BinaryNode<ItemType>::toVector(std::vector<ItemType>& v)
{

	if (leftChildPtr != nullptr)
	{
		leftChildPtr->toVector(v);
	}
	v.push_back(this->getItem());
	if (rightChildPtr != nullptr)
	{
		rightChildPtr->toVector(v);
	}
}