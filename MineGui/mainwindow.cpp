#include "mainwindow.h"

extern bool m_soundOpen = true;           //声音开关: true: 打开声音 false: 关闭声音

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),centralget(0),mineView(0),minescene(0),minenumLcd(0),timeLcd(0),smilebtn(0),m_timer(0)
{
    setWindowTitle("扫雷");
    setWindowIcon(QIcon("://images/mine1.png"));
    setWindowFlags(Qt::WindowCloseButtonHint);

    this->create_action();
    this->create_menu();
    this->slot_newgame();
}

void MainWindow::create_action()       //创建行为
{
    newaction = new QAction("开局");
    newaction->setCheckable(true);
    newaction->setShortcut(Qt::Key_N);
    this->connect(newaction,SIGNAL(triggered(bool)),this,SLOT(slot_newgame()));

    lowleveaction = new QAction("初级");
    lowleveaction->setShortcut(Qt::Key_B);
    lowleveaction->setCheckable(true);

    middleleveaction = new QAction("中级");
    middleleveaction->setShortcut(Qt::Key_I);
    middleleveaction->setCheckable(true);

    heightleveaction = new QAction("高级");
    heightleveaction->setShortcut(Qt::Key_E);
    heightleveaction->setCheckable(true);

    customaction = new QAction("自定义");
    customaction->setShortcut(Qt::Key_C);
    customaction->setCheckable(true);

    coloraction = new QAction("颜色");
    coloraction->setShortcut(Qt::Key_L);
    coloraction->setCheckable(true);
    this->connect(coloraction,SIGNAL(triggered(bool)),this,SLOT(slot_colorchanged()));

    soundaction = new QAction("声音");
    soundaction->setShortcut(Qt::Key_S);
    soundaction->setCheckable(true);
    soundaction->setChecked(true);
    this->connect(soundaction,SIGNAL(triggered(bool)),this,SLOT(slot_soundchanged()));

    heroaction = new QAction("扫雷英雄榜");        //英雄榜行为
    heroaction->setShortcut(Qt::Key_T);
    heroaction->setCheckable(true);
    this->connect(heroaction,SIGNAL(triggered(bool)),this,SLOT(slot_herochecked()));

    exitaction = new QAction("退出");
    exitaction->setShortcut(Qt::Key_X);
    this->connect(exitaction,SIGNAL(triggered(bool)),this,SLOT(close()));

    aboutaction = new QAction("关于扫雷");
    aboutaction->setShortcut(Qt::Key_A);
    aboutaction->setCheckable(true);
    this->connect(aboutaction,SIGNAL(triggered(bool)),this,SLOT(slot_about()));

    QActionGroup *actionGroup = new QActionGroup(this);
    actionGroup->addAction(lowleveaction);
    actionGroup->addAction(middleleveaction);
    actionGroup->addAction(heightleveaction);
    actionGroup->addAction(customaction);
    this->connect(actionGroup,SIGNAL(triggered(QAction*)),this,SLOT(slot_newgamebyleve(QAction*)));

}

void MainWindow::create_menu()         //创建菜单
{
    QMenuBar *mbr = this->menuBar();
    QMenu *game_menu = mbr->addMenu("游戏");

    game_menu->addAction(newaction);
    game_menu->addSeparator();
    game_menu->addAction(lowleveaction);
    game_menu->addAction(middleleveaction);
    game_menu->addAction(heightleveaction);
    game_menu->addAction(customaction);
    game_menu->addSeparator();
    game_menu->addAction(coloraction);
    game_menu->addAction(soundaction);
    game_menu->addSeparator();
    game_menu->addAction(heroaction);
    game_menu->addSeparator();
    game_menu->addAction(exitaction);
    QMenu *help_menu = mbr->addMenu("帮助");
    help_menu->addAction(aboutaction);
}

void MainWindow::readsettings()        //读当前游戏设置
{
    QSettings *setting = new QSettings("HAYJ","mine",this);
    setting->beginGroup("CustomGame");
    this->minescene->m_scenerow = setting->value("Custom_row",9).toInt();
    this->minescene->m_scenecol = setting->value("Custom_col",9).toInt();
    this->minescene->m_minesum = setting->value("Custom_mine",10).toInt();
    this->minescene->m_crrentleve = setting->value("Custom_leve",COMMON::CUSOMLEVE).toInt();
    setting->endGroup();
}

void MainWindow::writesettings()       //写当前游戏设置
{
    QSettings *setting = new QSettings("HAYJ","mine",this);
    setting->beginGroup("CustomGame");
    setting->setValue("Custom_row",this->minescene->m_scenerow);
    setting->setValue("Custom_col",this->minescene->m_scenecol);
    setting->setValue("Custom_mine",this->minescene->m_minesum);
    setting->setValue("Custom_leve",this->minescene->m_crrentleve);
    setting->endGroup();
}

