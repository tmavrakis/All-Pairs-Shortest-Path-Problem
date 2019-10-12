#include "LEDA/graph/graph.h"
#include "LEDA/core/list.h"
#include <string>
#include <iostream>
#include "LEDA/graph/node_array.h"
#include <time.h>
#include "LEDA/graph/node_matrix.h"
#include "LEDA/graph/graph_gen.h"

using namespace leda;
using namespace std;

int main(int argc, char const *argv[]) {

	graph G;
	int numNodes = 1000;
	node s, v1, w, k, v[6];
	edge e1, e[7];
	clock_t start, stop;
	double duration;

	random_graph(G, 1000, 10000);
	edge_array<int> cost(G);

	forall_edges(e1,G){
		srand ( time(NULL) ); //initialize the random seed
		int sub = rand() % 5;
		srand (time(NULL) + 10);
		cost[e1] = (rand() % 10 + 1) - sub;
	}

	start = clock();
	node_matrix<int> dist(G, INT_MAX);
	node_matrix<int> pred(G, 0);

	forall_nodes(v1, G){ dist(v1, v1) = 0; }

	int count = 0;
	forall_nodes(w, G){
		count++;
		forall_adj_edges(e1, w){
			dist(G.source(e1), G.target(e1)) = cost[e1];
			pred(G.source(e1), G.target(e1)) = count - 1;
		}
	}

	forall_nodes(k,G){
		forall_nodes(v1,G){
			forall_nodes(w,G){
				if ((dist(v1,k)!=INT_MAX) && (dist(k,w)!=INT_MAX) &&(dist(v1,w) > dist(v1,k) + dist(k,w))){
					dist(v1,w) = dist(v1,k) + dist(k,w);
					pred(v1,w) = pred(k,w);
				}
			}
			if(dist(v1,v1) < 0){
				std::cerr << "Negative cycle found!" << '\n';
				stop = clock();
				duration = (stop - start) / (double)CLOCKS_PER_SEC;
				std::cout << "Runtime of Floyd-Warshall with negative cycle is: " << duration*1000.0 << " ms \n";
				return 0;
			}
		}
	}

	stop = clock();
	duration = (stop - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Runtime of Floyd-Warshall is: " << duration*1000.0 << " ms \n";

	return 0;
}
