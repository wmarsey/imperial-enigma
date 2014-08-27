//Error class is a singleton
//I'm making this class a singleton so that I don't have to pass around an int
//between all my function for error reporting
#ifndef error_hpp
#define error_hpp

class Error{
  Error(){}
  static Error error_singleton;
  static int value;
public:
  int get();
  bool set(int input);
  static Error* singleton();
};

#endif
