#include <iostream>
#include <fstream>
using namespace std;

#include "errors.h"
#include "reflector.hpp"

//helper to check the pairing of configuration file
int Reflector :: check_pairs(ifstream &the_file){
  int counter = 0, test_num = 0, paired_num = 0;
  for( ; !the_file.eof(); ++counter){ //grab two numbers at a time
    the_file >> test_num >> ws;
    // if finish on an uneven number, complain
    if(the_file.eof()){
      cerr << "Error: incorrect number of reflector parameters (uneven amount)." << endl;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }
    the_file >> paired_num >> ws;
    // if trying to map to itself, complain
    if(test_num == paired_num){
      cerr << "Error: impossible reflector mapping (cannot map a letter to itself)." << endl;
      return INVALID_REFLECTOR_MAPPING;
    }
  }   

  the_file.seekg(0);
  
  //check for repeats BEFORE checking for too few pairs
  if(!check_repeat(the_file)){
    cerr << "Error: invalid reflector mapping (cannot map a letter twice, or to itself)." << endl;
    return INVALID_REFLECTOR_MAPPING;
  }
  
  // test to see if loop counter shows wrong number of parameters
  if(counter > ALPH_COUNT/2){ 
    cerr << "Error: invalid number of reflector parameters (too many)." << endl;
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  } else if (counter < ALPH_COUNT/2){
    cerr << "Error: invalid number of reflector parameters (too few)." << endl;
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;	
  }

  the_file.seekg(0);
  return NO_ERROR;
}

//calls helper functions in order to interrogate file
int Reflector :: file_check(ifstream &the_file){
  int status = NO_ERROR;

  if(is_empty(the_file)){
    cerr << "Error: invalid number of reflector parameters (file is empty)." << endl;
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }

  status = validate_numbers(the_file);
  if(status)
    return status;
 
  status = check_pairs(the_file);
  if(status)
    return status;

  the_file.seekg(0);
  return status;
}
