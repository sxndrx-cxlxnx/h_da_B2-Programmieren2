#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include "terminalui.h"

class DungeonCrawler;
class Tile;

class Character{
public:
    // constructor
    Character(Tile* pTile, Controller* pController, int pStrength, int pStamina);
    // setter - methods
    void setTile(Tile *newTile);
    void setLastDirection(int newLastDirection);

    // getter - methods
    std::string &getTexture();
    Tile *getTile() const;
    Controller *getController() const;
    int getMaxHP();
    int getStrength();
    int getStamina();
    int getHitpoints();

    //other methods
    int move();

private:
    // attributes
    Tile* tile;
    std::string texture;
    Controller* controller;
    int lastDirection = 5;
    int strength;
    int stamina;
    int hitpoints;
};

#endif // CHARACTER_H
