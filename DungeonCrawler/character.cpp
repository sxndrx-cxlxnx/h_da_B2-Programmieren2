#include "character.h"
// #include <conio.h>                       // just in Windows
#include <unistd.h>
#include <termios.h>

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

int Character::move(){

    return controller->move();
}






