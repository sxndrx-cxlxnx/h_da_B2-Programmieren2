#ifndef LEVEL_H
#define LEVEL_H

#include "tile.h"
#include "character.h"
#include "portal.h"
#include "switch.h"
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
    std::vector<Portal*> portals;
    std::vector<Switch*> switches;
    std::vector<Door*> doors;
    Levelchanger* levelchanger = nullptr;


public:
    // public attributes
    std::vector<QLabel*> labels;

    // assignment
    friend void swap(Level& lhs, Level& rhs);
    Level& operator=(Level rhs);

    // constructor
    Level(Controller *pTerminalUI, std::string levelString, bool isCharInLevel );

    // copy constructor
    Level(const Level &pLevel);

    // destructor
    virtual ~Level();

    // getter - methods
    int getWidth();
    int getLength();
    Tile *getTile(int row, int col);
    const Tile *getTile(int row, int col) const;
    std::vector<Character *> &getCharacters() ;
    const std::vector<Door *> &getDoors() const;
    Levelchanger *getLevelchanger() const;
    const std::vector<std::vector<Tile *> > &getDungeon() const;

    // setter - methods
    void setLevelchanger(Levelchanger *newLevelchanger);
    void setCharacters( Character* pCharacter );

    // other methods
    void placeCharacter(Character *c, int row, int col);
};

// friend method for assignement
void swap(Level& lhs, Level& rhs);

#endif // LEVEL_H
