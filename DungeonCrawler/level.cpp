#include "level.h"
#include "door.h"
#include "floor.h"
#include "pit.h"
#include "portal.h"
#include "ramp.h"
#include "switch.h"
#include "wall.h"

using namespace std;

// ************************ constructor ***********************************************
Level::Level(Controller* pTerminalUI){

    dungeon.resize(length, vector<Tile*> (width));              // resize level with width and length

    const string  levelString = {                               // create level as a string
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

    Portal* portal1 = new Portal(1, 1);                                 // set portal -> need for destination later
    Portal* portal2 = new Portal(7, 1);

    Switch* switch1 = new Switch(8, 4);                                 // set switch and door
    Door* door1 = new Door(6, 7);
    switch1->attach(door1);                                             // connect door with switch

    int atString = 0;
    bool firstPortalSet = false;

    for(int r = 0; r < length; r++){                                    // go through vector to set Tiles in dungeon like they are in "levelString"
        for(int c = 0; c < width; c++){

            switch(levelString[atString]){
                case '#': dungeon[r][c] = new Wall(r, c); break;
                case '.': dungeon[r][c] = new Floor(r, c); break;
                case '@': if(!firstPortalSet){                          // portals already created -> set them in dungeon
                              dungeon[r][c] = portal1;
                              firstPortalSet = true;
                          } else{
                              dungeon[r][c] = portal2;
                          }
                          break;
                case 'X': dungeon[r][c] = door1; break;
                case '_': dungeon[r][c] = new Pit(r, c); break;
                case '<': dungeon[r][c] = new Ramp(r, c); break;
                case '?': dungeon[r][c] = switch1; break;
            default: break;
            }
            atString++;
        }
    }

    portal1->setDestination(dungeon[7][1]);                             // set portal destination to the other portal
    portal2->setDestination(dungeon[1][1]);

    Character* who = new Character(dungeon[1][7], pTerminalUI);         // place character
    this->placeCharacter( who, 1, 7 );
    this->characters.push_back(who);
}

Level::Level(const Level &pLevel){

    width = pLevel.width;
    length = pLevel.length;

    dungeon.resize(length, vector<Tile*> (width));

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
                dungeon[r][c] = new Door(r, c);
            } else if(tileIsFloor){
                dungeon[r][c] = new Floor(r, c);
            } else if(tileIsPit){
                dungeon[r][c] = new Pit(r, c);
            } else if(tileIsPortal){
                dungeon[r][c] = new Portal(r, c);
            } else if(tileIsRamp){
                dungeon[r][c] = new Ramp(r, c);
            } else if(tileIsSwitch){
                dungeon[r][c] = new Switch(r, c);
            } else if(tileIsWall){
                dungeon[r][c] = new Wall(r, c);
            }

//            dungeon[r][c] = pLevel.dungeon[r][c];

            if( pLevel.dungeon[r][c]->hasCharacter() ){

                Character* who = new Character(dungeon[r][c], pLevel.dungeon[r][c]->getCharacter()->getController() );         // place character, Character/Player is always characters[0]
//                who = pLevel.dungeon[r][c]->getCharacter();
                this->characters.push_back(who);
                dungeon[r][c]->setCharacter(who);
            }
        }
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

const std::vector<Character *> &Level::getCharacters() const{
    return characters;
}

// ************************ other methods *********************************************
void Level::placeCharacter(Character *c, int row, int col){
    c->getTile()->setCharacter(nullptr);                                // old Tile get's nullpointer
    c->setTile(dungeon[row][col]);                                      // Character get's new Tile
    dungeon[row][col]->setCharacter(c);                                 // new Tile get's character
}
