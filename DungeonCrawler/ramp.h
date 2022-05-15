#ifndef RAMP_H
#define RAMP_H

#include "tile.h"

class Ramp : public Tile{
public:
    Ramp(const int pRow, const int pColumn):Tile(pRow, pColumn, "<"){};

    virtual Tile *onEnter(Tile* fromTile, Character* who) override;
    virtual std::string getTexture() const override{return texture;};
};

#endif // RAMP_H
