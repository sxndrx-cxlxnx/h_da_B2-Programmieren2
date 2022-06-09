#include "startscreen.h"
#include "ui_startscreen.h"
#include <QPushButton>
#include <QDialog>
#include "graphicalui.h"

Startscreen::Startscreen(GraphicalUI* pgui, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Startscreen)
{
    ui->setupUi(this);
    gui = pgui;
    connect(ui->newGameButton, SIGNAL(clicked()), this, SLOT(buttonPushed()));
}

Startscreen::~Startscreen(){
    delete ui;
}

void Startscreen::buttonPushed(){
    gui->startNewGame();
}
