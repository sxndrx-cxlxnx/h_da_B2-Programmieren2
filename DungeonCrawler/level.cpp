#include <cstdlib>
#include "level.h"
#include "door.h"
#include "floor.h"
#include "guardcontroller.h"
#include "levelchanger.h"
#include "lootchest.h"
#include "pit.h"
#include "portal.h"
#include "ramp.h"
#include "stationarycontroller.h"
#include "switch.h"
#include "wall.h"

using namespace std;

// ************************ assignment *************************************************
void swap(Level &lhs, Level &rhs){
    std::swap(lhs.dungeon, rhs.dungeon);
    std::swap(lhs.characters, rhs.characters);
}

Level& Level::operator=(Level rhs){
    swap(*this, rhs);
    return *this;
}

// ************************ constructor ***********************************************
Level::Level(Controller* pTerminalUI, std::string levelString, bool isCharInLevel ){

    dungeon.resize(length, vector<Tile*> (width));                      // resize level with width and length

    Portal* portal1 = nullptr;                                          // set portal -> need for destination later
    Portal* portal2 = nullptr;
    Portal* portal3 = nullptr;
    Portal* portal4 = nullptr;

    Switch* switch1 = nullptr;                                          // set switch and door
    Door* door1 = nullptr;

    Levelchanger* levelchanger1 = nullptr;

    int atString = 0;

    for(int r = 0; r < length; r++){                                     // go through vector to set Tiles in dungeon like they are in "levelString"
        for(int c = 0; c < width; c++){

            switch(levelString[atString]){
            case '#': dungeon[r][c] = new Wall(r, c); break;
            case '.': dungeon[r][c] = new Floor(r, c, floorType()); break;
            case '@': if( portal1 == nullptr ){                          // portals already created -> set them in dungeon
                    portal1 = new Portal(r, c, ":/Textures/Texturen-Paket/portal1.png");
                    dungeon[r][c] = portal1;
                    portals.push_back(portal1);
                    break;
                } else if( portal2 == nullptr ){
                    portal2 = new Portal(r, c, ":/Textures/Texturen-Paket/portal1.png");
                    dungeon[r][c] = portal2;
                    portals.push_back(portal2);
                    break;
                } else if( portal3 == nullptr ){
                    portal3 = new Portal(r, c, ":/Textures/Texturen-Paket/portal2.png");
                    dungeon[r][c] = portal3;
                    portals.push_back(portal3);
                    break;
                } else{
                    portal4 = new Portal(r, c, ":/Textures/Texturen-Paket/portal2.png");
                    dungeon[r][c] = portal4;
                    portals.push_back(portal4);
                }
                break;
            case 'X': door1 = new Door(r, c);
                      dungeon[r][c] = door1;
                break;
            case '_': dungeon[r][c] = new Pit(r, c); break;
            case '<': dungeon[r][c] = new Ramp(r, c); break;
            case '?': switch1 = new Switch(r, c);
                      dungeon[r][c] = switch1;
                      switches.push_back(switch1);
                    break;
            case 'S':
                    levelchanger1 = new Levelchanger(r,c);
                    dungeon[r][c] = levelchanger1;
                    break;
            case '$': dungeon[r][c] = new LootChest(r, c); break;
            default: break;
            }
            atString++;
        }
    }

    if( switch1 != nullptr ){
        switch1->attach(door1);                                              // connect door with switch
    }

    if( door1 != nullptr ){                                                  // push door in door-vector
        doors.push_back(door1);
    }

    if( portal1 != nullptr && portal2 != nullptr ){
        portal1->setDestination(portal2);                                    // set portal destination to the other portal
        portal2->setDestination(portal1);
    }
    if( portal3 != nullptr && portal4 != nullptr ){
        portal3->setDestination(portal4);
        portal4->setDestination(portal3);
    }

    if( isCharInLevel ){
        Character* who = new Character(dungeon[1][4], pTerminalUI, 25, 16, false);          // place character
        this->placeCharacter( who, 1, 4 );
        this->characters.push_back(who);
    }else{
        Controller* guard = new GuardController("6644");
        Character* zombie = new Character( dungeon[2][12], guard, 30, 6 ,true);
        this->placeCharacter( zombie, 2, 12 );
        this->characters.push_back(zombie);

        for(int i = 0; i < 3; i++){
            std::string movement;
            if(i == 0){
                movement = "644466";
            } else if (i == 1){
                movement = "664446";
            } else{
                movement = "666444";
            }
            Controller* guard2 = new GuardController(movement);

            Character* zombie2 = new Character( dungeon[6-i][1+i], guard2, 30, 6 ,true);
            this->placeCharacter( zombie2, 6-i, 1+i );
            this->characters.push_back(zombie2);
        }

        Controller* standingAround = new StationaryController();
        Character* boringZombie = new Character( dungeon[3][1], standingAround, 30, 6 ,true);
        this->placeCharacter( boringZombie, 3, 1 );
        this->characters.push_back(boringZombie);
    }

    if( levelchanger1 != nullptr ){
        this->setLevelchanger( levelchanger1 );
    }
}

