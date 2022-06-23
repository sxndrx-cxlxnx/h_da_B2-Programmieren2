#include "mainwindow.h"
#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QLabel>
#include <QTest>
#include <QPainter>
#include <QMessageBox>
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
void GraphicalUI::draw(Level *level){                                                                   // used in constructor

    int length = level->getLength();
    int width = level->getWidth();
    mainWindow->getUi()->gridDungeon->setSpacing(0);

    int counter = 0;

    for( int r = 0; r < length; r++ ){
        for( int c = 0; c < width;  c++ ){

            QString tex = QString::fromStdString ( level->getTile(r, c)->getTexture() );                // load texture of Tile
            QPixmap* pixmapTile = new QPixmap;
            pixmapTile->load(tex);

            QLabel* tile = new QLabel(this->getMainWindow());                                           // load texture in Label - temp store
            tile->setPixmap(*pixmapTile);
            tile->setScaledContents(true);
            tile->lower();

            //mainWindow->getUi()->gridDungeon->addWidget( tile, r, c );
            level->labels.push_back(tile);

            if(level->getTile(r, c)->hasCharacter()){
                level->getTile(r, c)->getCharacter()->label = new QLabel(/*this->getMainWindow()*/);                               // load texture of character
                QString tex2 = QString::fromStdString ( level->getTile(r,c)->getCharacter()->getTexture() );
                QPixmap* pixmapChar = new QPixmap;
                pixmapChar->load(tex2);
                pixmapChar->scaled(level->labels[counter]->size());

                QPainter p(pixmapTile);                                                                 // show character in front of Tile
                p.drawPixmap(0,0,*pixmapChar);
                level->getTile(r, c)->getCharacter()->label->setPixmap(*pixmapTile);

                //mainWindow->getUi()->gridDungeon->addWidget( level->character, r, c );                // actual output
                level->getTile(r, c)->getCharacter()->label->setScaledContents(true);
                level->getTile(r, c)->getCharacter()->label->raise();

                delete pixmapChar;

            }
            counter++;
            delete pixmapTile;
        }
    }
    // :/Textures/Texturen-Paket/bloody_frame.png
}

void GraphicalUI::draw2(Level *level){                                                                  // used to update playground

    int length = level->getLength();
    int width = level->getWidth();

    int counter = 0;

    for( int r = 0; r < length; r++ ){
        for( int c = 0; c < width;  c++ ){

            mainWindow->getUi()->gridDungeon->addWidget( level->labels[counter], r, c );
            level->labels[counter]->raise();
            if( level->getDoors().size() != 0 ){


                if( r == level->getDoors()[0]->getRow() && c == level->getDoors()[0]->getColumn() ){    // set door separately

                    QString texDoor = QString::fromStdString ( level->getTile(r,c)->getTexture() );
                    QPixmap* pixmapDoor = new QPixmap;
                    pixmapDoor->load(texDoor);

                    level->labels[counter]->setPixmap(*pixmapDoor);

                    delete pixmapDoor;
                }
            }
            if(level->getTile(r, c)->hasCharacter() ){
                if(level->getTile(r, c)->getCharacter()->label  == nullptr){

                    QString tex = QString::fromStdString ( level->getTile(r, c)->getTexture() );            // load texture of Tile
                    QPixmap* pixmapTile = new QPixmap;
                    pixmapTile->load(tex);

                    //delete level->character;
                    level->getTile(r, c)->getCharacter()->label = new QLabel(/*this->getMainWindow()*/);                           // load texture of character
                    QString tex2 = QString::fromStdString ( level->getTile(r,c)->getCharacter()->getTexture() );
                    QPixmap* pixmapChar = new QPixmap;
                    pixmapChar->load(tex2);
                    pixmapChar->scaled(level->labels[counter]->size());

                    QPainter p(pixmapTile);                                                             // show character in front of Tile
                    p.drawPixmap(0,0,*pixmapChar);
                    level->getTile(r, c)->getCharacter()->label->setPixmap(*pixmapTile);

                    //mainWindow->getUi()->gridDungeon->addWidget( level->character, r, c );            // actual output
                    level->getTile(r, c)->getCharacter()->label->setScaledContents(true);
                    level->getTile(r, c)->getCharacter()->label->raise();

                    delete pixmapChar;

                    delete pixmapTile;

                }else{
                    Tile* testPit = level->getTile(r,c);
                    bool tileIsPit = (typeid(*testPit) == typeid(Pit));

                    QPixmap* pixmapTile = new QPixmap;                                                  // load texture of Tile
                    QString tex1 = QString::fromStdString ( level->getTile(r,c)->getTexture());
                    pixmapTile->load(tex1);

                    QString tex2 = QString::fromStdString ( level->getTile(r,c)->getCharacter()->getTexture() );  // load texture of character
                    QPixmap* pixmapChar = new QPixmap;
                    pixmapChar->load(tex2);
                    pixmapChar->scaled(level->labels[counter]->size());

                    if( tileIsPit ){                                                                    // show character behind a pit,
                        pixmapTile->scaled(level->labels[counter]->size());

                        QPainter p(pixmapChar);
                        p.drawPixmap(0,0,*pixmapTile);

                        level->getTile(r, c)->getCharacter()->label->setPixmap(*pixmapChar);

                    } else{                                                                             // but show character in front of a Tile (!= Pit)
                        QPainter p(pixmapTile);
                        p.drawPixmap(0,0,*pixmapChar);

                        level->getTile(r, c)->getCharacter()->label->setPixmap(*pixmapTile);
                    }

                    mainWindow->getUi()->gridDungeon->addWidget( level->getTile(r, c)->getCharacter()->label , r, c );              // actual output
                    level->getTile(r, c)->getCharacter()->label->setScaledContents(true);
                    level->getTile(r, c)->getCharacter()->label->raise();

                    delete pixmapTile;
                    delete pixmapChar;
                }
            }
            counter++;
        }
    }
    QString qMessage = QString::fromStdString ( mainWindow->getStatusMessage() );
    //mainWindow->statusMessage = qMessage;
    mainWindow->getUi()->statusbar->showMessage(qMessage);
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

void GraphicalUI::messageBox(){
    QMessageBox msgBox;

    if( dungeonCrawler->getLevel()->getCharacters()[0]->getHitpoints() <= 0 ){
        msgBox.setWindowTitle( "Game lost");
        msgBox.setText("You were cuddled too hard by a zombie.");
    } else{
        msgBox.setWindowTitle( "Game won");
        msgBox.setText("You drowned in gold when you fell into the lootchest.");
    }
    msgBox.exec();
}

void GraphicalUI::cancel(){
    QMessageBox msgBox;

    msgBox.setWindowTitle( "Error 404");
    msgBox.setText("*******************************************\n\n"
                   "         Button not found ...\n\n"
                   "        *confused_Zombie_Noises*\n\n"
                   "*******************************************");

    msgBox.exec();
}

void GraphicalUI::cancelTry2(){
    QMessageBox msgBox;

    msgBox.setWindowTitle( "Error 404 - solved");
    msgBox.setText("*******************************************\n\n"
                   "         found the Button now ...\n\n"
                   "        *happy_Zombie_Noises*\n\n"
                   "*******************************************");

    msgBox.exec();
}
