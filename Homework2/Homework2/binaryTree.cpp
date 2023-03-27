#include <cstddef>
#include <iostream>
//*************************************************************
// Author: D.S. Malik
//
// class binaryTreeType
// This class specifies the basic operations to implement a
// binary tree.
//*************************************************************
//Definition of the node

using namespace std;

template <class elemType>
struct binaryTreeNode {
	elemType info;
	binaryTreeNode<elemType>* llink;
	binaryTreeNode<elemType>* rlink;
};

//Definition of the class
template <class elemType>
class binaryTreeType {
public:
	const binaryTreeType<elemType>& operator=
	(const binaryTreeType<elemType>&);

	//Overload the assignment operator.
	bool isEmpty() const;

	//Returns true if the binary tree is empty;
	//otherwise, returns false.
	void inorderTraversal() const;

	//Function to do an inorder traversal of the binary tree.
	void preorderTraversal() const;

	//Function to do a preorder traversal of the binary tree.
	void postorderTraversal() const;

	//Function to do a postorder traversal of the binary tree.
	int treeHeight() const;

	//Returns the height of the binary tree.
	int treeNodeCount() const;

	//Returns the number of nodes in the binary tree.
	int treeLeavesCount() const;

	//Returns the number of leaves in the binary tree.
	void destroyTree();

	//Deallocates the memory space occupied by the binary tree.
	//Postcondition: root = NULL;
	binaryTreeType(const binaryTreeType<elemType>& otherTree);

	int leafCount();

	//copy constructor
	binaryTreeType();

	//default constructor
	~binaryTreeType();

	//destructor
protected:
	binaryTreeNode<elemType>* root;

private:
	void copyTree(binaryTreeNode<elemType>*& copiedTreeRoot,
	              binaryTreeNode<elemType>* otherTreeRoot);

	//Makes a copy of the binary tree to which
	//otherTreeRoot points. The pointer copiedTreeRoot
	//points to the root of the copied binary tree.
	void destroy(binaryTreeNode<elemType>*& p);

	//Function to destroy the binary tree to which p points.
	//Postcondition: p = NULL
	void inorder(binaryTreeNode<elemType>* p) const;

	//Function to do an inorder traversal of the binary
	//tree to which p points.
	void preorder(binaryTreeNode<elemType>* p) const;

	//Function to do a preorder traversal of the binary
	//tree to which p points.
	void postorder(binaryTreeNode<elemType>* p) const;

	//Function to do a postorder traversal of the binary
	//tree to which p points.
	int height(binaryTreeNode<elemType>* p) const;

	//Function to return the height of the binary tree
	//to which p points.
	int max(int x, int y) const;

	//Returns the larger of x and y.
	int nodeCount(binaryTreeNode<elemType>* p) const;

	//Function to return the number of nodes in the binary
	//tree to which p points
	int leavesCount(binaryTreeNode<elemType>* p) const;

	//Function to return the number of leaves in the binary
	//tree to which p points
};


template <class elemType>
bool binaryTreeType<elemType>::isEmpty() const {
	return (root == nullptr);
}


template <class elemType>
binaryTreeType<elemType>::binaryTreeType() {
	root = NULL;
}


template <class elemType>
void binaryTreeType<elemType>::inorderTraversal() const {
	inorder(root);
}


template <class elemType>
void binaryTreeType<elemType>::preorderTraversal() const {
	preorder(root);
}


template <class elemType>
void binaryTreeType<elemType>::postorderTraversal() const {
	postorder(root);
}


template <class elemType>
int binaryTreeType<elemType>::treeHeight() const {
	return height(root);
}


template <class elemType>
int binaryTreeType<elemType>::treeNodeCount() const {
	return nodeCount(root);
}


template <class elemType>
int binaryTreeType<elemType>::treeLeavesCount() const {
	return leavesCount(root);
}


template <class elemType>
void binaryTreeType<elemType>::
inorder(binaryTreeNode<elemType>* p) const {
	if (p != nullptr) {
		inorder(p->llink);
		cout << p->info << " ";
		inorder(p->rlink);
	}
}


template <class elemType>
void binaryTreeType<elemType>::
preorder(binaryTreeNode<elemType>* p) const {
	if (p != nullptr) {
		cout << p->info << " ";
		preorder(p->llink);
		preorder(p->rlink);
	}
}


template <class elemType>
void binaryTreeType<elemType>::
postorder(binaryTreeNode<elemType>* p) const {
	if (p != nullptr) {
		postorder(p->llink);
		postorder(p->rlink);
		cout << p->info << " ";
	}
}


template <class elemType>
int binaryTreeType<elemType>::
height(binaryTreeNode<elemType>* p) const {
	if (p == nullptr)
		return 0;
	return 1 + max(height(p->llink), height(p->rlink));
}


template <class elemType>
int binaryTreeType<elemType>::max(int x, int y) const {
	if (x >= y)
		return x;
	return y;
}


template <class elemType>
void binaryTreeType<elemType>::copyTree
(binaryTreeNode<elemType>*& copiedTreeRoot,
 binaryTreeNode<elemType>* otherTreeRoot) {
	if (otherTreeRoot == nullptr)
		copiedTreeRoot = NULL;
	else {
		copiedTreeRoot = new binaryTreeNode<elemType>;
		copiedTreeRoot->info = otherTreeRoot->info;
		copyTree(copiedTreeRoot->llink, otherTreeRoot->llink);
		copyTree(copiedTreeRoot->rlink, otherTreeRoot->rlink);
	}
} //end copyTree
template <class elemType>
void binaryTreeType<elemType>::destroy(binaryTreeNode<elemType>*& p) {
	if (p != nullptr) {
		destroy(p->llink);
		destroy(p->rlink);
		delete p;
		p = NULL;
	}
}


template <class elemType>
void binaryTreeType<elemType>::destroyTree() {
	destroy(root);
}


//copy constructor
template <class elemType>
binaryTreeType<elemType>::binaryTreeType
(const binaryTreeType<elemType>& otherTree) {
	if (otherTree.root == nullptr) //otherTree is empty
		root = NULL;
	else
		copyTree(root, otherTree.root);
}


template <class elemType>
int binaryTreeType<elemType>::leafCount() {
	if (root) {
		
	}
}


//destructor
template <class elemType>
binaryTreeType<elemType>::~binaryTreeType() {
	destroy(root);
}


//overloading the assignment operator
template <class elemType>
const binaryTreeType<elemType>& binaryTreeType<elemType>::operator=
(const binaryTreeType<elemType>& otherTree) {
	if (this != &otherTree) //avoid self-copy
	{
		if (root != nullptr) //if the binary tree is not empty,
			//destroy the binary tree
			destroy(root);
		if (otherTree.root == nullptr) //otherTree is empty
			root = NULL;
		else
			copyTree(root, otherTree.root);
	} //end else
	return *this;
}

