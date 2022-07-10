#ifndef GRAPHICALUI_H
#define GRAPHICALUI_H

#include "abstractui.h"
#include "../Controller/controller.h"
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
    void draw(Level* level) override;           // used in constructor
    void draw2(Level* level);                   // used to update playground
    int move() override;
    void loadLevel( bool isStandardLevel );
    void storeLevel();
    void messageBox();
    void cancel();
    void cancelTry2();
    std::string getControllerName() override { return "GraphicalUI"; };
    std::string getMovePattern() override { return "error"; };
    unsigned int getWhereInMovePattern() override { return 10; };

private:
    // attributes
    Startscreen* startscreen;
    MainWindow* mainWindow;
    DungeonCrawler* dungeonCrawler;
};

#endif // GRAPHICALUI_H
