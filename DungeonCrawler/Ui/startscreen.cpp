#include "startscreen.h"
#include "ui_startscreen.h"
#include <QPushButton>
#include <QDialog>
#include "graphicalui.h"

// ************************ constructor ***********************************************
Startscreen::Startscreen(GraphicalUI* pgui, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Startscreen)
{
    ui->setupUi(this);
    gui = pgui;
    connect(ui->newGameButton, SIGNAL(clicked()), this, SLOT(buttonPushed()));
    connect(ui->loadLevelButton, SIGNAL(clicked()), this, SLOT(loadButtonPushed()));
}

// ************************ destructor ************************************************
Startscreen::~Startscreen(){
    delete ui;
}

// ************************ other methods *********************************************
void Startscreen::buttonPushed(){
    gui->startNewGame();
}

void Startscreen::loadButtonPushed(){
    gui->loadLevel();
}
