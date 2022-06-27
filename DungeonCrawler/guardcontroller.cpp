#include "guardcontroller.h"
#include <QTest>

GuardController::GuardController(std::string pMovePattern){
    movePattern = pMovePattern;
}

void GuardController::setWhereInMovePattern(int number){
    whereInMovePattern = number;
}

unsigned int GuardController::getWhereInMovePattern() const{
    return whereInMovePattern;
}

int GuardController::move(){

    int tempMoveWhichYouAreDoingRightNow = movePattern[whereInMovePattern]-48;

    if( (whereInMovePattern +1) == movePattern.length()){
        setWhereInMovePattern(0);
    } else{
        setWhereInMovePattern( (whereInMovePattern+1) );
    }
    return tempMoveWhichYouAreDoingRightNow;
}
