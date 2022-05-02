#include "dijkstraspq.h"


DijkstraPQ::DijkstraPQ(graph_w& we_g)
{

}
//===========================================================
DijkstraPQ::~DijkstraPQ()
{
	delete[] visited;
	visited = nullptr;
}

