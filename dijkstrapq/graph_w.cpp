#include "graph_w.h"

graph_w::graph_w(unsigned int n) {
	V = n;
	E = 0;
	adj_list = new vector<edge_w>[n];
}
//===========================================================
graph_w::~graph_w(){
	for (unsigned int i = 0; i < V; ++i)
		adj_list[i].clear();
	edge_list.clear();

	adj_list = nullptr;
}
//===========================================================
unsigned int graph_w::getV() {
	return V;
}
//===========================================================
unsigned int graph_w::getE() {
	return E;
}
//===========================================================
void graph_w::addEdge(edge_w e) {
	// Store the nodes at both ends of the edge into temp variables
	int v = e.either();
	int w = e.other(v);

	// Store the edge into the adjacency lists of each node and
	// increment the number of edges stored in this graph
	adj_list[v].push_back(e);
	adj_list[w].push_back(e);
	++E;
}
//===========================================================
vector<edge_w> graph_w::adj(unsigned int v)
{
	return adj_list[v];
}
//===========================================================
