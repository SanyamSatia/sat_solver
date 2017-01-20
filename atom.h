#ifndef ATOM_H
#define ATOM_H

class Atom {
  int num;
  bool neg;

 public:

  Atom(int num_, bool neg_);
  int getNum();
  bool isNeg();
};

#endif
