#include "door.h"

// ************************ getter - methods *****************************************
bool Door::getIsOpen() const
{
    return isOpen;
}

std::string Door::getTexture() const{
    if(isOpen){
        return ":/Textures/Texturen-Paket/door2.png";
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
