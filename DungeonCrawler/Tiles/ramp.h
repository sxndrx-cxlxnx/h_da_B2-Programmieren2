#ifndef RAMP_H
#define RAMP_H

#include "tile.h"

class Ramp : public Tile{
public:
    // construtor (inline)
    Ramp(const int pRow, const int pColumn):Tile(pRow, pColumn, ":/Textures/Texturen-Paket/ramp.png"){};

    // getter - methods
    virtual std::string getTexture() const override{ return texture; }; // inline - declaration

    // other methods
    virtual Tile *onEnter(Tile* fromTile, Character* who) override;
};

#endif // RAMP_H
