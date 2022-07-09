#ifndef LEVEL_H
#define LEVEL_H

#include "character.h"
#include "../Tiles/portal.h"
#include "../Tiles/switch.h"
#include "../Tiles/tile.h"
#include <array>
#include <vector>
#include <QLabel>

class Levelchanger;

class Level{
private:
    // attributes
    int width = 16;
    int length = 8;
    std::string floorType();
    std::vector< std::vector<Tile*> > dungeon;
    std::vector<Character*> characters;
    std::vector<Portal*> portalsVec;
    std::vector<Switch*> switches;
    std::vector<Door*> doors;
    Levelchanger* levelchanger = nullptr;
    std::vector< Tile* > allNodes;

    std::string levelString;


public:

    int levelID = 0;

    // public attributes
    std::vector<QLabel*> labels;

    // assignment
    friend void swap(Level& lhs, Level& rhs);
    Level& operator=(Level rhs);

    // constructor
    Level(Controller *pTerminalUI, std::string pPath, bool isCharInLevel, Character* player );

    // copy constructor
    Level(const Level &pLevel);

    // destructor
    virtual ~Level();

    // getter - methods
    int getWidth();
    int getLength();
    Tile *getTile(int row, int col);
    Levelchanger *getLevelchanger() const;
    const Tile *getTile(int row, int col) const;
    const std::vector<Door *> &getDoors() const;
    const std::vector<Portal *> &getPortals() const;
    const std::vector<std::vector<Tile *> > &getDungeon() const;
    std::vector<Character *> &getCharacters() ;
    std::vector<Tile*> getPath(Tile* from, Tile* to);

    // setter - methods
    void setLevelchanger(Levelchanger *newLevelchanger);
    void setCharacters( Character* pCharacter );

    // other methods
    void placeCharacter(Character *c, int row, int col);

    const std::string &getLevelString() const;
};

// friend method for assignement
void swap(Level& lhs, Level& rhs);

#endif // LEVEL_H
