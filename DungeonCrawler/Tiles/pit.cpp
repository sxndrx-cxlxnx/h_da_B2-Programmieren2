#include "pit.h"
#include "ramp.h"
#include <typeinfo>

// ************************ other methods *********************************************
Tile *Pit::onEnter(Tile *fromTile, Character *who){
    return this;
}

Tile *Pit::onLeave(Tile *destTile, Character *who){
    bool destTileIsPit = (typeid(*destTile) == typeid(Pit));
    bool destTileIsRamp = (typeid(*destTile) == typeid(Ramp));

    if(destTileIsPit || destTileIsRamp){                            // you can leave a pit only to a pit or ramp
        return this;
    } else{
        return nullptr;
    }
}
