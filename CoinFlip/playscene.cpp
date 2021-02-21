#include "playscene.h"
#include<QMenuBar>
#include<QPainter>
#include<QTimer>
#include<QDebug>
#include<QLabel>
#include<QSound>
#include"mypushbutton.h"
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
PlayScene::PlayScene(int levelNum)
{

    QString str = QString("第%1关").arg(levelNum);

    this->levelIndex = levelNum;

    //初始化游戏场景
    this->setFixedSize(320,588);

    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    this->setWindowTitle(str);

    QMenuBar *bar = menuBar();
    setMenuBar(bar);

    QMenu *startMenu = bar->addMenu("开始");

    QAction *quitAction = startMenu->addAction("退出");

    connect(quitAction,&QAction::triggered,[=](){this->close();});

    QLabel* winLabel = new QLabel;  //将成功图片先显示在窗口上方待定
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());


    //返回按钮

    myPushButton *backbtn = new myPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");

    //翻金币音效
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //胜利按钮音效
    QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);

    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());


    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);

    connect(backbtn,&myPushButton::pressed,[=]()
    {

        qDebug()<<"点击了返回按钮";

        backSound->play();

        QTimer::singleShot(300,this,[=]()
        {

            emit this->playsceneback();
        });


    });

    //显示第几关
    QLabel *label = new QLabel;

    label->setParent(this);

    QFont font;

    font.setFamily("华文新魏");

    font.setPointSize(20);

    //将字体设置到标签控件

    label->setFont(font);

    QString str1 = QString("Level : %1").arg(this->levelIndex);

    label->setText(str1);

    label->setGeometry(30,this->height()-50,120,50);

    //初始化每个关卡的二维数组
    //将dataconfig中对应的关卡数据读到成员函数gameArray中

    dataConfig config;

    for(int i = 0; i<5 ;i++)
    {
        for(int j = 0; j<5 ;j++)
        {

            this->gameArray[j][i] = config.mData[levelIndex][i][j];
        }

    }

    //创建金币的背景图片
    for(int i = 0 ; i < 5;i++)
    {
        for(int j = 0 ; j < 5; j++)
        {
            //绘制背景图片
            QLabel* label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            label->setParent(this);
            label->move(37 + i*50,200+j*50);



            //创建金币

            QString str;
            if(this->gameArray[i][j] == 1)

            {
                //显示金币
                str = ":/res/Coin0001.png";
            }

            else
            {
                 str = ":/res/Coin0008.png";
            }



            MyCoin *coin = new MyCoin(str);

            coin->setParent(this);

            coin->move(39 + i*50,204+j*50);

            //给金币属性赋值

            coin->posX = i;
            coin->poxY = j;

            coin->flag = gameArray[i][j]; //1正面

            //将金币放入到金币的二维数组中

            coinBtn[i][j] =coin;





            connect(coin,&MyCoin::clicked,[=]()
            {

                flipSound->play();

                //点击按钮 将所有按钮都禁用
               for( int i =0 ; i<5 ;i++)
               {
                   for(int j = 0 ; j<5 ; j++)
                   {

                       this->coinBtn[i][j]->isWin = true;

                   }


               }
               coin->changeFlag();
               this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1:0;

               //翻转周围金币

               QTimer::singleShot(300,this,[=]()
               {
                   if(coin->posX+1 <= 4)  //右侧可以翻转
                   {
                       coinBtn[coin->posX+1][coin->poxY]->changeFlag();
                       this->gameArray[coin->posX+1][coin->poxY] = this->gameArray[coin->posX+1][coin->poxY] == 0 ? 1:0;

                   }

                   if(coin->posX-1 >= 0)  //左侧可以翻转
                   {
                       coinBtn[coin->posX-1][coin->poxY]->changeFlag();
                       this->gameArray[coin->posX-1][coin->poxY] = this->gameArray[coin->posX-1][coin->poxY] == 0 ? 1:0;

                   }


                   if(coin->poxY-1 >= 0)  //上侧可以翻转
                   {
                       coinBtn[coin->posX][coin->poxY-1]->changeFlag();
                       this->gameArray[coin->posX][coin->poxY-1] = this->gameArray[coin->posX][coin->poxY-1] == 0 ? 1:0;

                   }

                   if(coin->poxY+1 <= 4)  //下侧可以翻转
                   {
                       coinBtn[coin->posX][coin->poxY+1]->changeFlag();
                       this->gameArray[coin->posX][coin->poxY+1] = this->gameArray[coin->posX][coin->poxY+1] == 0 ? 1:0;

                   }

                   //翻转完金币后 再解开禁用

                   for( int i =0 ; i<5; i++)
                   {
                       for(int j = 0 ; j<5 ; j++)
                       {

                           this->coinBtn[i][j]->isWin = false;

                       }


                   }

                   //判断是否胜利
                   this->isWin = true;

                   for(int i =0; i <5; i++)
                   {
                       for(int j=0 ;j<5 ; j++)
                       {
                           if(coinBtn[i][j]->flag == false)
                           {

                               this->isWin =false;
                               break;
                           }


                       }



                   }
                   if( this->isWin == true)
                   {



                       qDebug()<<"Win";
                       //将所有按钮的胜利标志改为true;

                       for(int i =0; i <5; i++)
                       {
                           for(int j=0 ;j<5 ; j++)
                           {
                               coinBtn[i][j]->isWin=true;


                           }


                       }
                       winSound->play();

                       //将胜利图片砸下来
                       QPropertyAnimation *animation = new QPropertyAnimation(winLabel,"geometry");
                       animation->setDuration(1000);


                       animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                       animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                       animation->setEasingCurve(QEasingCurve::OutBounce);
                       animation->start();


                   }



               });







            });



        }
    }




}




void PlayScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QPixmap pix;

    pix.load(":/res/PlayLevelSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");

    pix = pix.scaled(pix.width()/2,pix.height()/2);

    painter.drawPixmap(10,30,pix);








}
