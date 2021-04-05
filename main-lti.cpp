#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "functions.h"
using namespace std;

int main()
{
  vector<double> b, a, sig, output, input; //vectors for lti and signals
  int M1 = 0, N = 0;
  string outFilename;
  char menuchoice = 'a';
  string addTest;
  double signalAdd;
  bool LTI_exist = false;

  while(menuchoice != '0')
  {
    cout << "_________________________________\n";
    cout<<"\nCURRENT LTI SYSTEM"<<endl;
    showsys(M1, N, b, a);
    cout << "_________________________________\n";
    cout<<endl;

    cout<<"1. Load File"<<endl;
    cout<<"2. Specify Log File"<<endl;
    cout<<"3. View Data"<<endl;
    cout<<"4. Specify next Input"<<endl;
    cout<<"5. Specify next Signal Input File"<<endl;
    cout<<"6. Clear Memory"<<endl;
    cout<<"0. Close Program"<<endl;

    cin >> menuchoice;
    cout << endl;

    switch(menuchoice){
      case '1':
        outFilename = "";
        while(!datain(M1, N, b, a)) {} //loops until valid file is provided
        LTI_exist = true;
        cout << "LTI System and output log file have been reset.\n";
        break;
      case '2':
        outFilename = makeOutputFile();
        break;
      case '3':
        showsys(M1, N, b, a);
        cout << endl;
        showdata(input, "Input");
        showdata(output, "Output");
        break;
      case '4':     
        if(LTI_exist == true)
        {
          do
          {
            cout << "Input next signal value (must be double): ";
            cin >> addTest;
          } while(!isDouble(addTest,signalAdd));

          input.push_back(signalAdd);
          output.push_back(LTI(M1, N, b, a, input, output));
          writeToFile(output, outFilename);
        }
        else
        {
          cout << "Error. Please input an LTI system file first." << endl;
        }
        break;
      case '5':
        if(LTI_exist == true)
        {
          sig.clear();
          while(!getsigfile(sig)) {}
          for(int i = 0; i < sig.size(); i++)
          {
            input.push_back(sig[i]);
            output.push_back(LTI(M1, N, b, a, input, output));
            writeToFile(output, outFilename);
          }
        }
        else
        {
          cout << "Error. Please input an LTI system file first." << endl;
        }
        break;
      case '6':
        cout << "Input and output vectors cleared.\n";
        cout << "Output log file closed.\n";
        input.clear();
        output.clear();
        outFilename = "";
        break;
      case '0':
        break;
    }
  }
}
