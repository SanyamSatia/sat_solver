#include "clause.h"

int Clause::getSize() {
  return atoms.size();
}

void Clause::addAtom(int num, bool neg) {
  Atom newAtom(num, neg);
  atoms.push_back(newAtom);
}

Atom Clause::getAtom(int ind) {
  return atoms[ind];
}

int Clause::isSatisfiable(int assignments[]) {
  int num, neg, val;
  bool sat = false, unassigned = false;

  for(int i = 0; i < atoms.size(); ++i) {
    num = atoms[i].getNum();
    neg = atoms[i].isNeg();
    val = assignments[num];

    if(val == -1) {
      unassigned = true;
      continue;
    }

    if(neg) val = !val;

    sat = sat || val;

    if(sat) return 1;
  }

  if(unassigned) return 0;
  else return -1;
}
