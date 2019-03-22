#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QtWidgets/QWidget>
#include <gamemodel.h>

using namespace Game;

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget();
    void initGame(Game_Mode mode);  //初始化游戏
    void endGame();                 //结束游戏
    void again();                   //再来一次
protected:
    void paintEvent(QPaintEvent *event); //重写绘画事件
    void mouseMoveEvent(QMouseEvent *event); //重写鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event); //重写鼠标单击事件
signals:
    void winSignal(int winPlayer);  //胜利消息
public slots:
    void AIPLaySlot();
private:
    GameModel *game;
    int clickPosX;     //鼠标指针
    int clickPosY;
    int AIDelay;

    void dealWin();    //处理输赢
};

#endif // GAMEWIDGET_H
