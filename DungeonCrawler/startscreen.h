#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>

namespace Ui {
class Startscreen;
}
class GraphicalUI;

class Startscreen : public QDialog{

    Q_OBJECT

public:
    // constructor
    explicit Startscreen(GraphicalUI* pgui, QWidget *parent = nullptr);

    // destructor
    ~Startscreen();

public slots:
    void buttonPushed();

private:
    // attributes
    Ui::Startscreen *ui;
    GraphicalUI* gui;
};

#endif // STARTSCREEN_H
