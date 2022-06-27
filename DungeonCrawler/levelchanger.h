#ifndef LEVELCHANGER_H
#define LEVELCHANGER_H
#include "level.h"
#include "portal.h"
#include "tile.h"

class Levelchanger : public Tile{

private:
    // attributes
    Level* level = nullptr;
    Tile* destiny = nullptr;
    DungeonCrawler* dungeonCrawler = nullptr;

public:
    // constructor (inline)
    Levelchanger(const int pRow, const int pColumn) : Tile( pRow, pColumn, ":/Textures/Texturen-Paket/portal3.png"){};

    // destructor (inline)
    virtual ~Levelchanger(){};

    // getter - methods
    virtual std::string getTexture() const override;

    // setter - methods
    void setLevel(Level *newLevel);
    void setDestiny(Tile *newDestiny);
    void setDungeonCrawler(DungeonCrawler *newDungeonCrawler);

    // other methods
    virtual Tile* onEnter(Tile* fromTile, Character* who) override;
};

#endif // LEVELCHANGER_H
