#ifndef GRAPHICALUI_H
#define GRAPHICALUI_H

#include "abstractui.h"
#include "controller.h"
#include <QMainWindow>
#include <QWidget>

class GraphicalUI : public AbstractUI, public Controller{
public:
    GraphicalUI();
    virtual void draw(Level* level) override;
    virtual int move() override;

public slots:
    void startNewGame(QWidget *button);
};

#endif // GRAPHICALUI_H
