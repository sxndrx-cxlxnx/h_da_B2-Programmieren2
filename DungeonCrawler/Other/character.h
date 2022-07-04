#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <QLabel>
#include "../Ui/terminalui.h"

class DungeonCrawler;
class Tile;

class Character{
public:
    // constructor
    Character(Tile* pTile, Controller* pController, int pStrength, int pStamina, bool pIsNPC);

    // setter - methods
    void setTile(Tile *newTile);
    void setLastDirection(int newLastDirection);
    void setHitpoints(int newHitpoints);
    void setLootChestFound();

    // getter - methods
    std::string &getTexture();
    Tile *getTile() const;
    Controller *getController() const;
    int getMaxHP();
    int getStrength();
    int getStamina();
    int getHitpoints();
    bool getIsNPC();
    bool getLootChestFound();

    //other methods
    int move();
    bool isDead();

    // public attributes
    QLabel* label = nullptr;

private:
    // attributes
    Tile* tile;
    std::string texture;
    Controller* controller;
    int lastDirection = 5;
    int strength;
    int stamina;
    int hitpoints;
    bool isNPC;
    bool lootChestFound = false;
};

#endif // CHARACTER_H
