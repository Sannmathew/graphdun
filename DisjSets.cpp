#include "DisjSets.h"

DisjSets::DisjSets( int numElements ){
  unions_.resize(numElements);
  for(int i = 0; i < numElements; i++)
    unions_[i] = -1;
  //number of sets starts from total number of vertices created
  number_of_sets_ = numElements-1;
}

int DisjSets::find(int x) const {
  if(unions_[x] < 0)
    return x;
  else
    return find(unions_[x]);
}


int DisjSets::find(int x) {
  if(unions_[x] < 0)
    return x;
  else
    return unions_[x] = find(unions_[x]);
}

bool DisjSets::addSets(int node1, int node2) {

  int x = find(node1);
  int y = find(node2);

  //checks to make sure two of the same root are not added to each other
  if(x == y)
    return false;
  else {
    unionSets(x,y);
    return true;
  }
}

bool DisjSets::notFull() {
  if(number_of_sets_ != 1)
    return true;
  else {
    /*
    for(int i = 0; i < unions_.size(); i++) {
      cout << unions_[i] << endl;
    }
    */
    return false;
  }
}

void DisjSets::unionSets(int root1, int root2) {
  if(unions_[root2] < unions_[root1]) {
    number_of_sets_--; //decrease set as two are combined
    unions_[root1] = root2;
  }
  else {
    if(unions_[root1] == unions_[root2])
      --unions_[root1];
    number_of_sets_--;
    unions_[root2] = root1;
  }
}
