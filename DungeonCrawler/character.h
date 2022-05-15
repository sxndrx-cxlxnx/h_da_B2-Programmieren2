#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>

class Tile;


class Character{

public:
    // constructor
    Character(Tile* pTile) : tile(pTile), texture("O"){};

    // setter - methods
    void setTile(Tile *newTile);

    // getter - methods
    const std::string &getTexture() const;
    Tile *getTile() const;

    // other methods
    char getch(void);
    int move();

private:
    // attributes
    Tile* tile;
    std::string texture;

};

#endif // CHARACTER_H
