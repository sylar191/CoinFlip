#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include<QSound>
#include"mypushbutton.h"

chooseLevelscene::chooseLevelscene(QWidget *parent) : QMainWindow(parent)
{
    //配置基础信息

    this->setFixedSize(320,588);

    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    this->setWindowTitle("选择关卡场景");

    //创建菜单栏

    QMenuBar *bar =  menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu *startmenu = bar->addMenu("开始");

    //创建退出菜单子项
    QAction *quitAction =  startmenu->addAction("退出");

    connect(quitAction,&QAction::triggered,[=](){ this->close(); });

    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);

    //返回按钮
    myPushButton *backbtn = new myPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");

    backbtn->setParent(this);

    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());

    connect(backbtn,&myPushButton::pressed,[=](){     //点击返回

        //告诉主场景我返回了  主场景要监听返回请求

        backSound->play();


        QTimer::singleShot(300,this,[=]()

        {
        emit this->chooseSeeneBack();
        });
    });

    QSound *choosesound = new QSound(":/res/TapButtonSound.wav");


    //创建选择关卡的按钮

    for(int i=0 ; i<20 ; i++)
    {

        myPushButton *menubtn = new myPushButton(":/res/LevelIcon.png");
        menubtn->setParent(this);
        menubtn->move(25+i%4 * 70, 150+i/4 * 70);


        QLabel *label = new QLabel;
        label->setParent(this);

        label->setFixedSize(menubtn->width(),menubtn->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4 * 70, 150+i/4 * 70);
        label->setAlignment(Qt::AlignCenter );

        //label 覆盖了按钮  需要设置鼠标穿透  51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);


        connect(menubtn,&myPushButton::clicked,[=](){

            //选择关卡



            choosesound->play();

            play = new PlayScene(i+1);

            play->setGeometry(this->geometry());

            play->show();

            QTimer::singleShot(300,this,[=](){

                this->hide();

            });



            //此处为对每一个关卡中的返回按钮建立连接 因为 play指向的是当前的关卡
            //所以要在for循环中
            //for循环结束后 play只是指向了最后一个关卡
            //再建立连接只对最后一个关卡进行了链接


            connect(play,&PlayScene::playsceneback,[=](){

                this->setGeometry(play->geometry());

                this->show();

               QTimer::singleShot(300,this,[=]()
               {



                   delete play;

                   play = NULL;   //因为每次创建都是在点击关卡之后  所以不需要隐藏 直接释放掉

               });
            });

        });
    }



}


void chooseLevelscene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QPixmap  pix ;
    pix.load(":/res/OtherSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    pix.load(":/res/Title.png");

    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix);



}
