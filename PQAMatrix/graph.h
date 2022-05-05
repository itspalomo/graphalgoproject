#ifndef graph_h
#define graph_h

#include "vertex.h"
#include "pqueue.h"

#define watch(x) std::cout << (#x) << ": " << x << "\n"

#define MAX_WEIGHT 100                              // the max weight from one vertex to another

//////////////////////////-- Graph Class Interface --////////////////////////

class Graph{
public:
    Graph(int V, int E);                            // Constructor
    ~Graph();

    void Dijkstra_n(int s);                         // Dijkstra's single source shortest path (Naive)
    void Dijkstra_pq(int s);                        // Dijkstra's single source shortest path (PQ)
    void initialize_source(int s);                  // set all vertices to INFINITY but source
    void relax(int u, int v);                       // relax vertex 'v' if shorter path found

    int ID(int v) {return G[v].ID;}
    int depth(int v) {return G[v].d;}               // get v.d
    int predecessor(int v) {return G[v].p;}         // get v.p
    int weight(int i, int j) {return A[i*n+j];}     // get A[i,j]
    Vertex vertex(int v) {return (G[v]);}           // get G.v
    int size() {return n;}                          // get |G.V|

private:
    Vertex *G;                                      // Graph array pointer
    int *A;                                         // Adjacency Matrix
    int n;                                          // number of vertices
};


//////////////////////////-- Constructor/Destructor Definitions --////////////////////////

Graph::Graph(int V, int E) {
    // Constructor will allocate memory for vertex 'G' and matrix 'A' based on V
    // Then it will randomly assign values to the 'A' based on V and set vertex.ID based on their array location

    G = new Vertex[V];                              // allocating memory for G
    A = new int[V*V];                               // allocating memory for A

    for (int i = 0; i < V; i++)                     // assigning ID values
        G[i].ID = i;

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            A[i*V+j] = 0;                           // make sure all values are 0 first

    int edges = 0;                                  // edges should be equal to given 'E'
    for (int i = 0; i < V; i++) {
        int j = rand() % V;                         // this is so that if E<<|V^2| not all weight are at beginning of matrix


        if ((i!=j) && (A[i*V+j]==0)) {              // we assume that vertex does not go back to itself
                                                    //  and only assign if there isn't already some value>0 
            A[i*V+j] = rand() % MAX_WEIGHT+1;       // assign some random weight(i,j) from 0 to 100 (MAX_WEIGHT)
            edges++;
        }

        if (edges > E)
            break;
        if ((edges < E) && (i >= (V-1)))            // go back to first row if we don't have correct number of edges
            i = -1;
    }
    this->n = V;
}
Graph::~Graph() {
    delete[] G;                                     // deallocate memory once done with Graph
    delete[] A;
}


//////////////////////////-- Graph Member Function Definitions --////////////////////////

void Graph::Dijkstra_n(int s) {
    initialize_source(s);                         // set all but s's depth to 'infinity'

    int visits = 0;
    while (visits < n) {
        Vertex* min = NULL;                             // temp min vertex variable
        for (int i = 0; i < n; i++) {                   // u = extract_min()
            if (!min && !G[i].c) {                      //  set min as first non-visited vertex
                min = &(G[i]);
                continue;
            }
            if (!(G[i].c) && G[i].d < min->d)           //  if (have not visited & i.d < min.d)
                min = &(G[i]);                          //      min.d = i.d ; update min to vertex with min 'd'
        }
        min->c = 1;                                     // u.c = 1 ; mark as visited
        visits++;                                       // increment visits
        int u = min->ID;
        for (int v = 0; v < n; v++) {                   // for each vertex v in G.A[u]
            if (A[u*n+v]) {                             //  if (A[u,v]) ; if v is adjacent to u
                relax(u, v);                            //      relax u's adjacents
            }
        }
    }
}
void Graph::Dijkstra_pq(int s) {
    initialize_source(s);                         // set all but s's depth to 'infinity'

    PQueue<Vertex> Q(n);                             // Q <- G.V
    for (int i = 0; i < n; i++)
        Q.push(G[i]);

    while (!Q.empty()) {

        Vertex min = Q.pop();                           // u = Extract-Min()

        int u = min.ID;
        G[u].c = 1;

        for (int v = 0; v < n; v++) {
            if (A[u*n+v]) {
                int current = G[v].d;
                relax(u, v);
                if (G[v].d != current)
                    Q.modify(G[v], G[v].d);                    // G.v is pushed into queue to update relaxed vertex
            }
        }
    }
}           
void Graph::initialize_source(int s) {
    for (int v = 0; v < n; v++) {                       // for each vertex v in G
        G[v].d = INT_MAX;                               //  v.d = infinity
        G[v].p = -1;                                    //  v.p = NIL ; -1 to say no predecessor
        G[v].c = 0;                                     //  v.c = 0 ; set have not visit
    }
    G[s].d = 0;                                         // s.d = 0
}            
void Graph::relax(int u, int v) {
    if (G[v].d > G[u].d + A[u*n+v]) {                   // if (v.d > u.d + w(u,v))
        G[v].d = G[u].d + A[u*n+v];                     //  v.d = u.d + w(u,v)
        G[v].p = G[u].ID;                               //  v.p = u
    }
}               

#endif