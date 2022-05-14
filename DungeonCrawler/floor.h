#ifndef FLOOR_H
#define FLOOR_H

#include "tile.h"

class Floor : public Tile{

public:
    // constructor
    Floor(const int pRow, const int pColumn):Tile(pRow,pColumn,"."){};

    // destructor (virtuell)
    virtual ~Floor(){};

    // getter - methods
    virtual std::string getTexture() override;

    // other methods
    virtual Tile* onEnter(Tile* fromTile, Character* who) override;

};

#endif // FLOOR_H
