#include "clause.h"
#include <cstdlib>
#include <ctime>
#include "solver.h"

void input(int& numVars, vector<Clause>& clauses) {
  int num, numClauses;

  scanf("%d %d", &numVars, &numClauses);

  for(int i = 0; i < numClauses; ++i) {
    Clause newClause;

    while(true) {
      scanf("%d", &num);
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
  printf("Time taken: %lf secs\n", elapsed_time);

  return 0;
}
