#include <iostream>                                                                                                                                     // PG #3
#include "dungeoncrawler.h"                                                                                                                             // Sandra Gräf  - 1111826
#include "level.h"                                                                                                                                      // Emily Staatz - 1111831
#include <QApplication>
#include"startscreen.h"

using namespace std;

int main(int argc, char* argv[]){

    QApplication a(argc, argv);
    Startscreen s;
    s.show();
    return a.exec();

//    // initialize
//    DungeonCrawler *dungeonCrawler = new DungeonCrawler();

//    // play
//    dungeonCrawler->play();

//    // delete
//    delete dungeonCrawler;

//    return 0;
}
