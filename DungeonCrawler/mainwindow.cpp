#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "graphicalui.h"
#include "dungeoncrawler.h"
#include <QLabel>
#include <QPushButton>
#include <sstream>

// ************************ constructor ***********************************************
MainWindow::MainWindow(GraphicalUI* pgui, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gui = pgui;
    newEvent = false;

    connect(ui->buttonUL, SIGNAL(clicked()), this, SLOT(buttonUL()));
    connect(ui->buttonU,  SIGNAL(clicked()), this, SLOT(buttonU()));
    connect(ui->buttonUR, SIGNAL(clicked()), this, SLOT(buttonUR()));
    connect(ui->buttonL,  SIGNAL(clicked()), this, SLOT(buttonL()));
    connect(ui->buttonS,  SIGNAL(clicked()), this, SLOT(buttonS()));
    connect(ui->buttonR,  SIGNAL(clicked()), this, SLOT(buttonR()));
    connect(ui->buttonDL, SIGNAL(clicked()), this, SLOT(buttonDL()));
    connect(ui->buttonD,  SIGNAL(clicked()), this, SLOT(buttonD()));
    connect(ui->buttonDR, SIGNAL(clicked()), this, SLOT(buttonDR()));

    connect(ui->beenden, SIGNAL(clicked()), this, SLOT(closeWindow()));
    connect(ui->storeLevel, SIGNAL(clicked()), this, SLOT(storeLevel()));
}

// ************************ destructor ************************************************
MainWindow::~MainWindow(){
    delete ui;
}

// ************************ getter-methods ********************************************
Ui::MainWindow *MainWindow::getUi() const{
    return ui;
}

int MainWindow::getLastInput() const{
    return lastInput;
}

bool MainWindow::getNewEvent() const{
    return newEvent;
}

GraphicalUI *MainWindow::getGui(){
    return gui;
}

std::string MainWindow::getStatusMessage(){
    Character* currentCharacter = getGui()->getDungeonCrawler()->getLevel()->getCharacters()[0];
    std::stringstream strength;
    std::stringstream stamina;
    std::stringstream hitpoints;

    strength << currentCharacter->getStrength();
    stamina << currentCharacter ->getStamina();

    if(currentCharacter->getHitpoints() < 0){                   // prevent of negativ Hitpoints in Statusbar
        hitpoints << 0;
    } else{
        hitpoints << currentCharacter->getHitpoints();
    }

    std::string message;
    message = "Strength: " + strength.str() + "\t Stamina: " + stamina.str() +"\t Hitpoints: " + hitpoints.str();
    return message;
}

// ************************ setter-methods ********************************************
void MainWindow::setNewEvent(bool newNewEvent){
    newEvent = newNewEvent;
}

// ************************ Buttons / Slots *******************************************
void MainWindow::buttonUL(){                                                                        // up - left
    lastInput = 7;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

void MainWindow::buttonU(){                                                                         // up
    lastInput = 8;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

void MainWindow::buttonUR(){                                                                        // up - right
    lastInput = 9;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

void MainWindow::buttonL(){                                                                         // left
    lastInput = 4;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

void MainWindow::buttonS(){                                                                         // stay
    lastInput = 5;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

void MainWindow::buttonR(){                                                                         // right
    lastInput = 6;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

void MainWindow::buttonDL(){                                                                        // down - left
    lastInput = 1;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

void MainWindow::buttonD(){                                                                         // down
    lastInput = 2;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

void MainWindow::buttonDR(){                                                                        // downRight
    lastInput = 3;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

void MainWindow::closeWindow(){
    lastInput = 0;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

void MainWindow::storeLevel(){
    this->gui->storeLevel();
}
