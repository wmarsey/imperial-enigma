#include"error.h"

Error Error::error_singleton;

Error::Error(){
  value = NO_ERROR;
}

int Error::get(){
  return value;
}

bool Error::set(int input){
  if(input < NO_ERROR || input > ERROR_OPENING_CONFIGURATION_FILE)
    return false;
  value = input;
  return true;
}
  
Error* singleton(){
  return &error_singleton;
}
  
