#include "portal.h"

// ************************ getter - methods ******************************************
std::string Portal::getTexture(){
    return texture;
}

Tile *Portal::getDestination() const{
    return destination;
}

// ************************ setter - methods ******************************************
void Portal::setDestination(Tile *newDestination){
    destination = newDestination;
}


// ************************ other methods *********************************************
Tile *Portal::onEnter(Tile *fromTile, Character *who){
    return this->getDestination();
}

