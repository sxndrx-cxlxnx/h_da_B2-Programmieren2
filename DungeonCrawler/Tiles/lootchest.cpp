#include "lootchest.h"

// ************************ getter - methods ******************************************
std::string LootChest::getTexture() const{
    return texture;
}

// ************************ other methods *********************************************
Tile *LootChest::onEnter(Tile *fromTile, Character *who){
    return this;
}
