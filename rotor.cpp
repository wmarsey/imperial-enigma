#include <iostream>
#include <fstream>
using namespace std;

#include "errors.h"
#include "constants.h"
#include "rotor.hpp"

//default constructor
Rotor :: Rotor(){
  //sets up default notch situation - all false
  for(int i = 0; i < ALPH_COUNT; ++i)
    notching[i] = false;
}

//calls appropriate file-checking helpers
int Rotor :: file_check(ifstream &the_file){
  int status = NO_ERROR;

  status = validate_numbers(the_file);
  if(status)
    return status;  
  the_file.seekg(0);
  
  if(!check_repeat(the_file)){
    cerr << "Error: invalid rotor mapping (cannot map a letter twice)." << endl;
    return INVALID_ROTOR_MAPPING;
  }
    
  the_file.seekg(0);
  return status;
}

//use appropriate files on argv top configure class properties 
int Rotor :: configure(char* rot_file, char* &pos_file, int nth_rotor){
  int counter = 0, a_notch = 0, status = NO_ERROR;
  ifstream config, position;
  config.open(rot_file);
  position.open(pos_file);

  //call file_check, check for errors  
  status = file_check(config);
  if(status){
    config.close();
    position.close();
    return status;
  }

  //check if file didn't open
  if(!position){
    cerr << "Error: could not open file." << endl;
    config.close();
    position.close();
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  
  //set up mapping array - index is the rotor-side closest to plugboard
  for(counter = 0; counter < ALPH_COUNT; ++counter)
    config >> mapping[counter];

  //sets appropriate notches to true
  for(counter = 0; !config.eof(); ++counter){
    config >> a_notch >> ws;
    notching[a_notch] = true;
  }

  //default case for the position file is argv[0], so this will only run
  //if a position file is actually present. default case all rotors have 0 rotation
  if(pos_file[0] != '.')
    for(counter = 0; counter <= nth_rotor-1 && !position.eof(); ++counter)
      position >> rotation >> ws;
  
  config.close();
  position.close();

  //if loop terminates early, there weren't enough rotors starting 
  if(counter != nth_rotor){
    cerr << "Error: Insufficient number of rotor starting positions specified." << endl;
    config.close();
    position.close();
    return NO_ROTOR_STARTING_POSITION;
  }

  config.close();
  position.close();
  return NO_ERROR;
}

//function that increments rotation, rotating neighbour if notch is hit
void Rotor :: rotate(){
  rotation = (rotation + 1) % 26;
  if(notch_hit())
    next->rotate();
}

//function that asks if the current rotation corresponds to a recorded notch
bool Rotor :: notch_hit(){
  if(notching[rotation])
    return true;
  return false;
}
