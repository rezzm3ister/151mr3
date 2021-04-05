#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "functions.cpp"

using namespace std;

bool isDouble(string s, double& value);

bool isInt(string s, int& value);

bool datain(int &M, int &n, vector<double> &b, vector<double> &a);

bool getsigfile(vector<double> &sig);

double LTI(int &M1, int &N, vector<double> &b, vector<double> &a, vector<double> &input, vector<double> &output);

string makeOutputFile();

void writeToFile(vector<double> &output, string ofn);

void showsys(int &M, int &n, vector<double> &b, vector<double> &a);

void showdata(vector<double> data, string ttype);

#endif