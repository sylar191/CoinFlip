#include "mycoin.h"
#include <QDebug>

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg);

    if(!ret)
    {
        QString str = QString("图片 %1 加载失败").arg(btnImg);
        qDebug()<<str;
        return;

    }

    this->setFixedSize(pix.width(),pix.height());

    this->setStyleSheet("QPushButton{border:0px;}");

    this->setIcon(pix);

    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);


    connect(timer1,&QTimer::timeout,[=](){
            QPixmap pixmap;
            QString str = QString(":/res/Coin000%1.png").arg(this->min++);
            pixmap.load(str);
            this->setFixedSize(pixmap.width(),pixmap.height() );
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(pixmap);
            this->setIconSize(QSize(pixmap.width(),pixmap.height()));
            if(this->min > this->max) //如果大于最大值，重置最小值，并停止定时器
            {
                this->min = 1;
                isAnimateflag = false;
                timer1->stop();
            }
        });

        connect(timer2,&QTimer::timeout,[=](){
            QPixmap pixmap;
            QString str = QString(":/res/Coin000%1.png").arg((this->max)-- );
            pixmap.load(str);
            this->setFixedSize(pixmap.width(),pixmap.height() );
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(pixmap);
            this->setIconSize(QSize(pixmap.width(),pixmap.height()));
            if(this->max < this->min) //如果小于最小值，重置最大值，并停止定时器
            {
                this->max = 8;
                isAnimateflag = false;
                timer2->stop();
            }
        });


}

void MyCoin::mousePressEvent(QMouseEvent *e)
{

    if(this->isAnimateflag || this->isWin) return;  //如果在执行动画过程中按下按钮 就return 代表不执行此次按下事件

    else {
        QPushButton::mousePressEvent(e);  //只有在没有放动画时按下  才会响应此次按下事件
    }


}

void MyCoin::changeFlag()
{




    if(this->flag)
   {
        timer1->start(30);
        isAnimateflag = true;
        flag = false;

    }

    else {
        timer2->start(30);
        isAnimateflag = true;
        flag =true;
    }



}
