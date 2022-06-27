#ifndef GUARDCONTROLLER_H
#define GUARDCONTROLLER_H

#include "controller.h"
#include <iostream>

class GuardController : public Controller{

private:
    // attributes
    std::string movePattern = "66444466";
    unsigned int whereInMovePattern = 0;

public:
    // constructor
    GuardController(std::string pMovePattern);

    // setter - methods
    void setWhereInMovePattern(int number);

    // other methods
    virtual int move() override;
    unsigned int getWhereInMovePattern() const;
};

#endif // GUARDCONTROLLER_H
