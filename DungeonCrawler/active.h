#ifndef ACTIVE_H
#define ACTIVE_H

#include <iostream>
#include <vector>
#include "passive.h"

class Active{
protected:
    // attributes
    std::vector<Passive*> observers;

public:
    // constructor
    Active();

    // destructor (inline)
    virtual ~Active(){};

    // getter - methods
    const std::vector<Passive *> &getObservers() const;

    // other methods
    void attach(Passive *passiveTile);
    void detach(Passive *passiveTile);
    virtual void activate() = 0;
};

#endif // ACTIVE_H
