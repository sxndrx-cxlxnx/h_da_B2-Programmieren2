#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GraphicalUI;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{

    Q_OBJECT

public:
    // constructor
    explicit MainWindow(GraphicalUI* pgui, QWidget *parent = nullptr);

    // destructor
    ~MainWindow();

    // getter - methods
    Ui::MainWindow *getUi() const;
    int getLastInput() const;
    bool getNewEvent() const;
    GraphicalUI* getGui();
    std::string getStatusMessage();

    // setter - methods
    void setNewEvent(bool newNewEvent);

    GraphicalUI *getGui() const;

private:
    // attributes
    Ui::MainWindow *ui;
    GraphicalUI* gui;
    int lastInput;
    bool newEvent;
    QString statusMessage/*[getGui()->getDungeonCrawler()->getLevel()->getCharacters().size()]*/;

public slots:                       // buttons: up, down, left, right and stay
    void buttonUL();
    void buttonU();
    void buttonUR();
    void buttonL();
    void buttonS();
    void buttonR();
    void buttonDL();
    void buttonD();
    void buttonDR();

    void closeWindow();
};

#endif // MAINWINDOW_H
