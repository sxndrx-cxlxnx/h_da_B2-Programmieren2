#ifndef DOOR_H
#define DOOR_H

#include "tile.h"
#include "passive.h"

class Door : public Tile, public Passive{
private:
    bool isOpen = false;
public:
    Door(const int pRow, const int pColumn):Tile(pRow, pColumn, "X"), Passive(){};

    // getter - methods
    virtual std::string getTexture() const override;

    // other methods
    virtual Tile* onEnter(Tile* from, Character* who) override;
    virtual void notify(Active* source) override;
};

#endif // DOOR_H
