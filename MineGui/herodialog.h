#ifndef HERODIALOG_H
#define HERODIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QIcon>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSettings>

class herodialog : public QDialog
{
    Q_OBJECT
public:
    explicit herodialog(QWidget *parent = 0);

    QLabel *lowrecordtimelabel;     //初级纪录时间
    QLabel *middlerecordtimelabel;  //中级纪录时间
    QLabel *heightrecordtimelabel;  //高级纪录时间
    QLabel *lowrecordnamelabel;     //初级纪录姓名
    QLabel *middlerecordnamelabel;  //中级纪录姓名
    QLabel *heightrecordnamelabel;  //高级纪录姓名




    /*****************************
    描述：读英雄榜数据
    参数：无
    返回值：无
    *****************************/
    void readsettings();

    /*****************************
    描述：初始化英雄榜数据
    参数：无
    返回值：无
    *****************************/
    void init_herorecord();

signals:

public slots:

    /*****************************
    描述：重新设置英雄榜数据槽(slots:)
    参数：无
    返回值：无
    *****************************/
    void slot_reset();

};

#endif // HERODIALOG_H
