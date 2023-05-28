#ifndef _CONTEOMEDIDAS
#define _CONTEOMEDIDAS

#include <iostream>

using namespace std;

class  conteomedidas{
public:
  friend ostream& operator<<(ostream& out, const conteomedidas &a );
