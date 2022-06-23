#ifndef LOOTCHEST_H
#define LOOTCHEST_H

#include "tile.h"

class LootChest : public Tile{
public:
    // construtor (inline)
    LootChest(const int pRow, const int pColumn): Tile(pRow, pColumn, ":/Textures/Texturen-Paket/chest.png"){}

    // destructor (inline)
    virtual ~LootChest(){}

    // getter - methods
    virtual std::string getTexture() const override;// inline - declaration

    // other methods
    virtual Tile *onEnter(Tile* fromTile, Character* who) override;
};

#endif // LOOTCHEST_H
