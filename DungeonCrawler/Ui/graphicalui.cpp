#include "mainwindow.h"
#include <QMainWindow>
#include "ui_mainwindow.h"

#include <QLabel>
#include <QTest>
#include <QPainter>
#include <QMessageBox>
#include <vector>

#include "graphicalui.h"
#include "../Tiles/levelchanger.h"
#include "../Other/dungeoncrawler.h"
#include "startscreen.h"
#include "../Tiles/pit.h"

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

            level->labels.push_back(tile);

            if(level->getTile(r, c)->hasCharacter()){                                                   // if Tile has character
                level->getTile(r, c)->getCharacter()->label = new QLabel();                             // load texture of character
                QString tex2 = QString::fromStdString ( level->getTile(r,c)->getCharacter()->getTexture() );
                QPixmap* pixmapChar = new QPixmap;
                pixmapChar->load(tex2);
                pixmapChar->scaled(level->labels[counter]->size());

                QPainter p(pixmapTile);                                                                 // show character in front of Tile
                p.drawPixmap(0,0,*pixmapChar);
                level->getTile(r, c)->getCharacter()->label->setPixmap(*pixmapTile);

                level->getTile(r, c)->getCharacter()->label->setScaledContents(true);                   // actual output
                level->getTile(r, c)->getCharacter()->label->raise();

                delete pixmapChar;
            }                                                                                           // END - if Tile has Character
            counter++;
            delete pixmapTile;
        }
    }
}

void GraphicalUI::draw2(Level *level){                                                                  // used to update playground

    int length = level->getLength();
    int width = level->getWidth();

    int counter = 0;

    for( int r = 0; r < length; r++ ){
        for( int c = 0; c < width;  c++ ){

            mainWindow->getUi()->gridDungeon->addWidget( level->labels[counter], r, c );
            level->labels[counter]->raise();
            if( level->getDoors().size() != 0 ){                                                        // set doors separately

                if( r == level->getDoors()[0]->getRow() && c == level->getDoors()[0]->getColumn() ){

                    QString texDoor = QString::fromStdString ( level->getTile(r,c)->getTexture() );
                    QPixmap* pixmapDoor = new QPixmap;
                    pixmapDoor->load(texDoor);

                    level->labels[counter]->setPixmap(*pixmapDoor);

                    delete pixmapDoor;
                }
            }                                                                                           // END - set doors separately

            if(level->getTile(r, c)->hasCharacter() ){                                                  // if Tile has Character

                QString texTile = QString::fromStdString ( level->getTile(r, c)->getTexture() );        // load texture of Tile
                QPixmap* pixmapTile = new QPixmap;
                pixmapTile->load(texTile);

                QString texChar = QString::fromStdString ( level->getTile(r,c)->getCharacter()->getTexture() );  // load texture of character
                QPixmap* pixmapChar = new QPixmap;
                pixmapChar->load(texChar);
                pixmapChar->scaled(level->labels[counter]->size());

                Tile* testPit = level->getTile(r,c);
                bool tileIsPit = (typeid(*testPit) == typeid(Pit));

                if( tileIsPit ){                                                                        // show character behind a pit,
                    pixmapTile->scaled(level->labels[counter]->size());

                    QPainter painter(pixmapChar);
                    painter.drawPixmap(0,0,*pixmapTile);

                    level->getTile(r, c)->getCharacter()->label->setPixmap(*pixmapChar);
                } else{                                                                                 // but show character behind a tile (!= pit)
                    if(level->getTile(r, c)->getCharacter()->label  == nullptr){                        // if Label == nullptr
                        level->getTile(r, c)->getCharacter()->label = new QLabel();                     // set new Label
                    }
                    QPainter painter(pixmapTile);
                    painter.drawPixmap(0,0,*pixmapChar);

                    level->getTile(r, c)->getCharacter()->label->setPixmap(*pixmapTile);                // actual output
                }                                                                                       // END - show Character behind Tile
            mainWindow->getUi()->gridDungeon->addWidget( level->getTile(r, c)->getCharacter()->label , r, c );
            level->getTile(r, c)->getCharacter()->label->setScaledContents(true);
            level->getTile(r, c)->getCharacter()->label->raise();

            delete pixmapTile;
            delete pixmapChar;
        }
            counter++;
        }
    }
    QString qMessage = QString::fromStdString ( mainWindow->getStatusMessage() );
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

void GraphicalUI::loadLevel( bool isStandardLevel ){

    std::string path1 = "";
    std::string path2 = "";

    if( isStandardLevel ){
        path1 = "../standardLevel1.json";
        path2 = "../standardLevel2.json";
    } else{
        path1 = "../tempLevel1.json";
        path2 = "../tempLevel2.json";
    }

    Level* level1 = new Level( this->getDungeonCrawler()->getGraphicalui(), path1, true, nullptr );
    dungeonCrawler->setLevel( level1 );                                                 // set current Level in DungeonCrawler ( Level with Character )
    Level* level2 = new Level( this->getDungeonCrawler()->getGraphicalui(), path2, false, level1->getCharacters()[0] );

    level1->getLevelchanger()->setDestiny( level2->getLevelchanger() );
    level2->getLevelchanger()->setDestiny( level1->getLevelchanger() );

    level1->getLevelchanger()->setLevel( level2 );
    level2->getLevelchanger()->setLevel( level1 );

    level1->getLevelchanger()->setDungeonCrawler( dungeonCrawler );                               // give levelchanger this "dungeonCrawler" to know for later methods
    level2->getLevelchanger()->setDungeonCrawler( dungeonCrawler );

    //    levelList->push_back(level1);
    //    levelList->push_back(level2);


    draw(level1);                                                           // first draw - both levels
    draw(level2);

    draw2(level1);                                                         // draw startlevel above

    startscreen->hide();
    mainWindow->show();

    dungeonCrawler->everythingIsReady = true;

}

void GraphicalUI::storeLevel(){
    dungeonCrawler->store( dungeonCrawler->getLevel(), "../tempLevel1.json" );
    dungeonCrawler->store( dungeonCrawler->getLevel()->getLevelchanger()->getLevel(), "../tempLevel2.json" );
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
