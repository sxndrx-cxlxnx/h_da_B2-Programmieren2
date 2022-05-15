#include "level.h"
#include "wall.h"
#include "floor.h"
#include "portal.h"
#include "door.h"
#include "switch.h"

// ************************ constructor ***********************************************
Level::Level(){

    // set wall around the level - rest is floor
    for(int c = 0; c < width; c++){                         // column / width
        for(int r = 0; r < length; r++){                    // row / length

            if(r == 1 && c == width -2){                    // don't set Floor where portals will be
                continue;
            } else if(r == length -2 && c == 1){
                continue;
            }

            if(c == 0 || c == width -1){                    // sides
                dungeon[r][c] = new Wall(r,c);
            } else if(r == 0 || r == length -1){            // above and underneath
                dungeon[r][c] = new Wall(r,c);
            } else if(r == length -4){                      // seperate one portal from the other one
                dungeon [r][c] = new Wall(r,c);
            } else{
                dungeon[r][c] = new Floor (r,c);            // rest
            }
        }
    }

    // set 2 portals in the corners
    Portal* portal1 = new Portal(1, width -2, dungeon[length -2][1]);
    dungeon[1][width -2] = portal1;

    Portal* portal2 = new Portal(length -2, 1, dungeon[1][width -2]);
    dungeon[length -2][1] = portal2;

    // set portal destination (bring them to work)
    portal1->setDestination(dungeon[length -2][1]);
    portal2->setDestination(dungeon[1][width -2]);

    int midWidth = width /2;
    int midLength = length /2;

    // useless, just to make on Enter, 3 lines down, work               // -
    Character* who = new Character(dungeon[0][0]);                      //  |
                                                                        //  |
    // set character in the middle of the field                         //  v
    if(dungeon[midWidth][midLength]->onEnter(dungeon[length -4][midWidth], who) == nullptr){         // field == wall
        this->characters.push_back(new Character(dungeon[length -5][midWidth]));                     // one up
        this->placeCharacter(characters[0], length -5, midWidth);
    } else{
        this->characters.push_back(new Character(dungeon[midLength][midWidth]));
        this->placeCharacter(characters[0], midLength, midWidth);
    }
    delete who;     // delete useless Character*
}

// ************************ destructor ************************************************
Level::~Level(){
    for(int r = 0; r < length; r++){
        for(int c = 0; c < width; c++){
            delete dungeon[r][c];
        }
    }
    for (int i = 0; i < (int) characters.size(); i ++){
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