// ************************ copy constructor ******************************************
Level::Level(const Level &pLevel){

    width = pLevel.width;
    length = pLevel.length;

    dungeon.resize(length, vector<Tile*> (width));

    for(int r = 0; r < length; r++){
        for(int c = 0; c < width; c++){
            Tile* pLevelTile = pLevel.dungeon[r][c];
            bool tileIsDoor     = (typeid(*pLevelTile) == typeid(Door));
            bool tileIsFloor    = (typeid(*pLevelTile) == typeid(Floor));
            bool tileIsLoot     = (typeid(*pLevelTile) == typeid(LootChest));
            bool tileIsPit      = (typeid(*pLevelTile) == typeid(Pit));
            bool tileIsPortal   = (typeid(*pLevelTile) == typeid(Portal));
            bool tileIsRamp     = (typeid(*pLevelTile) == typeid(Ramp));
            bool tileIsSwitch   = (typeid(*pLevelTile) == typeid(Switch));
            bool tileIsWall     = (typeid(*pLevelTile) == typeid(Wall));

            if(tileIsDoor){                                                             // set tiles (push in vector if neccessary)
                Door* door = new Door(r, c);
                dungeon[r][c] = door;
                doors.push_back(door);
            } else if(tileIsFloor){
                dungeon[r][c] = new Floor(r, c, pLevel.getTile(r,c)->getTexture());
            } else if(tileIsLoot){
                dungeon[r][c] = new LootChest(r, c);
            } else if(tileIsPit){
                dungeon[r][c] = new Pit(r, c);
            } else if(tileIsPortal){
                Portal* portal = new Portal(r, c, pLevel.getTile(r,c)->getTexture());
                dungeon[r][c] = portal;
                portals.push_back(portal);
            } else if(tileIsRamp){
                dungeon[r][c] = new Ramp(r, c);
            } else if(tileIsSwitch){
                Switch* switch1 = new Switch(r, c);
                dungeon[r][c] = switch1;
                switches.push_back(switch1);
            } else if(tileIsWall){
                dungeon[r][c] = new Wall(r, c);
            }

            if( pLevel.dungeon[r][c]->hasCharacter()){                                  // place character
                Character* pLevelChar = pLevel.dungeon[r][c]->getCharacter();
                Character* character = new Character( dungeon[r][c], pLevelChar->getController(), pLevelChar->getStrength(), pLevelChar->getStamina(), pLevelChar->getIsNPC());
                this->characters.push_back(character);
                dungeon[r][c]->setCharacter(character);
            }
        }
    }

    for( int i = 0; i < (int) portals.size(); i++ ){                                    // set portal destination
        int colPLevelDest = pLevel.portals[i]->getDestination()->getColumn();
        int rowPLevelDest = pLevel.portals[i]->getDestination()->getRow();

        portals[i]->setDestination( dungeon[rowPLevelDest][colPLevelDest]);
    }

    for( int j = 0; j < (int) doors.size(); j++ ){                                      // connect switch with door
        switches[0]->attach(doors[j]);
    }
}

// ************************ destructor ************************************************
Level::~Level(){
    for(int r = 0; r < length; r++){                                    // go through dungeon-vector -> delete every dungeon field
        for(int c = 0; c < width; c++){
            delete dungeon[r][c];
        }
    }
    for (int i = 0; i < (int) characters.size(); i ++){                 // go through character-vector -> delete everyone
        delete characters[i];
    }
}

// ************************ getter - methods ******************************************
int Level::getWidth(){
    return width;
}

int Level::getLength(){
    return length;
}

Tile *Level::getTile(int row, int col){
    return dungeon[row][col];
}

const Tile *Level::getTile(int row, int col) const{
    return dungeon[row][col];
}

std::vector<Character *> &Level::getCharacters() {
    return characters;
}

const std::vector<Door *> &Level::getDoors() const{
    return doors;
}

Levelchanger *Level::getLevelchanger() const{
    return levelchanger;
}

const std::vector<std::vector<Tile *> > &Level::getDungeon() const{
    return dungeon;
}

// ************************ setter - methods ******************************************

void Level::setLevelchanger(Levelchanger *newLevelchanger){
    levelchanger = newLevelchanger;
}

void Level::setCharacters( Character* pCharacter){
    characters.insert( characters.begin(), pCharacter );
}

// ************************ other methods *********************************************
void Level::placeCharacter(Character *c, int row, int col){
    c->getTile()->setCharacter(nullptr);                                // old Tile gets nullpointer
    c->setTile(dungeon[row][col]);                                      // Character gets new Tile
    dungeon[row][col]->setCharacter(c);                                 // new Tile gets character
}

std::string Level::floorType(){

    switch(rand() % 5){
    case 0: return ":/Textures/Texturen-Paket/floor1.png";
        break;
    case 1: return ":/Textures/Texturen-Paket/floor2.png";
        break;
    case 2: return ":/Textures/Texturen-Paket/floor3.png";
        break;
    case 3: return ":/Textures/Texturen-Paket/floor4.png";
        break;
    case 4: return ":/Textures/Texturen-Paket/floor5.png";
        break;
    default: return ":/Textures/Texturen-Paket/floor1.png";
        break;
    }
}
