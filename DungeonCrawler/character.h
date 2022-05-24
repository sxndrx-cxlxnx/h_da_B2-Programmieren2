#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include "terminalui.h"
class DungeonCrawler;
class Tile;

class Character{
public:
    // constructor (inline)
    Character(Tile* pTile, Controller* pController) : tile(pTile), texture("O"), controller(pController){};

    // setter - methods
    void setTile(Tile *newTile);

    // getter - methods
    const std::string &getTexture() const;
    Tile *getTile() const;
    Controller *getController() const;

    //other methods
    int move();



private:
    // attributes
    Tile* tile;
    std::string texture;
    Controller* controller;
};

#endif // CHARACTER_H
