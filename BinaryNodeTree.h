/*
Nathan Engle
8/25/2021
Program Description: Implements binary tree data structure. Within the data structure is a function called bool isSameTree(Tree *) that takes an argument of a tree.  It returns true if the argument is the equivalent tree. Structure is ignored
*/

#pragma once
#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "PrecondViolatedExcept.h"
#include "NotFoundException.h"
#include <memory>
#include <vector>

template< class ItemType>
class BinaryNodeTree : public BinaryTreeInterface<ItemType>
{
private:
	std::shared_ptr<BinaryNode<ItemType>> rootPtr;
protected:
	//------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//------------------------------------------------------------

	int getHeightHelper(std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const;
	int getNumberOfNodesHelper(std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const;

	// Recursively adds a new node to the tree in a left/right fashion to
	// keep the tree balanced. 
	auto balancedAdd(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
		std::shared_ptr<BinaryNode<ItemType>> newNodePtr);

	// Removes the target value from the tree by calling moveValuesUpTree
	// to overwrite value with value from child.
	virtual std::shared_ptr<BinaryNode<ItemType>> removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
		const ItemType target, bool& isSuccessful);

	// Copies values up the tree to overwrite value in current node until
	// a leaf is reached; the leaf is then removed, since its value is
	// stored in the parent.
	std::shared_ptr<BinaryNode<ItemType>> moveValuesUpTree(std::shared_ptr<BinaryNode<ItemType>> subTreePtr);

	// Recursively searches for target value in the tree by using a
	// preorder traversal.
	virtual std::shared_ptr<BinaryNode<ItemType>> findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr,
		const ItemType& target, bool& isSuccessful) const;

	// Copies the tree rooted at treePtr and returns a pointer to
	// the copy.
	auto copyTree(const std::shared_ptr<BinaryNode<ItemType>> oldTreeRootPtr) const;

	//Recursively deletes all nodes from the tree
	void destroyTree(std::shared_ptr<BinaryNode<ItemType>> subTreePtr);

	// Recursive traversal helper methods:
	void preorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const;
	void inorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const;
	void postorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const;

	//creating own sort method for vectors
	void insertionSort(std::vector<ItemType>& v);
public:
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------

	BinaryNodeTree();
	BinaryNodeTree(const ItemType& rootItem);
	BinaryNodeTree(const ItemType& rootItem,
		const std::shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr,
		const std::shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr);
	BinaryNodeTree(const BinaryNodeTree<ItemType>& tree);
	virtual ~BinaryNodeTree();

	//------------------------------------------------------------
	// Public BinaryTreeInterface Methods Section.
	//------------------------------------------------------------

	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;
	ItemType getRootData() const throw(PrecondViolatedExcept);
	void setRootData(const ItemType& newData);
	bool add(const ItemType& newData); // Adds a node
	bool remove(const ItemType& data); // Removes a node
	void clear();
	ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException);
	bool contains(const ItemType& anEntry) const;

	//------------------------------------------------------------
	// Public Traversals Section.
	//------------------------------------------------------------

	void preorderTraverse(void visit(ItemType&)) const;
	void inorderTraverse(void visit(ItemType&)) const;
	void postorderTraverse(void visit(ItemType&)) const;

	//------------------------------------------------------------
	// Overloaded Operator Section.
	//------------------------------------------------------------

	BinaryNodeTree& operator=(const BinaryNodeTree& rightHandSide);

	void toVector(std::vector<ItemType>& v);

	bool isSameTree(BinaryNodeTree<ItemType>* tree);
};
#include "BinaryNodeTree.cpp"
