#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "graphicalui.h"
#include "dungeoncrawler.h"
#include <QLabel>
#include <QPushButton>

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

MainWindow::~MainWindow(){
    delete ui;
}

Ui::MainWindow *MainWindow::getUi() const{
    return ui;
}

int MainWindow::getLastInput() const{
    return lastInput;
}

void MainWindow::setNewEvent(bool newNewEvent)
{
    newEvent = newNewEvent;
}

bool MainWindow::getNewEvent() const
{
    return newEvent;
}

// ******* Buttons *******
void MainWindow::buttonUL(){
    lastInput = 7;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

void MainWindow::buttonU(){
    lastInput = 8;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

void MainWindow::buttonUR(){
    lastInput = 9;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

void MainWindow::buttonL(){
    lastInput = 4;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

void MainWindow::buttonS(){
    lastInput = 5;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

void MainWindow::buttonR(){
    lastInput = 6;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

void MainWindow::buttonDL(){
    lastInput = 1;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

void MainWindow::buttonD(){
    lastInput = 2;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

void MainWindow::buttonDR(){
    lastInput = 3;
    this->gui->getDungeonCrawler()->getLevel()->getCharacters()[0]->setLastDirection(lastInput);
    newEvent = true;
}

