#include "chess.h"

chess::chess()
{

}

chess::chess(COLOR c,TYPE t,QPoint p,QString str)
{
    this->color=c;
    this->type=t;
    this->pos=p;
    this->show=true;
    this->route=str;
}
