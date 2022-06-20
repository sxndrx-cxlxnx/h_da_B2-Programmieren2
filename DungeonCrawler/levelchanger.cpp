#include "levelchanger.h"
#include "dungeoncrawler.h"

// ************************ getter - methods ******************************************
std::string Levelchanger::getTexture() const{
    return texture;
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

    /*
    return this->getDestination();

    hier muss Level gewechselt werden
    */
    //level->setCharacters( dungeonCrawler->getLevel()->getCharacters()[0] );
    dungeonCrawler->setLevel( level );

    return destiny;

}
