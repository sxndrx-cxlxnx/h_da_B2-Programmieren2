#include "tile.h"
#include "../Controller/guardcontroller.h"
#include "../Other/level.h"
#include "../Tiles/lootchest.h"
#include "../Tiles/pit.h"
#include "../Tiles/portal.h"
#include "../Tiles/ramp.h"
#include "../Tiles/wall.h"

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

std::vector<Tile *> &Tile::getNeighborhood(){
    return neighborhood;
}
// ************************ setter - methods ******************************************
void Tile::setCharacter(Character *newCharacter){
    character = newCharacter;
}

void Tile::setNeighborhood(Level* pLevel){
    int thisRow = this->getRow();
    int thisCol = this->getColumn();
    bool thisTileIsPit = (typeid(*this) == typeid(Pit));
    bool thisTileIsWall = (typeid(*this) == typeid(Wall));

    Tile* newTile = nullptr;

    if( !thisTileIsWall ){
        for(int c = -1; c <= 1; c++){
            for(int r = -1; r <= 1; r++){
                newTile = pLevel->getDungeon()[thisRow + r][thisCol + c];
                bool nextTileIsPit = (typeid(*newTile) == typeid(Pit));
                bool nextTileIsPortal = (typeid(*newTile) == typeid(Portal));
                bool nextTileIsRamp = (typeid(*newTile) == typeid(Ramp));
                bool nextTileIsWall = (typeid(*newTile) == typeid(Wall));

                if(  c == 0 && r == 0 ){
                    // this Tile != neighbor of this Tile
                    // -> don't push_back
                } else if( thisTileIsPit && !( nextTileIsRamp || nextTileIsPit ) ){
                    // don't push_back
                } else if(nextTileIsWall){
                    // do not push_back
                } else if(nextTileIsPortal){
                    int portalPlace = -404;
                    for(size_t i = 0; i < pLevel->getPortals().size(); i++){
                        if(newTile == pLevel->getPortals()[i]){
                            portalPlace = i;
                            break;
                        }
                    }
                    if(portalPlace != -404){                    // set Portal-Destination as neighbor of thisTile
                        neighborhood.push_back( pLevel->getPortals()[portalPlace]->getDestination() );
                    }
                } else{
                    neighborhood.push_back( newTile );
                }
            }
        }
    }
}

void Tile::setTexture( std::string pTexture ){
     texture = pTexture;
}

// ************************ other methods *********************************************
bool Tile::hasCharacter(){
    if(this->character == nullptr || this->character->getHitpoints() <= 0 ){
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

            if( destTile->character->getHitpoints() > 0 ){         // if enemy live, you can't move
                return false;
            } else{                                                // else -> he will be discarded
                destTile->character = nullptr;
            }
            if( lastTile->character->getHitpoints() <= 0 ){        // if me is dead
                lastTile->character = nullptr;                     // i will be disarded
                return false;                                      // and can't move
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
    } else{                                                         // destTile - where I wanted to go (original destination)
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
