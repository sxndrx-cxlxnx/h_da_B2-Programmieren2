#ifndef PORTAL_H
#define PORTAL_H

#include "tile.h"

class Portal : public Tile{

public:
    // constructor (inline)
    Portal(const int pRow, const int pColumn, std::string pTexture) :
        Tile(pRow, pColumn, pTexture){};

    // destructor (inline)
    virtual ~Portal(){};

    // getter - methods
    virtual std::string getTexture() const override;
    Tile *getDestination() const;

    // setter - methods
    void setDestination(Tile *newDestination);

    // other methods
    virtual Tile* onEnter(Tile* fromTile, Character* who) override;

private:
    // attributes
    Tile* destination;
};

#endif // PORTAL_H
