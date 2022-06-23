#ifndef GUARDCONTROLLER_H
#define GUARDCONTROLLER_H

#include "controller.h"
#include <iostream>

class GuardController : public Controller{

private:
    std::string movePattern = "66444466";
    unsigned int whereInMovePattern = 0;


public:
    GuardController(std::string pMovePattern);

    void setWhereInMovePattern(int number);

    virtual int move() override;
    unsigned int getWhereInMovePattern() const;
};

#endif // GUARDCONTROLLER_H
