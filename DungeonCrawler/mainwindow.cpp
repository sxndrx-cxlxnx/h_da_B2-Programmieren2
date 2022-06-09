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

//    QPushButton* buttonUL = new QPushButton;
//    QLabel* UL = new QLabel;
//    UL->setPixmap(QPixmap(":/Textures/Texturen-Paket/arrow_up_left.png"));
//    buttonUL->setStyleSheet("backgroungimage");

//    QPushButton* buttonU = new QPushButton;
//    QLabel* U = new QLabel;
//    U->setPixmap(QPixmap(":/Textures/Texturen-Paket/arrow_up.png"));

//    QPushButton* buttonUR = new QPushButton;
//    QLabel* UR = new QLabel;
//    UR->setPixmap(QPixmap(":/Textures/Texturen-Paket/arrow_up_right.png"));

//    QPushButton* buttonL = new QPushButton;
//    QLabel* L = new QLabel;
//    L->setPixmap(QPixmap(":/Textures/Texturen-Paket/arrow_left.png"));

//    QPushButton* buttonStay = new QPushButton;
//    QLabel* Stay = new QLabel;
//    Stay->setPixmap(QPixmap(":/Textures/Texturen-Paket/arrow_skip.png"));

//    QPushButton* buttonR = new QPushButton;
//    QLabel* R = new QLabel;
//    R->setPixmap(QPixmap(":/Textures/Texturen-Paket/arrow_right.png"));

//    QPushButton* buttonDL = new QPushButton;
//    QLabel* DL = new QLabel;
//    DL->setPixmap(QPixmap(":/Textures/Texturen-Paket/arrow_down_left.png"));

//    QPushButton* buttonD = new QPushButton;
//    QLabel* D = new QLabel;
//    D->setPixmap(QPixmap(":/Textures/Texturen-Paket/arrow_down.png"));

//    QPushButton* buttonDR = new QPushButton;
//    QLabel* DR = new QLabel;
//    DR->setPixmap(QPixmap(":/Textures/Texturen-Paket/arrow_down_right.png"));

//    QString tex = QString::fromStdString ( this->getDungeonCrawler()->getLevel()->getTile(r, c)->getTexture() );
//    QPixmap* pixmap = new QPixmap;
//    pixmap->load(tex);
//    QLabel* tile = new QLabel();
//    tile->setPixmap(*pixmap);
//    tile->setScaledContents(true);

//    mainWindow->getUi()->gridDungeon->addWidget( tile, r, c );


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

