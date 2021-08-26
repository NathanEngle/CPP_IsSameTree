/*
Nathan Engle
8/25/2021
Program Description: Implements binary tree data structure. Within the data structure is a function called bool isSameTree(Tree *) that takes an argument of a tree.  It returns true if the argument is the equivalent tree. Structure is ignored
*/


#include "BinaryNodeTree.h"
#include "BinaryNode.h"
#include <iostream>
#include <memory>

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const
{
	if (subTreePtr == nullptr)
	{
		return 0;
	}
	else
	{
		return 1 + std::max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
	}
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const
{
	if (subTreePtr == nullptr)
	{
		return 0;
	}
	else
	{
		return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
	}
}


template<class ItemType>
auto BinaryNodeTree<ItemType>::balancedAdd(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
	std::shared_ptr<BinaryNode<ItemType>> newNodePtr)
{
	if (subTreePtr == nullptr)
	{
		return newNodePtr;
	}
	else
	{
		auto leftPtr = subTreePtr->getLeftChildPtr();
		auto rightPtr = subTreePtr->getRightChildPtr();

		if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
		{
			rightPtr = balancedAdd(rightPtr, newNodePtr);
			subTreePtr->setRightChildPtr(rightPtr);
		}
		else
		{
			leftPtr = balancedAdd(leftPtr, newNodePtr);
			subTreePtr->setLeftChildPtr(leftPtr);
		}
		return subTreePtr;
	}
}

//auto type (as called for in the book listing) was giving an error
//so return type was changed to expected return
template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
	const ItemType target, bool& isSuccessful)
{
	if (subTreePtr == nullptr)
	{
		return subTreePtr;
	}
	if (subTreePtr->getItem() == target)
	{
		subTreePtr = moveValuesUpTree(subTreePtr);
		isSuccessful = true;
		return subTreePtr;
	}
	else
	{
		std::shared_ptr<BinaryNode<ItemType>> targetNodePtr = removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful);
		subTreePtr->setLeftChildPtr(targetNodePtr);
		if (!isSuccessful)
		{
			targetNodePtr = removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful);
			subTreePtr->setRightChildPtr(targetNodePtr);
		}
		return subTreePtr;
	}
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::moveValuesUpTree(std::shared_ptr<BinaryNode<ItemType>> subTreePtr)
{
	auto leftPtr = subTreePtr->getLeftChildPtr();
	auto rightPtr = subTreePtr->getRightChildPtr();
	int leftHeight = getHeightHelper(leftPtr);
	int rightHeight = getHeightHelper(rightPtr);
	if (leftHeight > rightHeight)
	{
		subTreePtr->setItem(leftPtr->getItem());
		leftPtr = moveValuesUpTree(leftPtr);
		subTreePtr->setLeftChildPtr(leftPtr);
		return subTreePtr;



	}
	else
	{
		if (rightPtr != nullptr)
		{
			subTreePtr->setItem(rightPtr->getItem());
			rightPtr = moveValuesUpTree(rightPtr);
			subTreePtr->setRightChildPtr(rightPtr);
			return subTreePtr;
		}
		else
		{
			return nullptr;
		}
	}
}

//same issue as removeValue
//same solution
template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr,
	const ItemType& target, bool& isSuccessful) const
{
	if (treePtr == nullptr)
	{
		return treePtr;
	}
	if (treePtr->getItem() == target)
	{
		isSuccessful = true;
		return treePtr;
	}
	else
	{
		auto targetNodePtr = findNode(treePtr->getLeftChildPtr(), target, isSuccessful);
		if (!isSuccessful)
		{
			targetNodePtr = findNode(treePtr->getRightChildPtr(), target, isSuccessful);
		}
		return targetNodePtr;
	}
}

template<class ItemType>
auto BinaryNodeTree<ItemType>::copyTree(const std::shared_ptr<BinaryNode<ItemType>> oldTreeRootPtr) const
{
	std::shared_ptr<BinaryNode<ItemType>> newTreePtr;
	if (oldTreeRootPtr != nullptr)
	{
		newTreePtr = std::make_shared<BinaryNode<ItemType>>(oldTreeRootPtr->getItem(), nullptr, nullptr);
		newTreePtr->setLeftChildPtr(copyTree(oldTreeRootPtr->getLeftChildPtr()));
		newTreePtr->setRightChildPtr(copyTree(oldTreeRootPtr->getRightChildPtr()));
	}
	return newTreePtr;
}

template<class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(std::shared_ptr<BinaryNode<ItemType>> subTreePtr)
{
	if (subTreePtr != nullptr)
	{
		destroyTree(subTreePtr->getLeftChildPtr());
		destroyTree(subTreePtr->getRightChildPtr());
		subTreePtr.reset();
	}
}

template<class ItemType>
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const
{
	if (treePtr != nullptr)
	{
		ItemType theItem = treePtr->getItem();
		visit(theItem);
		preorder(visit, treePtr->getLeftChildPtr());
		preorder(visit, treePtr->getRightChildPtr());
	}
}

