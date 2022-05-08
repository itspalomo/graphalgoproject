#include <iostream>

using namespace std;

#define numvert 5

int main()
{
    // Representation of an Adjacency Matrix using a 2D Array
    int adjmat[numvert][numvert] =
    {{0, 1, 0, 3, 0},
    {1, 0, 4, 2, 4},
    {0, 4, 0, 0, 6},
    {3, 2, 0, 0, 1},
    {0, 4, 6, 1, 0}};

    // Starting node is always 0
    int source = 0;
    int dist[numvert];

    // Initialize all values in the distance array
    for (int i = 0; i < numvert; i++){
        dist[i] = 9999;
    }

    // Initialize the visited boolean array as all false
    bool visited[numvert] = { false, false, false, false, false };


    // Starting node is visited first
    visited[source] = true;
    dist[source] = 0;

    // Starting Dijkstra's Algo Proper
    cout << "Starting from source " << source << endl;
    int curvec = source; // current vector

    // Prints current list of distances
    cout << "Distances : ";
    for (int j = 0; j < numvert; j++){
        cout << dist[j] << " ";
    }
    cout << endl;

    while (1){
        for (int j = 0; j < numvert; j++){
            if (dist[curvec] + adjmat[curvec][j] < dist[j] && adjmat[curvec][j] != 0){
                dist[j] = dist[curvec] + adjmat[curvec][j];
            }
        }

        int min_dist = 9999;
        int new_curr = curvec;

        for (int j = 0; j < numvert; j++){
            if (!visited[j] && dist[j] < min_dist){
                new_curr = j;
                min_dist = dist[j];
            }
        }

        if (new_curr == curvec){
            cout << "No updates --- algorithm ends" << endl;
            break;
        } else {
            cout << "Visited " << new_curr << " distance: " << dist[new_curr] << endl;
            visited[new_curr] = true;
            curvec = new_curr;

            cout << "Distances : ";
            for (int j = 0; j < numvert; j++){
                cout << dist[j] << " ";
            }
            cout << endl;
        }

    }
    return 0;
}
