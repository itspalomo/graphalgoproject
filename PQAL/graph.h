#ifndef graph_h
#define graph_h

#include "vertex.h"
#include "pqueue.h"

#define MAX_WEIGHT 100

//////////////////////////-- Graph Class Interface --////////////////////////

class Graph{
protected:
public:
    Graph(int V, int E);
    ~Graph() {delete[] G;}

    void Dijkstra_n(int s);                         // Dijkstra's single source shortest path (Naive)
    void initialize_source(int s);                  // set all vertices to INFINITY but source
    void relax(int u, int v, int w);                       // relax vertex 'v' if shorter path found
    void Dijkstra_pq(int s);                        // Dijkstra's single source shortest path (PQ)
    

    int ID(int v) {return G[v].ID;}
    int depth(int v) {return G[v].d;}               // get v.d
    int predecessor(int v) {return G[v].p;}         // get v.p
    Vertex* vertex(int i) {return &G[i];}

private:
    Vertex *G;
    int n;
};

Graph::Graph(int V, int E) {
    G = new Vertex[V];                          // allocating memory for G for number of vertices

    for (int i = 0; i < V; i++)                 // assign ID values
        G[i].ID = i;
    
    int edges = 0;                              // edges should be equal to given 'E'
    while (edges < E) {
        int u = rand() % V;                     // go to some random vertex
        int v = rand() % V;
        
        if (u == v)                             // assuming vertex cannot go back to itself
            continue;

        Vertex *current = &G[u];
        bool repeat = 0;                        // check for repeated adj
        while (current->adj!=NULL && !repeat) { // go to end of vertex list
            if (current->adj->ID == G[v].ID) {  // check for no repeats
                repeat = 1;
            }
            current = current->adj;
        }
        if (!repeat) {                          // if not a repeat edge
            Vertex *newV = new Vertex;
            newV->ID = G[v].ID;
            newV->w = rand() % MAX_WEIGHT + 1;  // assign some random weight betwee 1-MAX_WEIGHT
            current->adj = newV;                // place G into list
            edges++;                            // increment number of edges accounted for
        }
    }
    this->n = V;
}

void Graph::Dijkstra_n(int s) {
    initialize_source(s);                         // set all but s's depth to 'infinity'

    int visits = 0;
    while (visits < n) {
        Vertex* u = NULL;                             // temp u vertex variable
        for (int i = 0; i < n; i++) {                   // u = extract_u()
            if (!u && !G[i].c) {                      //  set u as first non-visited vertex
                u = &(G[i]);
                continue;
            }
            if (!(G[i].c) && G[i].d < u->d)           //  if (have not visited & i.d < u.d)
                u = &(G[i]);                          //      u.d = i.d ; update u to vertex with u 'd'
        }
        u->c = 1;                                     // u.c = 1 ; mark as visited
        visits++;                                       // increment visits
        Vertex* v = u->adj;
        while (v != NULL) {                             // for each vertex v in G.A[u]
            relax(u->ID, v->ID, v->w);
            v = v->adj;
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

        Vertex* v = G[u].adj;
        while (v != NULL) {
            int current = v->d;
            relax(u, v->ID, v->w);
            if (v->d != current && !v->c)               // if v was relaxed and has not been visited
                    Q.modify(*v, v->d);
            v = v->adj;
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
void Graph::relax(int u, int v, int w) {
    if (G[v].d > G[u].d + w) {                   // if (v.d > u.d + w(u,v))
        G[v].d = G[u].d + w;                     //  v.d = u.d + w(u,v)
        G[v].p = G[u].ID;                               //  v.p = u
    }
}

#endif