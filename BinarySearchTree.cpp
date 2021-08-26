/*
Nathan Engle
8/25/2021
Program Description: Implements binary tree data structure. Within the data structure is a function called bool isSameTree(Tree *) that takes an argument of a tree.  It returns true if the argument is the equivalent tree. Structure is ignored
*/

#include <iostream>
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "BinarySearchTree.h"

template<class ItemType>
auto BinarySearchTree<ItemType>::placeNode(std::shared_ptr<BinaryNode<ItemType>>subTreePtr,
    std::shared_ptr<BinaryNode<ItemType>> newNode)
{
    if (subTreePtr == nullptr)
    {
        return newNode;
    }
    else
    {
        //add new node to the right if greater than subTreePtr
        //and to the left child if less than subTreePtr
        if (subTreePtr->getItem() < newNode->getItem())
        {
            subTreePtr->setRightChildPtr(placeNode(subTreePtr->getRightChildPtr(), newNode));
        }
        else
        {
            subTreePtr->setLeftChildPtr(placeNode(subTreePtr->getLeftChildPtr(), newNode));
        }
        return subTreePtr;
    }
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeValue(std::shared_ptr<BinaryNode<ItemType>>subTreePtr,
    const ItemType target,
    bool& success)
{
    if (subTreePtr == nullptr)
    {
        success = false;
    }
    else if (subTreePtr->getItem() == target)
    {
        subTreePtr = removeNode(subTreePtr);
        success = true;
    }
    else if (subTreePtr->getItem() > target)
    {
        std::shared_ptr<BinaryNode<ItemType>> tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
        subTreePtr->setLeftChildPtr(tempPtr);
    }
    else
    {
        std::shared_ptr<BinaryNode<ItemType>> tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
        subTreePtr->setRightChildPtr(tempPtr);
    }
    return subTreePtr;
}

template<class ItemType>
auto BinarySearchTree<ItemType>::removeNode(std::shared_ptr<BinaryNode<ItemType>> nodePtr)
{
    if (nodePtr->isLeaf()) // no children
    {
        nodePtr = nullptr;
        return nodePtr;
    }

    std::shared_ptr<BinaryNode<ItemType>> nodeToConnectPtr;

    if ((nodePtr->getLeftChildPtr() == nullptr) || (nodePtr->getRightChildPtr() == nullptr)) //one child
    {
        if (nodePtr->getRightChildPtr() == nullptr) //if child is left
        {
            nodeToConnectPtr = nodePtr->getLeftChildPtr();
        }
        else //child is right
        {
            nodeToConnectPtr = nodePtr->getRightChildPtr();
        }
        return nodeToConnectPtr;
    }
    else //nodePtr has two children
    {
        std::shared_ptr<BinaryNode<ItemType>> tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), nodePtr->getItem());
        nodePtr->setRightChildPtr(tempPtr);
        nodePtr->setItem(nodePtr->getItem());
        return nodePtr;
    }
}

template<class ItemType>
auto BinarySearchTree<ItemType>::removeLeftmostNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
    ItemType inorderSuccessor)
{
    if (subTreePtr->getLeftChildPtr() == nullptr)
    {
        inorderSuccessor = subTreePtr->getItem();
        return removeNode(subTreePtr);
    }
    else
    {
        std::shared_ptr<BinaryNode<ItemType>> tempPtr = removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor);
        subTreePtr->setLeftChildPtr(tempPtr);
        return subTreePtr;
    }
}

template<class ItemType>
auto BinarySearchTree<ItemType>::findNode(std::shared_ptr<BinaryNode<ItemType>>treePtr,
    const ItemType& target, bool& isSuccessful) const
{
    if (treePtr == nullptr)
    {
        return treePtr;
    }
    if (treePtr->getItem() == target) //found
    {
        isSuccessful = true;
        return treePtr;
    }
    else if (treePtr->getItem() > target) //item in treePtr is greater than target, search left branch, else search right
    {
        return findNode(treePtr->getLeftChildPtr(), target, isSuccessful);
    }
    else
    {
        return findNode(treePtr->getRightChildPtr(), target, isSuccessful);
    }
}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree()
{}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem)
    :rootPtr(std::make_shared<BinaryNode<ItemType>>(rootItem, nullptr, nullptr))
{}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& tree)
{
    rootPtr = copyTree(tree.rootPtr);
}

template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree()
{
    this->destroyTree(rootPtr);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const
{
    return (rootPtr == nullptr);
}

template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() const
{
    return this->getHeightHelper(rootPtr);
}

template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const
{
    return this->getNumberOfNodesHelper(rootPtr);
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getRootData() const throw (PrecondViolatedExcept)
{
    if (isEmpty())
    {
        throw PrecondViolatedExcept("getRootData() called with an empty tree");

    }
    return rootPtr->getItem();
}

template<class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType& newData) const throw (PrecondViolatedExcept)
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
bool BinarySearchTree<ItemType>::add(const ItemType& newEntry)
{
    auto newNodePtr = std::make_shared<BinaryNode<ItemType>>(newEntry);
    rootPtr = placeNode(rootPtr, newNodePtr);
    return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& target)
{
    bool isRemoved = false;
    rootPtr = removeValue(rootPtr, target, isRemoved);
    return isRemoved;
}

template<class ItemType>
void BinarySearchTree<ItemType>::clear()
{
    this->destroyTree(rootPtr);
    rootPtr.reset();
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry) const throw (NotFoundException)
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
bool BinarySearchTree<ItemType>::contains(const ItemType& anEntry) const
{
    bool isFound = false;
    findNode(rootPtr, anEntry, isFound);
    return isFound;
}

template<class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
    this->preorder(visit, rootPtr);
}

template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
    this->inorder(visit, rootPtr);
}

template<class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
    this->postorder(visit, rootPtr);
}

template<class ItemType>
BinarySearchTree<ItemType>& BinarySearchTree<ItemType>::operator=(const BinarySearchTree<ItemType>& rightHandSide)
{
    if (!isEmpty())
    {
        clear();
    }
    this = copyTree(&rightHandSide);
    return *this;
}

//insertion sort chosen for ease of implementation
template<class ItemType>
void BinarySearchTree<ItemType>::insertionSort(std::vector<ItemType>& v)
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
void BinarySearchTree<ItemType>::toVector(std::vector<ItemType>& v)
{
    this->rootPtr->toVector(v);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::isSameTree(BinarySearchTree<ItemType>* tree)
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