#include <iostream>
#include <fstream>
using namespace std;

#include "errors.h"
#include "plugboard.hpp"

//helper to check the pairing of configuration file
int Plugboard :: check_pairs(ifstream &the_file){
  int test_num = 0, paired_num = 0;
  for(int i = 0 ; !the_file.eof(); ++i){ 
    the_file >> test_num >> ws;
    // if finish on an uneven number, complain
    if(the_file.eof()){ 
      cerr << "Error: incorrect number of plugboard parameters (uneven amount)." << endl;
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }
    the_file >> paired_num >> ws;
    //if trying to map to itself, complain
    if(test_num == paired_num){ 
      cerr << "Error: impossible plugboard configuration (cannot map a letter to itself)." << endl;
      return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    }
  }

  the_file.clear();
  the_file.seekg(0);
  return NO_ERROR;
}

//calls helper functions in order to interrogate file
int Plugboard :: file_check(ifstream &the_file){
  int status = NO_ERROR;
  if(is_empty(the_file))
    return status;

  status = validate_numbers(the_file);
  if(status)
    return status;

  status = check_pairs(the_file);
  if(status)
    return status;

  if(!check_repeat(the_file)){
    cerr << "Error: Impossible plugboard configuration (cannot plug a letter twice)." << endl;
    return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
  }
  
  the_file.seekg(0);
  return status;
}
