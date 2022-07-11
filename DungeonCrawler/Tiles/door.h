#ifndef DOOR_H
#define DOOR_H

#include "tile.h"
#include "passive.h"

class Door : public Tile, public Passive{
private:
    // attributes
    bool isOpen = false;

public:
    // constructor (inline)
    Door(const int pRow, const int pColumn):Tile(pRow, pColumn, ":/Textures/Texturen-Paket/door1.png"), Passive(){};

    // getter - methods
    bool getIsOpen() const;
    virtual std::string getTexture() const override;

    // setter - methods
    void setIsOpen(bool newIsOpen);

    // other methods
    virtual Tile* onEnter(Tile* from, Character* who) override;
    virtual void notify(Active* source) override;

};

#endif // DOOR_H
