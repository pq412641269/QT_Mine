#ifndef CUSTOMGAMEDIALOG_H
#define CUSTOMGAMEDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QSpinBox>
#include <QDebug>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QSettings>
#include <QPushButton>
#include "common.h"


class customgamedialog : public QDialog
{
    Q_OBJECT
public:
    explicit customgamedialog(QWidget *parent = 0);

    QSpinBox *colspinbox;                       //列分量框
    QSpinBox *rowspinbox;                       //行分量框
    QSpinBox *minenumspinbox;                   //雷数分量框

    /*****************************
    描述：读注册表自定义的游戏设置文件
    参数：无
    返回值：无
    *****************************/
    void readsettings();

    /*****************************
    描述：写入注册表自定义的游戏设置文件
    参数：无
    返回值：无
    *****************************/
    void writesettings();


signals:
    /*****************************
    描述：发送自定义游戏行，列，雷数的信号(signals)
    参数：行 列 雷数
    返回值：无
    *****************************/
    void signal_sendCustomset(int,int,int);

public slots:
    /*****************************
    描述：接收确定按钮的槽(slots:)
    参数：无
    返回值：无
    *****************************/
    void slot_accpetok();
};

#endif // CUSTOMGAMEDIALOG_H
