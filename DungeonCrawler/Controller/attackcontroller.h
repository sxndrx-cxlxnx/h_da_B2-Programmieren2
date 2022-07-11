#ifndef ATTACKCONTROLLER_H
#define ATTACKCONTROLLER_H

#include "controller.h"
#include "../Other/level.h"

class AttackController : public Controller{

private:
    // attributes
    Level* level;
    Character* character;

public:
    // constructor
    AttackController( Level* pLevel ): level( pLevel ){};

    // setter - methods
    void setCharacter(Character *newCharacter);

    // other methods
    virtual int move() override;
    virtual std::string getControllerName() override { return "AttackController"; };
    virtual std::string getMovePattern() override { return "error";};
    virtual unsigned int getWhereInMovePattern() override {return 10;};
};

#endif // ATTACKCONTROLLER_H
