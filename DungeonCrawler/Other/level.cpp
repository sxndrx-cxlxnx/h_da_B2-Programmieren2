#include <cstdlib>
#include <queue>
#include <fstream>
#include <json.hpp>

#include "../Controller/attackcontroller.h"
#include "../Controller/guardcontroller.h"
#include "../Controller/stationarycontroller.h"
#include "../Other/level.h"
#include "../Tiles/door.h"
#include "../Tiles/floor.h"
#include "../Tiles/levelchanger.h"
#include "../Tiles/lootchest.h"
#include "../Tiles/pit.h"
#include "../Tiles/portal.h"
#include "../Tiles/ramp.h"
#include "../Tiles/switch.h"
#include "../Tiles/wall.h"

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
Level::Level(Controller* pGUI, std::string pPath, bool isCharInLevel, Character* player ){

    dungeon.resize(length, vector<Tile*> (width));                      // resize level with width and length

    std::ifstream file( pPath );
    nlohmann::json jFile;
    file >> jFile;

    levelString = jFile["levelString"];
    levelID = jFile["levelID"];

    int atString = 0;
    Portal* portalTmp = nullptr;
    Door* doorTmp = nullptr;
    Switch* switchTmp = nullptr;

    for(int r = 0; r < length; r++){                                     // go through vector to set Tiles in dungeon like they are in "levelString"
        for(int c = 0; c < width; c++){

            switch(levelString[atString]){
            case '#': dungeon[r][c] = new Wall(r, c); break;
            case '.': dungeon[r][c] = new Floor(r, c, floorType());
                      allNodes.push_back( dungeon[r][c] );
                  break;
            case '@':
                    portalTmp = new Portal(r, c);
                    dungeon[r][c] = portalTmp;
                    portals.push_back(portalTmp);
                    allNodes.push_back( dungeon[r][c] );
                break;
            case 'X':
                    doorTmp = new Door(r, c);
                    dungeon[r][c] = doorTmp;
                    doors.push_back( doorTmp );
                    allNodes.push_back( dungeon[r][c] );
                break;
            case '_': dungeon[r][c] = new Pit(r, c);
                      allNodes.push_back( dungeon[r][c] );
                break;
            case '<': dungeon[r][c] = new Ramp(r, c);
                      allNodes.push_back( dungeon[r][c] );
                break;
            case '?':
                    switchTmp = new Switch(r, c);
                    dungeon[r][c] = switchTmp;
                    switches.push_back(switchTmp);
                    allNodes.push_back( dungeon[r][c] );
                break;
            case 'S':
                    levelchanger = new Levelchanger(r,c);
                    dungeon[r][c] = levelchanger;
                    levelchanger->predecessor = levelchanger;
                    levelchanger->visited = true;
                 break;
            case '$': dungeon[r][c] = new LootChest(r, c); break;
            default: break;
            }
            atString++;
        }
    }

    if( !switches.empty() && !doors.empty() ){
        for( size_t i = 0; i < doors.size(); i++ ){                                          // connect door with switch
            switches[0]->attach(doors[i]);
        }
    }
    int p = 0;
    for( const auto& portalTmp : jFile["portals"] ){
        int r = portalTmp["destRow"];
        int c = portalTmp["destColumn"];
        portals[p]->setDestination( dungeon[r][c]);
        portals[p]->setTexture( portalTmp["texture"] );
        p++;
    }

    int d = 0;
    for( const auto& doorTmp : jFile["doors"] ){
        doors[d]->setIsOpen( doorTmp["isOpen"] );
        d++;
    }

    int c = 0;
    for( const auto& cTmp : jFile["characters"]){

        int jRow       = cTmp["row"];
        int jColumn    = cTmp["column"];
        int jStrength  = cTmp["strength"];
        int jStamina   = cTmp["stamina"];
        bool jNPC      = cTmp["isNPC"];
        int jHitpoints = cTmp["hitpoints"];
        int jDirection = cTmp["lastDirection"];

        if( c == 0 && isCharInLevel ){
            Character* who = new Character( dungeon[ jRow ][ jColumn ], pGUI, jStrength, jStamina, jNPC, jHitpoints );
            placeCharacter( who, jRow, jColumn );
            characters.push_back( who );
            who->setLastDirection( jDirection );

        } else if ( c == 0 && !isCharInLevel ){
            characters.push_back( player );

        } else{
            Controller* controller = nullptr;
            Character* who = nullptr;

            if( cTmp["controller"] == "AttackController" ){
                AttackController* attack = new AttackController( this );
                controller = attack;
                who = new Character( dungeon[ jRow ][ jColumn ], controller, jStrength, jStamina, jNPC, jHitpoints );
                attack->setCharacter( who );

            } else if ( cTmp["controller"] == "GuardController" ){
                controller = new GuardController( cTmp["movePattern"], cTmp["whereInMovePattern"] );
                who = new Character( dungeon[ jRow ][ jColumn ], controller, jStrength, jStamina, jNPC, jHitpoints );

            } else{
                controller = new StationaryController();
                who = new Character( dungeon[ jRow ][ jColumn ], controller, jStrength, jStamina, jNPC, jHitpoints );
            }

            placeCharacter( who, jRow, jColumn );
            characters.push_back( who );
            who->setLastDirection( jDirection );
        }
        c++;
    }

    for(int r = 0; r < this->getLength(); r++){                                  // put every neighboor of every Tile in their adjaceny list "neighborhood"
        for(int c = 0; c < this->getWidth(); c++){
            this->getDungeon()[r][c]->setNeighborhood(this);
        }
    }
}

