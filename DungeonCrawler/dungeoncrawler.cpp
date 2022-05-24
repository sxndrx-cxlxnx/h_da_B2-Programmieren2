#include "dungeoncrawler.h"

// ************************ constructor ***********************************************
DungeonCrawler::DungeonCrawler(){

    TerminalUI* terminalui = new TerminalUI();
    abstractui = terminalui;

    Controller* controller = terminalui;          // put control to user via terminal input

//    level = new Level(controller);

    // Test copy ctor
    auto* tmp = new Level(controller);
    level = new Level(*tmp);               // currentLevel is attribute of DungeonCrawler
    delete tmp;

/*    // Test assignment
    tmp = new Level(controller);
    level =tmp;
    delete tmp;
*/
}

// ************************ destructor ************************************************
DungeonCrawler::~DungeonCrawler(){
    delete level;
    delete abstractui;
}

// ************************ getter - methods ******************************************
AbstractUI *DungeonCrawler::getAbstractui() const{
    return abstractui;
}

// ************************ other methods *********************************************
void DungeonCrawler::play(){
    // set few refactor-variables
    bool run = true;
    Tile* fromTile;
    Character* thisChar = this->level->getCharacters()[0];

    // Playloop
    while(run){
        fromTile = thisChar->getTile();         // Tile where you standing on at the moment
        int r,c;
        r = fromTile->getRow();
        c = fromTile->getColumn();

       this->abstractui->draw(this->level);                     // Output of Playground

        // Explanation of control: (user input)

        // 7 8 9              \  |  up  |   /
        // 4 5 6            left | stay | right
        // 1 2 3              /  | down |  \
        //   0                    Abbruch

       switch (thisChar->move()){
           case 0: run = false;                                                 // end of program
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
       default: break;
       }
    }
}
