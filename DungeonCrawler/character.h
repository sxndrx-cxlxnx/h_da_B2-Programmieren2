#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include "terminalui.h"

class DungeonCrawler;
class Tile;

class Character{
public:
    // constructor (inline)
    Character(Tile* pTile, Controller* pController) : tile(pTile), texture(":/Character/Texturen-Paket/char/char_front_2.png"), controller(pController){};

    // setter - methods
    void setTile(Tile *newTile);
    void setLastDirection(int newLastDirection);

    // getter - methods
    std::string &getTexture();
    Tile *getTile() const;
    Controller *getController() const;

    //other methods
    int move();

private:
    // attributes
    Tile* tile;
    std::string texture;
    Controller* controller;
    int lastDirection = 5;
};

#endif // CHARACTER_H
