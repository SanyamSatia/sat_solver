#include <iostream>
#include "solver.h"

Solver::Solver(int numVars_, vector<Clause>& clauses_) {
  numVars = numVars_;
  clauses = clauses_;
}

int Solver::clausesAreSatisfiable() {
  int res;
  bool falsePossible = false;

  for(int i = 0; i < clauses.size(); ++i) {
    res = clauses[i].isSatisfiable(assignments);
    if(res == -1) return -1;
    else if(res == 0) falsePossible = true;
  }

  if(falsePossible) return 0;
  else return 1;
}

bool Solver::backtrack(int n) {
  int res;
  bool childRes;

  for(int i = 0; i < 2; ++i) {
    assignments[n] = i;
    res = clausesAreSatisfiable();
    if(res == 1) return true;
    else if(res == 0) {
      childRes = backtrack(n + 1);
      if(childRes) return true;
    }
  }

  // Reset and backtrack
  assignments[n] = -1;
  return false;
}

void Solver::solve() {
  bool sat;
  assignments = new int[numVars + 1];
  memset(assignments, -1, sizeof(int) * (numVars + 1));

  sat = backtrack(1);

  if(sat) {
    cout<<"Satisfiable\n";
    for(int i = 1; i <= numVars; ++i) {
      cout<<i<<": ";
      if(assignments[i] == 1) {
        cout<<"T";
      }
      else if(assignments[i] == 0) {
        cout<<"F";
      }
      else {
        cout<<"T/F";
      }
      cout<<endl;
    }
  }
  else {
    cout<<"Unsatisfiable\n";
  }

  // cout<<numVars<<' '<<assignments[1]<<endl;

  delete[] assignments;
}
