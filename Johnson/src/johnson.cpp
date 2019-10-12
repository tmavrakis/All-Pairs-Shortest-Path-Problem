#include "LEDA/graph/graph.h"
#include "LEDA/core/list.h"
#include <string>
#include <iostream>
#include "LEDA/graph/node_array.h"
#include <time.h>
#include "LEDA/graph/templates/shortest_path.h"
#include "LEDA/graph/node_matrix.h"
#include "LEDA/graph/graph_gen.h"

using namespace leda;
using namespace std;

int main(int argc, char const *argv[]) {

	graph G;
	node v1, w;
	edge e1;
	clock_t start, stop;
  double duration;

	random_graph(G, 30, 40);
	edge_array<int> cost(G);

	forall_edges(e1,G){
		srand ( time(NULL) ); //initialize the random seed
		int sub = rand() % 5;
		srand (time(NULL) + 10);
		cost[e1] = (rand() % 10 + 1) - sub;
	}

	node s;
  s = G.choose_node(); //o random node
	node_array<int> dist(G);
	node_array<edge> pred(G);

	start = clock();

	bool no_negative_cycle = BELLMAN_FORD_T(G,s,cost,dist,pred);


	if (no_negative_cycle){
		node v;
		node_matrix<int> RDist(G);

		//make all edges positive to use Dijkstra
		forall_edges(e1,G) cost[e1] = cost[e1] + dist[G.source(e1)] - dist[G.target(e1)];

		forall_nodes(v,G) { DIJKSTRA_T(G,v,cost,RDist[v],pred);}
		forall_nodes(v,G){
			int dv = dist[v];
			forall_nodes(w,G){
				if(RDist(v,w)!=INT_MAX){
					RDist(v,w) = RDist(v,w) + (dist[w] - dv);
				}
			}
		}
	}
	else std::cout << "There are negative cycles!" << std::endl
                 << "All dist-values unspecified!" << std::endl;

	stop = clock();
	duration = (stop - start) / (double)CLOCKS_PER_SEC;
	cout << "Runtime of Johnson Algorithm is: " << duration*1000.0 << " ms \n";



	return 0;
}
