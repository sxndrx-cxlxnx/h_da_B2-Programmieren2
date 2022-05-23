#include "door.h"

// ************************ getter - methods *****************************************
std::string Door::getTexture() const{
    if(isOpen){
        return "/";
    } else{
        return texture;
    }
}

// ************************ other methods *********************************************
Tile *Door::onEnter(Tile *from, Character *who){
    if(isOpen){
        return this;
    } else{
        return nullptr;
    }
}

void Door::notify(Active *source){
    isOpen = !isOpen;
}
