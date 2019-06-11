#ifndef CHESS_H
#define CHESS_H
#include<QPoint>
#include<QPixmap>
#include<QString>
enum COLOR{
    RED=0,
    BLACK=1,
    COLOL_MAX
};

enum TYPE{
    JU=0,
    MA,
    XIANG,
    SHI,
    KING,
    PAO,
    ZU,
    TYPE_MAX
};

class chess
{
public:
    chess();
    chess(COLOR c,TYPE t,QPoint p,QString str);
    COLOR color;
    TYPE type;
    QPoint pos;
    bool show;
    QString route;
};

#endif // CHESS_H
