#include "solver.h"
#include <vector>

Solver::Solver(int numVars_, vector<Clause>& clauses_) {
  numVars = numVars_;
  clauses = clauses_;
  varsInClauses = new vector<int> [numVars + 1];
}

int Solver::clausesAreSatisfiable(int var) {
  int res, clauseNum;
  bool falsePossible = false;

  for(int i = 0; i < varsInClauses[var].size(); ++i) {
    clauseNum = varsInClauses[var][i];
    res = clauses[clauseNum].isSatisfiable(assignments);
    if(res == -1) return -1;
    else if(res == 0) falsePossible = true;
  }

  if(falsePossible) return 0;
  else return 1;
}

void Solver::storeVarsInClauses() {
  int var;

  for(int i = 0; i < clauses.size(); ++i) {
    for(int j = 0; j < clauses[i].getSize(); ++j) {
      var = clauses[i].getAtom(j).getNum();
      varsInClauses[var].push_back(i);
    }
  }
}

bool Solver::backtrack(int n) {
  int res;
  bool childRes;

  for(int i = 0; i < 2; ++i) {
    assignments[n] = i;
    res = clausesAreSatisfiable(n);
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

  storeVarsInClauses();

  sat = backtrack(1);

  if(sat) {
    printf("Satisfiable\n");
    for(int i = 1; i <= numVars; ++i) {
      printf("%d: ", i);
      if(assignments[i] == 1) {
        printf("T");
      }
      else if(assignments[i] == 0) {
        printf("F");
      }
      else {
        printf("T/F");
      }
      printf("\n");
    }
  }
  else {
    printf("Unsatisfiable\n");
  }

  delete[] assignments;
  delete[] varsInClauses;
}
