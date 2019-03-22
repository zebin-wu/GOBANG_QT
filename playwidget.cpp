#include "playwidget.h"

#include <QLayout>
#include <QPushButton>

PlayWidget::PlayWidget(QWidget *parent) :QWidget(parent)
{
    gameWidget.setParent(this);
    //布局
    QVBoxLayout *mainLayout = new QVBoxLayout;   //主布局
    QHBoxLayout *topBarLayout = new QHBoxLayout; //顶栏布局
    QHBoxLayout *bottomLayout = new QHBoxLayout; //底部布局
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(&gameWidget);

    //设置该widget的布局
    setLayout(mainLayout);
    setFixedSize(gameWidget.size());
}

PlayWidget::~PlayWidget()
{

}
