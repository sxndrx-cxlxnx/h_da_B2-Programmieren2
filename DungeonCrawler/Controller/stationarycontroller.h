#ifndef STATIONARYCONTROLLER_H
#define STATIONARYCONTROLLER_H

#include "controller.h"

class StationaryController : public Controller{

public:
    // constructor
    StationaryController();

    // other methods
    virtual int move() override;
};

#endif // STATIONARYCONTROLLER_H
