#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<QTimer>
#include<mycoin.h>
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:

    PlayScene(int levelNum);

    //重写paintevent

    void paintEvent(QPaintEvent *event);


    int levelIndex;  //记录所选关卡



    int gameArray[5][5]; //二维数组 维护每个关卡的具体数据

    MyCoin *coinBtn[5][5];

    bool isWin; //胜利的标志


signals:
    void playsceneback();
};

#endif // PLAYSCENE_H
