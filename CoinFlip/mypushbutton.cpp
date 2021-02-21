#include "mypushbutton.h"
#include<QDebug>
#include<QPropertyAnimation>

//myPushButton::myPushButton(QWidget *parent) : QPushButton(parent)
//{

//}


myPushButton::myPushButton(QString normalImage,QString pressImage )
{

    this->normalImagePath=normalImage;
    this->pressImagePath = pressImage;


    QPixmap pix;
    bool ret = pix.load(normalImage);

    if(!ret)
    {

        qDebug()<<"加载图片失败!";
        return;

    }


    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());

    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));



}


void  myPushButton::mousePressEvent(QMouseEvent *e)
{

    if(this->pressImagePath != "")//传入的图片不为空 说明需要有按下的效果图片
    {
        QPixmap pix;
        bool ret = pix.load(this->pressImagePath);

        if(!ret)
        {

            qDebug()<<"加载图片失败!";
            return;

        }


        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //交给父类 让父类执行其他内容
    return QPushButton::mousePressEvent(e);

}

void myPushButton::mouseReleaseEvent(QMouseEvent *e)
{

    if(this->pressImagePath != "")//传入的图片不为空 说明需要有按下的效果图片
    {
        QPixmap pix;
        bool ret = pix.load(this->normalImagePath);

        if(!ret)
        {

            qDebug()<<"加载图片失败!";
            return;

        }


        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //交给父类 让父类执行其他内容
    return QPushButton::mouseReleaseEvent(e);

}



void myPushButton::zoom1()  //按下的动画效果
{
    //创建动画对象
    QPropertyAnimation *animation1 = new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation1->setDuration(200);

    //起始位置
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //结束位置
     animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

     //设置缓和曲线  QEasingCurve::OutBounce为弹跳效果
     animation1->setEasingCurve(QEasingCurve::OutBounce);

     //开始执行动画

     animation1->start();


}


void myPushButton::zoom2()  //弹起
{
    //创建动画对象
    QPropertyAnimation *animation1 = new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation1->setDuration(200);

    //起始位置
    animation1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //结束位置
     animation1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

     //设置缓和曲线  QEasingCurve::OutBounce为弹跳效果
     animation1->setEasingCurve(QEasingCurve::OutBounce);

     //开始执行动画

     animation1->start();


}
