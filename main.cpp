#include "clause.h"
#include <cmath>
#include <iostream>
#include "solver.h"

void input(int& numVars, vector<Clause>& clauses) {
  int num, numClauses;

  cin>>numVars>>numClauses;

  for(int i = 0; i < numClauses; ++i) {
    Clause newClause;

    while(true) {
      cin >> num;
      if(!num) break;

      newClause.addAtom(abs(num), num < 0);
    }

    clauses.push_back(newClause);
  }
}

int main() {
  int numVars;
  vector<Clause> clauses;

  input(numVars, clauses);

  Solver s(numVars, clauses);
  s.solve();

  return 0;
}
