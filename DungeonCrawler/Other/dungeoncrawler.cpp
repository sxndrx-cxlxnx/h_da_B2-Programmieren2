#include "dungeoncrawler.h"
#include "../Ui/mainwindow.h"
#include "ui_mainwindow.h"
#include "../Tiles/levelchanger.h"
#include "../Controller/guardcontroller.h"
#include "../Controller/stationarycontroller.h"
#include <QTest>

// ************************ constructor ***********************************************
DungeonCrawler::DungeonCrawler(GraphicalUI* pgui){

    graphicalui = pgui;

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

    graphicalui->setDungeonCrawler(this);

    levelList->push_back(level1);                                                       // put levels in level-vector
    levelList->push_back(level2);

    level1->getLevelchanger()->setLevel( level2 );                                      // set Levelchanger in their own level
    level2->getLevelchanger()->setLevel( level1 );

    level1->getLevelchanger()->setDestiny( level2->getLevelchanger() );                 // set destiny of Levelchanger to the Levelchanger of the other level
    level2->getLevelchanger()->setDestiny( level1->getLevelchanger() );

    level1->getLevelchanger()->setDungeonCrawler( this );                               // give levelchanger this "dungeonCrawler" to know for later methods
    level2->getLevelchanger()->setDungeonCrawler( this );

    level2->setCharacters( level1->getCharacters()[0] );                                // put the same character in the 2nd level as well (not playing with different ones)

    for(int r = 0; r < level1->getLength(); r++){                                       // put every neighboor of every Tile in their adjaceny list "neighborhood"
        for(int c = 0; c < level1->getWidth(); c++){
            level1->getDungeon()[r][c]->setNeighborhood(level1);
        }
    }

    for(int r = 0; r < level2->getLength(); r++){                                       // do the same for every Tile in level2 as well
        for(int c = 0; c < level2->getWidth(); c++){
            level2->getDungeon()[r][c]->setNeighborhood(level2);
        }
    }

    graphicalui->draw(level1);                                                           // first draw - both levels
    graphicalui->draw(level2);

    graphicalui->draw2(level1);                                                          // draw startlevel above

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
    delete graphicalui;
    delete levelList;
}

// ************************ getter - methods ******************************************
GraphicalUI *DungeonCrawler::getGraphicalui() const{
    return graphicalui;
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
            graphicalui->messageBox();
            break;
        }

        QTest::qWait(50);
        QCoreApplication::processEvents();

        if( this->getGraphicalui()->getMainWindow()->getNewEvent() ){

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

                if(i != 0){
                    this->level->getCharacters()[i]->setLastDirection(direction);
                }

                switch (direction){
                case 0:                                                               // end of program
                    if( !cancelTry ){
                        graphicalui->cancel();
                        cancelTry = true;
                    } else{
                        graphicalui->cancelTry2();
                        run = false;
                    }
                    break;
                case 1: fromTile->moveTo(level->getTile(r+1, c-1), thisChar);         // down - left
                    graphicalui->draw2(level);
                    break;
                case 2: fromTile->moveTo(level->getTile(r+1, c), thisChar);           // down
                    graphicalui->draw2(level);
                    break;
                case 3: fromTile->moveTo(level->getTile(r+1, c+1), thisChar);         // down - right
                    graphicalui->draw2(level);
                    break;
                case 4: fromTile->moveTo(level->getTile(r, c-1), thisChar);           // left
                    graphicalui->draw2(level);
                    break;
                case 5: graphicalui->draw2(level);                                    // stay
                    break;
                case 6: fromTile->moveTo(level->getTile(r, c+1), thisChar);           // right
                    graphicalui->draw2(level);
                    break;
                case 7: fromTile->moveTo(level->getTile(r-1, c-1), thisChar);         // up - left
                    graphicalui->draw2(level);
                    break;
                case 8: fromTile->moveTo(level->getTile(r-1, c), thisChar);           // up
                    graphicalui->draw2(level);
                    break;
                case 9: fromTile->moveTo(level->getTile(r-1, c+1), thisChar);         // up - right
                    graphicalui->draw2(level);
                    break;
                default: break;
                }
            }
        }
    }
}
