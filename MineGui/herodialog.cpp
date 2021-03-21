#include "herodialog.h"

herodialog::herodialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("扫雷英雄榜");
    this->setWindowIcon(QIcon("://images/mine0.png"));

    QLabel *lable_1 = new QLabel("初级:");
    QLabel *lable_2 = new QLabel("中级:");
    QLabel *lable_3 = new QLabel("高级:");

    lowrecordtimelabel = new QLabel;     //初级纪录时间
    middlerecordtimelabel = new QLabel;  //中级纪录时间
    heightrecordtimelabel = new QLabel;  //高级纪录时间
    lowrecordnamelabel = new QLabel;     //初级纪录姓名
    middlerecordnamelabel = new QLabel;  //中级纪录姓名
    heightrecordnamelabel = new QLabel;  //高级纪录姓名

    QPushButton *reset_button = new QPushButton("重新设置");
    QPushButton *ok_button = new QPushButton("确定");
    this->connect(reset_button,SIGNAL(clicked(bool)),this,SLOT(slot_reset()));
    this->connect(ok_button,SIGNAL(clicked(bool)),this,SLOT(close()));

    QHBoxLayout *hlayout_1 = new QHBoxLayout;
    hlayout_1->addWidget(lable_1);
    hlayout_1->addStretch();
    hlayout_1->addWidget(lowrecordtimelabel);
    hlayout_1->addStretch();
    hlayout_1->addWidget(lowrecordnamelabel);

    QHBoxLayout *hlayout_2 = new QHBoxLayout;
    hlayout_2->addWidget(lable_2);
    hlayout_2->addStretch();
    hlayout_2->addWidget(middlerecordtimelabel);
    hlayout_2->addStretch();
    hlayout_2->addWidget(middlerecordnamelabel);

    QHBoxLayout *hlayout_3 = new QHBoxLayout;
    hlayout_3->addWidget(lable_3);
    hlayout_3->addStretch();
    hlayout_3->addWidget(heightrecordtimelabel);
    hlayout_3->addStretch();
    hlayout_3->addWidget(heightrecordnamelabel);

    QHBoxLayout *hlayout_4 = new QHBoxLayout;
    hlayout_4->addWidget(reset_button);
    hlayout_4->addWidget(ok_button);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout_1);
    vlayout->addLayout(hlayout_2);
    vlayout->addLayout(hlayout_3);
    vlayout->addLayout(hlayout_4);
    this->readsettings();
}

void herodialog::readsettings() //读英雄榜数据
{
    QSettings *setting = new QSettings("HAYJ","hero",this);
    setting->beginGroup("Game_time");
    lowrecordtimelabel->setText(setting->value("low_time",9999).toString());
    middlerecordtimelabel->setText(setting->value("mid_time",9999).toString());
    heightrecordtimelabel->setText(setting->value("high_time",9999).toString());
    setting->endGroup();

    setting->beginGroup("Game_name");
    lowrecordnamelabel->setText(setting->value("low_name","N A").toString());
    middlerecordnamelabel->setText(setting->value("mid_name","N A").toString());
    heightrecordnamelabel->setText(setting->value("high_name","N A").toString());
    setting->endGroup();
}

void herodialog::init_herorecord() //初始化英雄榜数据
{

    QSettings *setting = new QSettings("HAYJ","hero",this);
    setting->beginGroup("Game_time");
    setting->setValue("low_time",lowrecordtimelabel->text());
    setting->setValue("mid_time",middlerecordtimelabel->text());
    setting->setValue("high_time",heightrecordtimelabel->text());
    setting->endGroup();

    setting->beginGroup("Game_name");
    setting->setValue("low_name",lowrecordnamelabel->text());
    setting->setValue("mid_name",middlerecordnamelabel->text());
    setting->setValue("high_name",heightrecordnamelabel->text());
    setting->endGroup();
}

void herodialog::slot_reset() //重新设置英雄榜数据槽(slots:)
{
    lowrecordtimelabel->setText("9999");        //初级纪录时间
    middlerecordtimelabel->setText("9999");     //中级纪录时间
    heightrecordtimelabel->setText("9999");     //高级纪录时间
    lowrecordnamelabel->setText("N A");         //初级纪录姓名
    middlerecordnamelabel->setText("N A");      //中级纪录姓名
    heightrecordnamelabel->setText("N A");      //高级纪录姓名
    this->init_herorecord();
}
