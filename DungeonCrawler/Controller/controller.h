#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>

class Controller{
public:
    // constructor
    Controller();

    // destructor
    virtual ~Controller(){};

    // other methods
    virtual int move() = 0;
    virtual std::string getControllerName(){ return ""; };
    virtual std::string getMovePattern(){ return ""; };
    virtual unsigned int getWhereInMovePattern(){ return 0; };
}                                                                                                                                          ;

#endif // CONTROLLER_H
