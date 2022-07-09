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
    void draw(Level* level) override;
    int move() override;
    std::string getMovePattern() override { return "error";};
    unsigned int getWhereInMovePattern() override {return 10;};
};

#endif // TERMINALUI_H
