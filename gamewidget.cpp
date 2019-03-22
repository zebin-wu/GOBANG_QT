#include "gamewidget.h"
#include <QPainter>
#include <QBrush>
#include <QMouseEvent>
#include <QTimer>


//#define DEBUG

#ifdef DEBUG
#include <QDebug>
#endif //DEBUG

const int BoardMargin = 30;  //边缘间距
const int BlockSize = 40;    //方块大小
const int Radius = 15;       //落子半径
const int MarkSize = 6;      //标记点大小

GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    AIDelay = 500;
    setFixedSize(BoardMargin * 2 + BlockSize * (BOARD_LEN - 1),
                 BoardMargin * 2 + BlockSize * (BOARD_LEN - 1));  //设置Widget的大小
    setMouseTracking(true);
    update(); //刷新界面
}

GameWidget::~GameWidget()
{
    if(game) delete game;
    game = nullptr;
}

void GameWidget::initGame(Game_Mode mode)  //初始化游戏
{
    if(mode == PVP) game = new GameModel(PVP);
    else            game = new GameModel(PVE);
}

void GameWidget::endGame()
{
    if(game) delete game;
    game = nullptr;
}

void GameWidget::again()
{
    Game_Mode mode = game->mode();
    endGame();
    initGame(mode);
}

void GameWidget::paintEvent(QPaintEvent *event) //重写绘画事件
{
    QPainter painter(this);
    //抗锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);
    //绘制方格
    for(int i = 0; i < BOARD_LEN; i++)
    {
        painter.drawLine(BoardMargin + BlockSize * i, BoardMargin,
                         BoardMargin + BlockSize * i, size().height() - BoardMargin);
        painter.drawLine(BoardMargin , BoardMargin + BlockSize * i,
                         size().width() - BoardMargin, BoardMargin + BlockSize * i);
    }
    //使用画刷
    QBrush brush;
    brush.setStyle(Qt::SolidPattern); //设置成填充模式
    //绘制鼠标落点
    if(game->player() == WPlayer)
        brush.setColor(Qt::white);
    else
        brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.drawRect(BoardMargin + BlockSize * clickPosX - MarkSize / 2,
                        BoardMargin + BlockSize * clickPosY - MarkSize / 2,
                        MarkSize, MarkSize);
    //绘制棋子
    int value;
    for(int i = 0; i < BOARD_LEN; i++)
    {
        for(int j = 0; j < BOARD_LEN; j++)
        {
            value = game->getRole(j, i);
            if     (value == WRITE) brush.setColor(Qt::white);
            else if(value == BLACK) brush.setColor(Qt::black);
            else                    continue;
            painter.setBrush(brush);
            painter.drawEllipse(BoardMargin + BlockSize * j - Radius,
                                BoardMargin + BlockSize * i - Radius,
                                Radius * 2, Radius * 2);
        }
    }
}

void GameWidget::mouseMoveEvent(QMouseEvent *event) //重写鼠标移动事件
{
    int PosX = (event->x() - BoardMargin / 2)/BlockSize; //获得位置
    int PosY = (event->y() - BoardMargin / 2)/BlockSize;
    //如果位置与上一次相同则不操作
    if(clickPosX == PosX && clickPosY == PosY)
        return;
    //刷新
    clickPosX = PosX;
    clickPosY = PosY;
    update();
}

void GameWidget::mouseReleaseEvent(QMouseEvent *event) //重写鼠标单击事件
{
    //判断是否可以下棋
    if(game->getRole(clickPosX, clickPosY) != EMPTY)
        return;
    //判断如果玩家是ai则不下棋
    if(game->mode() == PVE && game->player() != game->gamer())
        return;
    //下棋
    game->gamerPlay(clickPosX, clickPosY);
    update();
    dealWin();
    //ai下棋
    if(game->mode() != PVE) return;
    QTimer::singleShot(AIDelay, this, &GameWidget::AIPLaySlot);
}

void GameWidget::AIPLaySlot()
{
    game->AIPlay();
    update();
    dealWin();
}

void GameWidget::dealWin()    //处理输赢
{
    //处理输赢
    int status = game->status();
    if(status == WIN)
        emit winSignal(game->player());
    else if(status == DEAD)
        emit winSignal(DEAD);
}


