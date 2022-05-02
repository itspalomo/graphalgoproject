#ifndef GRAPH_W_H_INCLUDED
#define GRAPH_W_H_INCLUDED

#include "edge_w.h"
#include <vector>
#include <iostream>

using namespace std;

class graph_w {
	private:
		unsigned int V;
		unsigned int E;
		vector<edge_w> edge_list;
		vector<edge_w>* adj_list;

	public:

		graph_w(unsigned int n);
		~graph_w();
		unsigned int getV();
		unsigned int getE();
		void addEdge(edge_w e);
		vector<edge_w> adj(unsigned int v);

		friend ostream& operator<<(ostream& os, const graph_w& g)
		{
			os << "Vertices: " << g.V << "\nEdges: " << g.E << endl;

			// Print the egdes of each adjacency list
			for (unsigned int i = 0; i < g.V; ++i)
			{
				os << "\nAdjacency List " << i << ":\n";
				for (edge_w& e : g.adj_list[i])
					os << e << endl;
			}
			return os;
		}

		friend istream& operator>>(istream& is, graph_w& g)
		{
			// Clear the graph if it was previously constructed
			if(g.V != 0) g.~graph_w();
			g.E = 0;


			// Read in number of vertices and edges
			unsigned int edges;
			is >> g.V >> edges;

			// Create a new array of adjacency lists
			g.adj_list = new vector<edge_w>[g.V];

			// Add each edge into the adjacency lists
			for (unsigned int i = 0; i < edges; ++i)
			{
				edge_w newEdge(0, 0, 0.00);
				is >> newEdge;
				g.addEdge(newEdge);
			}
			return is;
		}
};

#endif // GRAPH_W_H_INCLUDED
