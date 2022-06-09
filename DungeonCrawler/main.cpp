#include <iostream>                                                                                                                                     // PG #3
#include "dungeoncrawler.h"                                                                                                                             // Sandra Gräf  - 1111826
#include "level.h"                                                                                                                                      // Emily Staatz - 1111831
#include <QApplication>
#include "mainwindow.h"
#include"startscreen.h"

using namespace std;

int main(int argc, char* argv[]){

    QApplication a(argc, argv);
    GraphicalUI* dungeonCrawlerGui = new GraphicalUI();
    DungeonCrawler *dungeonCrawler = new DungeonCrawler(dungeonCrawlerGui);

    dungeonCrawlerGui->getStartscreen()->show();

    // play
    dungeonCrawler->play();

    return a.exec();


//    // delete
//    delete dungeonCrawler;

    //    return 0;
}
