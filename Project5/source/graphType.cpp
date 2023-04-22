#include "graphType.h"
#include <fstream>
#include <iostream>

using namespace std;


bool graphType::isEmpty() const {
	return (gSize == 0);
}


void graphType::createGraph() {
	ifstream infile;
	char fileName[50];
	int vertex;
	int adjacentVertex;
	if (gSize != 0) //if the graph is not empty, make it empty
		clearGraph();
	cout << "Enter input file name: ";
	cin >> fileName;
	cout << endl;
	infile.open(fileName);
	if (!infile) {
		cout << "Cannot open input file." << endl;
		return;
	}
	infile >> gSize; //get the number of vertices
	for (int index = 0; index < gSize; index++) {
		infile >> vertex;
		infile >> adjacentVertex;
		while (adjacentVertex != -999) {
			graph[vertex].insertLast(adjacentVertex);
			infile >> adjacentVertex;
		} //end while
	} // end for
	infile.close();
} //end createGraph


void graphType::clearGraph() {
	for (int index = 0; index < gSize; index++)
		graph[index].destroyList();
	gSize = 0;
} //end clearGraph

void graphType::printGraph() const {
	for (int index = 0; index < gSize; index++) {
		cout << index << " ";
		graph[index].print();
		cout << endl;
	}
	cout << endl;
} //end printGraph

//Constructor
graphType::graphType(int size) {
	maxSize = size;
	gSize = 0;
	graph = new unorderedLinkedList<int>[size];
}


//Destructor
graphType::~graphType() {
	clearGraph();
}


void graphType::dft(int v, bool visited[]) {
	visited[v] = true;
	cout << " " << v << " "; //visit the vertex
	linkedListIterator<int> graphIt;
	//for each vertex adjacent to v
	for (graphIt = graph[v].begin(); graphIt != graph[v].end();
	     ++graphIt) {
		int w = *graphIt;
		if (!visited[w])
			dft(w, visited);
	} //end while
} //end dft
void graphType::depthFirstTraversal() {
	bool* visited; //pointer to create the array to keep
	//track of the visited vertices
	visited = new bool[gSize];
	for (int index = 0; index < gSize; index++)
		visited[index] = false;
	//For each vertex that is not visited, do a depth
	//first traverssal
	for (int index = 0; index < gSize; index++)
		if (!visited[index])
			dft(index, visited);
	delete[] visited;
} //end depthFirstTraversal
void graphType::dftAtVertex(int vertex) {
	bool* visited;
	visited = new bool[gSize];
	for (int index = 0; index < gSize; index++)
		visited[index] = false;
	dft(vertex, visited);
	delete[] visited;
} // end dftAtVertex
void graphType::breadthFirstTraversal() {
	linkedQueueType<int> queue;
	bool* visited;
	visited = new bool[gSize];
	for (int ind = 0; ind < gSize; ind++)
		visited[ind] = false; //initialize the array
	//visited to false
	linkedListIterator<int> graphIt;
	for (int index = 0; index < gSize; index++)
		if (!visited[index]) {
			queue.addQueue(index);
			visited[index] = true;
			cout << " " << index << " ";
			while (!queue.isEmptyQueue()) {
				int u = queue.front();
				queue.deleteQueue();
				for (graphIt = graph[u].begin();
				     graphIt != graph[u].end(); ++graphIt) {
					int w = *graphIt;
					if (!visited[w]) {
						queue.addQueue(w);
						visited[w] = true;
						cout << " " << w << " ";
					}
				}
			} //end while
		}
	delete[] visited;
} //end breadthFirstTraversal
