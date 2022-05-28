#include "floor.h"

// ************************ getter - methods ******************************************
std::string Floor::getTexture() const{
    return texture;
}

// ************************ other methods *********************************************
Tile *Floor::onEnter(Tile *fromTile, Character *who){
    return this;
}
