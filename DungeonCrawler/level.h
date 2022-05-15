#ifndef LEVEL_H
#define LEVEL_H

#include "tile.h"
#include "character.h"

#include <array>
#include <vector>

class Level{


private:
    // attributes
    static const int width{7};      // hardcoded changeable (level generates automatically)
    static const int length{7};     // min. width = 5 & length = 6
    std::array<std::array<Tile*, width>, length> dungeon;
    std::vector<Character*> characters;

public:
    // constructor
    Level();

    // destructor
    virtual ~Level();

    // getter - methods
    static int getWidth();
    static int getLength();
    Tile *getTile(int row, int col);
    const Tile *getTile(int row, int col) const;
    const std::vector<Character *> &getCharacters() const;

    // other methods
    void placeCharacter(Character *c, int row, int col);

};



#endif // LEVEL_H








