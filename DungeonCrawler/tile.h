#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "character.h"

class Tile{
    // abstract basisclass of Floor, Wall and Portal

protected:
    // attributes
    const int row;
    const int column;
    std::string texture;
    Character* character = nullptr;

public:
    // constructor
    Tile(const int pRow, const int pColumn, std::string pTexture):
        row(pRow), column(pColumn), texture(pTexture){};

    // destructor
    virtual ~Tile(){};

    // getter - methods
    int getRow() const;
    int getColumn() const;
    Character *getCharacter() const;
    virtual std::string getTexture() = 0;

    // setter - methods
    void setCharacter(Character *newCharacter);

    // other methods
    bool hasCharacter();
    bool moveTo(Tile* destTile, Character* who);                // move to
    virtual Tile* onEnter(Tile* fromTile, Character* who);      // on Enter
    Tile* onLeave(Tile* destTile, Character* who);              // on Leave
    void goAStepWithCharacter(Tile *from, Tile *to /* , Character *who */);

};

#endif // TILE_H
