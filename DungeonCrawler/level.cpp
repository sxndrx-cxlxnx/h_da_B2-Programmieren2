#include "level.h"
#include "door.h"
#include "floor.h"
#include "pit.h"
#include "portal.h"
#include "ramp.h"
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
Level::Level(Controller* pTerminalUI){

    dungeon.resize(length, vector<Tile*> (width));                      // resize level with width and length

    const string  levelString = {                                       // create level as a string
        "##########"
        "#@.......#"
        "#...<....#"
        "#..___...#"
        "#..___...#"
        "#........#"
        "#######X##"
        "#@.......#"
        "#...?....#"
        "##########"};

    Portal* portal1 = nullptr;                                          // set portal -> need for destination later
    Portal* portal2 = nullptr;

    Switch* switch1 = nullptr;                                          // set switch and door
    Door* door1 = nullptr;

    int atString = 0;

    for(int r = 0; r < length; r++){                                     // go through vector to set Tiles in dungeon like they are in "levelString"
        for(int c = 0; c < width; c++){

            switch(levelString[atString]){
            case '#': dungeon[r][c] = new Wall(r, c); break;
            case '.': dungeon[r][c] = new Floor(r, c); break;
            case '@': if( portal1 == nullptr ){                          // portals already created -> set them in dungeon
                    portal1 = new Portal(r, c);
                    dungeon[r][c] = portal1;
                } else{
                    portal2 = new Portal(r, c);
                    dungeon[r][c] = portal2;
                }
                break;
            case 'X': door1 = new Door(r, c);
                      dungeon[r][c] = door1;
                break;
            case '_': dungeon[r][c] = new Pit(r, c); break;
            case '<': dungeon[r][c] = new Ramp(r, c); break;
            case '?': switch1 = new Switch(r, c);
                      dungeon[r][c] = switch1;
                break;
            default: break;
            }
            atString++;
        }
    }

    switch1->attach(door1);                                              // connect door with switch

    portal1->setDestination(portal2);                                    // set portal destination to the other portal
    portal2->setDestination(portal1);

    Character* who = new Character(dungeon[1][7], pTerminalUI);          // place character
    this->placeCharacter( who, 1, 7 );
    this->characters.push_back(who);
}

// ************************ copy constructor ******************************************
Level::Level(const Level &pLevel){

    width = pLevel.width;
    length = pLevel.length;

    dungeon.resize(length, vector<Tile*> (width));

    Portal* portal1 = nullptr;
    Portal* portal2 = nullptr;
    Door* door1 = nullptr;
    Switch* switch1 = nullptr;

    for(int r = 0; r < length; r++){
        for(int c = 0; c < width; c++){

            bool tileIsDoor     = (typeid(*pLevel.dungeon[r][c]) == typeid(Door));
            bool tileIsFloor    = (typeid(*pLevel.dungeon[r][c]) == typeid(Floor));
            bool tileIsPit      = (typeid(*pLevel.dungeon[r][c]) == typeid(Pit));
            bool tileIsPortal   = (typeid(*pLevel.dungeon[r][c]) == typeid(Portal));
            bool tileIsRamp     = (typeid(*pLevel.dungeon[r][c]) == typeid(Ramp));
            bool tileIsSwitch   = (typeid(*pLevel.dungeon[r][c]) == typeid(Switch));
            bool tileIsWall     = (typeid(*pLevel.dungeon[r][c]) == typeid(Wall));

            if(tileIsDoor){
                door1 = new Door(r, c);
                dungeon[r][c] = door1;
            } else if(tileIsFloor){
                dungeon[r][c] = new Floor(r, c);
            } else if(tileIsPit){
                dungeon[r][c] = new Pit(r, c);
            } else if(tileIsPortal){

                if( portal1 == nullptr ){
                    portal1 = new Portal(r, c);
                    dungeon[r][c] = portal1;
                }else{
                    portal2 = new Portal(r, c);
                    dungeon[r][c] = portal2;
                }
            } else if(tileIsRamp){
                dungeon[r][c] = new Ramp(r, c);
            } else if(tileIsSwitch){
                switch1 = new Switch(r, c);
                dungeon[r][c] = switch1;
            } else if(tileIsWall){
                dungeon[r][c] = new Wall(r, c);
            }

            if( pLevel.dungeon[r][c]->hasCharacter() ){
                Character* who = new Character( dungeon[r][c], pLevel.dungeon[r][c]->getCharacter()->getController() );
                this->characters.push_back(who);
                dungeon[r][c]->setCharacter(who);
            }
        }
    }
    portal1->setDestination(portal2);
    portal2->setDestination(portal1);

    switch1->attach(door1);
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

const std::vector<Character *> &Level::getCharacters() const{
    return characters;
}

// ************************ other methods *********************************************
void Level::placeCharacter(Character *c, int row, int col){
    c->getTile()->setCharacter(nullptr);                                // old Tile get's nullpointer
    c->setTile(dungeon[row][col]);                                      // Character get's new Tile
    dungeon[row][col]->setCharacter(c);                                 // new Tile get's character
}
