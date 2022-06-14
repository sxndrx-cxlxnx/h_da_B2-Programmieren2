#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H

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
    Level *getLevel() const;

    // other methods
    void play();

private:
    // attributes
    GraphicalUI* abstractui;
    Level* level;
};

#endif // DUNGEONCRAWLER_H
