#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

#include "errors.h"
#include "terminal.hpp"

Terminal :: Terminal(){
  the_reflector = NULL;
  the_plugboard = NULL;
  rot_num = 0;
}

//deletes heap memory allocated for each element
Terminal :: ~Terminal(){
  //delete each (if pointer not null)
  delete the_reflector;
  delete the_plugboard;
  for(unsigned int i = 0; i < the_rotors.size(); ++i)
    delete the_rotors[i];
}

//helper function to link components together
void Terminal :: link_components(){
  if(rot_num){
    the_plugboard->next = the_rotors[rot_num-1];
    for(int i = rot_num-1; i > 0; --i){
      the_rotors[i]->next = the_rotors[i-1];	
    }
    the_rotors[0]->next = the_reflector;
  } else 
    the_plugboard->next = the_reflector;
}

//helper function to toggle between ASCII codes and absolute alphabet index
int Terminal :: abs_trans(int input){
  if(input < 91 && input > ALPH_COUNT)
    return (input - 65);
  else
    return (input + 65);
}

//function to create and link together the associated parts of the machine terminal
int Terminal :: configure(int argc, char **argv){
  int status = NO_ERROR, pos_position = 0;
  if(argc > 3){
    rot_num = argc - 4;
    pos_position = argc-1;
  } 
  //else if(argc == 3)
  //rot_num = 0;
  
  //make plugboard, check memory went ok, configure, and check for errors
  the_plugboard = new Plugboard();
  status = the_plugboard->configure(argv[1]);
  if(status){
    cerr << "Error found in file \"" << argv[1] << "\"" << endl;
    return status;
  }
  
  //make plugboard, configure and check for errors
  the_reflector = new Reflector();
  status = the_reflector->configure(argv[2]);
  if(status){
    cerr << "Error found in file \"" << argv[2] << "\"" << endl;
    return status;
  }
  
  //if there is space in argv for a rotor, make a series of them
  if(rot_num)
    for(int i = 0; i < rot_num; ++i){
      Rotor* a_rotor;
      a_rotor = new Rotor();
      status = a_rotor->configure(argv[i+3],argv[pos_position],i+1);
      if(status){
	cerr << "Error found in file \"" << argv[i+3] << "\"" << endl;
	return status;
      }
      the_rotors.push_back(a_rotor);
    }

  link_components();
  return status;
}

//function to cypher the input
int Terminal :: cypher(char &input){
  char ch_input = input;
  int abs_val = 0;
  //error check the input
  if(input-65 > ALPH_COUNT - 1 || input < 0 || !isupper(ch_input)){
    cerr << "Error while processing input: invalid input character." << endl;
    return INVALID_INPUT_CHARACTER;
  }
  abs_val = abs_trans(input);
  //rotate the first rotor (rotate function automatically rotates next in line)
  if(rot_num){
    the_rotors[rot_num-1]->rotate();
  }
  abs_val = the_plugboard->transform(abs_val);
  input = abs_trans(abs_val);
  return NO_ERROR;
}
