#include "levelchanger.h"
#include "../Other/dungeoncrawler.h"

// ************************ getter - methods ******************************************
std::string Levelchanger::getTexture() const{
    return texture;
}

Level *Levelchanger::getLevel() const{
    return level;
}

Tile *Levelchanger::getDestiny() const{
    return destiny;
}
// ************************ setter - methods ******************************************
void Levelchanger::setDestiny(Tile *newDestiny){
    destiny = newDestiny;
}

void Levelchanger::setLevel(Level *newLevel){
    level = newLevel;
}

void Levelchanger::setDungeonCrawler(DungeonCrawler *newDungeonCrawler){
    dungeonCrawler = newDungeonCrawler;
}

// ************************ other methods *********************************************
Tile *Levelchanger::onEnter(Tile *fromTile, Character *who){
    dungeonCrawler->setLevel( level );
    return destiny;
}
