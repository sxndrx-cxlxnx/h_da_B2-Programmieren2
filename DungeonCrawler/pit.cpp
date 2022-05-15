#include "pit.h"
#include "ramp.h"
#include <typeinfo>


Tile *Pit::onEnter(Tile *fromTile, Character *who){
    return this;
}

Tile *Pit::onLeave(Tile *destTile, Character *who){
    bool destTileIsPit = (typeid(*destTile) == typeid(Pit));
    bool destTileIsRamp = (typeid(*destTile) == typeid(Ramp));

    if(destTileIsPit || destTileIsRamp){
        return this;
    } else{
        return nullptr;
    }
}
