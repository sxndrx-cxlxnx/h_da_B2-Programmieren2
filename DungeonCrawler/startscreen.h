#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>

namespace Ui {
class Startscreen;
}

class Startscreen : public QDialog
{
    Q_OBJECT

public:
    explicit Startscreen(QWidget *parent = nullptr);
    ~Startscreen();

private:
    Ui::Startscreen *ui;
};

#endif // STARTSCREEN_H
