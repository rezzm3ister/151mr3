#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include "functions.h"
using namespace std;

int main()
{
  vector<double> b, a, sig; //vectors containing signal values
  int M1,n, sigindex;
  double temp;
  b.clear();
  a.clear();
  M1=0;
  n=0;
 
  while(!menu(M1,n,b,a, sig, sigindex)){}
}




  