#ifndef MINEITEM_H
#define MINEITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QVector>
#include <common.h>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QSound>
#include <QMessageBox>
#include <QDebug>




class MineItem : public QObject ,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit MineItem(int t_x,int t_y,QPixmap pixmap,QGraphicsItem *parent = 0);

    int m_X;                //在容器中的行数
    int m_Y;                //在容器中的列数
    bool m_isMine;          //是否为雷
    bool m_isOpened;        //是否打开
    bool m_isrightMouse;
    int m_aroundMineNum;    //周围雷数
    int m_rMouseKeyNum;     //右键点击的次数


    /*****************************
    描述：鼠标点击事件(右键)
    参数：点击事件
    返回值：无
    *****************************/
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


    /*****************************
    描述：鼠标释放事件（左键）
    参数：点击事件
    返回值：无
    *****************************/
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:


    /*****************************
    描述：重新开始游戏信号
    参数：无
    返回值：无
    *****************************/
    void sig_restartGame();


    /*****************************
    描述：重设雷数信号
    参数：右键标记的雷数
    返回值：无
    *****************************/
    void sig_resetMineNum(int t_signedMineNum);


public slots:
};

#endif // MINEITEM_H
