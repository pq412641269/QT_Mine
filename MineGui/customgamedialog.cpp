#include "customgamedialog.h"

customgamedialog::customgamedialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("自定义游戏");

    QLabel *label_1 = new QLabel("自定义行数");
    QLabel *label_2 = new QLabel("自定义列数");
    QLabel *label_3 = new QLabel("自定义雷数");

    colspinbox = new QSpinBox; //列分量框
    colspinbox->setRange(5,100);
    colspinbox->setSingleStep(5);
    colspinbox->setValue(9);

    rowspinbox = new QSpinBox; //行分量框
    rowspinbox->setRange(5,100);
    rowspinbox->setSingleStep(5);
    rowspinbox->setValue(9);

    minenumspinbox = new QSpinBox; //雷数分量框
    minenumspinbox->setRange(1,50);
    minenumspinbox->setSingleStep(3);
    minenumspinbox->setValue(10);

    QPushButton *ok_button = new QPushButton("确 定");
    QPushButton *cancel_button = new QPushButton("取 消");

    QGridLayout *glayout = new QGridLayout(this);
    glayout->addWidget(label_1,0,0);
    glayout->addWidget(rowspinbox,0,1);
    glayout->addWidget(label_2,1,0);
    glayout->addWidget(colspinbox,1,1);
    glayout->addWidget(label_3,2,0);
    glayout->addWidget(minenumspinbox,2,1);
    glayout->addWidget(ok_button,3,0);
    glayout->addWidget(cancel_button,3,1);

    this->connect(ok_button,SIGNAL(clicked(bool)),this,SLOT(slot_accpetok()));
    this->connect(cancel_button,SIGNAL(clicked(bool)),this,SLOT(close()));

}

void customgamedialog::readsettings()    //读自定义游戏设置文件
{
    QSettings *setting = new QSettings("HAYJ","mine",this);
    setting->beginGroup("CustomGame");
    int row = setting->value("Custom_row",9).toInt();
    int col = setting->value("Custom_col",9).toInt();
    int mine = setting->value("Custom_mine",10).toInt();
    setting->endGroup();

    rowspinbox->setValue(row);
    colspinbox->setValue(col);
    minenumspinbox->setValue(mine);

}

void customgamedialog::writesettings()   // 写自定义游戏设置文件
{
    QSettings *setting = new QSettings("HAYJ","mine",this);
    setting->beginGroup("CustomGame");
    setting->setValue("Custom_row",rowspinbox->value());
    setting->setValue("Custom_col",colspinbox->value());
    setting->setValue("Custom_mine",minenumspinbox->value());
    setting->setValue("Custom_leve",COMMON::CUSOMLEVE);
    setting->endGroup();
}

void customgamedialog::slot_accpetok()    //接收确定按钮的槽(slots:)
{
    int row = rowspinbox->value();
    int col = colspinbox->value();
    int mine = minenumspinbox->value();
    emit this->signal_sendCustomset(row,col,mine); //发送自定义游戏行，列，雷数的信号(signals)
    this->writesettings();
    this->close();

}
