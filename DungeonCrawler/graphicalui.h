#ifndef GRAPHICALUI_H
#define GRAPHICALUI_H

#include "abstractui.h"
#include "controller.h"
//#include "startscreen.h"
#include <QMainWindow>
#include <QWidget>

class MainWindow;
class Startscreen;

class DungeonCrawler;

class GraphicalUI : public AbstractUI, public Controller{
public:
    GraphicalUI();
    virtual void draw(Level* level) override;
    virtual int move() override;
    void startNewGame();

    Startscreen *getStartscreen() const;
    DungeonCrawler *getDungeonCrawler() const;
    MainWindow *getMainWindow() const;

    void setDungeonCrawler(DungeonCrawler *newDungeonCrawler);

private:
    Startscreen* startscreen;
    MainWindow* mainWindow;
    DungeonCrawler* dungeonCrawler;
};

#endif // GRAPHICALUI_H
