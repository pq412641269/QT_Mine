#ifndef COMMON_H
#define COMMON_H

class COMMON
{
public:
    //1. 游戏级别定义
    enum gameLeve
    {
        LOWLEVE = 0,
        MIDDLELEVE = 1,
        HEIGHTLEVE = 2,
        CUSOMLEVE = 3
    };

    //2. 初级行、列、雷数设置
    enum lowset
    {
        LOWROWANDCOL = 9,
        LOWMINENUM = 1
    };

    //3. 中级行、列、雷数设置
    enum middleset
    {
        MIDDLEROWANDCOL = 16,
        MIDDLEMINENUM = 40
    };

    //4. 高级级行、列、雷数设置
    enum heightset
    {
        HEIGHTROW = 16,
        HEIGHTCOL = 30,
        HEIGHTMINENUM = 99
    };

    //5. 图片大小设置
    enum mapset
    {
        MAPWIDTH = 25,
        MAPHEIGHT = 25
    };

};

#endif // COMMON_H
