#include "tile.h"

// ************************ getter - methods ******************************************
int Tile::getRow() const
{
    return row;
}

int Tile::getColumn() const
{
    return column;
}

Character *Tile::getCharacter() const
{
    return character;
}

std::string Tile::getTexture(){
    return texture;
}

// ************************ setter - methods ******************************************

void Tile::setCharacter(Character *newCharacter){
    character = newCharacter;
}

// ************************ other methods *********************************************

bool Tile::hasCharacter(){
    if(this->character == nullptr){
        return false;
    }else{
        return true;
    }
}

bool Tile::moveTo(Tile *destTile, Character *who){
    Tile* lastTile;
    lastTile = this->onLeave(destTile, who);                        // lastTile - where I come from
    if(lastTile == nullptr){        // standing on a one-way road
        return false;
    }else{                                                          // destTile - where I wanted to go (original destination)
        Tile* nextTile;                                             // nextTile - where I'm arriving (actual destination)
        nextTile = destTile->onEnter(lastTile, who);
        if(nextTile == nullptr){    // run into a wall
            return false;
        }else{                      // actually move
            if(nextTile != destTile ){                              // if DestTile == Portal
                goAStepWithCharacter(lastTile, nextTile);           // -> set Character to Portal target (NextTile)
            } else{
                goAStepWithCharacter(lastTile, destTile);
            }
            return true;
        }
    }
}

Tile *Tile::onEnter(Tile *fromTile, Character *who){
    return nullptr;
}

Tile *Tile::onLeave(Tile *destTile, Character *who){
    return this;
}

void Tile::goAStepWithCharacter(Tile *from, Tile *to){
    to->setCharacter(from->character);
    from->character->setTile(to);
    from->setCharacter(nullptr);
}


