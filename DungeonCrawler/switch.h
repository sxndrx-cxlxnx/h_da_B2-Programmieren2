#ifndef SWITCH_H
#define SWITCH_H
#include "tile.h"
#include "door.h"
#include "active.h"
#include <vector>

class Switch : public Tile, public Active{
public:
    // constructor (inline)
    Switch(const int pRow, const int pColumn):Tile(pRow, pColumn, "?"){};

    // getter - methods
    virtual std::string getTexture() const override;

    // other methods
    virtual Tile* onEnter(Tile* from, Character* who) override;
    virtual void activate() override;
};

#endif // SWITCH_H
