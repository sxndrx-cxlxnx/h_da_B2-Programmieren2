#ifndef STATIONARYCONTROLLER_H
#define STATIONARYCONTROLLER_H

#include "controller.h"

class StationaryController : public Controller{

public:
    // constructor
    StationaryController();

    // other methods
    int move() override;
    std::string getControllerName() override { return "StationaryController"; };
    std::string getMovePattern() override { return "error";};
    unsigned int getWhereInMovePattern() override {return 10;};
};

#endif // STATIONARYCONTROLLER_H
