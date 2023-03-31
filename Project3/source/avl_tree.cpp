#include <iostream>
#include "avl_tree.h"
using namespace std;


void AVLTree::insert(const int newValue) {
	bool isTaller = false;
	AVLNode* newNode;
	newNode = new AVLNode(newValue);
	insertIntoAVL(root, newNode, isTaller);
}


void AVLTree::insertIntoAVL(AVLNode* & root, AVLNode* newNode, bool& isTaller) {
	if (root == NULL) {
		root = newNode;
		isTaller = true;
	}
	else if (root->value == newNode->value) {
		cout << "Duplicate" << endl;
	}
	else if (root->value > newNode->value) {
		insertIntoAVL(root->left, newNode, isTaller);

		if (isTaller) {
			switch (root->bf) {
			case -1:
				balanceFromLeft(root);
				isTaller = false;
				break;

			case 0:
				root->bf = -1;
				isTaller = true;
				break;

			case 1:
				root->bf = 0;
				isTaller = false;
			}
		}
	}
	else {
		insertIntoAVL(root->right, newNode, isTaller);

		if (isTaller) {
			switch (root->bf) {
			case -1:
				root->bf = 0;
				isTaller = false;
				break;

			case 0:
				root->bf = 1;
				isTaller = true;
				break;

			case 1:
				balanceFromRight(root);
				isTaller = false;
			}
		}
	}
}


void AVLTree::rotateToLeft(AVLNode* & root) {
	AVLNode* p;

	if (root == NULL)
		cout << "Error in the tree" << endl;
	else if (root->right == NULL)
		cout << "Error in the tree: No right subtree to rotate." << endl;
	else {
		p = root->right;
		root->right = p->left;
		p->left = root;
		root = p;
	}
}


void AVLTree::rotateToRight(AVLNode* & root) {
	AVLNode* p;

	if (root == NULL)
		cout << "Error in the tree" << endl;
	else if (root->left == NULL)
		cout << "Error in the tree: No left subtree to rotate." << endl;
	else {
		p = root->left;
		root->left = p->right;
		p->right = root;
		root = p;
	}
}


void AVLTree::balanceFromLeft(AVLNode* & root) {
	AVLNode* p;
	AVLNode* w;
	int rootVal = root->value;

	p = root->left;

	switch (p->bf) {
	case -1:
		root->bf = 0;
		p->bf = 0;
		rotateToRight(root);
		break;

	case 0: // You need to handle this case; possible in AVL deletion

		cout << "You need to handle this case, as it is possible in AVL deletion. " << endl;
		root->value = p->value;
		root->right = root->left;
		root->left = NULL;

		root->left = p->left;
		p->left = NULL;

		p->left = p->right;
		p->right = NULL;

		p->value = rootVal;
		p->bf = -1;

		root->bf = 1;
		break;
		break;

	case 1:
		w = p->right;

		switch (w->bf) {
		case -1:
			root->bf = 1;
			p->bf = 0;
			break;
		case 0:
			root->bf = 0;
			p->bf = 0;
			break;
		case 1:
			root->bf = 0;
			p->bf = -1;
		}

		w->bf = 0;
		rotateToLeft(p);
		root->left = p;
		rotateToRight(root);
	}
}


void AVLTree::balanceFromRight(AVLNode* & root) {
	AVLNode* p;
	AVLNode* w;
	int rootVal = root->value;

	p = root->right;
	switch (p->bf) {
	case -1:

		w = p->left;
		switch (w->bf) {
		case -1:
			root->bf = 0;
			p->bf = 1;
			break;
		case 0:
			root->bf = 0;
			p->bf = 0;
			break;
		case 1:
			root->bf = -1;
			p->bf = 0;
		}

		w->bf = 0;
		rotateToRight(p);
		root->right = p;
		rotateToLeft(root);
		break;

	case 0: // You need to handle this case; possible in AVL deletion


		root->value = p->value;
		root->left = root->right;
		root->right = NULL;

		root->right = p->right;
		p->right = NULL;

		p->right = p->left;
		p->left = NULL;

		p->value = rootVal;
		p->bf = 1;

		root->bf = -1;
		break;

	case 1:
		root->bf = 0;
		p->bf = 0;
		rotateToLeft(root);
	}
}


