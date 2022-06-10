#include "graphicalui.h"
#include <QLabel>
#include "dungeoncrawler.h"
#include "startscreen.h"
#include "mainwindow.h"
#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QTest>
#include <vector>
#include <QPainter>
#include "pit.h"

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

    int counter = 0;

    for( int r = 0; r < length; r++ ){
        for( int c = 0; c < width;  c++ ){

            QString tex = QString::fromStdString ( level->getTile(r, c)->getTexture() );
            QPixmap* pixmapTile = new QPixmap;
            pixmapTile->load(tex);

            QLabel* tile = new QLabel(this->getMainWindow());           //zwischenspeichern
            tile->setPixmap(*pixmapTile);
            tile->setScaledContents(true);
//            tile->resize(this->getMainWindow()->size());
            tile->lower();

            mainWindow->getUi()->gridDungeon->addWidget( tile, r, c );

            labels.push_back(tile);


            if(level->getTile(r, c)->hasCharacter()){       //QPainter, in QPixmap

               /* tex = QString::fromStdString ( level->getCharacters()[0]->getTexture() );
                QPixmap* pixmap2 = new QPixmap;
                pixmap2->load(tex);

                character = new QLabel();
                character->setPixmap(*pixmap2);

                mainWindow->getUi()->gridDungeon->addWidget( character, r, c );
                character->setScaledContents(true);
   //             character->resize(tile->size());
                character->raise();
                */

//                QPixmap* pixmapTile = new QPixmap;
//                QString tex1 = QString::fromStdString ( level->getTile(r,c)->getTexture());
//                pixmapTile->load(tex1);

                character = new QLabel(this->getMainWindow());
                QString tex2 = QString::fromStdString ( level->getCharacters()[0]->getTexture() );
                QPixmap* pixmapChar = new QPixmap;
                pixmapChar->load(tex2);


                pixmapChar->scaled(labels[counter]->size());

                QPainter p(pixmapTile);
                p.drawPixmap(0,0,*pixmapChar);

                character->setPixmap(*pixmapTile);

                mainWindow->getUi()->gridDungeon->addWidget( character, r, c );
                character->setScaledContents(true);
                character->raise();
            }
            counter++;
        }
    }
}

void GraphicalUI::draw2(Level *level){

    int length = this->getDungeonCrawler()->getLevel()->getLength();
    int width = this->getDungeonCrawler()->getLevel()->getWidth();

    int counter = 0;

    for( int r = 0; r < length; r++ ){
        for( int c = 0; c < width;  c++ ){

            mainWindow->getUi()->gridDungeon->addWidget( labels[counter], r, c );
            if( r == level->getDoors()[0]->getRow() && c == level->getDoors()[0]->getColumn()){

                QString texDoor = QString::fromStdString ( level->getTile(r,c)->getTexture() );
                QPixmap* pixmapDoor = new QPixmap;
                pixmapDoor->load(texDoor);

                labels[counter]->setPixmap(*pixmapDoor);

            }


            if(level->getTile(r, c)->hasCharacter()){

                Tile* testPit = level->getTile(r,c);
                bool tileIsPit = (typeid(*testPit) == typeid(Pit));

                if(tileIsPit){

                    QPixmap* pixmapTile = new QPixmap;
                    QString tex1 = QString::fromStdString ( level->getTile(r,c)->getTexture());
                    pixmapTile->load(tex1);
                    pixmapTile->scaled(labels[counter]->size());

                    QString tex2 = QString::fromStdString ( level->getCharacters()[0]->getTexture() );
                    QPixmap* pixmapChar = new QPixmap;
                    pixmapChar->load(tex2);
                    pixmapChar->scaled(labels[counter]->size());

                    QPainter p(pixmapChar);
                    p.drawPixmap(0,0,*pixmapTile);

                    //QLabel* character = new QLabel(this->getMainWindow());
                    character->setPixmap(*pixmapChar);

                    mainWindow->getUi()->gridDungeon->addWidget( character, r, c );
                    character->setScaledContents(true);
                    character->raise();

                }else{

                    QPixmap* pixmapTile = new QPixmap;
                    QString tex1 = QString::fromStdString ( level->getTile(r,c)->getTexture());
                    pixmapTile->load(tex1);

                    QString tex2 = QString::fromStdString ( level->getCharacters()[0]->getTexture() );
                    QPixmap* pixmapChar = new QPixmap;
                    pixmapChar->load(tex2);
                    pixmapChar->scaled(labels[counter]->size());

                    QPainter p(pixmapTile);
                    p.drawPixmap(0,0,*pixmapChar);

                    //QLabel* character = new QLabel(this->getMainWindow());
                    character->setPixmap(*pixmapTile);

                    mainWindow->getUi()->gridDungeon->addWidget( character, r, c );
                    character->setScaledContents(true);
                    character->raise();
                }
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
