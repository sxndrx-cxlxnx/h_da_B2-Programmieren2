#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H

#include "graphicalui.h"
#include "level.h"
#include "list.h"

class DungeonCrawler{
public:
    // constructor
    DungeonCrawler(GraphicalUI* pgui);

    // destructor
    virtual ~DungeonCrawler();

    // getter - methods
    GraphicalUI *getAbstractui() const;
    Level *getLevel() const;

    // setter - methods
    void setLevel(Level* pLevel);

    // other methods
    void play();

private:
    // attributes
    GraphicalUI* abstractui;
    Level* level;
    List* levelList;
};

#endif // DUNGEONCRAWLER_H
