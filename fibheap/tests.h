#ifndef tests_h
#define tests_h

#include <fstream>
#include <sstream>
#include <chrono>
#include "graph.h"

/******************************************************************************
 * The tests will include:
 * - Verification of Dijkstra's algorithm by giving it a small graph size.
 * 
 * - Measuring execution time of Sparse vs Dense graphs:
 *      I. A sparse graph is a graph whose number of edges is approximately
 *      equal to it's number of vertices (E = O(V)), in this case E = 2V.
 * 
 *      II. A dense graph is a graph whose number of edges is approximately
 *      equal to it's number of vertices, squared (E = O(V^2)). For the
 *      test, a dense graph will have E = (V(V-1))/2.
 * 
 *      III. The graph can also be measured for something in-between a dense
 *      and a sparse graph. 
 * 
 *  - Other tests...
******************************************************************************/

#define sparse(V) 2*V
#define dense(V) (V*(V-1))/2          // fully connected

void test_Dijkstra(int V, int E);
void measure_sparse_graph(int V_initial, int V_final, int datapoints, int avg_count);
void measure_dense_graph(int V_initial, int V_final, int datapoints, int avg_count);


void test_Dijkstra(int V, int E) {
	//*** Testing Dijkstra's Algorithm for both Naive and PQ implementation

	Graph* G = new Graph(V, E);						// generating a small graph to verify correctness
	printf("Testing the graph: G(V,E)=G(%i,%i)\n\n",V,E);
	printf("Adjacency List:\n");
	for (int i = 0; i < V; i++){
        Vertex* v = G->vertex(i);
		while (v!=NULL){
			printf("v%i(%i)->", v->ID, v->w);
            v = v->adj;
        }
        printf("NULL\n");
	}
	printf("\nDijkstra_n with the source s=0\n");

	G->Dijkstra_n(0);								// testing naive implementation

	for (int i = 0; i < V; i++)
		printf("v%i(%i, %i)\n", G->ID(i), G->depth(i), G->predecessor(i));
	printf("\nDijkstra_pq with the source s=0\n");

	G->Dijkstra_pq(0);								// testing pq implementation

	for (int i = 0; i < V; i++)
		printf("v%i(%i, %i)\n", G->ID(i), G->depth(i), G->predecessor(i));
	printf("\nDijkstra_fh with the source s=0\n");

	G->Dijkstra_fh(0);								// testing pq implementation

	for (int i = 0; i < V; i++)
		printf("v%i(%i, %i)\n", G->ID(i), G->depth(i), G->predecessor(i));
	printf("\n");

	delete G;
}
void measure_sparse_graph(int V_initial, int V_final, int datapoints, int avg_count) {
    std::fstream file;
	std::stringstream ss, ss_n, ss_pq, ss_fh;

	std::chrono::system_clock::time_point start, end;

	Graph *G;


	file.open("sparse_time_log.txt");
	file << "V\tE\tt_n\tt_pq\tt_fh\n";

	unsigned int s = 0;
	double average_n, average_pq, average_fh;
    int increment = (V_final - V_initial) / datapoints;
	for (int V = V_initial; V <= V_final; V += increment) {
        int E = sparse(V);
			printf("G(%i,%i)", V, E);				// printing for logs to know when fail
			G = new Graph(V,E);
			average_n = 0.0;
			average_pq = 0.0;
			average_fh = 0.0;

			std::stringstream().swap(ss);
			ss << std::fixed << V;
			std::string s_V = ss.str();
			file << s_V << "\t";

			std::stringstream().swap(ss);
			ss << std::fixed << E;
			std::string s_E = ss.str();
			file << s_E << "\t";

			for (int i = 0; i < avg_count; i++) {
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

				//** Measuring Dijkstra Algorithm (fh) **//
				start = std::chrono::system_clock::now();
				G->Dijkstra_fh(s);
				end = std::chrono::system_clock::now();

				duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
				average_fh += double(duration.count());

				printf(".");				// for visual purposes
			}
			average_n /= avg_count;
			average_pq /= avg_count;
			average_fh /= avg_count;

			std::stringstream().swap(ss_n);
			std::stringstream().swap(ss_pq);
			std::stringstream().swap(ss_fh);

			ss_n.precision(2);										// setting precision to 2 decimal places
			ss_pq.precision(2);
			ss_fh.precision(2);

			ss_n << std::fixed << average_n;						// putting double value into stringstream
			ss_pq << std::fixed << average_pq;
			ss_fh << std::fixed << average_fh;

			std::string s_n = ss_n.str();							// putting stringstream into string
			std::string s_pq = ss_pq.str();
			std::string s_fh = ss_fh.str();

			file << s_n << "\t";									// putting string results into file
			file << s_pq << "\t";
			file << s_fh << "\n";

			delete G;
        printf("Finished!\n");
	}

	file.close();
}
void measure_dense_graph(int V_initial, int V_final, int datapoints, int avg_count) {
    std::fstream file;
	std::stringstream ss, ss_n, ss_pq, ss_fh;

	std::chrono::system_clock::time_point start, end;

	Graph *G;


	file.open("dense_time_log.txt");
	file << "V\tE\tt_n\tt_pq\n";

	unsigned int s = 0;
	double average_n, average_pq, average_fh;
    int increment = (V_final - V_initial) / datapoints;
	for (int V = V_initial; V <= V_final; V += increment) {
        int E = dense(V);
			printf("G(%i,%i)", V, E);				// printing for logs to know when fail
			G = new Graph(V,E);
			average_n = 0.0;
			average_pq = 0.0;
			average_fh = 0.0;

			std::stringstream().swap(ss);
			ss << std::fixed << V;
			std::string s_V = ss.str();
			file << s_V << "\t";

			std::stringstream().swap(ss);
			ss << std::fixed << E;
			std::string s_E = ss.str();
			file << s_E << "\t";

			for (int i = 0; i < avg_count; i++) {
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

				//** Measuring Dijkstra Algorithm (fh) **//
				start = std::chrono::system_clock::now();
				G->Dijkstra_fh(s);
				end = std::chrono::system_clock::now();

				duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
				average_fh += double(duration.count());

				printf(".");				// for visual purposes
			}
			average_n /= avg_count;
			average_pq /= avg_count;
			average_fh /= avg_count;

			std::stringstream().swap(ss_n);
			std::stringstream().swap(ss_pq);
			std::stringstream().swap(ss_fh);

			ss_n.precision(2);										// setting precision to 2 decimal places
			ss_pq.precision(2);
			ss_fh.precision(2);

			ss_n << std::fixed << average_n;						// putting double value into stringstream
			ss_pq << std::fixed << average_pq;
			ss_fh << std::fixed << average_fh;

			std::string s_n = ss_n.str();							// putting stringstream into string
			std::string s_pq = ss_pq.str();
			std::string s_fh = ss_fh.str();

			file << s_n << "\t";									// putting string results into file
			file << s_pq << "\t";
			file << s_fh << "\n";

			delete G;
        printf("Finished!\n");
	}

	file.close();
}

#endif
