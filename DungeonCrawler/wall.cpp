#include "wall.h"

// ************************ getter - methods ******************************************
std::string Wall::getTexture() const{
    return texture;
}

// ************************ other methods *********************************************
Tile *Wall::onEnter(Tile *fromTile, Character *who){
    return nullptr;
}
