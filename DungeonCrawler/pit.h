#ifndef PIT_H
#define PIT_H

#include "tile.h"

class Pit : public Tile{
public:
    // constructor (inline)
    Pit(const int pRow, const int pColumn):Tile(pRow, pColumn, "_"){};

    // getter - methods
    virtual std::string getTexture() const override{ return texture; }; // inline - declaration

    // other methods
    virtual Tile *onEnter(Tile* fromTile, Character* who) override;
    virtual Tile* onLeave(Tile* destTile, Character* who) override;
};

#endif // PIT_H
