#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include "functions.h"
using namespace std;

int main()
{
  vector<double> b, a; //vectors containing signal values
  int M,n;
  double temp;
 
  while(!datain(M,n,b,a))
  {
    //loops until valid file is provided
  }

  cout<<"b"<<endl;
  for (int i=0;i<M+1;i++)
  {
    cout<<b[i]<<endl;
  }
  cout<<"a\n";
  for (int i=0;i<n;i++)
  {
    cout<<a[i]<<endl;
  }
}




  