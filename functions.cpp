#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "functions.h"
using namespace std;

bool isDouble(string s, double& value)
{
  double temp; //sets a temp variable
  
  //checks if the content is a valid double ignoring whitespaces
  bool check = (istringstream(s) >> temp >> ws).eof();

  if(check == 0)
  {
    return false;
    //returns 0 without updating value
  }

  else
  {
    value = temp;
    return true;
    //returns 1 and updating value
  }
}

bool isInt(string s, int& value)
{
  int temp; //sets a temp variable

  //checks if the content is a valid int ignoring whitespaces
  bool check = (istringstream(s) >> temp >> ws).eof();

  if(check == 0)
  {
    return false;
    //returns 0 without updating value
  }

  else
  {
    value = temp;
    return true;
    //returns 1 and updating value
  }
}

bool datain(int &M1, int &N, vector<double> &b, vector<double> &a)
{
  a.clear();
  b.clear();
  string fname;
  cout << "File Name for LTI system: ";
  //getline(cin,fname); //take user input filename
  cin >> fname;
  string ts; //string being read in file
  double tempv; //temp storage for valid doubles
  int tempi; //temp storage for valid start index

  fstream fin;
  fin.open(fname);
  if(!fin) //if file not found, throw error
  {
    cout<<"Error, file not detected. Try again.\n\n";
    return 0;
  }
  else //check if number of coefficients are specified
  {
    fin >> ts; //check first string in file (M+1)

    //if not int, invalid file
    if(!isInt(ts,tempi))
    {
      cout << "Error, not a valid LTI file.\n\n";
      return 0;
    }
    else //if first entry is int
    {
      M1 = tempi;
      getline(fin,ts); //skips rest of first line
    }

    fin >> ts; //check first string in second line (N)
    if(!isInt(ts,tempi))
    {
      cout << "Error, not a valid LTI file.\n\n";
      return 0;
    }
    else //if next entry is int
    {
      N = tempi;
    }
  }

  for(int i = 0; i < M1; i++) //reads until M+1 coefficients
  {
    fin >> ts; //reads the first string in a line
    //if double and not blank
    if((isDouble(ts,tempv)) && (ts != ""))
    {
      b.push_back(tempv); //add value to data vector
    }
    else
    {
      cout << "Error, not a valid LTI file.\n\n";
      return 0; //if not enough valid doubles, file is invalid
    }
    getline(fin,ts); //skips the rest of the line
  }

  for(int i = 0; i < N; i++) //reads until N coefficients
  {
    fin >> ts; //reads the first string in a line
    //if double and not blank
    if((isDouble(ts,tempv)) && (ts != ""))
    {
      a.push_back(tempv); //add value to data vector
    }
    else
    {
      cout << "Error, not a valid LTI file.\n\n";
      return 0; //if not enough valid doubles, file is invalid
    }
    getline(fin,ts); //skips the rest of the line
  }
  cout << "Valid LTI system file found.\n\n";
  return 1;
}

bool getsigfile(vector<double> &sig)
{
  string fname;
  cout << "Signal File Name: ";
  cin >> fname; //take user input filename
  string ts; //string being read in file
  double tempv; //temp storage for valid doubles
  int tempi; //temp storage for valid start index

  fstream fin;
  fin.open(fname);
  if(!fin) //if file not found/invalid, throw error
  {
    cout<<"Error, file not detected. Try again.\n\n";
    return 0;
  }
  else //check for possible index on first line
  {
    fin >> ts; //check first string in file

    //if not int, either no specified index or invalid file
    if(!isInt(ts,tempi))
    {
      cout << "Index not specified, checking if valid double.\n";
      
      //if first entry is not double, invalid file
      if(!isDouble(ts,tempv))
      {
        cout<<"Error, not a valid signal file.\n\n";
        return 0;
      }
      else //if double, set index to 0
      {
        cout<<"Valid signal file found.\n\n";

        //returns to start of file so it may read signal value
        fin.seekg(0, fin.beg);
      }
    }
    else //if first entry is int
    {
      getline(fin,ts); //read the rest of the first line
  
      stringstream ss(ts);
      string ts2;
      ss >> ts2; //read string after the first int

      //if followed by double, first int is index
      if((isDouble(ts2,tempv)) && (!ts2.empty()))
      {
        cout<<"Valid signal file found.\n\n";
        fin.seekg(0, fin.beg);
        fin >> ts; //go to second string
      }
      else //if no double after, first value is signal value
      {
        cout<<"Valid signal file found.\n\n";
        fin.seekg(0, fin.beg);
      }
    }

    while(!fin.eof()) //reads until end of file
    {
      fin >> ts; //reads the first string in a line

      //if double and not blank
      if((isDouble(ts,tempv)) && (ts != ""))
      {
        sig.push_back(tempv); //add value to data vector
      }
      else
      {
        break; //ends when start of line is not valid signal value
      }
      
      getline(fin,ts); //skips the rest of the line
    }
  }
  return 1;
}

double LTI(int &M1, int &N, vector<double> &b, vector<double> &a, vector<double> &input, vector<double> &output)
{
  double sumX = 0, sumY = 0, y_n = 0;
  int negativeTest;
  
  for(int i = 1; i <= N; i++)
  {
    negativeTest = output.size() - i;
    if(negativeTest > 0)
    {
      sumY = sumY + a[i-1] * output[negativeTest];
    }
  }

  for(int j = 0; j <= M1 - 1; j++)
  {
    negativeTest = output.size() - j;
    if(negativeTest > 0)
    {
      sumX = sumX + b[j] * input[negativeTest];
    }
  }
  y_n = 0 - sumY + sumX;
  return y_n;
}

string makeOutputFile()
{
  string ofn;
  cout << "Enter filename of output log file: ";
  cin >> ofn;
  return ofn;
}

void writeToFile(vector<double> &output, string ofn)
{
  ofstream outfile;
  outfile.open(ofn, std::ios::app);
  cout << "Output: " << output[output.size()-1] << endl;
  outfile << output[output.size()-1] << endl;
}

void showsys(int &M1, int &N, vector<double> &b, vector<double> &a)
{
  cout<<"Non-recursive coefficients: "<<M1<<endl;

  for(int i=0;i<M1;i++)
  {
    cout<<"b_"<<i<<" = "<<b[i]<<endl;
  }
  cout<<endl;
  cout<<"Recursive coefficients: "<<N<<endl;

  for(int i=0;i<N;i++)
  {
    cout<<"a_"<<i+1<<" = "<<a[i]<<endl;
  }
}

void showdata(vector<double> data, string ttype)
{
  cout << ttype << ": ";
  for(int i = 0; i < data.size(); i++)
  {
    if(i == data.size() - 1)
    {
      cout << data[i];
    }
    else
    {
      cout << data[i] << ", ";
    }
  }
  cout << endl;
}