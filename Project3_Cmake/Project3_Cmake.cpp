// Project3_Cmake.cpp : Defines the entry point for the application.
//

#include "Project3_Cmake.h"
#include <>
using namespace std;

int main(int argc, char** argv) {

	AVLTree tree;

	char option;
	int key;

	do {
		cin >> option;
		switch (option)
		{
		case 'i':
			cin >> key;
			tree.insert(key);
			break;
		case 'r':
			cin >> key;
			tree.remove(key);
			break;
		case 'h':
			tree.print('h');
			break;
		case 'p':
			tree.print('p');
			break;
		default:
			break;
		}
	} while (option != 'q');
}
