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
  bool polarity[numVars + 1][2];
  memset(polarity, 0, sizeof(polarity));

  for(int i = 0; i < clauses.size(); ++i) {
    for(int j = 0; j < clauses[i].getSize(); ++j) {
      num = clauses[i].getAtom(j).getNum();
      varsInClauses[num].push_back(i);
      if(clauses[i].getAtom(j).isNeg()) polarity[num][0] = 1;
      else polarity[num][1] = 1;
    }
  }

  for(int i = 1; i <= numVars; ++i) {
    if(polarity[i][0] ^ polarity[i][1]) {
      assignments[i] = polarity[i][1];
    }
  }
}

bool Solver::backtrack(int ind) {
  int n = unassignedVars[ind], res;
  bool childRes;

  for(int i = 0; i < 2; ++i) {
    assignments[n] = i;
    res = clausesAreSatisfiable(n);
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
