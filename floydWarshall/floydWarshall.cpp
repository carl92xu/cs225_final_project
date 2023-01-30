// #include "floydWarshall.h"
#include "../Graph.h"
#include <iostream>
#include <string>

// string floydwarshall(Graph graph, string src, string dest) {
//     auto srcNode = graph.abbr_to_Node(src);
//     auto destNode = graph.abbr_to_Node(dest);
// }


#include <bits/stdc++.h>
using namespace std;

#define V 67663 // total airport number

#define INF 9999999999

void printSolution(int dist[][V]);

void floydWarshall(int graph[][V])
{
	int dist[V][V], i, j, k;

	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			dist[i][j] = graph[i][j];

	for (k = 0; k < V; k++) {
		for (i = 0; i < V; i++) {
			for (j = 0; j < V; j++) {
				if ((dist[i][j] > (dist[i][k] + dist[k][j])) && (dist[k][j] != INF) && (dist[i][k] != INF))
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}

	// Print the shortest distance matrix
	printSolution(dist);
}

/* A utility function to print solution */
void printSolution(int dist[][V])
{
	cout << "The following matrix shows the shortest "
			"distances"
			" between every pair of vertices \n";
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (dist[i][j] == INF)
				cout << "INF"
					<< "	 ";
			else
				cout << dist[i][j] << "	 ";
		}
		cout << endl;
	}
}

// Driver code
int main()
{
	/* ex.
		  10
    (0)------->(3)
	 |	       /|\
   5 |	        |
     |	        | 1
	\|/         |
	(1)------->(2)
		  3
	int graph[V][V] = { { 0, 5, INF, 10 },
						{ INF, 0, 3, INF },
						{ INF, INF, 0, 1 },
						{ INF, INF, INF, 0 } };
    */

    // convert our graph into an array of this sort
    Graph g;
    int graph[V][V];

    for (int i = 0; i < V; i++) {       // vertical
        auto airport_i = g.id_to_Node(i);
        for (int j = 0; j < V; j++) {   // horizontal
            auto airport_j = g.id_to_Node(j);
            graph[i][j] = g.computeDist(airport_i, airport_j);
        }
    }

	// Print the solution
	floydWarshall(graph);
	return 0;
}
