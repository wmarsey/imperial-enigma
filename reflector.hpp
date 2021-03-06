#ifndef REFLECTOR_HPP
#define REFLECTOR_HPP

#include "transformer.hpp"

//reflector class, inherits most qualities from Transformer.
//the below functions override parent virtuals
class Reflector : public Transformer{
  //helper to check the pairing of configuration file
  int check_pairs(ifstream &the_file);

  //calls helper functions in order to interrogate file
  int file_check(ifstream &the_file);
};

#endif
