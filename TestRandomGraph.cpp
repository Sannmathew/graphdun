#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Graph.h"
#include "DisjSets.cpp"
using namespace std;

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <maximum_number_of_nodes>" << endl;
    return 0;
  }
  const string number(argv[1]);
  const int nodes_ = atoi(number.c_str());

  DisjSets Union(nodes_+1);
  Graph Example(nodes_);


  bool not_connected = true;
  bool values = true;
  bool addSet = true;
  int adj1_ = 0;
  int adj2_ = 0;
  srand(time(0)); //use current time as seed for random generator
  while (not_connected) {
    while (values) {
      adj1_ = rand() % nodes_ + 1;
      adj2_ = rand() % nodes_ + 1;
      values = false;
    }

    values = true;
    addSet = Union.addSets(adj1_,adj2_);
    if(addSet == true) {
      Example.AddAdj(adj1_, adj2_);
      Example.AddWei(adj1_, 1);
      Example.AddAdj(adj2_, adj1_);
      Example.AddWei(adj2_, 1);
    }
    not_connected = Union.notFull();
  }
  Example.OutDegrees();
}
