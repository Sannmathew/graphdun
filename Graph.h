#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Graph  class
//
// CONSTRUCTION: with/without parameters
//
// ******************PUBLIC OPERATIONS*********************
// void CreateVertex( x )       --> creates vertex with id x
// void AddAdj( x, y)           --> Adds adj to location with id x
// void AddWei (x,y)  -->          Adds wei to location with id x
// void Test(x,y )        --> Checks if two points are connected
// void ShortestPath(x )      --> Finds shortest path with given flag
// void OutDegrees( rhs )      --> Returns number of edges and statistics on out-degrees

// ******************PRIVATE OPERATIONS*********************
// void DijkstraAlgo(vertex)        --> finds shortest path and distance for each node
// bool PreviousRecursive(vertex,int, bool )      --> Recursively finds path of each node

class Graph {
public:
  // Default constructor.
Graph() {current_size_=0;}

Graph(int size): vertices_(size) {
  int i = 1;
  for (auto & root : vertices_) {
    CreateVertex(i);
    i++;
  }
}

// Copy constructor.
Graph(const Graph &rhs) {
  cout <<"sure"<<endl;
  vertices_.resize(rhs.vertices_.size());
  current_size_=rhs.current_size_;
  for(int i = 0; i < rhs.vertices_.size(); ++i)
    vertices_[i] = rhs.vertices_[i];
}

// Move constructor.
Graph(Graph &&rhs):
vertices_{std::move(rhs.vertices_)}, current_size_{rhs.current_size_} { }


// Move constructor.
Graph(Graph& rhs){
  for (int i = 0; i < rhs.current_size_; i++) {
    vertices_[i]->Clear();
  }
  current_size_ = 0;
}

// Copy assignment operator.
Graph & operator=(const Graph &rhs) {
      Graph copy = rhs;
      std::swap(*this, copy);
      return *this;
}

// Move assignment operator.
Graph & operator=(Graph && rhs) {
  std::swap(vertices_, rhs.vertices_);
  std::swap(current_size_, rhs.current_size_);

  return *this;
}

~Graph() = default;

//creates new vertex with given id
void CreateVertex(int ide) {
    Vertex* s;
    s = new Vertex(ide);
    vertices_[current_size_] = s;
    current_size_++;
}

//adds adj to position with given id
void AddAdj(int ide, int ad) {
  number_of_edges_++;
  vertices_[ide-1]->current_size_++;
  vertices_[ide-1]->adj_.push_back(vertices_[ad-1]);
}

//adds wei to position with given id
void AddWei(int ide, double wei) {
  vertices_[ide-1]->weight_.push_back(wei);
}

void Print(int i, int j) {
  cout << vertices_[i]->id_ << endl;
  cout << vertices_[i]->weight_[j] << endl;
}

//tests if two inputs are connected
void Test(int x, int y) {
  bool found = false;
  for(int i = 0; i < vertices_[x-1]->current_size_; i++) {
    if (vertices_[x-1]->adj_[i] == vertices_[y-1]) {
      cout << x << " " << y << ": " << "Connected, weight of edge is " << vertices_[x-1]->weight_[i] << endl;
      found = true;
    }
  }
  if(found == false)
    cout << x << " " << y << ": " << "Not connected" << endl;

}

//prints shortest path to each node
void ShortestPath(int flag) {
  Vertex* v = vertices_[flag-1];
  DijkstraAlgo(v);
  for(int i = 0; i < current_size_; i++) {
    v = vertices_[i];
    if(v != vertices_[flag-1]) {
      cout << v->id_ << ": ";
      PreviousRecursive(v,vertices_[flag-1]->id_,false);
      cout << " Total cost: " << v->distance_ << endl;
    }
  }
}

//finds number of edges and stats on out-degrees
void OutDegrees() {
  int max = 0;
  int min = vertices_[0]->current_size_;
  int total = 0;
  for(int i = 0; i < current_size_; i++){
    if(vertices_[i]->current_size_ > max)
      max = vertices_[i]->current_size_;
    if(vertices_[i]->current_size_ < min)
      min = vertices_[i]->current_size_;
    total= total + vertices_[i]->current_size_;
    }
  cout << "Number of edges in graph: " << total/2 << " "  << endl;
  cout << "Smallest out-degree: " << min << endl;
  cout << "Largest out-degree: " << max << endl;
  cout << "Average out-degree: " << total/current_size_ << endl;

}

int GetSize() {
  return current_size_;
}

int GetVectorSize() {
  return vertices_.size();
}

private:
  struct Vertex {
    int current_size_ = 0;
    int id_ = 0;
    vector<Vertex *> adj_;
    vector<double>weight_;

    bool known_ = false;
    double distance_ = 0;
    Vertex* previous_ = nullptr;


    Vertex(){  }

    Vertex(int ide){
      id_ = ide;
    }
    // Copy constructor.
    Vertex(const Vertex &rhs){
      current_size_ = rhs.current_size_;
      for (int i = 0; i < rhs.current_size_; ++i) {
        adj_[i] = rhs.adj_[i];
        weight_[i] = rhs.weight_[i];
      }
    }

    Vertex * clone(Vertex * copy) const {
      Vertex *s;
      s = new Vertex(copy->id_);
      int c_size_ = copy->current_size_;
      for (int i = 0; i < c_size_; i++) {
        s->adj_[i] = copy->adj_[i];
        s->weight_[i] = copy->weight_[i];
      }
      return s;
    }

    ~Vertex() {Clear();}

    void Clear() {
      id_ = -1;
      for (int i = 0; i < current_size_; ++i) {
        delete adj_[i];
        adj_[i] = nullptr;
        weight_[i] = 0;
      }
      delete previous_;
      previous_ = nullptr;
    }
  };

  //calculates shortest path/distance to each node from starting vertex
  void DijkstraAlgo(Vertex* s) {
    for(int i = 0; i < current_size_; i++) {
      vertices_[i]->distance_ = numeric_limits<double>::max();
      vertices_[i]->known_ = false;
    }
    s-> distance_ = 0;

    priority_queue<Vertex*> P;
    P.push(s);

    for(;;) {
      Vertex* v = nullptr;
      bool success = false;
      while(!P.empty() && !success) {
        v = P.top();
        P.pop();
        if(!v->known_)
          success = true;

      }
      if(!success)
        break;
      v->known_ = true;

      for(int i = 0; i < v->current_size_; ++i) {
        if(v->distance_ + v->weight_[i] < v->adj_[i]->distance_) {
          v->adj_[i]->distance_ = v->distance_ + v->weight_[i];
          P.push(v->adj_[i]);
          v->adj_[i]->previous_ = v;
        }
      }

    }
  }

  //recursively calculates path to node from starting node
  bool PreviousRecursive(Vertex* v, int ids, bool temp) {
    if(v->previous_ == nullptr && temp == false) {
      if(v->id_!=ids)
        return false;
      cout << v->id_ << ", ";
      return true;
    } else if(v->previous_ != nullptr && temp == true) {
      cout << v->id_ << ", ";
      return true;
    } else
      return PreviousRecursive(v,ids, PreviousRecursive(v->previous_,ids, temp));
  }

  int current_size_ = 0;
  vector<Vertex *> vertices_;
  int number_of_edges_;

};

#endif  // COURSES_CSCI335_BINOMIAL_QUEUE_H_
