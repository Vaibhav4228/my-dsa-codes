// 2. Bellman Ford Algorithm

/*
What is the Bellman-Ford Algorithm:
This loop-based algorithm is used to find the shortest path from a single source node to all other destination nodes and detect the negative cycle in the graph. 

Where to use the Bellman Ford Algorithm:
Note 1: The Bellman-Ford algorithm can indeed be used to find the shortest paths from a single source to all other nodes in a graph, regardless of whether the weights are positive, negative, or a mix of both. This applies to both directed and undirected graphs.

Note 2: Bellman-Ford algorithm is capable of detecting the presence of negative cycles in a graph. 
*/


#include<iostream>
#include<vector>
#include<unordered_map>
#include<limits.h>
#include<list>

using namespace std;

class Graph
{
    public:
        unordered_map<char, list<pair<char, int>>> adjList;

        void addEdges(char u, char v, int wt, int direction){
            if(direction == 1){
                // Directed Graph
                adjList[u].push_back({v,wt});
            }
            else{
                // Undirected Graph
                adjList[u].push_back({v,wt});
                adjList[v].push_back({u,wt});
            }
        }

        void printAdjList(){
            for(auto i: adjList){
                cout << i.first << " : { ";
                for(auto j: i.second){
                    cout << "( " << j.first << ", " << j.second << " ), ";
                }
                cout << " }" << endl;
            }
        }

        void bellManFord(int n, char src) {
            // Initial state
            vector<int> dist(n, INT_MAX);
            dist[src-'A'] = 0;

            // Step 1: Relaxation N-1 times to get the all shortest path from single node.
            for(int i=1; i<n; i++){
                // Traverse on entire edge list
                for(auto a: adjList){
                    for(auto b: a.second){
                        char u = a.first;
                        char v = b.first;
                        int wt = b.second;
                        if(dist[u-'A'] != INT_MAX && dist[u-'A'] + wt < dist[v-'A']){
                            dist[v-'A'] = dist[u-'A'] + wt;
                        }
                    }
                }           
            }

            // Step 2: One more relaxation after N-1 times to detect the negative cycle
            // 1 time relaxation
            bool anyUpdate = false;
            for(auto a: adjList){
                for(auto b: a.second){
                    char u = a.first;
                    char v = b.first;
                    int wt = b.second;
                    if(dist[u-'A'] != INT_MAX && dist[u-'A'] + wt < dist[v-'A']){
                        anyUpdate = true;
                        break;
                        dist[v-'A'] = dist[u-'A'] + wt;
                    }
                }
            }

            // Expected Output
            if(anyUpdate == true){
                cout << "Negative Cycle Present" << endl;
            }
            else{
                cout << "No Negative Cycle Present in Graph" << endl;
                cout << "Printing Distance Array: ";
                for(auto i: dist){
                    cout << i << ", ";
                }
                cout << endl;
            }
        }
};

int main(){
    Graph g;
	g.addEdges('A','B',-1,1);
	g.addEdges('A','E',4,1);
	g.addEdges('B','C',2,1);
	g.addEdges('B','D',2,1);
	g.addEdges('B','E',3,1);
	g.addEdges('C','D',-3,1);
	g.addEdges('D','E',5,1);
	g.addEdges('D','B',1,1);
    g.printAdjList();

    int n = 5;
	char src = 'A';
	g.bellManFord(n, src);

    return 0;
}

/*
AdjList:
D : { ( E, 5 ), ( B, 1 ),  }
C : { ( D, -3 ),  }
B : { ( C, 2 ), ( D, 2 ), ( E, 3 ),  }
A : { ( B, -1 ), ( E, 4 ),  }
No Negative Cycle Present in Graph
Printing Distance Array: 0, -1, 1, -2, 2,
*/


//fllow this code 
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	/*  Function to implement Bellman Ford
	*   edges: vector of vectors which represents the graph
	*   S: source vertex to start traversing graph with
	*   V: number of vertices
	*/
	vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {
		vector<int> dist(V, 1e8);
		dist[S] = 0;
		for (int i = 0; i < V - 1; i++) {
			for (auto it : edges) {
				int u = it[0];
				int v = it[1];
				int wt = it[2];
				if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
					dist[v] = dist[u] + wt;
				}
			}
		}
		// Nth relaxation to check negative cycle
		for (auto it : edges) {
			int u = it[0];
			int v = it[1];
			int wt = it[2];
			if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
				return { -1};
			}
		}


		return dist;
	}
};


int main() {

	int V = 6;
	vector<vector<int>> edges(7, vector<int>(3));
	edges[0] = {3, 2, 6};
	edges[1] = {5, 3, 1};
	edges[2] = {0, 1, 5};
	edges[3] = {1, 5, -3};
	edges[4] = {1, 2, -2};
	edges[5] = {3, 4, -2};
	edges[6] = {2, 4, 3};

	int S = 0;
	Solution obj;
	vector<int> dist = obj.bellman_ford(V, edges, S);
	for (auto d : dist) {
		cout << d << " ";
	}
	cout << endl;

	return 0;
}
