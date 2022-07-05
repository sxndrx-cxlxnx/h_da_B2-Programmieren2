#include "dungeoncrawler.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "levelchanger.h"
#include "guardcontroller.h"
#include "stationarycontroller.h"
#include <QTest>

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
        "#..@?#.$.#.#.S.#"
        "#....#...X.#...#"
        "#.########@#...#"
        "#....#...#####.#"
        "#....#.#.#...#.#"
        "#......#...#...#"
        "################"};

    Level* level1 = new Level(controller, levelString1, true );
    level = level1;              // normal initialisation (without testing of ctor and assignement)
    Level* level2 = new Level(controller, levelString2, false );

    abstractui->setDungeonCrawler(this);

    levelList->push_back(level1);                                                       // put levels in level-vector
    levelList->push_back(level2);

    level1->getLevelchanger()->setLevel( level2 );                                      // set Levelchanger in their own level
    level2->getLevelchanger()->setLevel( level1 );

    level1->getLevelchanger()->setDestiny( level2->getLevelchanger() );                 // set destiny of Levelchanger to the Levelchanger of the other level
    level2->getLevelchanger()->setDestiny( level1->getLevelchanger() );

    level1->getLevelchanger()->setDungeonCrawler( this );                               // give levelchanger this "dungeonCrawler" to know for later methods
    level2->getLevelchanger()->setDungeonCrawler( this );

    level2->setCharacters( level1->getCharacters()[0] );                                // put the same character in the 2nd level as well (not playing with different ones)

    abstractui->draw(level1);                                                           // first draw - both levels
    abstractui->draw(level2);

    abstractui->draw2(level1);                                                          // draw startlevel above

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
    delete levelList;
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
    bool cancelTry = false;

    // Playloop
    while(run){

        if( level->getCharacters()[0]->getHitpoints() <= 0 || level->getCharacters()[0]->getLootChestFound()){
            run = false;           
            abstractui->messageBox();
            break;
        }

        QTest::qWait(50);
        QCoreApplication::processEvents();

        if( this->getAbstractui()->getMainWindow()->getNewEvent() ){

            for( size_t i = 0; i < this->level->getCharacters().size(); i++ ){
                Character* thisChar = this->level->getCharacters()[i];

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

                if( thisChar->isDead() ){
                    continue;
                }

                switch (direction){
                case 0:
                    if( !cancelTry ){
                        abstractui->cancel();
                        cancelTry = true;
                    }else{
                        abstractui->cancelTry2();
                        run = false;
                    }                                                                // end of program
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
    }
}
