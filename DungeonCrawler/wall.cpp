#include "wall.h"

// ************************ getter - methods ******************************************
std::string Wall::getTexture(){
    return texture;
}

// ************************ other methods *********************************************
Tile *Wall::onEnter(Tile *fromTile, Character *who){
    return nullptr;
}
