#ifndef LEVEL_H
#define LEVEL_H

#include "tile.h"
#include "character.h"
#include <array>
#include <vector>

class Level{
private:
    // attributes
    int width = 10;
    int length = 10;
    std::vector< std::vector<Tile*> > dungeon;
    std::vector<Character*> characters;

public:
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

    // other methods
    void placeCharacter(Character *c, int row, int col);

};

#endif // LEVEL_H
