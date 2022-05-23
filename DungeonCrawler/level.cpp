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
    c->getTile()->setCharacter(nullptr);
    c->setTile(dungeon[row][col]);
    dungeon[row][col]->setCharacter(c);
}
