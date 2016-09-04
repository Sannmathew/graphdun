#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Graph.h"

using namespace std;

void Test(string vertices, string adjacencies_test ) {
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
  ifstream readin2(adjacencies_test);
  int a, b;
  while(getline(readin2,input)) {
    stringstream temp2(input);
    while(getline(temp2,input2,' ')) {
      if(offset == true) {
        a = atoi(input2.c_str());
        offset = false;
      }
      else {
        b = atoi(input2.c_str());
        Example.Test(a,b);
        offset = true;
      }
    }
  }

/*
  Graph Construct;
  Construct = Example;
  Graph Testing = Example;
  Testing.AddAdj(8,1);
  Testing.AddWei(8,33);
  Graph Test(Example);
*/





}

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <vertices> <testadjacencies>" << endl;
    return 0;
  }

  const string vertices_file(argv[1]);
  const string adjacencies_test_file(argv[2]);
  Test(vertices_file, adjacencies_test_file);

}
