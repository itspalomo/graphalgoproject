#include <iostream>
#include <queue>

using namespace std;

int main()
{
    // Priority Queue in STL is Max PQ by default
    // By using the 'greater' modifier we can convert into Min PQ
    priority_queue<int, vector<int>, greater<int>> pq;

    pq.push(4);
    pq.push(2);
    pq.push(3);

    while(!pq.empty()){ // while queue is not empty

        int t = pq.top();   // Extract-Min (retrieve minimum value)
        pq.pop();           // Extract-Min (remove minimum from queue)

        cout << t << " ";
    }

    return 0;
}
