#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#include "errors.h"
#include "constants.h"
#include "transformer.hpp"

//default mapping of all objects - 0 to 0, 1 to 1, etc.
Transformer :: Transformer(){
  next = NULL;
  rotation = 0;
  for(int i = 0; i < ALPH_COUNT; ++i) mapping[i] = i;
}

//helper function, check a file for repeated numbers in the first ALPH_COUNT numbers
bool Transformer :: check_repeat(ifstream &the_file){
  int a_num = 0;
  vector<int>the_numbers;
  vector<int>::iterator it;
  
  for(int i = 0; !the_file.eof() && i < ALPH_COUNT-1; ++i){
    the_file >> a_num >> ws;
    it = find(the_numbers.begin(), the_numbers.end(), a_num);
    if(it != the_numbers.end())
      return false;
    else
      the_numbers.push_back(a_num);
  }
  
  the_file.clear();
  the_file.seekg(0);
  return true;
}

//helper function to check for non-digits and numbers with invalid index
int Transformer :: validate_numbers(ifstream &the_file){
  int test_num = 0;
  //loop through looking for bad index
  while((the_file >> test_num >> ws) && !the_file.eof()){ 
    if(test_num >= ALPH_COUNT){
      cerr << "Error: configuration file contains a number that is too large ";
      cerr << "to be mapped to the alphabet." << endl;
      return INVALID_INDEX;
    } else if (test_num < 0){
      cerr << "Error: configuration file contains a negative number." << endl;
      return INVALID_INDEX;
    }  
  }
  //if loop terminated early, problem is non-numerical
  if(!the_file.eof()){
    cerr << "Error: Non-numerical character found." << endl;
    return NON_NUMERIC_CHARACTER;
  }
  
  the_file.seekg(0);
  return NO_ERROR;
}

//the mapping algorithm for all transformers
int Transformer :: transform(int &input){
  //map the input offset by rotation, then remove offset on output.
  input = (mapping[(input+rotation)%ALPH_COUNT] - rotation + ALPH_COUNT) % ALPH_COUNT;
  if(next){
    //recursive call: ask next in chain to transform, map the return value 
    //base case is the reflector - it has a null next value
    input = (next->transform(input) + rotation) % ALPH_COUNT;
    //reverse mapping (finding by value rather than index)
    for(int i = 0; i < ALPH_COUNT; ++i)
      if(mapping[i] == input){
	input = (i - rotation + ALPH_COUNT) % ALPH_COUNT;
	break;
      }
  }
  return input;
}

//configuration is same for Reflector & Plugboard, different for rotor
int Transformer :: configure(char* &the_file){
  int index = 0, map_to = 0, status = NO_ERROR;
  ifstream config;

  config.open(the_file);
  
  status = file_check(config);
  if(status){
    config.close();
    return status;
  }
  
  while(!config.eof()){
    // grab two numbers
    config >> index;
    config >> map_to;
    // doubly map all numbers, so mapping is same back to forth  
    mapping[index] = map_to;
    mapping[map_to] = index;
  }
  config.close();

  return status;
}

//functions for sub-class file checking 
bool Transformer :: is_empty(ifstream &the_file){
  the_file >> ws;
  if(the_file.eof())
    return true;
  return false;
}
