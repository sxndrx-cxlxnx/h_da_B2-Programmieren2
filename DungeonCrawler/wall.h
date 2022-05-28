#ifndef WALL_H
#define WALL_H

#include "tile.h"

class Wall : public Tile{
public:
    // constructor (inline)
    Wall(const int pRow, const int pColumn):Tile(pRow, pColumn, "#"){};

    // destructor (inline)
    virtual ~Wall(){};

    // getter - methods
    virtual std::string getTexture() const override;

    // other methods
    virtual Tile* onEnter(Tile* fromTile, Character* who) override;
};

#endif // WALL_H
