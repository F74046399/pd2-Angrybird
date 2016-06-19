#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QWidget>
#include <QIcon>
#include <QCursor>

#include "gameitem.h"
#include "land.h"
#include "bird.h"
#include "sling.h"
#include "enemy.h"
#include "barrier.h"
#include "bbird.h"
#include "wbird.h"
#include "ybird.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void generateElement();
    void destory();
    int num=0;
    int count=1;
    int up=0;
    int a,b;
    float c;
    float x1,y1;
    float xb,yb;
    float mouseX;
    float mouseY;
    float Vx,Vy;
    bool onSling=true;
    bool shoot=true;
    bool done=true;
    bool canMove=true;
    bool skill=true;
    bool pigchange=true;
    bool torestart=true;
    int alivebird[4]={0};

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void Restart();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    QLabel *slingshot;
    Bird *birdie[4];
    Enemy *enemy[2];
    Bar *bar[4];
    QLabel *number;
    QLabel *score;
    QLabel *life1;
    QLabel *life[5];
    sling *slingbox;
    QPushButton *exit;
    QPushButton *restart;
    bool S1,S2;
    float Vxe,Vye,Vxe1,Vye1;




};

#endif // MAINWINDOW_H
