#include <iostream>                                                                                                                                     // PG #2
#include "dungeoncrawler.h"                                                                                                                             // Sandra Gräf  - 1111826
#include "level.h"                                                                                                                                      // Emily Staatz - 1111831

using namespace std;

int main(){
    // initialize
    DungeonCrawler *dungeonCrawler = new DungeonCrawler();

    // play
    dungeonCrawler->play();

    // delete
    delete dungeonCrawler;

    return 0;
}
