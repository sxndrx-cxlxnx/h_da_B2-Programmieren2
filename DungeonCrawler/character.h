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

    // getter - methods
    const std::string &getTexture() const;
    Tile *getTile() const;
    Controller *getController() const;

    //other methods
    int move();

    void setLastDirection(int newLastDirection);

private:
    // attributes
    Tile* tile;
    std::string texture;
    Controller* controller;
    int lastDirection = 5;
};

#endif // CHARACTER_H
