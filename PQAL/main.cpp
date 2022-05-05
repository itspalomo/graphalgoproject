#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "ggraph.h"


void test_Dijkstra(int V, int E);

int main() {
    Graph *G;
    int V(5), E(16);

	std::fstream file;
	std::stringstream ss, ss_n, ss_pq;

	std::chrono::system_clock::time_point start, end;

	/*
		Test Parameters:
		- sparse vs dense graph
		- constant source vertex
		- random source vertex
	*/

	file.open("time_log.txt");
	file << "V\tE\tt_n\tt_pq\n";

	unsigned int number_of_tests = 5;			// run amount for average
	unsigned int s = 0;
	double average_n, average_pq;
	for (V = 100; V <= 1000; V += 100) {
		unsigned int max_edges = (V*(V-1)/2);
		for (E = V*2; E <= max_edges; E += ((max_edges-(V*2))/10)) {
			printf("G(%i,%i)", V, E);				// printing for logs to know when fail
			G = new Graph(V,E);
			average_n = 0.0;
			average_pq = 0.0;

			std::stringstream().swap(ss);
			ss << std::fixed << V;
			std::string s_V = ss.str();
			file << s_V << "\t";

			std::stringstream().swap(ss);
			ss << std::fixed << E;
			std::string s_E = ss.str();
			file << s_E << "\t";

			for (int i = 0; i < number_of_tests; i++) {
				//** Measuring Dijkstra Algorithm (naive) **//
				start = std::chrono::system_clock::now();
				G->Dijkstra_n(s);
				end = std::chrono::system_clock::now();

				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
				average_n += double(duration.count());

				//** Measuring Dijkstra Algorithm (pq) **//
				start = std::chrono::system_clock::now();
				G->Dijkstra_pq(s);
				end = std::chrono::system_clock::now();

				duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
				average_pq += double(duration.count());

				printf(".");				// for visual purposes
			}
			average_n /= number_of_tests;
			average_pq /= number_of_tests;

			std::stringstream().swap(ss_n);
			std::stringstream().swap(ss_pq);

			ss_n.precision(2);										// setting precision to 2 decimal places
			ss_pq.precision(2);

			ss_n << std::fixed << average_n;						// putting double value into stringstream
			ss_pq << std::fixed << average_pq;

			std::string s_n = ss_n.str();							// putting stringstream into string
			std::string s_pq = ss_pq.str();

			file << s_n << "\t";									// putting string results into file
			file << s_pq << "\n";

			delete G;
			printf("Finished!\n");
		}		
	}

	file.close();

    return 0;
}

void test_Dijkstra(int V, int E) {
	//*** Testing Dijkstra's Algorithm for both Naive and PQ implementation

	Graph* G = new Graph(V, E);						// generating a small graph to verify correctness
	printf("Testing the graph: G(V,E)=G(5,15)\n\n");
	printf("Adjacency List:\n");
	for (int i = 0; i < 5; i++){
        Vertex* v = G->vertex(i);
		while (v!=NULL){
			printf("v%i(%i)->", v->ID, v->w);
            v = v->adj;
        }
        printf("NULL\n");
	}
	printf("\nDijkstra_n with the source s=0\n");

	G->Dijkstra_n(0);								// testing naive implementation

	for (int i = 0; i < 5; i++)
		printf("v%i(%i, %i)\n", G->ID(i), G->depth(i), G->predecessor(i));
	printf("\nDijkstra_pq with the source s=0\n");

	G->Dijkstra_pq(0);								// testing pq implementation

	for (int i = 0; i < 5; i++)
		printf("v%i(%i, %i)\n", G->ID(i), G->depth(i), G->predecessor(i));
	printf("\n");

	delete[] G;
}
