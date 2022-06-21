#include "dungeoncrawler.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "levelchanger.h"

// ************************ constructor ***********************************************
DungeonCrawler::DungeonCrawler(GraphicalUI* pgui){

    abstractui = pgui;

    List* pList = new List();
    levelList = pList;

    Controller* controller = pgui;                 // put control to user via graphic input

    std::string  levelString1 = {                                       // create level as a string
        "################"
        "#.......#@._<..#"
        "#@....###.___..#"
        "#.....#@#......#"
        "#.......###X####"
        "#########......#"
        "#@....?##....S.#"
        "################"};

     std::string  levelString2 = {
        "################"
        "#............S.#"
        "#..............#"
        "#..............#"
        "#..............#"
        "#..............#"
        "#..............#"
        "################"};

    Level* level1 = new Level(controller, levelString1, true );
    level = level1;              // normal initialisation (without testing of ctor and assignement)
    Level* level2 = new Level(controller, levelString2, false );

    abstractui->setDungeonCrawler(this);

    levelList->push_back(level1);
    levelList->push_back(level2);

    level1->getLevelchanger()->setLevel( level2 );
    level2->getLevelchanger()->setLevel( level1 );

    level1->getLevelchanger()->setDestiny( level2->getLevelchanger() );
    level2->getLevelchanger()->setDestiny( level1->getLevelchanger() );

    level1->getLevelchanger()->setDungeonCrawler( this );
    level2->getLevelchanger()->setDungeonCrawler( this );

    level2->setCharacters( level1->getCharacters()[0] );

    abstractui->draw(level1);
    abstractui->draw(level2);

    abstractui->draw2(level1);



//    // Test copy ctor
//    auto* tmp = new Level(controller);
//    level = new Level(*tmp);                      // level is attribute of DungeonCrawler
//    delete tmp;

//    // Test assignment
//    tmp = new Level(controller);
//    *level = *tmp;
//    delete tmp;
}

// ************************ destructor ************************************************
DungeonCrawler::~DungeonCrawler(){
    delete level;
    delete abstractui;
}

// ************************ getter - methods ******************************************
GraphicalUI *DungeonCrawler::getAbstractui() const{
    return abstractui;
}

Level *DungeonCrawler::getLevel() const{
    return level;
}

// ************************ setter - methods ******************************************
void DungeonCrawler::setLevel(Level *pLevel){
    level = pLevel;
}

// ************************ other methods *********************************************
void DungeonCrawler::play(){
    // set few refactor-variables
    bool run = true;
    Tile* fromTile;
    Character* thisChar = this->level->getCharacters()[0];

    // Playloop
    while(run){
        fromTile = thisChar->getTile();                         // Tile where you standing on at the moment
        int r,c;
        r = fromTile->getRow();
        c = fromTile->getColumn();

        // Explanation of control: (user input)

        // 7 8 9              \  |  up  |   /
        // 4 5 6            left | stay | right
        // 1 2 3              /  | down |  \
        //   0                    Abbruch

       int direction = thisChar->move();
       switch (direction){
           case 0: // run = false;                                              // end of program
              break;
           case 1: fromTile->moveTo(level->getTile(r+1,c-1), thisChar);         // down - left
                   abstractui->draw2(level);
              break;
           case 2: fromTile->moveTo(level->getTile(r+1,c), thisChar);           // down
                   abstractui->draw2(level);
              break;
           case 3: fromTile->moveTo(level->getTile(r+1,c+1), thisChar);         // down - right
                   abstractui->draw2(level);
              break;
           case 4: fromTile->moveTo(level->getTile(r,c-1), thisChar);           // left
                   abstractui->draw2(level);
              break;
           case 5: abstractui->draw2(level);                                    // stay
              break;
           case 6: fromTile->moveTo(level->getTile(r,c+1), thisChar);           // right
                   abstractui->draw2(level);
              break;
           case 7: fromTile->moveTo(level->getTile(r-1,c-1), thisChar);         // up - left
                   abstractui->draw2(level);
              break;
           case 8: fromTile->moveTo(level->getTile(r-1,c), thisChar);           // up
                   abstractui->draw2(level);
              break;
           case 9: fromTile->moveTo(level->getTile(r-1,c+1), thisChar);         // up - right
                   abstractui->draw2(level);
              break;
       default: break;
       }
    }    
}
