#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class myPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit myPushButton(QWidget *parent = nullptr);

    myPushButton(QString normalImage,QString pressImage = "");

    void zoom1();

    void zoom2();

    //重写按钮 按下和释放事件

    void  mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);


    QString normalImagePath;
    QString pressImagePath;

signals:

};

#endif // MYPUSHBUTTON_H
