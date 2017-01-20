#include <iostream>
#include <map>
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

bool Solver::assignUnitClauses() {
  int num;
  bool val;

  for(int i = 0; i < clauses.size(); ++i) {
    if(clauses[i].getSize() == 1) {
      num = clauses[i].getAtom(0).getNum();
      val = !clauses[i].getAtom(0).isNeg();

      if(assignments[num] != -1 && assignments[num] != val) return false;
      assignments[num] = val;
    }
  }

  return true;
}

void Solver::assignPureVars() {
  int num;
  map<int, bool> table;

  for(int i = 0; i < clauses.size(); ++i) {
    for(int j = 0; j < clauses[i].getSize(); ++j) {
      num = clauses[i].getAtom(j).getNum();
      if(clauses[i].getAtom(j).isNeg()) num = -num;
      table[num] = true;
    }
  }

  for(int i = 1; i <= numVars; ++i) {
    if(table[i] ^ table[-i]) {
      assignments[i] = table[i];
    }
  }
}

bool Solver::backtrack(int ind) {
  int n = unassignedVars[ind], res;
  bool childRes;

  for(int i = 0; i < 2; ++i) {
    assignments[n] = i;
    res = clausesAreSatisfiable();
    if(res == 1) return true;
    else if(res == 0) {
      childRes = backtrack(ind + 1);
      if(childRes) return true;
    }
  }

  // Reset and backtrack
  assignments[n] = -1;
  return false;
}

void Solver::solve() {
  bool sat = 1;
  assignments = new int[numVars + 1];
  memset(assignments, -1, sizeof(int) * (numVars + 1));

  sat = assignUnitClauses();
  assignPureVars();

  for(int i = 1; i <= numVars; ++i) {
    if(assignments[i] == -1) unassignedVars.push_back(i);
  }

  if(sat) {
    sat = backtrack(0);
  }

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
