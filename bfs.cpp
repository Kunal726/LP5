#include <iostream>
#include <omp.h>
#include <map>
#include <list>
#include <queue>

using namespace std;

class Graph
{
public:
    map<int, bool> visited;
    map<int, list<int> > adj;

    // function to add an edge to graph
    void addEdge(int v, int w);

    // DFS traversal of the vertices
    // reachable from v
    void BFS(int v);
};

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

void Graph::BFS(int v)
{
    queue<int> q;
    q.push(v);

    visited[v] = true;

	#pragma omp parallel
    while (!q.empty())
    {
        int v1 = q.front();
        q.pop();
        cout << v1 << "  ";

        list<int>::iterator i;

		#pragma omp parallel for
        for (i = adj[v1].begin(); i != adj[v1].end(); ++i)
        {
            if (!visited[*i])
            {
                q.push(*i);
                visited[*i] = true;
            }
        }
    }
}

int main()
{
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 6);
    g.addEdge(3, 7);

    cout << "Following is Breadth First Traversal"
            " (starting from vertex 1) \n";

    // Function call
    g.BFS(1);

    return 0;
}