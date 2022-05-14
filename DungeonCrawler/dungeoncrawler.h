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

    // other methods
    void play();

private:
    // attributes
    AbstractUI* abstractui;
    Level* level;
};



#endif // DUNGEONCRAWLER_H
