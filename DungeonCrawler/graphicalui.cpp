#include "mainwindow.h"
#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QLabel>
#include <QTest>
#include <QPainter>
#include <vector>
#include "graphicalui.h"
#include "dungeoncrawler.h"
#include "startscreen.h"
#include "pit.h"

// ************************ constructor ***********************************************
GraphicalUI::GraphicalUI(){
    startscreen = new Startscreen(this);
    mainWindow = new MainWindow(this);
}

// ************************ getter-methods ********************************************
Startscreen *GraphicalUI::getStartscreen() const{
    return startscreen;
}

DungeonCrawler *GraphicalUI::getDungeonCrawler() const{
    return dungeonCrawler;
}

MainWindow *GraphicalUI::getMainWindow() const{
    return mainWindow;
}

// ************************ setter-methods ********************************************
void GraphicalUI::setDungeonCrawler(DungeonCrawler *newDungeonCrawler){
    dungeonCrawler = newDungeonCrawler;
}

// ************************ other methods *********************************************
void GraphicalUI::draw(Level *level){                                                               // used in constructor

    int length = this->getDungeonCrawler()->getLevel()->getLength();
    int width = this->getDungeonCrawler()->getLevel()->getWidth();
    mainWindow->getUi()->gridDungeon->setSpacing(0);

    int counter = 0;

    for( int r = 0; r < length; r++ ){
        for( int c = 0; c < width;  c++ ){

            QString tex = QString::fromStdString ( level->getTile(r, c)->getTexture() );            // load texture of Tile
            QPixmap* pixmapTile = new QPixmap;
            pixmapTile->load(tex);

            QLabel* tile = new QLabel(this->getMainWindow());                                       // load texture in Label - temp store
            tile->setPixmap(*pixmapTile);
            tile->setScaledContents(true);
            tile->lower();

            mainWindow->getUi()->gridDungeon->addWidget( tile, r, c );
            labels.push_back(tile);

            if(level->getTile(r, c)->hasCharacter()){
                character = new QLabel(this->getMainWindow());                                      // load texture of character
                QString tex2 = QString::fromStdString ( level->getCharacters()[0]->getTexture() );
                QPixmap* pixmapChar = new QPixmap;
                pixmapChar->load(tex2);
                pixmapChar->scaled(labels[counter]->size());

                QPainter p(pixmapTile);                                                             // show character in front of Tile
                p.drawPixmap(0,0,*pixmapChar);
                character->setPixmap(*pixmapTile);

                mainWindow->getUi()->gridDungeon->addWidget( character, r, c );                     // actual output
                character->setScaledContents(true);
                character->raise();
            }
            counter++;
        }
    }
    // :/Textures/Texturen-Paket/bloody_frame.png
}

void GraphicalUI::draw2(Level *level){                                                              // used to update playground

    int length = this->getDungeonCrawler()->getLevel()->getLength();
    int width = this->getDungeonCrawler()->getLevel()->getWidth();

    int counter = 0;

    for( int r = 0; r < length; r++ ){
        for( int c = 0; c < width;  c++ ){

            mainWindow->getUi()->gridDungeon->addWidget( labels[counter], r, c );
            if( r == level->getDoors()[0]->getRow() && c == level->getDoors()[0]->getColumn()){     // set door separately

                QString texDoor = QString::fromStdString ( level->getTile(r,c)->getTexture() );
                QPixmap* pixmapDoor = new QPixmap;
                pixmapDoor->load(texDoor);

                labels[counter]->setPixmap(*pixmapDoor);
            }

            if(level->getTile(r, c)->hasCharacter()){

                Tile* testPit = level->getTile(r,c);
                bool tileIsPit = (typeid(*testPit) == typeid(Pit));

                QPixmap* pixmapTile = new QPixmap;                                                   // load texture of Tile
                QString tex1 = QString::fromStdString ( level->getTile(r,c)->getTexture());
                pixmapTile->load(tex1);

                QString tex2 = QString::fromStdString ( level->getCharacters()[0]->getTexture() );  // load texture of character
                QPixmap* pixmapChar = new QPixmap;
                pixmapChar->load(tex2);
                pixmapChar->scaled(labels[counter]->size());

                if(tileIsPit){                                                                      // show character behind a pit,
                    pixmapTile->scaled(labels[counter]->size());

                    QPainter p(pixmapChar);
                    p.drawPixmap(0,0,*pixmapTile);

                    character->setPixmap(*pixmapChar);

                } else{                                                                             // but show character in front of a Tile(!= Pit)
                    QPainter p(pixmapTile);
                    p.drawPixmap(0,0,*pixmapChar);

                    character->setPixmap(*pixmapTile);
                }

                mainWindow->getUi()->gridDungeon->addWidget( character, r, c );                     // actual output
                character->setScaledContents(true);
                character->raise();
            }
            counter++;
        }
    }
}

int GraphicalUI::move(){
    QTest::qWait(50);
    QCoreApplication::processEvents();
    if( mainWindow->getNewEvent() ){
        mainWindow->setNewEvent(false);
        return mainWindow->getLastInput();
    }else{
        return 0;
    }

}

void GraphicalUI::startNewGame(){
    startscreen->hide();
    mainWindow->show();
}
