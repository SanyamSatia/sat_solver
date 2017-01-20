#ifndef CLAUSE_H
#define CLAUSE_H

#include "atom.h"
#include <vector>
using namespace std;

class Clause {
  vector<Atom> atoms;

 public:

  int getSize();
  void addAtom(int num, bool neg);
  Atom getAtom(int ind);
  int isSatisfiable(int assignments[]);
};

#endif
