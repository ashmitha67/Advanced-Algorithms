
/*
  Graph represented by adjacency matrix.
 */
class Graph {

  int ** tab; //adjacency matrix
  int n; //number of vertices in the graph

 public:

  //---------CONSTRUCTORS----------
  Graph() {} //default constructor
  Graph(int n); //Creates a graph with no edges and given number of vertices

  //---------DESTRUCTOR-----------
  ~Graph();

  //---------METHODS--------------
  void addEdge(int u, int v); //add the edge (u,v) to the graph. If u or v is out of range, then the method has no effect
  void deleteEdge(int u, int v); // delete the edge (u,v) from the graph. If the edge does not exist, then the method has no effect
  int vertices() { return n; } // return the number of vertices of the graph
  void show(); // show the vertices of the graph
  int edgeConnectivity(); // calculates the edge connectivity of the graph using flow

};
