/*
Nathan Engle
8/25/2021
Program Description: Implements binary tree data structure. Within the data structure is a function called bool isSameTree(Tree *) that takes an argument of a tree.  It returns true if the argument is the equivalent tree. Structure is ignored
*/

#pragma once
/** Link-based implementation of the ADT binary search tree.
@file BinarySearchTree.h */
#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcept.h"
#include <memory>



template <class ItemType> class BinarySearchTree : public BinaryNodeTree<ItemType>
{
private:
    std::shared_ptr<BinaryNode<ItemType>> rootPtr;
protected:
    //------------------------------------------------------------
    // Protected Utility Methods Section:
    // Recursive helper methods for the public methods.
    //------------------------------------------------------------
    // Places a given new node at its proper position in this binary
    // search tree.
    auto placeNode(std::shared_ptr<BinaryNode<ItemType>>subTreePtr,
        std::shared_ptr<BinaryNode<ItemType>> newNode);

    // Removes the given target value from the tree while maintaining a
    // binary search tree.
    std::shared_ptr<BinaryNode<ItemType>> removeValue(std::shared_ptr<BinaryNode<ItemType>>subTreePtr,
        const ItemType target,
        bool& success) override;

    // Removes a given node from a tree while maintaining a
    // binary search tree.
    auto removeNode(std::shared_ptr<BinaryNode<ItemType>>nodePtr);

    // Removes the leftmost node in the left subtree of the node
    // pointed to by nodePtr.
    // Sets inorderSuccessor to the value in this node.
    // Returns a pointer to the revised subtree.
    auto removeLeftmostNode(std::shared_ptr<BinaryNode<ItemType>>subTreePtr,
        ItemType inorderSuccessor);

    // Returns a pointer to the node containing the given value,
    // or nullptr if not found.
    auto findNode(std::shared_ptr<BinaryNode<ItemType>>treePtr,
        const ItemType& target, bool& isSuccessful) const;

    //creating own sort method for vectors
    void insertionSort(std::vector<ItemType>& v);

public:
    //------------------------------------------------------------
    // Constructor and Destructor Section.
    //------------------------------------------------------------
    BinarySearchTree();
    BinarySearchTree(const ItemType& rootItem);

    BinarySearchTree(const BinarySearchTree<ItemType>& tree);

    virtual ~BinarySearchTree();
    //------------------------------------------------------------
    // Public Methods Section.
    //------------------------------------------------------------
    bool isEmpty() const override;

    int getHeight() const override;

    int getNumberOfNodes() const override;

    ItemType getRootData() const throw (PrecondViolatedExcept)override;

    void setRootData(const ItemType& newData) const throw (PrecondViolatedExcept);

    bool add(const ItemType& newEntry) override;

    bool remove(const ItemType& target) override;

    void clear() override;

    ItemType getEntry(const ItemType& anEntry) const throw (NotFoundException)override;

    bool contains(const ItemType& anEntry) const override;

    //------------------------------------------------------------
    // Public Traversals Section.
    //------------------------------------------------------------
    void preorderTraverse(void visit(ItemType&)) const override;

    void inorderTraverse(void visit(ItemType&)) const override;

    void postorderTraverse(void visit(ItemType&)) const override;

    //------------------------------------------------------------
    // Overloaded Operator Section.
    //------------------------------------------------------------
    BinarySearchTree<ItemType>&
        operator=(const BinarySearchTree<ItemType>& rightHandSide);

    void toVector(std::vector<ItemType>& v);
    bool isSameTree(BinarySearchTree<ItemType>* tree);
};

#include "BinarySearchTree.cpp"