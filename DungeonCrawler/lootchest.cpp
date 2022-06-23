#include "lootchest.h"

// constructor
//LootChest::LootChest(const int pRow, const int pColumn) : Tile(pRow, pColumn, ":/Textures/Texturen-Paket/chest.png"){

//}

// ************************ getter - methods ******************************************
std::string LootChest::getTexture() const{
    return texture;
}

// ************************ other methods *********************************************
Tile *LootChest::onEnter(Tile *fromTile, Character *who){
    return this;
}
