#include <iostream>
// the 'unistd' header allows me to detect if cin / cout is redirected 
// from the terminal. So I can have a lovely snazzy screen output. 
// (It only works on POSIX systems and I really hope it doesn't break 
// the testing mechanism - it works fine on the lab machines!)
#include <unistd.h>
using namespace std;

#include "errors.h"
#include "constants.h"
#include "terminal.hpp"

//function for printing errors - use other definition to specify problem file
int main(int argc, char **argv){
  int status = NO_ERROR; 
  char input = 0;
  Terminal enigma_terminal;

  if(argc < 3){
    cerr << "Error: insufficient number of parameters." << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  status = enigma_terminal.configure(argc,argv);
  
  if(status){
    return status;
  }

  //prompt ONLY if both cin is from keyboard AND cout is to the SCREEN.
  if(isatty(STDIN_FILENO) && isatty(STDOUT_FILENO)){
    cout << endl;
    cout << "Welcome to the Enigma machine." << endl;
    cout << "Enter your letters one-by-one below, followed by the return key. " << endl;
    cout << "They must be UPPER-CASE characters, A - Z." << endl;
    cout << "End input by typing ctrl + D. Happy encrypting!" << endl << endl; 
   }
  
  while(cin >> input){
    status = enigma_terminal.cypher(input);
    if(status){
      return status;
    } else{
      //use isatty to make snazzy output
      if(isatty(STDIN_FILENO) && isatty(STDOUT_FILENO)){
	cout << "-> ";
      }

      //print output
      cout << input;

      //use isatty to make snazzy output      
      if(isatty(STDIN_FILENO) && isatty(STDOUT_FILENO)){
	cout << " <-" << endl;
      }
    }
  }
  
  //clear the line ONLY if output is to a terminal screen
  if(isatty(STDOUT_FILENO)){
    cout << endl;
  }

  return status;
}
