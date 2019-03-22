#include "widget.h"
#include "ui_widget.h"

#ifdef DEBUG
#include <QDebug>
#endif //DEBUG

#include "gamemodel.h"
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //scoreWidget = nullptr;
    ui->setupUi(this);

    setMinimumSize(playWidget.size());

    playWidget.setParent(this);  //设置游戏界面
    playWidget.hide();           //设置隐藏
    int cx = (width() - playWidget.width()) / 2;
    int cy = (height() - playWidget.height()) / 2;
    playWidget.move(cx, cy);
    //评分界面
    scoreWidget = new ScoreWidget(playWidget.size(), this);
    scoreWidget->hide();
    //设置按钮
    connect(ui->pushButton_pvp, &QPushButton::clicked,    //PVP
            [this]()
            {
                playWidget.show();
                ui->StartWidget->hide();
                playWidget.gameWidget.initGame(PVP);
            }
            );
    connect(ui->pushButton_pve, &QPushButton::clicked,    //PVE
            [this]()
            {
                playWidget.show();
                ui->StartWidget->hide();
                playWidget.gameWidget.initGame(PVE);
            }
            );
    connect(&playWidget.gameWidget, &GameWidget::winSignal,          //WIN
            [this](int winPlayer)
            {
                int cx = (width() - scoreWidget->width()) / 2;
                int cy = (height() - scoreWidget->height()) / 2;
                scoreWidget->move(cx, cy);
                scoreWidget->setLabel(winPlayer);
                scoreWidget->show();
            }
            );
    connect(scoreWidget, &ScoreWidget::againSignal,        //AGAIN
            [this]()
            {
                playWidget.gameWidget.again();
                scoreWidget->hide();
            }
            );
    connect(scoreWidget, &ScoreWidget::homeSignal,         //HOME
            [this]()
            {
                playWidget.hide();
                playWidget.gameWidget.endGame();

                scoreWidget->hide();
                ui->StartWidget->show();
            }
            );
}

void Widget::resizeEvent(QResizeEvent *event) //重写调整窗口事件
{
    Q_UNUSED(event);

    int cx = (width() - playWidget.width()) / 2;
    int cy = (height() - playWidget.height()) / 2;
    playWidget.move(cx, cy);
    if(scoreWidget == nullptr)  return;
    cx = (width() - scoreWidget->width()) / 2;
    cy = (height() - scoreWidget->height()) / 2;
    scoreWidget->move(cx, cy);
#ifdef DEBUG
    qDebug() << cx << cy;
#endif //DEBUG
}
Widget::~Widget()
{
    delete ui;
    delete scoreWidget;
}
