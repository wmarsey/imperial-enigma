#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <vector>

#include "transformer.hpp"
#include "rotor.hpp"
#include "reflector.hpp"
#include "plugboard.hpp"

//terminal class: instantiates as a full input-output abstraction of an enigma machine
class Terminal{
  //pointers to component parts
  vector<Rotor*> the_rotors;
  Reflector* the_reflector;
  Plugboard* the_plugboard;
  //for later checking
  int rot_num;
  
  //helper function to link components together
  void link_components();

  //helper function to toggle between ASCII codes and absolute alphabet index
  int abs_trans(int input);
public:
  //initialises pointers to NULL
  Terminal();

  //deletes heap memory allocated for each element
  ~Terminal();
  
  //function to cypher the input
  int cypher(char &input);

  //function to create and link together the associated parts of this machine terminal
  int configure(int argc, char **argv);
};

#endif
