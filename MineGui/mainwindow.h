#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QGraphicsView>
#include <QAction>
#include <QPushButton>
#include <QLCDNumber>
#include <QDebug>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QPalette>
#include <QWidget>
#include <QInputDialog>
#include <QColorDialog>
#include "minescene.h"
#include "common.h"
#include "customgamedialog.h"
#include "herodialog.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QAction *newaction;
    QAction *lowleveaction;
    QAction *middleleveaction;
    QAction *heightleveaction;
    QAction *customaction;
    QAction *coloraction;
    QAction *soundaction;
    QAction *heroaction;        //英雄榜行为
    QAction *exitaction;
    QAction *aboutaction;

    QWidget *centralget;        //主程序界面
    QGraphicsView *mineView;    //主程序视图
    MineScene *minescene;       //主程序场景
    QLCDNumber *minenumLcd;     //雷数 LCD
    QLCDNumber *timeLcd;        //时间 LCD
    QPushButton *smilebtn;      //笑脸按钮
    int m_time;                 //当前用时数
    QTimer *m_timer;            //定时器

    /*****************************
    描述：创建菜单行为
    参数：无
    返回值：无
    *****************************/
    void create_action();

    /*****************************
    描述：创建菜单
    参数：无
    返回值：无
    *****************************/
    void create_menu();

    /*****************************
    描述：读取注册表游戏设置
    参数：无
    返回值：无
    *****************************/
    void readsettings();

    /*****************************
    描述：写当前游戏设置到注册表
    参数：无
    返回值：无
    *****************************/
    void writesettings();

public slots:

    /*****************************
    描述：开始新游戏槽
    参数：无
    返回值：无
    *****************************/
    void slot_newgame();

    /*****************************
    描述：点击游戏级别行为开始新游戏槽
    参数：行为
    返回值：无
    *****************************/
    void slot_newgamebyleve(QAction *);

    /*****************************
    描述：接收自定义游戏设置开始新游戏槽
    参数：行 列 雷数
    返回值：无
    *****************************/
    void slot_acceptCutsomvale(int,int,int);

    /*****************************
    描述：设置颜色的槽
    参数：无
    返回值：无
    *****************************/
    void slot_colorchanged();

    /*****************************
    描述：设置声音的槽
    参数：无
    返回值：无
    *****************************/
    void slot_soundchanged();

    /*****************************
    描述：显示英雄榜的槽
    参数：无
    返回值：无
    *****************************/
    void slot_herochecked();

    /*****************************
    描述：显示扫雷游戏信息槽
    参数：无
    返回值：无
    *****************************/
    void slot_about();

    /*****************************
    描述：扫雷成功更新英雄榜的槽
    参数：无
    返回值：无
    *****************************/
    void slot_updatehero();

    /*****************************
    描述：显示雷数的槽
    参数：右键标记的雷数
    返回值：无
    *****************************/
    void slot_displayMineNum(int);

    /*****************************
    描述：显示时间的槽
    参数：无
    返回值：无
    *****************************/
    void slot_displayTime();

};

#endif // MAINWINDOW_H
