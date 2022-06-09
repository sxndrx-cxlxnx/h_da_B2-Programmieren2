#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H

//#include "terminalui.h"
#include "graphicalui.h"
#include "level.h"

class DungeonCrawler{
public:
    // constructor
    DungeonCrawler(GraphicalUI* pgui);

    // destructor
    virtual ~DungeonCrawler();

    // getter - methods
    GraphicalUI *getAbstractui() const;

    // other methods
    void play();

    Level *getLevel() const;

private:
    // attributes
    GraphicalUI* abstractui;
    Level* level;
};

#endif // DUNGEONCRAWLER_H
