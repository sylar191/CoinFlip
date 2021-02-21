#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QTimer>
#include"mypushbutton.h"
#include<QSound>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(320,588);

    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    this->setWindowTitle("翻金币");

    connect(ui->actionquit,&QAction::triggered,[=](){this->close();});


    //开始按钮
    myPushButton *startbtn = new myPushButton(":/res/MenuSceneStartButton.png");

    startbtn->setParent(this);  //放到当前窗口中
    startbtn->move(this->width()*0.5 - startbtn->width()*0.5,this->height()*0.7);

    QSound *startsound = new QSound(":/res/TapButtonSound.wav");


    //实例化关卡场景
    chooseScene = new chooseLevelscene;

    connect(startbtn,&myPushButton::clicked,[=]()
    {


        //播放开始音效

       // startsound->setLoops(-1);//循环次数  -1 表示无限循环
        startsound->play();


        //点击动画
        startbtn->zoom1();
        startbtn->zoom2();



        //延时进入
        QTimer::singleShot(300,this,[=](){



            //进入到选择关卡场景
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();

            //先show出新场景  再hide  减少闪烁 在之间加入延时函数 更加有效防止闪烁
            QTimer::singleShot(300,this,[=](){


                //自身隐藏
                this->hide();

            });





        });



    });

    //监听选择关卡的返回按钮信号

    connect(chooseScene,&chooseLevelscene::chooseSeeneBack,this,[=](){



            this->setGeometry(chooseScene->geometry());
            this->show();//重新显示主场景


             QTimer::singleShot(300,this,[=]()
             {
                   chooseScene->hide();//将选择关卡场景隐藏
             });







    });

}


void MainWindow::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);

    QPixmap pix;

    pix.load(":/res/PlayLevelSceneBg.png");   //绘制背景

    painter.drawPixmap(0,0,this->width(),this->height(),pix);



    pix.load(":/res/Title.png");  //绘制标题

    pix = pix.scaled(pix.width()/2,pix.height()/2); //缩放图片

    painter.drawPixmap(10,30,pix);






}

MainWindow::~MainWindow()
{
    delete ui;
}

