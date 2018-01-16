#include "graph.h"
#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
using namespace std;


Graph::Graph(int n)
{
  this->n = n;

  tab = new int*[n];
  for (int i = 0; i < n; i++)
    {
      tab[i] = new int[n];
      for (int j = 0; j < n; j++)
	tab[i][j] = false;
    }
}

Graph::~Graph()
{
  for (int i = 0; i < n; i++)
    delete[] tab[i];
  delete[] tab;
}

void Graph::addEdge(int u, int v)
{
  //if the u or v is out of range, or if u = v, the method have no effect
  if (u < 0 || u >= n || v < 0 || v >= n || u == v)
    return;
  tab[u][v] = 1;
  tab[v][u] = 1;
}

void Graph::deleteEdge(int u, int v)
{
  //if the u or v is out of range, or if u = v, the method have no effect
  if (u < 0 || u >= n || v < 0 || v >= n || u == v)
    return;
  tab[u][v] = 0;
  tab[v][u] = 0;
}

void Graph::show()
{
  for(int i = 0; i < n; i++)
    for(int j = 0 ; j < n; j++)
      if(tab[i][j] == 1 && i < j)
	cout << i << "-" << j << endl;
}


// Returns true if there is a path from source 's' to sink 't' in
//  residual graph. Also fills parent[] to store the path 
bool bfs(int n, int ** rGraph, int s, int t, int parent[])
{
    // Create a visited array and mark all vertices as not visited
    bool visited[n];
    memset(visited, 0, sizeof(visited));
 
    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
 
        for (int v=0; v<n; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
 
    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[t] == true);
}
 
// Returns tne maximum flow from s to t in the given graph
int fordFulkerson(int n, int ** graph, int s, int t)
{
    int u, v;
 
    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
    int **rGraph = new int *[n]; // Residual graph where rGraph[i][j] indicates 
                     // residual capacity of edge from i to j (if there
                     // is an edge. If rGraph[i][j] is 0, then there is not) 
    for(int i = 0; i < n ; i++)
      rGraph[i] = new int[n];

    for (u = 0; u < n; u++)
      for (v = 0; v < n; v++)
	rGraph[u][v] = graph[u][v];

    int parent[n];  // This array is filled by BFS and to store path
 
    int max_flow = 0;  // There is no flow initially
 
    // Augment the flow while tere is path from source to sink
    while (bfs(n, rGraph, s, t, parent))
    {
        // Find minimum residual capacity of the edhes along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
 
        // update residual capacities of the edges and reverse edges
        // along the path
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
 
        // Add path flow to overall flow
        max_flow += path_flow;
    }
 
    // Return the overall flow
    return max_flow;
}


int Graph::edgeConnectivity()
{
  int e = 0; //the edge connectivity
  /* int tmp;
  int max = 0;
  for(int i = 1; i < n ; i ++){
    e = fordFulkerson(n, tab, 0,i);
    if(e > max)
      max = e;
  }
  e = max;
*/

  e = fordFulkerson(n, tab, 0,n-1);
  return e;
}
