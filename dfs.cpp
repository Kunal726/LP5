#include <iostream>
#include <omp.h>
#include <stack>
#include <map>
#include <list>

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
    void DFS(int v);
};

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

void Graph::DFS(int v)
{
    stack<int> s;
    // Mark the current node as visited and
    // print it
    visited[v] = true;
    s.push(v);

    #pragma omp parallel
    while (!s.empty())
    {
        int v1 = s.top();
        s.pop();
        cout << v1 << " ";
		
		// use reverse_iterator to iterate from back for stack left to right and iterator to right to left
        list<int>::reverse_iterator i;

        #pragma omp parallel for
        for (i = adj[v1].rbegin(); i != adj[v1].rend(); i++)
            if (!visited[*i])
            {
                s.push(*i);
                visited[*i] = true;
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

    cout << "Following is Depth First Traversal"
            " (starting from vertex 1) \n";

    // Function call
    g.DFS(1);

    return 0;
}