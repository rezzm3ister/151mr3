#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>
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

bool datain(int &M1, int &n, vector<double> &b, vector<double> &a)
{
  string fname;
  cout << "File Name for LTI system: ";
  //getline(cin,fname); //take user input filename
  cin>>fname;
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
  else
  {
    fin >> ts;
    if(!isInt(ts,tempi))
    {
      cout<<"invalid file."<<endl;
      return 0;
    }
    else
    {
      M1=tempi;
      fin >> ts;
      if (!isInt(ts,tempi))
      {
        cout<<"invalid file."<<endl;
        return 0;
      }
      else
      {
        n=tempi;
      }
    }
    for (int i=0;i<M1;i++){
      fin >> ts; //reads the first string in a line

      //if double and not blank
      if((isDouble(ts,tempv)) && (ts != ""))
      {
        b.push_back(tempv); //add value to data vector
      }
      else
      {
        break; //ends when start of line is not valid signal value
      }
      
      getline(fin,ts); //skips the rest of the line
    }
    for (int i=0;i<n;i++){
      fin >> ts; //reads the first string in a line

      //if double and not blank
      if((isDouble(ts,tempv)) && (ts != ""))
      {
        a.push_back(tempv); //add value to data vector
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

bool showsys(int &M1, int &n, vector<double> &b, vector<double> &a)
{
  cout<<"M + 1 = "<<M1<<endl;

  for(int i=0;i<M1;i++)
  {
    cout<<"b["<<i<<"] = "<<b[i]<<endl;
  }
  cout<<endl;
  cout<<"n = "<<n<<endl;

  for(int i=0;i<n;i++)
  {
    cout<<"b["<<i+1<<"] = "<<a[i]<<endl;
  }
}

bool getsigfile(vector<double> &sig, int &sigindex)
{
  string fname;
  cout << "Signal File Name: ";
  getline(cin,fname); //take user input filename
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
        cout<<"Valid signal file with start index 0 found.\n\n";
        sigindex = 0;

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
        sigindex = tempi;
        fin.seekg(0, fin.beg);
        fin >> ts; //go to second string
      }
      else //if no double after, first value is signal value
      {
        cout<<"Valid signal file with start index 0 found.\n\n";
        fin.seekg(0, fin.beg);
        sigindex = 0;
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

bool menu(int &M1, int &n, vector<double> &b, vector<double> &a, vector<double> &sig, int &sigindex)
{
  char menuchoice;
  cout<<"Current System: "<<endl;
  showsys(M1,n,b,a);
  cout<<endl<<endl;

  cout<<"1. Load File"<<endl;
  cout<<"2. Specify Log File"<<endl;
  cout<<"3: View LTI System"<<endl;
  cout<<"4. Specify next Input"<<endl;
  cout<<"5. Specify next Signal Input File"<<endl;
  cout<<"6. Clear Memory"<<endl;
  cout<<"0. Close Program"<<endl;

  cin>>menuchoice;

  switch(menuchoice){
    case '1':
      //texy
      while(!datain(M1,n,b,a))
      {//loops until valid file is provided
      }
      break;
    case '2':
      //texy
      break;
    case '3':
      //texy
      
      break;
    case '4':
      //texy
      break;
    case '5':
      while(!getsigfile(sig, sigindex))
      {}
      //texy
      break;
    case '6':
      //texy
      b.clear();
      a.clear();
      M1=0;
      n=0;
      break;
    case '0':
      //texy
      return 1;
      break;
    
  }
  return 0;
}