// ************************ copy constructor ******************************************
Level::Level(const Level &pLevel){

    width = pLevel.width;
    length = pLevel.length;

    dungeon.resize(length, vector<Tile*> (width));

    for(int r = 0; r < length; r++){
        for(int c = 0; c < width; c++){
            Tile* pLevelTile = pLevel.dungeon[r][c];
            bool tileIsDoor     = (typeid(*pLevelTile) == typeid(Door));
            bool tileIsFloor    = (typeid(*pLevelTile) == typeid(Floor));
            bool tileIsLoot     = (typeid(*pLevelTile) == typeid(LootChest));
            bool tileIsPit      = (typeid(*pLevelTile) == typeid(Pit));
            bool tileIsPortal   = (typeid(*pLevelTile) == typeid(Portal));
            bool tileIsRamp     = (typeid(*pLevelTile) == typeid(Ramp));
            bool tileIsSwitch   = (typeid(*pLevelTile) == typeid(Switch));
            bool tileIsWall     = (typeid(*pLevelTile) == typeid(Wall));

            if(tileIsDoor){                                                             // set tiles (push in vector if neccessary)
                Door* door = new Door(r, c);
                dungeon[r][c] = door;
                doors.push_back(door);
            } else if(tileIsFloor){
                dungeon[r][c] = new Floor(r, c, pLevel.getTile(r,c)->getTexture());
            } else if(tileIsLoot){
                dungeon[r][c] = new LootChest(r, c);
            } else if(tileIsPit){
                dungeon[r][c] = new Pit(r, c);
            } else if(tileIsPortal){
                Portal* portal = new Portal(r, c, pLevel.getTile(r,c)->getTexture());
                dungeon[r][c] = portal;
                portals.push_back(portal);
            } else if(tileIsRamp){
                dungeon[r][c] = new Ramp(r, c);
            } else if(tileIsSwitch){
                Switch* switch1 = new Switch(r, c);
                dungeon[r][c] = switch1;
                switches.push_back(switch1);
            } else if(tileIsWall){
                dungeon[r][c] = new Wall(r, c);
            }

            if( pLevel.dungeon[r][c]->hasCharacter()){                                  // place character
                Character* pLevelChar = pLevel.dungeon[r][c]->getCharacter();
                Character* character = new Character( dungeon[r][c], pLevelChar->getController(), pLevelChar->getStrength(), pLevelChar->getStamina(), pLevelChar->getIsNPC(), pLevelChar->getHitpoints() );
                this->characters.push_back(character);
                dungeon[r][c]->setCharacter(character);
            }
        }
    }

    for( int i = 0; i < (int) portals.size(); i++ ){                                 // set portal destination
        int colPLevelDest = pLevel.portals[i]->getDestination()->getColumn();
        int rowPLevelDest = pLevel.portals[i]->getDestination()->getRow();

        portals[i]->setDestination( dungeon[rowPLevelDest][colPLevelDest]);
    }

    for( int j = 0; j < (int) doors.size(); j++ ){                                      // connect switch with door
        switches[0]->attach(doors[j]);
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

Levelchanger *Level::getLevelchanger() const{
    return levelchanger;
}

const Tile *Level::getTile(int row, int col) const{
    return dungeon[row][col];
}

const std::vector<Door *> &Level::getDoors() const{
    return doors;
}

const std::vector<Portal *> &Level::getPortals() const{
    return portals;
}

const std::vector<std::vector<Tile *> > &Level::getDungeon() const{
    return dungeon;
}

std::vector<Character *> &Level::getCharacters() {
    return characters;
}

std::vector<Tile *> Level::getPath(Tile *from, Tile *to){

    for( size_t y = 0; y < allNodes.size(); y++ ){
        allNodes[y]->predecessor = nullptr;
        allNodes[y]->visited = false;
    }

    vector< Tile* > wayToGo;                                                        // wayToGo will be the shortest path from "from" to "to" (but reversed order)
    queue< Tile* > q;                                                               // queue for the next Tiles

    q.push( from );                                                                 // "from" is the startvalue for the breadth-first-search

    while( !q.empty() ){
        auto *currentNode = q.front();
        q.pop();

        if( !currentNode->visited ){
            vector < Tile* > currentNeighbors = currentNode->getNeighborhood();
            currentNode->visited = true;

            for( Tile* &nextNode: currentNeighbors ){
                if( nextNode->predecessor == nullptr ){                             // set predecessor of neighbors to current Node
                        nextNode->predecessor = currentNode;

                    q.push( nextNode );                                             // push neighbors of currentNode to Queue

                    if( nextNode == to ){                                           // if end of way is reached
                        wayToGo.push_back( nextNode );
                        Tile* goBack = currentNode;

                        while( goBack != from ){                                    // store current node and every ancestor as "Way to go"
                            wayToGo.push_back( goBack );
                            goBack = goBack->predecessor;
                        }

                        return wayToGo;
                    }
                }
            }
        }
    }
    return wayToGo;                                                                 // if q == empty -> Character not found
}

const std::string &Level::getLevelString() const{
    return levelString;
}

// ************************ setter - methods ******************************************

void Level::setLevelchanger(Levelchanger *newLevelchanger){
    levelchanger = newLevelchanger;
}

void Level::setCharacters( Character* pCharacter){
    characters.insert( characters.begin(), pCharacter );
}

// ************************ other methods *********************************************
void Level::placeCharacter(Character *c, int row, int col){
    c->getTile()->setCharacter(nullptr);                                // old Tile gets nullpointer
    c->setTile(dungeon[row][col]);                                      // Character gets new Tile
    dungeon[row][col]->setCharacter(c);                                 // new Tile gets character
}

std::string Level::floorType(){

    switch(rand() % 5){
    case 0: return ":/Textures/Texturen-Paket/floor1.png";
        break;
    case 1: return ":/Textures/Texturen-Paket/floor2.png";
        break;
    case 2: return ":/Textures/Texturen-Paket/floor3.png";
        break;
    case 3: return ":/Textures/Texturen-Paket/floor4.png";
        break;
    case 4: return ":/Textures/Texturen-Paket/floor5.png";
        break;
    default: return ":/Textures/Texturen-Paket/floor1.png";
        break;
    }
}
