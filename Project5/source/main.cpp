/**
 * @author Pete Newman
 * @file main.cpp
 * @brief find the shortest path using Dijkstra’s algorithm
*/
#include <iostream>
#include <string>
#include <vector>
#include <queue>



using namespace std;


struct City {
	string name;
	int index;
};

struct Edge {
	int weight;
	int destination;
};

vector<City> cities;
vector<vector<Edge>> graph;


/**
 * \brief the heap implementation of dijkstra's alg.
 * \param start the starting vertex
 * \param end the ending vertex
 * \param numCities the number of cities
 */
void dijkstra(int start, int end, int numCities);


/**
 * \brief the main function 
 * \return 1
 */
int main() {
	// the first line is the number of tests
	int numTests;
	cin >> numTests;

	for (int t = 0; t < numTests; t++) {
		int numCities;
		cin >> numCities;

		cities.clear();
		graph.clear();

		// build the graph
		for (int i = 0; i < numCities; i++) {
			City c;
			cin >> c.name;
			c.index = i;
			cities.push_back(c);
		}

		graph.resize(numCities);

		for (int i = 0; i < numCities; i++) {
			for (int j = 0; j < numCities; j++) {
				int d;
				cin >> d;
				if (d != 0) {
					Edge e;
					e.weight = d;
					e.destination = j;
					graph[i].push_back(e);
				}
			}
		}

		// perform the algorithm and print the results
		dijkstra(0, numCities - 1, numCities);
	}

	return 0;
}

void dijkstra(int start, int end, int numCities) {
	vector<int> dist;
	vector<int> pred;
	vector<bool> visited;
	// set all of the arrays to their initial values
	for (int i = 0; i < numCities; i++) {
		dist.push_back(INT_MAX);
		pred.push_back(-1);
		visited.push_back(false);
	}
	dist[start] = 0;

	// create the heap
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push(make_pair(dist[start], start));

	while (!pq.empty()) {
		int smallDistance = pq.top().second;
		pq.pop();
		if (visited[smallDistance]) {
			continue;
		}
		visited[smallDistance] = true;


		for (auto edge : graph[smallDistance]) {
			int weight = edge.weight;
			if (dist[smallDistance] + weight < dist[edge.destination]) {
				dist[edge.destination] = dist[smallDistance] + weight;
				pred[edge.destination] = smallDistance;
				pq.push(make_pair(dist[edge.destination], edge.destination));
			}
		}
	}

	vector<string> path;
	int curr = end;
	// use backtracking to get the names of the cities into the array to be printed
	while (curr != start) {
		path.push_back(cities[curr].name);
		curr = pred[curr];
	}
	path.push_back(cities[start].name);
	cout << path[path.size() - 1];
	for (int i = path.size() - 2; i >= 0; i--) {
		cout << " " << path[i];
	}

	// print the final distance
	cout << " " << dist[end] << endl;
}