template<class ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const
{
	if (treePtr != nullptr)
	{
		inorder(visit, treePtr->getLeftChildPtr());
		ItemType theItem = treePtr->getItem();
		visit(theItem);
		inorder(visit, treePtr->getRightChildPtr());
	}
}

template<class ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const
{
	if (treePtr != nullptr)
	{
		postorder(visit, treePtr->getLeftChildPtr());
		postorder(visit, treePtr->getRightChildPtr());
		ItemType theItem = treePtr->getItem();
		visit(theItem);
	}
}

//PUBLIC METHODS
//constructors
template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree()
{}

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem)
	:rootPtr(std::make_shared<BinaryNode<ItemType>>(rootItem, nullptr, nullptr))
{}

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem,
	const std::shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr,
	const std::shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr)
	: rootPtr(std::make_shared<BinaryNode<ItemType>>(rootItem,
		copyTree(leftTreePtr->rootPtr),
		copyTree(rightTreePtr->rootPtr)))
{}

//copy constructor
template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType>& treePtr)
{
	rootPtr = copyTree(treePtr.rootPtr);
}

//destructor
template<class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree()
{
	destroyTree(rootPtr);
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const
{
	return (rootPtr == nullptr);
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const
{
	return getHeightHelper(rootPtr);
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const
{
	return getNumberOfNodesHelper(rootPtr);
}

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getRootData() const throw(PrecondViolatedExcept)
{
	if (isEmpty())
	{
		throw PrecondViolatedExcept("getRootData() called with an empty tree");

	}
	return rootPtr->getItem();
}

template<class ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType& newData)
{
	if (isEmpty())
	{
		rootPtr = std::make_shared<BinaryNode<ItemType>>(newData, nullptr, nullptr);
	}
	else
	{
		rootPtr->setItem(newData);
	}
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData)
{
	auto newNodePtr = std::make_shared<BinaryNode<ItemType>>(newData);
	rootPtr = balancedAdd(rootPtr, newNodePtr);
	return true;
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType& data)
{
	bool isRemoved = false;
	rootPtr = removeValue(rootPtr, data, isRemoved);
	return isRemoved;
}

template<class ItemType>
void BinaryNodeTree<ItemType>::clear()
{
	destroyTree(rootPtr);
	rootPtr.reset();
}

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
	bool entryIsFound = false;
	auto entryNodePtr = findNode(rootPtr, anEntry, entryIsFound);

	if (entryIsFound)
	{
		return entryNodePtr->getItem();
	}
	else
	{
		throw NotFoundException("Entry not found");
	}
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::contains(const ItemType& anEntry) const
{
	bool isFound = false;
	findNode(rootPtr, anEntry, isFound);
	return isFound;
}

template<class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
	preorder(visit, rootPtr);
}

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
	inorder(visit, rootPtr);
}

template<class ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
	postorder(visit, rootPtr);
}

template<class ItemType>
BinaryNodeTree<ItemType>& BinaryNodeTree<ItemType>::operator=(const BinaryNodeTree& rightHandSide)
{
	if (!isEmpty())
	{
		clear();
	}
	//overloaded operator will be used as:
	//tree1 = tree2
	//so tree1's 'this' pointer is used
	this = copyTree(&rightHandSide);
	return *this;
}


//insertionsort chosen for ease of implementation
//and implemented to avoid dependence on <algorithm> header
template<class ItemType>
void BinaryNodeTree<ItemType>::insertionSort(std::vector<ItemType>& v)
{
	for (int unsorted = 1; unsorted < v.size(); unsorted++)
	{
		ItemType nextItem = v.at(unsorted);
		int loc = unsorted;
		while ((loc > 0) && (v.at(loc - 1) > nextItem))
		{
			v.at(loc) = v.at(loc - 1);
			loc--;
		}
		v.at(loc) = nextItem;
	}
}

template<class ItemType>
void BinaryNodeTree<ItemType>::toVector(std::vector<ItemType>& v)
{
	rootPtr->toVector(v);
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::isSameTree(BinaryNodeTree<ItemType>* tree)
{
	if (rootPtr == nullptr && tree->isEmpty())
	{
		return true;
	}
	else if ((rootPtr == nullptr && !tree->isEmpty()) || (rootPtr != nullptr && tree->isEmpty()))
	{
		return false;
	}
	else
	{
		//load vectors
		std::vector<ItemType> vectOfThisTree;
		std::vector<ItemType> vectOfOtherTree;
		rootPtr->toVector(vectOfThisTree);
		tree->toVector(vectOfOtherTree);

		//test simple case of vector length
		if (vectOfThisTree.size() != vectOfOtherTree.size())
		{
			return false;
		}

		//sort and do a simple comparison
		insertionSort(vectOfThisTree);
		insertionSort(vectOfOtherTree);
		return(vectOfThisTree == vectOfOtherTree);

	}
}

