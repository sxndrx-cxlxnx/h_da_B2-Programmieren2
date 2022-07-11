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
    GuardController( std::string pMovePattern, unsigned int pWhereInMovePattern ): movePattern(pMovePattern), whereInMovePattern(pWhereInMovePattern){};

    // setter - methods
    void setWhereInMovePattern(int number);

    // getter - methods
    unsigned int getWhereInMovePattern() const;
    std::string getControllerName() override { return "GuardController"; };
    std::string getMovePattern() override { return movePattern; };
    unsigned int getWhereInMovePattern() override { return whereInMovePattern; };

    // other methods
    int move() override;
};

#endif // GUARDCONTROLLER_H
