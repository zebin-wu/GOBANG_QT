#include "scorewidget.h"
#include "ui_scorewidget.h"
#include "gamemodel.h"
#include <QPainter>
#include <QStyleOption>

using namespace Game;

ScoreWidget::ScoreWidget(const QSize &size, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreWidget)
{
    ui->setupUi(this);

    setMinimumSize(size); //设置大小
    //setAutoFillBackground(true);
    setStyleSheet("background: rgba(240, 240, 240, 40%)");

    connect(ui->againBtn, &QPushButton::clicked,
            [this]()
            {
                emit againSignal();
            }
            );
    connect(ui->homeBtn, &QPushButton::clicked,
            [this]()
            {
                emit homeSignal();
            }
            );
}

void ScoreWidget::setLabel(int winPlayer)
{
    if(winPlayer == WPlayer)
        ui->textLable->setText("白棋玩家获胜！!");
    else if(winPlayer == BPlayer)
        ui->textLable->setText("黑棋玩家获胜！！");
    else
        ui->textLable->setText("平局！！");
}

ScoreWidget::~ScoreWidget()
{
    delete ui;
}
