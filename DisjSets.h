
#ifndef DISJSETS_H_
#define DISJSETS_H_

class DisjSets {
public:
 DisjSets(int numElements);

 // Copy constructor.
 DisjSets(const DisjSets &rhs) {
   unions_.resize(rhs.unions_.size());
   number_of_sets_=rhs.number_of_sets_;
   for (int i = 0; i < rhs.unions_.size(); ++i) {
     unions_[i] = rhs.unions_[i];
   }
 }

 // Move constructor.
 DisjSets(DisjSets &&rhs):
 unions_{std::move(rhs.unions_)}, number_of_sets_{rhs.number_of_sets_} { }


 // Move constructor.
 DisjSets(DisjSets& rhs){
   for (int i = 0; i < rhs.unions_.size(); i++) {
     unions_[i]=-1;
   }
   number_of_sets_ = 0;
 }


 // Copy assignment operator.
 DisjSets & operator=(const DisjSets &rhs) {
       DisjSets copy = rhs;
       std::swap(*this, copy);
       return *this;
 }

 // Move assignment operator.
 DisjSets & operator=(DisjSets && rhs) {
   std::swap(unions_, rhs.unions_);
   std::swap(number_of_sets_, rhs.number_of_sets_);

   return *this;
 }

  ~DisjSets() = default;

  int find(int x) const;
  int find(int x);

  void unionSets(int root1, int root2);

  bool addSets(int root1, int root2);

  //checks if union-find sets are under one whole set
  bool notFull();

private:
  vector<int> unions_;
  int number_of_sets_ = 0;

};

#endif  // COURSES_CSCI335_DISJSETS_H_
