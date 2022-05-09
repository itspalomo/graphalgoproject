#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <chrono>
#include "tests.h"

int main() {
#if 0
	printf("Sparse Graph:\n");
	measure_sparse_graph(10, 25, 15, 10);
	printf("Dense Graph:\n");
	measure_dense_graph(10, 25, 15, 10);
#endif

	for (int i = 10; i <= 20; i++)
		test_Dijkstra(5,i);

    return 0;
}

