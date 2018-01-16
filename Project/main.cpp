#include "graph.h"
#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;

Graph loadFile(char * name)
{
  ifstream  file;
  file.open(name, ios::in);
  
  //set the number of vertices
  int n;
  file >> n;

  //create the graph with n vertices
  Graph g(n);

  //add the edges to the graph
  int u,v;
  //while we are not at the end of the file
  while(!file.eof()){
    file >> u;
    file >> v;
    g.addEdge(u,v);
  }

  file.close();

  //return the graph;
  return g;
}

//write the number n in the file "output.txt"
void writeOutput(int n)
{
  ofstream outfile ("output.txt");
  outfile << n <<endl;
}

//check if the input file exist or not
bool exist(char * name)
{
  ifstream file(name);
  if(file.good()){
    file.close();
    return true;
  }else{
    cout << "\""<< name << "\"" << " doesn't exist, retry !" << endl;
    return false;
  }
}

int main()
{
  char file[100];
  //while the input file is not correct, we ask the user to choose one
  do {
    cout << "Choose a correct input file in the current folder : " << endl;
    cin >> file;
  }while(!exist(file));

  Graph g = loadFile(file);
  //  g.show();
  
  int edge_connectivity = g.edgeConnectivity();
  cout << "The edge connectivity of this graph is " << edge_connectivity << endl;
  writeOutput(edge_connectivity); // we write the output in a file "output.txt"

  return 0;
}
