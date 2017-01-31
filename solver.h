#ifndef SOLVER_H
#define SOLVER_H

#include "clause.h"

class Solver {
  int numVars;
  int *assignments;
  vector<Clause> clauses;
  vector<int> unassignedVars;
  vector<int>* varsInClauses;

 public:

  Solver(int numVars_, vector<Clause>& clauses_);
  void solve();
  bool backtrack(int n);
  int clausesAreSatisfiable(int var);
  bool assignUnitClauses();
  void assignPureVars();
  void storeVarsInClauses();
};

#endif
