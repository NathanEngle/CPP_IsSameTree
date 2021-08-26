/*
Nathan Engle
8/25/2021
Program Description: Implements binary tree data structure. Within the data structure is a function called bool isSameTree(Tree *) that takes an argument of a tree.  It returns true if the argument is the equivalent tree. Structure is ignored
*/

#pragma once
#include <memory>
#include <vector>
template<class ItemType>
class BinaryNode
{
private:
	ItemType item;
	std::shared_ptr<BinaryNode<ItemType>> leftChildPtr;
	std::shared_ptr<BinaryNode<ItemType>> rightChildPtr;
public:
	BinaryNode();
	BinaryNode(const ItemType& anItem);
	BinaryNode(const ItemType& anItem,
		std::shared_ptr<BinaryNode<ItemType>> leftPtr,
		std::shared_ptr<BinaryNode<ItemType>> rightPtr);

	void setItem(const ItemType& anItem);
	ItemType getItem() const;

	bool isLeaf() const;

	auto getLeftChildPtr() const;
	auto getRightChildPtr() const;

	void setLeftChildPtr(std::shared_ptr<BinaryNode<ItemType>> leftPtr);
	void setRightChildPtr(std::shared_ptr<BinaryNode<ItemType>> rightPtr);

	void toVector(std::vector<ItemType>& v);
};
#include "BinaryNode.cpp"