#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H


#include "terminalui.h"

#include "level.h"

class DungeonCrawler{
public:
    // constructor
    DungeonCrawler();

    // destructor
    virtual ~DungeonCrawler();

    // getter - methods
    TerminalUI *getAbstractui() const;

    // other methods
    void play();

private:
    // attributes
    TerminalUI* abstractui;
    Level* level;
};



#endif // DUNGEONCRAWLER_H
