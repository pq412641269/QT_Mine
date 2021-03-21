#include "minescene.h"

QPoint t_around[8] =
{
    QPoint(-1,-1),
    QPoint(-1,0),
    QPoint(-1,1),
    QPoint(0,-1),
    QPoint(0,1),
    QPoint(1,-1),
    QPoint(1,0),
    QPoint(1,1)
};

MineScene::MineScene(QObject *parent) : QGraphicsScene(parent)
{
    m_signedMineNum = 0;                            //右键标记的雷数
    m_rightMineNum = 0;                             //右键标记正确的雷数
    this->m_isGameOver = false;                     //游戏是否结束
}

//函数功能: 初始化游戏场景，主要创建方块和随机布雷及连接信号
void MineScene::initscene()                         //初始化游戏场景
{
    //1)初始化非雷数＝方块总数 - 总雷数
    this->m_remainNoMines = m_scenerow * m_scenecol - m_minesum;

    //2)根据当前行，列循环创建方块并加入行 vector 和场景中，并将行 vector 加入到总 vector 中
    for(int i = 0; i < m_scenerow; i++)
    {
        QVector< MineItem *> x_vec;
        for(int j = 0 ; j < m_scenecol ; j++)
        {
            MineItem *x_item = new MineItem(i,j,QPixmap("://images/cover1.png"));
            x_item->setPos(j * COMMON::MAPWIDTH, i * COMMON::MAPHEIGHT);
            this->addItem(x_item);
            x_vec.push_back(x_item);
        }
        this->m_itemVec.push_back(x_vec);
    }
    //3)根据雷数循环随机布雷
    srand(time(NULL));
    for(int i = 0 ; i < m_minesum ; i++)
    {
        //4)随机产生一个坐标
        int mine_row = rand() % m_scenerow;
        int mine_col = rand() % m_scenecol;
        if(!this->m_itemVec[mine_row][mine_col]->m_isMine)
        {
            this->m_itemVec[mine_row][mine_col]->m_isMine = true;
            //5)如果该方块不是雷，则设置其为雷，并将周围八个方块上的周围雷数加 1
            this->countAroundMines(this->m_itemVec[mine_row][mine_col]);
        }
        else
        {
            i--;
        }
    }

    //6)将所有方块的重新开始游戏信号连接到场景的重新开始游戏信号
    //7)将所有方块的重新设置雷数信号连接到场景的重新显示雷数信号
    for(int i = 0 ; i < m_scenerow ; i++)
    {
        for(int j =0 ; j < m_scenecol ; j++)
        {
            this->connect(this->m_itemVec[i][j],SIGNAL(sig_restartGame()),this,SIGNAL(sig_scenenewGame()));
            this->connect(this->m_itemVec[i][j],SIGNAL(sig_resetMineNum(int)),this,SIGNAL(sig_scenedisplayMineNum(int)));
        }
    }
}

void MineScene::countAroundMines(MineItem *t_item)        //统计方块周围的雷数
{
    if(t_item == NULL || !t_item->m_isMine)
    {
        return;
    }

    for(int i = 0; i < 8; i++)
    {
        int t_x = t_item->m_X + t_around[i].x();
        int t_y = t_item->m_Y + t_around[i].y();

        if(t_x < 0 || t_x >= this->m_scenerow || t_y < 0 || t_y >= this->m_scenecol)
        {
            continue;
        }

        if(m_itemVec[t_x][t_y]->m_isMine)
        {
            continue;
        }
        m_itemVec[t_x][t_y]->m_aroundMineNum++;
    }
}

//函数功能:打开所有的方块
void MineScene::openAllItems()                            //打开所有的方块
{
    //1)循环遍历所有方块
    for(int i = 0; i < this->m_scenerow; i++)
    {
        for(int j = 0; j < this->m_scenecol; j++)
        {
            //2)将方块设置为打开
            this->m_itemVec[i][j]->m_isOpened = true;

            //3)如果是雷则将方块图片设置为雷图片
            if(this->m_itemVec[i][j]->m_isMine)
            {
                this->m_itemVec[i][j]->setPixmap(QPixmap("://images/mine1.png"));
            }
            else
            {
                //4)如果不是雷则将方块图片设置为方块周围雷数所对应图片
                QString path = tr("://images/") + QString::number(m_itemVec[i][j]->m_aroundMineNum) + tr(".png");
                m_itemVec[i][j]->setPixmap(QPixmap(path));
            }
        }
    }
}

//函数功能:扩散函数，查找周围8个方位方块的周围雷数是否为0,如果是则递归，如果不是则设置方块图片为方块周围雷数对应图片
void MineScene::expendWater(MineItem *t_item)             //扩散函数
{    
    //1)如果为空，如果是雷则返回
    if(NULL == t_item || t_item->m_isMine)
    {
        return;
    }

    //2)循环查找8个方位
    for(int i = 0; i < 8 ; i++)
    {
        //3)计算所找方块在容器中的行
        int t_x = t_item->m_X + t_around[i].x();
        int t_y = t_item->m_Y + t_around[i].y();
        //4)如果越界,则重新下一次循环
        if(t_x < 0 || t_x >= this->m_scenerow || t_y < 0 || t_y >= this->m_scenecol)
        {
            continue;
        }

        //5)如果所找方块是雷或者已打开，则重新下一次循环
        if(m_itemVec[t_x][t_y]->m_isMine || m_itemVec[t_x][t_y]->m_isOpened)
        {
            continue;
        }
        //6)如果所找方块的已经右键点击
        if(m_itemVec[t_x][t_y]->m_rMouseKeyNum)
        {
            continue;
        }

        //7)设置所找方块已打开，当前剩余非雷数减1
        m_itemVec[t_x][t_y]->m_isOpened = true;
        this->m_remainNoMines--;
        //8)如果所找方块周围雷数为0，则设置相应图片，并递归查找
        if(!m_itemVec[t_x][t_y]->m_aroundMineNum)
        {
            expendWater(m_itemVec[t_x][t_y]);
        }

        //9)如果所找方块周围雷数不为0,则设置所找方块的图片为所找方块的周围雷数对应图片
        QString path = tr("://images/") + QString::number(m_itemVec[t_x][t_y]->m_aroundMineNum) + tr(".png");
        m_itemVec[t_x][t_y]->setPixmap(QPixmap(path));

        //10)如果当前剩余非雷数为0
        if(!this->m_remainNoMines)
        {
            //11)设置当前游戏结束，如果声音打开，则播放声音
            QSound::play("://sound/win.wav");
            //12)打开所有雷
            this->openAllItems();
            //13)发送成功过关的信号
            emit this->sig_successPassGame();
        }
    }
}
