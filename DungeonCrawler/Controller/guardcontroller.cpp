#include "guardcontroller.h"
#include <QTest>

// ************************ constructor ***********************************************
GuardController::GuardController(std::string pMovePattern){
    movePattern = pMovePattern;
}

// ************************ setter - methods ******************************************
void GuardController::setWhereInMovePattern(int number){
    whereInMovePattern = number;
}

// ************************ getter - methods ******************************************
unsigned int GuardController::getWhereInMovePattern() const{
    return whereInMovePattern;
}

// ************************ other methods *********************************************
int GuardController::move(){

    int tempMoveWhichYouAreDoingRightNow = movePattern[whereInMovePattern]-48;

    if( (whereInMovePattern +1) == movePattern.length()){
        setWhereInMovePattern(1);
    } else{
        setWhereInMovePattern( (whereInMovePattern +1) );
    }
    return tempMoveWhichYouAreDoingRightNow;
}
