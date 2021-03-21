#ifndef MINESCENE_H
#define MINESCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <time.h>
#include <QVector>
#include "mineitem.h"


class MineScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MineScene(QObject *parent = 0);

    QVector< QVector< MineItem *> > m_itemVec;      //存储方块的容器
    int m_scenerow;                                 //当前场景行数
    int m_scenecol;                                 //当前场景列数
    int m_minesum;                                  //当前场景雷数
    int m_crrentleve;                               //当前场景难度级别
    int m_signedMineNum;                            //右键标记的雷数
    int m_rightMineNum;                             //右键标记正确的雷数
    bool m_isGameOver;                              //游戏是否结束
    int m_remainNoMines;                            //剩余非雷数

    /*****************************
    描述：初始化游戏场景
    参数：无
    返回值：无
    *****************************/
    void initscene();

    /*****************************
    描述：统计方块周围的雷数
    参数：需要统计的item
    返回值：无
    *****************************/
    void countAroundMines(MineItem *t_item);

    /*****************************
    描述：打开所有的方块
    参数：无
    返回值：无
    *****************************/
    void openAllItems();

    /*****************************
    描述：扩散函数
    参数：导入需要递归的item
    返回值：无
    *****************************/
    void expendWater(MineItem *t_item);

signals:

    /*****************************
    描述：游戏成功过关信号
    参数：无
    返回值：无
    *****************************/
    void sig_successPassGame();

    /*****************************
    描述：重新开始游戏信号
    参数：无
    返回值：无
    *****************************/
    void sig_scenenewGame();

    /*****************************
    描述：显示雷数信号
    参数：右键标记的雷数
    返回值：无
    *****************************/
    void sig_scenedisplayMineNum(int);

public slots:
};

#endif // MINESCENE_H
