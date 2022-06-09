#include "graphicalui.h"
#include <QLabel>
#include "dungeoncrawler.h"
#include "startscreen.h"
#include "mainwindow.h"
#include <QMainWindow>
#include "ui_mainwindow.h"

// *******************************
GraphicalUI::GraphicalUI(){

    startscreen = new Startscreen(this);
    mainWindow = new MainWindow(this);
}

// *******************************
void GraphicalUI::draw(Level *level){

    int length = this->getDungeonCrawler()->getLevel()->getLength();
    int width = this->getDungeonCrawler()->getLevel()->getWidth();
    mainWindow->getUi()->gridDungeon->setSpacing(0);

    for( int r = 0; r < length; r++ ){
        for( int c = 0; c < width;  c++ ){

            QString tex = QString::fromStdString ( this->getDungeonCrawler()->getLevel()->getTile(r, c)->getTexture() );
            QPixmap* pixmap = new QPixmap;
            pixmap->load(tex);

            QLabel* tile = new QLabel();
            tile->setPixmap(*pixmap);
            tile->setScaledContents(true);
            tile->lower();

            mainWindow->getUi()->gridDungeon->addWidget( tile, r, c );

            if(this->getDungeonCrawler()->getLevel()->getTile(r, c)->hasCharacter()){

                tex = QString::fromStdString ( this->getDungeonCrawler()->getLevel()->getCharacters()[0]->getTexture() );
                QPixmap* pixmap2 = new QPixmap;
                pixmap2->load(tex);

                QLabel* character = new QLabel();
                character->setPixmap(*pixmap2);
                character->setScaledContents(true);
                mainWindow->getUi()->gridDungeon->addWidget( character, r, c );
//                character->raise();
            }

        }
    }
}

int GraphicalUI::move(){

}

void GraphicalUI::startNewGame(){
    startscreen->hide();
    mainWindow->show();
}

Startscreen *GraphicalUI::getStartscreen() const{
    return startscreen;
}

DungeonCrawler *GraphicalUI::getDungeonCrawler() const{
    return dungeonCrawler;
}

void GraphicalUI::setDungeonCrawler(DungeonCrawler *newDungeonCrawler){
    dungeonCrawler = newDungeonCrawler;
}

MainWindow *GraphicalUI::getMainWindow() const{
    return mainWindow;
}
