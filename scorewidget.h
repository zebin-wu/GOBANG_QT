#ifndef SCOREWIDGET_H
#define SCOREWIDGET_H

#include <QWidget>

namespace Ui {
class ScoreWidget;
}

class ScoreWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreWidget(const QSize &size, QWidget *parent = nullptr);
    ~ScoreWidget();
    void setLabel(int winPlayer);
private:
    Ui::ScoreWidget *ui;
signals:
    void againSignal();
    void homeSignal();
};

#endif // SCOREWIDGET_H
