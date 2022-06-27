#include "character.h"

// ************************ constructor **********************************************
Character::Character(Tile* pTile, Controller* pController, int pStrength, int pStamina, bool pIsNPC){
    tile = pTile;

    if(pIsNPC){
        texture = ":/Textures/Texturen-Paket/zombie_left.png";
    } else{
        texture = ":/Character/Texturen-Paket/char/char_front_2.png";
    }

    controller = pController;
    strength = pStrength;
    stamina = pStamina;
    hitpoints = getMaxHP();
    isNPC = pIsNPC;
}

// ************************ setter - methods *****************************************
void Character::setTile(Tile *newTile){
    tile = newTile;
}

void Character::setLastDirection(int newLastDirection){
    lastDirection = newLastDirection;
}

void Character::setHitpoints(int newHitpoints){
    hitpoints = newHitpoints;
}

void Character::setLootChestFound(){
    lootChestFound = true;
}

// ************************ getter - methods *****************************************
std::string &Character::getTexture(){

    if( isNPC ){

        switch(lastDirection){
        case 1:     texture = ":/Textures/Texturen-Paket/zombie_left.png";
            break;
        case 2:     texture = ":/Textures/Texturen-Paket/zombie_left.png";
            break;
        case 3:     texture = ":/Textures/Texturen-Paket/zombie_right.png";
            break;
        case 4:     texture = ":/Textures/Texturen-Paket/zombie_left.png";
            break;
        case 5:     texture = ":/Textures/Texturen-Paket/zombie_right.png";
            break;
        case 6:     texture = ":/Textures/Texturen-Paket/zombie_right.png";
            break;
        case 7:     texture = ":/Textures/Texturen-Paket/zombie_left.png";
            break;
        case 8:     texture = ":/Textures/Texturen-Paket/zombie_right.png";
            break;
        case 9:     texture = ":/Textures/Texturen-Paket/zombie_right.png";
            break;
        default:    texture = ":/Textures/Texturen-Paket/zombie_right.png";
            break;
        }

    } else{

        switch(lastDirection){
        case 1:     texture = ":/Character/Texturen-Paket/char/char_left_2.png";
            break;
        case 2:     texture = ":/Character/Texturen-Paket/char/char_front_2.png";
            break;
        case 3:     texture = ":/Character/Texturen-Paket/char/char_right_2.png";
            break;
        case 4:     texture = ":/Character/Texturen-Paket/char/char_left_2.png";
            break;
        case 5:     texture = ":/Character/Texturen-Paket/char/char_front_2.png";
            break;
        case 6:     texture = ":/Character/Texturen-Paket/char/char_right_2.png";
            break;
        case 7:     texture = ":/Character/Texturen-Paket/char/char_left_2.png";
            break;
        case 8:     texture = ":/Character/Texturen-Paket/char/char_back_2.png";
            break;
        case 9:     texture = ":/Character/Texturen-Paket/char/char_right_2.png";
            break;
        default:    texture = ":/Character/Texturen-Paket/char/char_right_2.png";
            break;
        }
    }
    return texture;
}

Tile *Character::getTile() const{
    return tile;
}

Controller *Character::getController() const{
    return controller;
}

int Character::getMaxHP(){
    int MaxHP = 20 + (stamina *5);
    return MaxHP;
}

int Character::getStrength(){
    return strength;
}

int Character::getStamina(){
    return stamina;
}

int Character::getHitpoints(){
    return hitpoints;
}

bool Character::getIsNPC(){
    return isNPC;
}

bool Character::getLootChestFound(){
    return lootChestFound;
}

// ************************ other methods ********************************************
int Character::move(){
    return controller->move();
}
