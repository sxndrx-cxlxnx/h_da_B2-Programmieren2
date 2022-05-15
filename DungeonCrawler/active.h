#ifndef ACTIVE_H
#define ACTIVE_H
#include <iostream>
#include <vector>
#include "passive.h"


class Active{
protected:
    std::vector<Passive*> observers;
public:
    Active();
    virtual ~Active(){};
    void attach(Passive *passiveTile);
    void detach(Passive *passiveTile);
    virtual void activate() = 0;
};

#endif // ACTIVE_H
