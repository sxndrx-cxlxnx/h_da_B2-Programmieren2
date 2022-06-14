#ifndef LEVEL_H
#define LEVEL_H

#include "tile.h"
#include "character.h"
#include "portal.h"
#include "switch.h"
#include <array>
#include <vector>

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

public:
    // assignment
    friend void swap(Level& lhs, Level& rhs);
    Level& operator=(Level rhs);

    // constructor
    Level(Controller *pTerminalUI);
    Level(const Level &pLevel);

    // destructor
    virtual ~Level();

    // getter - methods
    int getWidth();
    int getLength();
    Tile *getTile(int row, int col);
    const Tile *getTile(int row, int col) const;
    const std::vector<Character *> &getCharacters() const;
    const std::vector<Door *> &getDoors() const;

    // other methods
    void placeCharacter(Character *c, int row, int col);
};

void swap(Level& lhs, Level& rhs);

#endif // LEVEL_H
