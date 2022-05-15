#ifndef TERMINALUI_H
#define TERMINALUI_H

#include "abstractui.h"
#include "controller.h"

class TerminalUI : virtual public AbstractUI, virtual public Controller{

public:
    // constructor
    TerminalUI();

    // destructor
    ~TerminalUI(){};

    // other methods
    virtual void draw(Level* level) override;
    virtual int move() override;
};

#endif // TERMINALUI_H
