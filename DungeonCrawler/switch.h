#ifndef SWITCH_H
#define SWITCH_H
#include "tile.h"
#include "active.h"


class Switch : public Tile, public Active{
public:
    Switch(const int pRow, const int pColumn):Tile(pRow, pColumn, "?"), Active(){};

    virtual Tile* onEnter(Tile* from, Character* who) override;
    virtual void activate() override;
};

#endif // SWITCH_H
