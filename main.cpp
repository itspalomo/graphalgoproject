#include <iostream>

using namespace std;

struct Vertex {
    int ID;                                             // unique vertex identifier
    int d;                                              // min total depth from source
    int p;                                              // predecessor vertex
    bool c;                                             // vertex 'color' to indicate if visited
};

void Dijstra(Vertex G[], int A[], int n, int s);
void initialize_source(Vertex G[], int n, int s);
void relax(Vertex G[], int A[], int n, int u, int v);

int main() {
    const int n = 5;
    Vertex G[n];                                        // vertex array
    int A[n*n] =                                        // adjacency weighted nxn matrix
    {
        0, 10, 5, 0, 0,
        0, 0, 2, 1, 0,
        0, 3, 0, 9, 2,
        0, 0, 0, 0, 4,
        7, 0, 0, 6, 0
    };

    for (int i = 0; i < n; i++)
        G[i].ID = i;                                    // set vertex id based on array position

    Dijstra(G, A, n, 0);

    // Verifying results
    cout << "v(d, p)\n";
    cout << "-----------------------\n";
    for (int i = 0; i < n; i++) {
        cout << "v" << i << "(" << G[i].d << ", " << G[i].p << ")\n";
    }

    /****************************************************************************
    Sample graph taken from pg 659 of the textbook.

    Results:
        v(d, p)
        -----------------------
        v0(0, -1)
        v1(8, 2)
        v2(5, 0)
        v3(9, 1)
        v4(7, 2)
    
    What this Means:
        - The predecessor 'p' value indicates vertex just prior to current vertex.
        The 'p' value of -1 indicates the source vertex.

        - The depth 'd' value indicate the smallest total depth weight from source
        to the current vertex.
    
    Example:
        - Shortest path from source v0 to v1 is through v2, as indicated by the
        'p' value. Even though v1 is adjacent to v0, the weight from v0 to v1
        is 10 as compared to d=8 comming from v0, v2 then v1 (p=2, from v2).

        - Shortest path from v0 to v3: from v3, p=1 so the vertex before is v1.
        Looking at v1, p=2, vertex before v1 is v2. From v2, p=0 which is the
        source. Therefore, shortest path from v0 to v3 is: v0->v2->v1->v3.
    
    ***************************************************************************/

    return 0;
}

void Dijstra(Vertex G[], int A[], int n, int s) {
    initialize_source(G, n, s);                         // set all but s's depth to 'infinity'

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
                relax(G, A, n, u, v);                   //      relax u's adjacents
            }
        }
    }
}
void initialize_source(Vertex G[], int n, int s) {
    for (int v = 0; v < n; v++) {                       // for each vertex v in G
        G[v].d = INT_MAX;                               //  v.d = infinity
        G[v].p = -1;                                    //  v.p = NIL ; -1 to say no predecessor
        G[v].c = 0;                                     //  v.c = 0 ; set have not visit
    }
    G[s].d = 0;                                         // s.d = 0
}
void relax(Vertex G[], int A[], int n, int u, int v) {
    if (G[v].d > G[u].d + A[u*n+v]) {                   // if (v.d > u.d + w(u,v))
        G[v].d = G[u].d + A[u*n+v];                     //  v.d = u.d + w(u,v)
        G[v].p = G[u].ID;                               //  v.p = u
    }
}