#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H

#include "../Ui/graphicalui.h"
#include "level.h"
#include "list.h"

class DungeonCrawler{
public:
    // constructor
    DungeonCrawler(GraphicalUI* pgui);

    // destructor
    virtual ~DungeonCrawler();

    // getter - methods
    GraphicalUI *getGraphicalui() const;
    Level *getLevel() const;

    // setter - methods
    void setLevel(Level* pLevel);

    // other methods
    void play();
    void store( Level* pLevel, std::string pPath );

    bool everythingIsReady = false;

private:
    // attributes
    GraphicalUI* graphicalui;
    Level* level;
    List* levelList;
};

#endif // DUNGEONCRAWLER_H
