#ifndef ROTOR_HPP
#define ROTOR_HPP

#include "constants.h"
#include "transformer.hpp"

class Rotor: public Transformer{
  //calls appropriate file-checking helpers
  int file_check(ifstream &the_file);

  //function that asks if the current rotation corresponds to a recorded notch
  bool notch_hit();

  bool notching[ALPH_COUNT];
public:
  //use appropriate files on argv top configure class properties 
  int configure(char* rot_file, char* &pos_file, int rotor_number);

  //function that increments rotation, rotating neighbour if notch is hit
  void rotate();

  //default constructor: initialises notching array
  Rotor();
};

#endif
