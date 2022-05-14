#include "dungeoncrawler.h"

// ************************ constructor ***********************************************
DungeonCrawler::DungeonCrawler(){
    Level* level1 = new Level();
    level = level1;
    AbstractUI* terminalui = new TerminalUI();
    abstractui = terminalui;
}

// ************************ destructor ************************************************
DungeonCrawler::~DungeonCrawler(){
    delete level;
    delete abstractui;
}

// ************************ other methods *********************************************

void DungeonCrawler::play(){

    bool run = true;
    Tile* fromTile;
    Character* thisChar = this->level->getCharacters()[0];



    while(run){                                                    // Playloop
        fromTile = thisChar->getTile();
        int r,c;
        r = fromTile->getRow();
        c = fromTile->getColumn();

       this->abstractui->draw(this->level);                     // Output of Playground

        // 7 8 9              \  |  up  |   /
        // 4 5 6            left | stay | right
        // 1 2 3              /  | down |  \
        //
        //   0                    Abbruch


       switch (thisChar->move()) {
           case 0: run = false;
              break;
           case 1: fromTile->moveTo(level->getTile(r+1,c-1), thisChar);         // down - left
              break;
           case 2: fromTile->moveTo(level->getTile(r+1,c), thisChar);           // down
              break;
           case 3: fromTile->moveTo(level->getTile(r+1,c+1), thisChar);         // down - right
              break;
           case 4: fromTile->moveTo(level->getTile(r,c-1), thisChar);           // left
              break;
           case 5:                                                              // stay
              break;
           case 6: fromTile->moveTo(level->getTile(r,c+1), thisChar);           // right
              break;
           case 7: fromTile->moveTo(level->getTile(r-1,c-1), thisChar);         // up - left
              break;
           case 8: fromTile->moveTo(level->getTile(r-1,c), thisChar);           // up
              break;
           case 9: fromTile->moveTo(level->getTile(r-1,c+1), thisChar);         // up - right
              break;
       default: std::cout << "Fehler" << std::endl;

       }
   }
}
