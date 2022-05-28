#ifndef ABSTRACTUI_H
#define ABSTRACTUI_H

//#include "level.h"

class Level;

class AbstractUI{

public:
    // constructor
    AbstractUI();

    // destructor (inline)
    virtual ~AbstractUI(){};

    // other methods
    virtual void draw(Level*) = 0;
};

#endif // ABSTRACTUI_H
