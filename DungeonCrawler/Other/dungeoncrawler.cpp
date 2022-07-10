#include "dungeoncrawler.h"
#include "../Ui/mainwindow.h"
#include "ui_mainwindow.h"
#include "../Tiles/levelchanger.h"
#include "../Controller/guardcontroller.h"
#include "../Controller/stationarycontroller.h"
#include <QTest>
#include <json.hpp>
#include <fstream>

// ************************ constructor ***********************************************
DungeonCrawler::DungeonCrawler(GraphicalUI* pgui){

    graphicalui = pgui;

    List* pList = new List();
    levelList = pList;

    graphicalui->setDungeonCrawler(this);

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

    while( !everythingIsReady ){ QTest::qWait(50); }
    // Playloop

    bool cancelTry = false;

    while(run){

        if( level->getCharacters()[0]->getHitpoints() <= 0 || level->getCharacters()[0]->getLootChestFound()){
            run = false;           
            graphicalui->messageBox();
            continue;
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

void DungeonCrawler::store( Level* pLevel, std::string pPath ){

    nlohmann::json level;

     level["levelString"] = pLevel->getLevelString();
     level["levelID"]     = pLevel->levelID;

     // ************************************************************ //
     //                         Portals                              //
     // ************************************************************ //

     level["numberOfPortals"] = pLevel->getPortals().size();

     for( size_t i = 0; i < pLevel->getPortals().size(); i++){
         nlohmann::json portal;

         portal["destRow"]    = pLevel->getPortals()[i]->getDestination()->getRow();
         portal["destColumn"] = pLevel->getPortals()[i]->getDestination()->getColumn();
         portal["texture"]    = pLevel->getPortals()[i]->getTexture();

         level["portals"].push_back( portal );
     }
     // ------------------------------------------------------------ //

     // ************************************************************ //
     //                       Levelchanger                           //
     // ************************************************************ //

     if( pLevel->getLevelchanger()->getLevel()->levelID == 1 ){
         level["levelchangerDestLevel"] = "../tempLevel1.json";
     } else{
         level["levelchangerDestLevel"] = "../tempLevel2.json";
     }

     level["levelchangerDestTileRow"] = pLevel->getLevelchanger()->getDestiny()->getRow();
     level["levelchangerDestTileCol"] = pLevel->getLevelchanger()->getDestiny()->getColumn();

     // ------------------------------------------------------------ //

     // ************************************************************ //
     //                         Character                            //
     // ************************************************************ //

     level["numberOfCharacters"] = pLevel->getCharacters().size();

     for( size_t i = 0; i < pLevel->getCharacters().size(); i++ ){
            nlohmann::json character;
            Character* iChar = pLevel->getCharacters()[i];

            character["texture"]            = iChar->getTexture();
            character["row"]                = iChar->getTile()->getRow();
            character["column"]             = iChar->getTile()->getColumn();
            character["controller"]         = iChar->getController()->getControllerName();
            character["movePattern"]        = iChar->getController()->getMovePattern();
            character["whereInMovePattern"] = iChar->getController()->getWhereInMovePattern();
            character["strength"]           = iChar->getStrength();
            character["stamina"]            = iChar->getStamina();
            character["hitpoints"]          = iChar->getHitpoints();
            character["isNPC"]              = iChar->getIsNPC();
            character["lastDirection"]      = iChar->getLastDirection();

            level["characters"].push_back(character);
     }
     // ------------------------------------------------------------ //

     // ************************************************************ //
     //                           Doors                              //
     // ************************************************************ //

     level["numberOfDoors"] = pLevel->getDoors().size();

     for( size_t i = 0; i < pLevel->getDoors().size(); i++ ){
         nlohmann::json door;
         door["isOpen"] = pLevel->getDoors()[i]->getIsOpen();

         level["doors"].push_back( door );
     }
     // ------------------------------------------------------------ //

     std::ofstream outfile( pPath );
     outfile << level.dump(2);
}
