#include "character.h"

// ************************ setter - methods *****************************************
void Character::setTile(Tile *newTile){
    tile = newTile;
}

// ************************ getter - methods *****************************************
const std::string &Character::getTexture() const{
    return texture;
}

Tile *Character::getTile() const{
    return tile;
}

// ************************ other methods ********************************************
int Character::move(){
    return controller->move();
}

void Character::setLastDirection(int newLastDirection){
    lastDirection = newLastDirection;
}

Controller *Character::getController() const{
    return controller;
}
