#include "startscreen.h"
#include "ui_startscreen.h"
#include <QPushButton>
#include <QDialog>

Startscreen::Startscreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Startscreen)
{
    ui->setupUi(this);
}

Startscreen::~Startscreen()
{
    delete ui;
}
