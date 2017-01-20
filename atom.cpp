#include "atom.h"

Atom::Atom(int num_, bool neg_) {
  num = num_;
  neg = neg_;
}

int Atom::getNum() {
  return num;
}

bool Atom::isNeg() {
  return neg;
}
