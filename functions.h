#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "functions.cpp"

using namespace std;

bool isDouble(string s, double& value);

bool isInt(string s, int& value);

bool datain(int &M, int &n, vector<double> &b, vector<double> &a);

bool showsys(int &M, int &n, vector<double> &b, vector<double> &a);

bool getsigfile(vector<double> &sig, int &sigindex);

bool menu(int &M, int &n, vector<double> &b, vector<double> &a, vector<double> &sig, int &sigindex);




#endif