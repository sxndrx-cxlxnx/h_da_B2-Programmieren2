#include "switch.h"


// ************************ getter - methods ******************************************
std::string Switch::getTexture() const{
    return texture;
}

// ************************ other methods *********************************************
Tile *Switch::onEnter(Tile *from, Character *who){
    activate();
    return this;
}

void Switch::activate(){
    for(int i = 0; i < static_cast<int>( observers.size() ); i++){
        observers[i]->notify(this);
    }
}
