#ifndef TERMINALUI_H
#define TERMINALUI_H

#include "abstractui.h"

class TerminalUI : public AbstractUI{

public:
    // constructor
    TerminalUI();

    // destructor
    ~TerminalUI(){};

    // other methods
    virtual void draw(Level* level) override;
};

#endif // TERMINALUI_H
