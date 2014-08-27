#ifndef TRANSFORMER_HPP
#define TRANSFORMER_HPP

#include "constants.h"

//Parent class of Plugboard, Reflector & Rotors
class Transformer{
protected:
  //mapping and rotation common to all Tranformers. (see Transformer->transform)
  int mapping[ALPH_COUNT], rotation;
  
  //functions for sub-class file checking 
  bool is_empty(ifstream &the_file);

  //helper function, check a file for repeated numbers in the first ALPH_COUNT numbers
  bool check_repeat(ifstream &the_file);
  
  //helper function to check for non-digits and numbers with invalid index
  int validate_numbers(ifstream &the_file);

  //pure function, overridden by all children
  virtual int file_check(ifstream &the_file) = 0;

  //virtual function overridden in plugboard & reflector
  virtual int check_pairs(ifstream &the_file){return 0;};

public:
  //pointer to the next Transformer in the queue (pointing away from plugboard) 
  Transformer* next;

  //default mapping of all objects - 0 to 0, 1 to 1, etc.
  Transformer();

  //the mapping algorithm for all transformers
  int transform(int &input);
  
  //configuration is same for Reflector & Plugboard, different for rotor
  virtual int configure(char* &the_file);

  //rotation is called on all objects (see Terminal->cypher), but only performs a task in rotors
  virtual void rotate(){};

  //virtual Transformer for 
  virtual ~Transformer(){};
};

#endif
