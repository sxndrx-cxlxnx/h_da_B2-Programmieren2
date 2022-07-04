#ifndef ATTACKCONTROLLER_H
#define ATTACKCONTROLLER_H

#include "controller.h"
#include "level.h"

class AttackController : public Controller{

private:
    Level* level;
    Character* character;

public:
    // constructor
    AttackController( Level* pLevel ): level( pLevel ){};

    // other methods
    virtual int move() override;
    void setCharacter(Character *newCharacter);
};

#endif // ATTACKCONTROLLER_H
