#ifndef GRAPHICALUI_H
#define GRAPHICALUI_H

#include "abstractui.h"
#include "controller.h"
#include <QMainWindow>
#include <QWidget>
#include <QLabel>

class MainWindow;
class Startscreen;
class DungeonCrawler;

class GraphicalUI : public AbstractUI, public Controller{
public:
    // construktor
    GraphicalUI();

    // getter - methods
    Startscreen *getStartscreen() const;
    DungeonCrawler *getDungeonCrawler() const;
    MainWindow *getMainWindow() const;

    // setter - methods
    void setDungeonCrawler(DungeonCrawler *newDungeonCrawler);

    // other methods
    virtual void draw(Level* level) override;                       // used in constructor
    void draw2(Level* level);                                       // used to update playground
    virtual int move() override;
    void startNewGame();

private:
    // attributes
    Startscreen* startscreen;
    MainWindow* mainWindow;
    DungeonCrawler* dungeonCrawler;
    std::vector<QLabel*> labels;
    QLabel* character;
};

#endif // GRAPHICALUI_H
