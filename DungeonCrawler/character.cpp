#include "character.h"

// ************************ setter - methods *****************************************
void Character::setTile(Tile *newTile){
    tile = newTile;
}

// ************************ getter - methods *****************************************
std::string &Character::getTexture(){

    switch(lastDirection){
    case 1:     texture = ":/Character/Texturen-Paket/char/char_left_1.png";
        break;
    case 2:     texture = ":/Character/Texturen-Paket/char/char_front_1.png";
        break;
    case 3:     texture = ":/Character/Texturen-Paket/char/char_right_1.png";
        break;
    case 4:     texture = ":/Character/Texturen-Paket/char/char_left_1.png";
        break;
    case 5:     texture = ":/Character/Texturen-Paket/char/char_front_1.png";
        break;
    case 6:     texture = ":/Character/Texturen-Paket/char/char_right_1.png";
        break;
    case 7:     texture = ":/Character/Texturen-Paket/char/char_left_1.png";
        break;
    case 8:     texture = ":/Character/Texturen-Paket/char/char_back_1.png";
        break;
    case 9:     texture = ":/Character/Texturen-Paket/char/char_right_1.png";
        break;
    default:    texture = ":/Character/Texturen-Paket/char/char_right_1.png";
        break;
    }

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