void MainWindow::slot_newgame()                        //开始新游戏槽
{    
    centralget->deleteLater();
    mineView->deleteLater();
    minescene->deleteLater();
    minenumLcd->deleteLater();
    timeLcd->deleteLater();
    smilebtn->deleteLater();
    m_timer->deleteLater();

    centralget = new QWidget(this);         //主程序界面 mainwindow->setcellwidget(centralget);
    this->setCentralWidget(centralget);

    QPalette pale;
    pale.setColor(QPalette::WindowText,Qt::red);
    minenumLcd = new QLCDNumber(centralget);        //雷数 LCD
    minenumLcd->setPalette(pale);
    minenumLcd->setDigitCount(4);

    timeLcd = new QLCDNumber(centralget);            //时间 LCD
    timeLcd->setPalette(pale);
    timeLcd->setDigitCount(4);

    smilebtn = new QPushButton(centralget);                     //笑脸按钮
    smilebtn->setIcon(QIcon("://images/cenNormal0.png"));
    this->connect(smilebtn,SIGNAL(clicked(bool)),this,SLOT(slot_newgame()));

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(minenumLcd);
    hlayout->addStretch();
    hlayout->addWidget(smilebtn);
    hlayout->addStretch();
    hlayout->addWidget(timeLcd);

    mineView = new QGraphicsView(centralget);   //主程序视图
    minescene = new MineScene(mineView);          //主程序场景
    mineView->setScene(minescene);
    this->readsettings();

    this->connect(minescene,SIGNAL(sig_scenenewGame()),this,SLOT(slot_newgame()));
    this->connect(minescene,SIGNAL(sig_scenedisplayMineNum(int)),this,SLOT(slot_displayMineNum(int)));
    this->connect(minescene,SIGNAL(sig_successPassGame()),this,SLOT(slot_updatehero()));

    QVBoxLayout *vlayout = new QVBoxLayout(centralget);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(mineView);

    this->setFixedSize(minescene->m_scenecol * COMMON::MAPWIDTH + 25,minescene->m_scenerow * COMMON::MAPHEIGHT + 80);
    mineView->setFixedSize(minescene->m_scenecol * COMMON::MAPWIDTH + 10,minescene->m_scenerow * COMMON::MAPHEIGHT + 10);
    minescene->setSceneRect(0,0,minescene->m_scenecol * COMMON::MAPWIDTH,minescene->m_scenerow * COMMON::MAPHEIGHT);

    if(minescene->m_crrentleve == COMMON::LOWLEVE)
    {
        lowleveaction->setChecked(true);
    }
    else if(minescene->m_crrentleve == COMMON::MIDDLELEVE)
    {
        middleleveaction->setChecked(true);
    }
    else if(minescene->m_crrentleve == COMMON::HEIGHTLEVE)
    {
        heightleveaction->setChecked(true);
    }
    else if(minescene->m_crrentleve == COMMON::CUSOMLEVE)
    {
        customaction->setChecked(true);
    }

    m_time = 0;             //当前用时数
    minenumLcd->display(minescene->m_minesum);
    timeLcd->display(m_time);

    m_timer = new QTimer(this);            //定时器
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slot_displayTime()));
    m_timer->start(1000);

    minescene->initscene();
}

void MainWindow::slot_newgamebyleve(QAction *act)         //点击游戏级别行为开始新游戏槽
{
    if(act == lowleveaction)
    {
        this->minescene->m_scenerow = COMMON::LOWROWANDCOL;
        this->minescene->m_scenecol = COMMON::LOWROWANDCOL;
        this->minescene->m_minesum = COMMON::LOWMINENUM;
        this->minescene->m_crrentleve = COMMON::LOWLEVE;
        this->writesettings();
        this->slot_newgame();
    }
    if(act == middleleveaction)
    {
        this->minescene->m_scenerow = COMMON::MIDDLEROWANDCOL;
        this->minescene->m_scenecol = COMMON::MIDDLEROWANDCOL;
        this->minescene->m_minesum = COMMON::MIDDLEMINENUM;
        this->minescene->m_crrentleve = COMMON::MIDDLELEVE;
        this->writesettings();
        this->slot_newgame();

    }
    else if(act == heightleveaction)
    {
        this->minescene->m_scenerow = COMMON::HEIGHTROW;
        this->minescene->m_scenecol = COMMON::HEIGHTCOL;
        this->minescene->m_minesum = COMMON::HEIGHTMINENUM;
        this->minescene->m_crrentleve = COMMON::HEIGHTLEVE;
        this->writesettings();
        this->slot_newgame();
    }
    if(act == customaction)
    {
        customgamedialog *custom = new customgamedialog(this);
        this->connect(custom,SIGNAL(signal_sendCustomset(int,int,int)),this,SLOT(slot_acceptCutsomvale(int,int,int)));
        custom->exec();
    }
}

