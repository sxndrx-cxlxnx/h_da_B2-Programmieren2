#include "stationarycontroller.h"

StationaryController::StationaryController(){

}

int StationaryController::move(){
    /*                                                  // aus GUI
    QTest::qWait(50);
    QCoreApplication::processEvents();
    if( mainWindow->getNewEvent() ){
        mainWindow->setNewEvent(false);
        return mainWindow->getLastInput();
    }else{
        return 0;
    }
    */
    return 5;
}
