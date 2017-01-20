#include "clause.h"
#include <cmath>
#include <ctime>
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
  double elapsed_time;
  vector<Clause> clauses;

  input(numVars, clauses);
  Solver s(numVars, clauses);

  clock_t begin = clock();
  s.solve();
  clock_t end = clock();

  elapsed_time = double(end - begin) / CLOCKS_PER_SEC;
  cout<<"Time taken: "<<elapsed_time<<" secs\n";

  return 0;
}