void MainWindow::slot_acceptCutsomvale(int row,int col,int mine)    //接收自定义游戏设置槽
{
    this->minescene->m_scenerow = row;
    this->minescene->m_scenecol = col;
    this->minescene->m_minesum = mine;
    this->minescene->m_crrentleve = COMMON::CUSOMLEVE;
    this->writesettings();
    this->slot_newgame();
}

void MainWindow::slot_colorchanged()                   //设置颜色的槽
{
    this->coloraction->setChecked(true);
    QColor color = QColorDialog::getColor(Qt::blue,this,"选择颜色");
    if(color.isValid())
    {
        //1.获取调色板
        QPalette pale = this->minenumLcd->palette();
        QPalette pale_1 = this->timeLcd->palette();
        //2.设置调色板的颜色
        pale.setColor(QPalette::WindowText,color);
        pale_1.setColor(QPalette::WindowText,color);
        //3.设回调色板
        this->minenumLcd->setPalette(pale);
        this->timeLcd->setPalette(pale_1);
    }
}

void MainWindow::slot_soundchanged()                   //设置声音的槽
{   
    if(!m_soundOpen)
    {
        m_soundOpen = true;
        this->soundaction->setChecked(true);
    }
    else
    {
        m_soundOpen = false;
    }
}

void MainWindow::slot_herochecked()                    //显示英雄榜的槽
{
    herodialog *hero = new herodialog(this);
    hero->exec();
}

void MainWindow::slot_about()                          //显示 about 扫雷的槽
{
    QMessageBox messagebox;
    messagebox.setWindowTitle(tr("关于扫雷"));
    messagebox.setWindowIcon(QPixmap("://images/mine1.png"));
    QString text = tr("游 戏 名 称 : 风 云 扫 雷\n")
            + tr("游 戏 版 本 : V 1.0\n")
            + tr("游 戏 作 者 : 彭 琦\n")
            + tr("发 布 日 期 : 2021 - 03 - 04\n");
    messagebox.setText(text);
    messagebox.setIconPixmap(QPixmap("://images/mine1.png"));
    messagebox.exec();
}

void MainWindow::slot_updatehero()                     //更新英雄榜的槽
{
    int flag = QMessageBox::information(this,tr("扫雷成功"),tr("恭喜你，扫雷成功！"),QMessageBox::Ok,QMessageBox::Cancel);
    if(flag != QMessageBox::Ok)
    {
        this->close();
    }

    herodialog *hero = new herodialog(this);
    hero->readsettings();
    if(COMMON::LOWLEVE == minescene->m_crrentleve)
    {
        if(this->m_time < hero->lowrecordtimelabel->text().toInt())
        {
            bool ok;
            QString text = QInputDialog::getText(this,tr("新记录"),tr("型记录诞生，请输入你的名字:"),QLineEdit::Normal,tr("无名氏"),&ok);
            if(ok && !text.isEmpty())
            {
                hero->lowrecordtimelabel->setText(QString::number(this->m_time));
                hero->lowrecordnamelabel->setText(text);
                hero->init_herorecord();
            }
        }
    }
    else if(COMMON::MIDDLELEVE == minescene->m_crrentleve)
    {
        if(this->m_time < hero->middlerecordtimelabel->text().toInt())
        {
            bool ok;
            QString text = QInputDialog::getText(this,tr("新记录"),tr("型记录诞生，请输入你的名字:"),QLineEdit::Normal,tr("无名氏"),&ok);
            if(ok && !text.isEmpty())
            {
                hero->middlerecordtimelabel->setText(QString::number(this->m_time));
                hero->middlerecordnamelabel->setText(text);
                hero->init_herorecord();
            }
        }
    }
    else if(COMMON::HEIGHTLEVE == minescene->m_crrentleve)
    {
        if(this->m_time < hero->heightrecordtimelabel->text().toInt())
        {
            bool ok;
            QString text = QInputDialog::getText(this,tr("新记录"),tr("型记录诞生，请输入你的名字:"),QLineEdit::Normal,tr("无名氏"),&ok);
            if(ok && !text.isEmpty())
            {
                hero->heightrecordtimelabel->setText(QString::number(this->m_time));
                hero->heightrecordnamelabel->setText(text);
                hero->init_herorecord();
            }
        }
    }
    this->slot_newgame();
}

void MainWindow::slot_displayMineNum(int minesum)              //显示雷数的槽
{
    if(minescene->m_minesum - minesum < 0)
    {
        this->minenumLcd->display(0);
    }
    else
    {
        this->minenumLcd->display(minescene->m_minesum - minesum);
    }
}

void MainWindow::slot_displayTime()                    //显示时间的槽
{    
    if(minescene->m_isGameOver)
    {
        return ;
    }

    if(m_time > 9999)
    {
        this->timeLcd->display(9999);
    }
    else
    {
        this->timeLcd->display(++m_time);
        if(m_soundOpen)
        {
            QSound::play("://sound/time.wav");
        }
    }
}

MainWindow::~MainWindow()
{

}
