#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//#include "gamewidget.h"
#include "scorewidget.h"
#include "playwidget.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void resizeEvent(QResizeEvent *event); //重写调整窗口事件
private:
    Ui::Widget *ui;
    PlayWidget playWidget;
    //GameWidget gameWidget;
    ScoreWidget *scoreWidget;
};

#endif // WIDGET_H
