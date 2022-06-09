#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GraphicalUI;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(GraphicalUI* pgui, QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *getUi() const;

    int getLastInput() const;

private:
    Ui::MainWindow *ui;
    GraphicalUI* gui;
    int lastInput;

public slots:
    void buttonUL();
    void buttonU();
    void buttonUR();
    void buttonL();
    void buttonS();
    void buttonR();
    void buttonDL();
    void buttonD();
    void buttonDR();
};

#endif // MAINWINDOW_H
