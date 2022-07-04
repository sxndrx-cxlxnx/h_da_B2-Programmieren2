#ifndef TERMINALUI_H
#define TERMINALUI_H

#include "abstractui.h"
#include "../Controller/controller.h"

class TerminalUI : virtual public AbstractUI, virtual public Controller{

public:
    // constructor
    TerminalUI();

    // destructor (inline)
    ~TerminalUI(){};

    // other methods
    virtual void draw(Level* level) override;
    virtual int move() override;
};

#endif // TERMINALUI_H
