#ifndef PLAYWIDGET_H
#define PLAYWIDGET_H

#include <QWidget>
#include "gamewidget.h"

class PlayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayWidget(QWidget *parent = nullptr);
    ~PlayWidget();

public:
    GameWidget gameWidget;

};

#endif // PLAYWIDGET_H
