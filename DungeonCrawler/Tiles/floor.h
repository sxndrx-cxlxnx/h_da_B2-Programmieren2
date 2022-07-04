#ifndef FLOOR_H
#define FLOOR_H

#include "tile.h"

class Floor : public Tile{
public:
    // constructor (inline)
    Floor(const int pRow, const int pColumn, std::string pTexture):Tile(pRow,pColumn,pTexture){};

    // destructor (inline)
    virtual ~Floor(){};

    // getter - methods
    virtual std::string getTexture() const override;

    // other methods
    virtual Tile* onEnter(Tile* fromTile, Character* who) override;
};

#endif // FLOOR_H
