#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include "Vertex.h"
#include "Graph.h"
#include <queue>


using namespace std;

void Test(string vertices, int starting_flag ) {
  ifstream readin(vertices);
  string input;
  getline(readin, input);
  Graph Example(atoi(input.c_str()));

  bool offset = true;
  string input2;

  while(getline(readin, input)) {

    stringstream temp(input);
    getline(temp,input2, ' ');
    int id = atoi(input2.c_str());
    while(getline(temp,input2,' ')) {
      if(offset == true) {
        Example.AddAdj(id, atoi(input2.c_str()));
        offset = false;
      }
      else{
        Example.AddWei(id, atof(input2.c_str()));
        offset = true;
      }

    }
  }
  Example.ShortestPath(starting_flag);
/*
  Graph Construct;
  Construct = Example;
  //Graph Testing = Example;
  Graph Test(Example);
  Testing.ShortestPath(1);
  */
}

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <GRAPH_FILE> <STARTING_VERTEX>" << endl;
    return 0;
  }

  const string graph_file(argv[1]);
  const string starting_vertices_flag(argv[2]);
  int flag_int = atoi(starting_vertices_flag.c_str());
  Test(graph_file, flag_int);


}
