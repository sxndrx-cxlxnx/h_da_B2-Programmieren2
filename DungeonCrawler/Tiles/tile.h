#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>
#include "../Other/character.h"

class Level;

class Tile{             // abstract basisclass of Floor, Wall, Portal, Switch, Door, Ramp and Pit
protected:
    // attributes
    const int row;
    const int column;
    std::string texture;
    Character* character = nullptr;
    std::vector<Tile*> neighborhood;

public:
    // public attributes
    Tile* predecessor = nullptr;
    bool visited = false;

    // constructor (inline)
    Tile(const int pRow, const int pColumn, std::string pTexture):
        row(pRow), column(pColumn), texture(pTexture){};

    // destructor (inline)
    virtual ~Tile(){};

    // getter - methods
    int getRow() const;
    int getColumn() const;
    Character *getCharacter() const;
    virtual std::string getTexture() const = 0;
    std::vector<Tile *> &getNeighborhood();

    // setter - methods
    void setCharacter(Character *newCharacter);
    void setNeighborhood(Level* pLevel);

    // other methods
    bool hasCharacter();
    void fightEvent(Character* attacker, Character* defender);
    bool moveTo(Tile* destTile, Character* who);                // move to
    virtual Tile* onEnter(Tile* fromTile, Character* who);      // on Enter
    virtual Tile* onLeave(Tile* destTile, Character* who);      // on Leave
    void goAStepWithCharacter(Tile *from, Tile *to);
};

#endif // TILE_H
