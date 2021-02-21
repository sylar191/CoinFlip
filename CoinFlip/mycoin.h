#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTImer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString btnImg);


    void changeFlag();

    QTimer *timer1;

    QTimer *timer2;

    int min = 1;

    int max = 8;

    //执行动画的标志

    bool isAnimateflag = false;

    //重写按下

    void mousePressEvent(QMouseEvent *e);

    bool isWin =false; //胜利的标志

    int posX;
    int poxY;  //坐标

    bool flag;      //正反

signals:

};

#endif // MYCOIN_H
