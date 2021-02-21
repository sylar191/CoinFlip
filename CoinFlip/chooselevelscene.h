#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include"playscene.h"
class chooseLevelscene : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooseLevelscene(QWidget *parent = nullptr);




    //重写paintevent

    void paintEvent(QPaintEvent *event);

    PlayScene *play = NULL;


signals:
    //写一个自定义信号,告诉主场景点击了返回
    void chooseSeeneBack();

};

#endif // CHOOSELEVELSCENE_H