int AVLTree::getHeight(struct AVLNode* node) {
	if (node->left == NULL && node->right == NULL) {
		return 1;
	}

	int lHeight = 0;
	int rHeight = 0;


	if (node ->left != NULL) {
		lHeight = getHeight(node->left);
	}
	if (node -> right != NULL) {
		rHeight = getHeight(node->right);
	}
	

	return 1 + max(lHeight, rHeight);
}


void AVLTree::printHeight(AVLNode* root) {
	// If the node is a leaf, print the height and return
	if (root -> left == NULL && root->right == NULL) {
		cout << getHeight(root) << ' ';
		return;
	}

	// if a left node exists, go down that node and print there
	if (root->left != NULL) {
		printHeight(root->left);
	}

	// after the left node is printed, print the root value
	cout << getHeight(root) << ' ';
	   
	// go down the right branch if it exists
	if (root -> right != NULL) {
		printHeight(root->right);
	}
	return;
}


void AVLTree::printValue(AVLNode* root) {
	// If the node is a leaf, print the value and return
	if (root->left == NULL && root->right == NULL) {
		cout << root->value << ' ';
		return;
	}

	// if a left node exists, go down that node and print there
	if (root->left != NULL) {
		printValue(root->left);
	}

	// after the left node is printed, print the root value
	cout << root->value << ' ';

	// go down the right branch if it exists
	if (root->right != NULL) {
		printValue(root->right);
	}
	return;
}


void AVLTree::print(char letter) {
	if (letter == 'h') {
		printHeight(root);
		cout << endl;
	}
	else if (letter == 'p') {
		printValue(root);
		cout << endl;
	}
	return;
}


AVLNode* AVLTree::getPred(AVLNode* node) {
	// find the right most node in the left subtree

	if (node->right == NULL) {
		return node;
	}
	else {
		return getPred(node->right);
	}
}


void AVLTree::remove(int badValue) {
	bool isShorter = false;
	remove(root, badValue, isShorter);
}


void AVLTree::remove(AVLNode* & root, int badValue, bool& isShorter) {
	// recursively find the node and perform a deletion 

	// base case 1 - The search has resulted in a NULL node meaning that it is not in the tree
	if(root == NULL) {
		cout << "The node to be deleted is not in the tree." << endl;
		return;
	}


	// base case 2 - The node is the value to be deleted.
	else if(root->value == badValue) {
		// perform the deletion
		// there are 4 possible cases for the deletion


		// case 1 - The node being deleted is a leaf node
		if (root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
			isShorter = true;
		}


		// case 2 - has a right child only
		else if(root->right != NULL && root->left == NULL) {
			AVLNode* tmp = root->right;
			root->left = root->right = NULL;
			delete root;
			root = tmp;
			isShorter = true;
		}


		// case 3 - has a left child only
		else if (root->left != NULL && root->right == NULL) {
			AVLNode* tmp = root->left;
			root->left = root->right = NULL;
			delete root;
			root = tmp;
			isShorter = true;
		}


		// case 4 - has 2 child nodes
		else {
			// get the pred
			AVLNode* pred = getPred(root->left);
			// make a copy of it to become the new root
			int tmp = pred->value;

			// the pred can now be deleted with either case 2 or 3 because of the nature of predecessors.
			bool tmpIsShorter = false;
			remove(root, pred->value, tmpIsShorter);
			
			// replace the value of the root with the value of the pred.
			if (root->left->value == badValue) {
				root->left->value = tmp;
			}
			else if (root->right->value == badValue) {
				root->right->value = tmp;
			}
			else {
				root->value = tmp;
			}

			// since the tree has already been balanced from the pred deletion the tree is
			// no shorter and requires no further balancing.
			isShorter = tmpIsShorter;
		}
	}


	// go down the correct subtree according to the value of the node and the bad value.
	else {
		// badValue is less than the current node so go down the left sub tree.
		if (badValue < root->value) {
			remove(root->left, badValue, isShorter);
			if (isShorter) {
				switch (root->bf) {
				case -1:
					root->bf = 0;
					isShorter = true;
					break;

				case 0:
					root->bf = 1;
					isShorter = false;
					break;

				case 1:
					balanceFromRight(root);
					isShorter = false;
				}
			}
		}
		// otherwise it is greater and should go down the right subtree
		else {
			remove(root->right, badValue, isShorter);
			if (isShorter) {
				switch (root->bf) {
				case -1:
					balanceFromLeft(root); 
					isShorter = true;
					break;

				case 0:
					root->bf = -1;
					isShorter = false;
					break;

				case 1:
					root->bf = 0;
					isShorter = true;
				}
			}
		}
	}
	return;
}