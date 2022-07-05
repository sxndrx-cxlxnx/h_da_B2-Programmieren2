#include "tile.h"
#include "guardcontroller.h"
#include "lootchest.h"

// ************************ getter - methods ******************************************
int Tile::getRow() const{
    return row;
}

int Tile::getColumn() const{
    return column;
}

Character *Tile::getCharacter() const{
    return character;
}

std::string Tile::getTexture() const{
    return texture;
}

// ************************ setter - methods ******************************************
void Tile::setCharacter(Character *newCharacter){
    character = newCharacter;
}

// ************************ other methods *********************************************
bool Tile::hasCharacter(){
    if( this->character == nullptr || this->character->getHitpoints() <= 0 ){
        return false;
    } else{
        return true;
    }
}

void Tile::fightEvent(Character *attacker, Character *defender){     
    int damage = attacker->getStrength();
    defender->setHitpoints(defender->getHitpoints() - damage);

    if( defender->getHitpoints() > 0 ){
        damage = defender->getStrength();
        attacker->setHitpoints(attacker->getHitpoints() - damage);
    }
}

bool Tile::moveTo(Tile *destTile, Character *who){
    Tile* lastTile;
    lastTile = this->onLeave(destTile, who);                        // lastTile - where I come from

    if(destTile->hasCharacter()){
        if( destTile->character->getIsNPC() != who->getIsNPC() ){
            fightEvent( who, destTile->getCharacter() );
            if( destTile->character->getHitpoints() > 0 ){
                return false;
            }else{
                destTile->character = nullptr;
            }

            if( lastTile->character->getHitpoints() <= 0 ){         // if me is dead
                lastTile->character = nullptr;                      // i will be disarded
                return false;                                       // and can't move
            }

        } else{
            return false;
        }
    }

    bool destTileIsLootChest = (typeid(*destTile) == typeid(LootChest));
    if(destTileIsLootChest){
        who->setLootChestFound();
    }

    if(lastTile == nullptr){        // f.e. standing on a one-way road
        return false;
    }else{                                                          // destTile - where I wanted to go (original destination)
        Tile* nextTile;                                             // nextTile - where I'm arriving (actual destination)
        nextTile = destTile->onEnter(lastTile, who);
        if(nextTile == nullptr){    // run into a wall
            return false;
        } else{                     // actually move
            if(nextTile != destTile ){                              // if DestTile == Portal
                goAStepWithCharacter(lastTile, nextTile);           // -> set Character to Portal target (= NextTile)
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

void Tile::goAStepWithCharacter(Tile *from, Tile *to){              // "Tile *to" (destination) differs, when Tile is portal)

    to->setCharacter(from->character);                              // destination get the character
    from->character->setTile(to);                                   // character get the new Tile (destination)
    from->setCharacter(nullptr);                                    // old tile get to know, that character has moved on
}
