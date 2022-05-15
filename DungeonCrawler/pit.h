#ifndef PIT_H
#define PIT_H

#include "tile.h"

class Pit : public Tile{
public:
    Pit(const int pRow, const int pColumn):Tile(pRow, pColumn, "_"){};

    virtual Tile *onEnter(Tile* fromTile, Character* who) override;
    virtual Tile* onLeave(Tile* destTile, Character* who) override;
    virtual std::string getTexture() const override{return texture;};
};

#endif // PIT_H
