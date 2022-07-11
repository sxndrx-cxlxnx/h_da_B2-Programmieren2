#include <iostream>                                                                                                                                         // PG #5
#include "Other/dungeoncrawler.h"                                                                                                                           // Sandra Gräf  - 1111826
#include "Other/level.h"                                                                                                                                    // Emily Staatz - 1111831
#include "Ui/mainwindow.h"
#include "Ui/startscreen.h"
#include <QApplication>

using namespace std;

int main(int argc, char* argv[]){

    QApplication a(argc, argv);
    GraphicalUI* dungeonCrawlerGui = new GraphicalUI();
    DungeonCrawler *dungeonCrawler = new DungeonCrawler(dungeonCrawlerGui);

    dungeonCrawlerGui->getStartscreen()->show();

    // play
    dungeonCrawler->play();

    return 0;
}
