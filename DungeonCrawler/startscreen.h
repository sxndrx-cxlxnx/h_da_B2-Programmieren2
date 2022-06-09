#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>

namespace Ui {
class Startscreen;
}
class GraphicalUI;

class Startscreen : public QDialog
{
    Q_OBJECT

public:
    explicit Startscreen(GraphicalUI* pgui, QWidget *parent = nullptr);
    ~Startscreen();

public slots:
        void buttonPushed();

private:
    Ui::Startscreen *ui;
    GraphicalUI* gui;
};

#endif // STARTSCREEN_H
