#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "graphicalui.h"
#include "dungeoncrawler.h"
#include <QLabel>
#include <QPushButton>

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

