#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QInputDialog>
#include<QMessageBox>
#include<QTimer>

//棋盘的左上角坐标为（36，42）
#define INTERVAL 60
#define INITROW 36
#define INITCOL 42

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    initchess();
    ui->pushButton->setEnabled(connectd);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recolor(COLOR c)
{
    Local_color=c;
}
void MainWindow::colorchange(COLOR & c)
{
    if(c==RED)
    {
        c=BLACK;
    }
    else
    {
        c=RED;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    QPoint p=QPoint( (event->x()-(INITROW-INTERVAL/2))/INTERVAL, (event->y()-(INITCOL-INTERVAL/2))/INTERVAL);

    if(isstart)
    {

        if(isselected)
        {



            if(event->button()==Qt::LeftButton)
            {


                for(int i=0;i<my_chess.size();++i)
                {
                    if(p==my_chess[i].pos)
                    {
                        if(my_chess[i].color==isorder&&Local_color==isorder)
                        {
                            posid=i;
                            isselected=false;

                        }


                    }

                }
                gameend();
            }


        }
        else
        {
            //QPoint p= QPoint( (event->x()-(INITROW-INTERVAL/2))/INTERVAL, (event->y()-(INITCOL-INTERVAL/2))/INTERVAL);

            QVector<QPoint> point;

            GetMoveArea(point,posid);


            for(int i=0;i<point.size();++i)
            {

                if(p==point[i])
                {
                    for(int j=0;j<my_chess.size();++j)
                    {

                        if(p==my_chess[j].pos)
                        {
                            my_chess[j].show=false;
                            my_chess[j].pos=QPoint(9,9);
                            QString s="1"+QString::number(j)+QString::number(my_chess[j].show);
                            s+=QString::number(my_chess[j].pos.x());
                            s+=QString::number(my_chess[j].pos.y());
                            s+=QString::number(isorder);
                            tcpsocket->write(s.toLatin1());

                            tcpsocket->waitForBytesWritten(500);
                        }
                    }
                    my_chess[posid].pos=p;

                    colorchange(isorder);
                    isselected=true;

                    QString q="1"+QString::number(posid)+QString::number(my_chess[posid].show);
                    q+=QString::number(my_chess[posid].pos.x());
                    q+=QString::number(my_chess[posid].pos.y());
                    q+=QString::number(isorder);
                    tcpsocket->write(q.toLatin1());




                }
                else
                {
                    isselected=true;
                }

            }


        }
    }

    update();
}

void MainWindow::gameend()
{
    QVector<QPoint> point;
    for(int i=0;i<my_chess.size();++i)
    {
        GetMoveArea(point,i);
    }

    for(int i=0;i<point.size();++i)
    if(point[i]==my_chess[8].pos||point[i]==my_chess[24].pos)
    {
        QMessageBox::information(this,"","将军！！！！");

    }
    else
    {

    }

    if(my_chess[8].show!=my_chess[24].show)
    {
        QMessageBox::information(this,"","游戏结束！！！！");
        initchess();
    }
}

void MainWindow::GetMoveArea(QVector<QPoint>& point,int posid)
{
    int i=posid;
    switch (my_chess[i].type)
    {
    case JU:
        getMove_JU(my_chess[posid],point);
        break;
    case MA:
        getMove_MA(my_chess[posid],point);
        break;
    case XIANG:
        getMove_XIANG(my_chess[posid],point);
        break;
    case SHI:
        getMove_SHI(my_chess[posid],point);
        break;
    case KING:
        getMove_KING(my_chess[posid],point);
        break;
    case PAO:
        getMove_PAO(my_chess[posid],point);
        break;
    case ZU:
        getMove_BING(my_chess[posid],point);
        break;
    default:
        break;
    }
}

void MainWindow::initchess()
{
    isstart=false;     //游戏开始标识
    isselected=true;   //棋子选定标识
    isorder=RED;       //红先还是黑先
    posid=0;           //记录当前选定棋子的ID
    connectd=false;
    my_chess.clear();
    //初始化黑方棋子
    chess chess1(BLACK,JU,QPoint(0,0),":/rec/black_ju.png");
    chess chess2(BLACK,JU,QPoint(8,0),":/rec/black_ju.png");
    chess chess3(BLACK,MA,QPoint(1,0),":/rec/black_ma.png");
    chess chess4(BLACK,MA,QPoint(7,0),":/rec/black_ma.png");
    chess chess5(BLACK,XIANG,QPoint(2,0),":/rec/black_xiang.png");
    chess chess6(BLACK,XIANG,QPoint(6,0),":/rec/black_xiang.png");
    chess chess7(BLACK,SHI,QPoint(3,0),":/rec/black_shi.png");
    chess chess8(BLACK,SHI,QPoint(5,0),":/rec/black_shi.png");
    chess chess9(BLACK,KING,QPoint(4,0),":/rec/black_king.png");
    chess chess10(BLACK,PAO,QPoint(1,2),":/rec/black_pao.png");
    chess chess11(BLACK,PAO,QPoint(7,2),":/rec/black_pao.png");
    chess chess12(BLACK,ZU,QPoint(0,3),":/rec/black_bing.png");
    chess chess13(BLACK,ZU,QPoint(2,3),":/rec/black_bing.png");
    chess chess14(BLACK,ZU,QPoint(4,3),":/rec/black_bing.png");
    chess chess15(BLACK,ZU,QPoint(6,3),":/rec/black_bing.png");
    chess chess16(BLACK,ZU,QPoint(8,3),":/rec/black_bing.png");

    //初始化红方棋子
    chess chess_1(RED,JU,QPoint(0,9),":/rec/red_ju.png");
    chess chess_2(RED,JU,QPoint(8,9),":/rec/red_ju.png");
    chess chess_3(RED,MA,QPoint(1,9),":/rec/red_ma.png");
    chess chess_4(RED,MA,QPoint(7,9),":/rec/red_ma.png");
    chess chess_5(RED,XIANG,QPoint(2,9),":/rec/red_xiang.png");
    chess chess_6(RED,XIANG,QPoint(6,9),":/rec/red_xiang.png");
    chess chess_7(RED,SHI,QPoint(3,9),":/rec/red_shi.png");
    chess chess_8(RED,SHI,QPoint(5,9),":/rec/red_shi.png");
    chess chess_9(RED,KING,QPoint(4,9),":/rec/red_king.png");
    chess chess_10(RED,PAO,QPoint(1,7),":/rec/red_pao.png");
    chess chess_11(RED,PAO,QPoint(7,7),":/rec/red_pao.png");
    chess chess_12(RED,ZU,QPoint(0,6),":/rec/red_bing.png");
    chess chess_13(RED,ZU,QPoint(2,6),":/rec/red_bing.png");
    chess chess_14(RED,ZU,QPoint(4,6),":/rec/red_bing.png");
    chess chess_15(RED,ZU,QPoint(6,6),":/rec/red_bing.png");
    chess chess_16(RED,ZU,QPoint(8,6),":/rec/red_bing.png");

    my_chess.push_back(chess1);
    my_chess.push_back(chess2);
    my_chess.push_back(chess3);
    my_chess.push_back(chess4);
    my_chess.push_back(chess5);
    my_chess.push_back(chess6);
    my_chess.push_back(chess7);
    my_chess.push_back(chess8);
    my_chess.push_back(chess9);
    my_chess.push_back(chess10);
    my_chess.push_back(chess11);
    my_chess.push_back(chess12);
    my_chess.push_back(chess13);
    my_chess.push_back(chess14);
    my_chess.push_back(chess15);
    my_chess.push_back(chess16);

    my_chess.push_back(chess_1);
    my_chess.push_back(chess_2);
    my_chess.push_back(chess_3);
    my_chess.push_back(chess_4);
    my_chess.push_back(chess_5);
    my_chess.push_back(chess_6);
    my_chess.push_back(chess_7);
    my_chess.push_back(chess_8);
    my_chess.push_back(chess_9);
    my_chess.push_back(chess_10);
    my_chess.push_back(chess_11);
    my_chess.push_back(chess_12);
    my_chess.push_back(chess_13);
    my_chess.push_back(chess_14);
    my_chess.push_back(chess_15);
    my_chess.push_back(chess_16);

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    if(event->type())
    {

    }
    QPainter painter(this);
    QPixmap board(":/rec/board.png");
    painter.drawPixmap(0,0,board);
    for (int i=0;i<my_chess.size();++i) {
        if(my_chess[i].show==true)
        {
            DrawItem(painter,my_chess[i]);
        }
        else
        {
            continue;
        }
    }
    if(!isselected)
    {
        Drawframe(painter,my_chess[posid].pos);
    }
    update();
}

void MainWindow::DrawItem(QPainter& painter, chess item )
{
    QPixmap pix(item.route);
    painter.drawPixmap(INITROW+item.pos.x()*INTERVAL-INTERVAL/2,INITCOL+item.pos.y()*INTERVAL-INTERVAL/2,INTERVAL,INTERVAL,pix);
}

void MainWindow::Drawframe(QPainter& painter,QPoint p)
{
    painter.setPen(QPen(Qt::blue,4,Qt::DashLine));
    painter.drawRect(INITROW+p.x()*INTERVAL-INTERVAL/2,INITCOL+p.y()*INTERVAL-INTERVAL/2,INTERVAL,INTERVAL);
}




void MainWindow::on_start_clicked()
{
    bool i=false;
    while(!i)
    {
        i=startstyle();
    }

    bool j=false;
    while(!j)
    {
        j=entername();
    }

}

bool MainWindow::startstyle()
{
    bool ok;
    QStringList items;
    items<<"作为服务器启动"<<"作为客户端启动";
    QString item = QInputDialog::getItem(this,tr(""),tr("选择启动方式"),items,0,true,&ok);
    if(ok&&item==items[0])
    {
        recolor(RED);
        tcpserver = new QTcpServer(this);
        tcpsocket=new QTcpSocket(this);
        tcpserver->listen(QHostAddress::Any, 8888);
        connect(tcpserver, &QTcpServer::newConnection, this, &MainWindow::ConnectToClient);
        connectd=true;
        ui->pushButton->setEnabled(connectd);


        return ok;
    }
    else if(ok&&item==items[1])
    {
        recolor(BLACK);
        tcpsocket=new QTcpSocket(this);
        QString ip=ui->lineEdit->text();
        quint16 prot=( ui->lineEdit_2->text()).toUShort();
            //主动和服务器进行连接
        tcpsocket->abort();
        tcpsocket->connectToHost(ip, prot);
        connect(tcpsocket, &QTcpSocket::connected, this, &MainWindow::connectToServer);
        connect(tcpsocket, &QTcpSocket::readyRead, this, &MainWindow::ReadInformation);
        connectd=true;
        ui->pushButton->setEnabled(connectd);
        return ok;
    }
    else
    {
        QMessageBox::information(this,"","请选择启动方式");
        return ok;
    }
}

void MainWindow::connectToServer()
{
    ui->information->setText("成功和服务器进行连接");
}

void MainWindow::ConnectToClient()
{
    tcpsocket = tcpserver->nextPendingConnection();
    connect(tcpsocket, &QTcpSocket::readyRead, this, &MainWindow::ReadInformation);
    //获取对方的端口号和ip地址，并且显示在文本编辑框中。
    QString ip = tcpsocket->peerAddress().toString();
    quint16 port = tcpsocket->peerPort();

    ui->information->setText(QString("[%1:%2]连接成功").arg(ip).arg(port));

}


void MainWindow::ReadInformation()
{
    //获取套接字中的内容
    QString temp = tcpsocket->readAll();
    if(temp[0]=='0')
    {
        temp.replace(0,1,"");
        ui->information->append(temp);
    }
    else
    {
        QString i,j,k,m,p,n;
        if(temp.size()==6)
        {
            i=temp[1];
            j=temp[2];
            k=temp[3];
            m=temp[4];
            p=temp[5];
            my_chess[i.toInt()].show=j.toInt();
            my_chess[i.toInt()].pos=QPoint(k.toInt(),m.toInt());
            if(p.toInt()==0)
            isorder=RED;
            else
            isorder=BLACK;

        }
        else
        {
            i=temp[1];
            n=temp[2];
            j=temp[3];
            k=temp[4];
            m=temp[5];
            p=temp[6];
            int index=(i+n).toInt();
            my_chess[index].show=j.toInt();
            my_chess[index].pos=QPoint(k.toInt(),m.toInt());
            if(p.toInt()==0)
            isorder=RED;
            else
            isorder=BLACK;

        }


    }

}
void MainWindow::on_emits_clicked()
{
    if(isstart)
    {
        QString str1,str2;

        str1="0"+name+":"+ui->chat->toPlainText();
        str2=name+":"+ui->chat->toPlainText();
        tcpsocket->write(str1.toLatin1());
        ui->information->append(str2);
        ui->chat->clear();
    }

}



bool MainWindow::entername()
{
    bool ok;
    if(Local_color==RED)
    {
        name = QInputDialog::getText(this,tr("输入名字"),tr("名字"),QLineEdit::Normal,tr("Tom"),&ok);
        if(ok)
        {
            isstart=true;
            return ok;
        }
        else
        {
            QMessageBox::information(this,"","请输入名字");
            return ok;
        }
    }
    else
    {
        name = QInputDialog::getText(this,tr("输入名字"),tr("名字"),QLineEdit::Normal,tr("Jack"),&ok);
        if(ok)
        {
            isstart=true;
            return ok;
        }
        else
        {
            QMessageBox::information(this,"","请输入名字");
            return ok;
        }
    }

}
void MainWindow::getMove_JU(chess item,QVector<QPoint>& moveArea)
{
    int x = item.pos.x() - 1;
    while(x>=0)
    {
        QPoint ptNew = QPoint(x,item.pos.y());
        chess item2;
        if (FindItemAtPoint(ptNew ,item2))
        {
            if (item.color != item2.color)
            {
                moveArea.append(ptNew);
            }
            break;
        }
        moveArea.append(ptNew);
        x--;
    }
    //右边
    x = item.pos.x() + 1;
    while(x<=8)
    {
        QPoint ptNew = QPoint(x,item.pos.y());
        chess item2;
        if (FindItemAtPoint(ptNew ,item2))
        {
            if (item.color != item2.color)
            {
                moveArea.append(ptNew);
            }
            break;
        }
        moveArea.append(ptNew);
        x++;
    }

    //上边
    int y = item.pos.y() - 1;
    while(y>=0)
    {
        QPoint ptNew = QPoint(item.pos.x(),y);
        chess item2;
        if (FindItemAtPoint(ptNew ,item2))
        {
            if (item.color != item2.color)
            {
                moveArea.append(ptNew);
            }
            break;
        }
        moveArea.append(ptNew);
        y--;
    }
    //下方
    y = item.pos.y() + 1;
    while(y<=9)
    {
        QPoint ptNew = QPoint(item.pos.x(),y);
        chess item2;
        if (FindItemAtPoint(ptNew ,item2))
        {
            if (item.color != item2.color)
            {
                moveArea.append(ptNew);
            }
            break;
        }
        moveArea.append(ptNew);
        y++;
    }
}
void MainWindow::getMove_MA(chess item,QVector<QPoint>& moveArea)
{
    chess item2;
    for (int i = -2; i<=2; i++)
    {
        for(int j = -2; j<=2; j++)
        {
            if (qAbs(i) + qAbs(j) == 3)
            {
                QPoint ptNew = item.pos + QPoint(i,j);
                if (ptNew.x() >= 0 && ptNew.x() <= 8 && ptNew.y()>=0 && ptNew.y() <= 9)
                {

                }
                else
                {
                    continue;
                }

                //求该方向行走路线的 卡位元素位置
                QPoint ptDirect(0,0);
                if (qAbs(i) > qAbs(j))
                {
                    if (i>0)
                    {
                        ptDirect = QPoint(1,0);
                    }
                    else
                    {
                        ptDirect = QPoint(-1,0);
                    }
                }
                else
                {
                    if (j>0)
                    {
                        ptDirect = QPoint(0,1);
                    }
                    else
                    {
                        ptDirect = QPoint(0,-1);
                    }
                }
                QPoint ptHit = item.pos + ptDirect;	//马的卡位元素位置
                if (FindItemAtPoint(ptHit,item2))
                {
                    //卡位
                    continue;
                }
                if (FindItemAtPoint(ptNew ,item2) && item.color == item2.color)
                {
                    //有本组item
                    continue;
                }
                moveArea.append(ptNew);
            }
        }
    }
}
void MainWindow::getMove_XIANG(chess item,QVector<QPoint>& moveArea)
{
    QVector<QPoint> directions;
    directions.push_back(QPoint(-2,-2));
    directions.push_back(QPoint(2,-2));
    directions.push_back(QPoint(2,2));
    directions.push_back(QPoint(-2,2));

    for (int i = 0; i<directions.size(); i++)
    {
        QPoint ptNew = item.pos + directions[i];									//移动后的点
        if (item.pos.y() <= 4)														//上方的
        {
            if (ptNew.x() >= 0 && ptNew.x() <= 8 && ptNew.y()>=0 && ptNew.y() <= 4)		//移动后需仍在上半棋盘
            {

            }
            else
            {
                continue;
            }
        }
        else
        {
            if (ptNew.x() >= 0 && ptNew.x() <= 8 && ptNew.y()>=5 && ptNew.y() <= 9)		//移动后需仍在下半棋盘
            {

            }
            else
            {
                continue;
            }
        }

        QPoint ptHit = item.pos + QPoint(directions[i].x()/2,directions[i].y()/2);		//卡位点在中点
        chess item2;
        if (FindItemAtPoint(ptHit,item2))
        {
            //存在卡位棋子
            continue;
        }
        if (FindItemAtPoint(ptNew ,item2) && item.color == item2.color)
        {
            //终点是同色的棋子
            continue;
        }
        moveArea.append(ptNew);
    }
}
void MainWindow::getMove_KING(chess item,QVector<QPoint>& moveArea)
{
    QVector<QPoint> directions;
    directions.push_back(QPoint(-1,0));
    directions.push_back(QPoint(1,0));
    directions.push_back(QPoint(0,1));
    directions.push_back(QPoint(0,-1));

    for (int i = 0; i<directions.size(); i++)
    {
        QPoint ptNew = item.pos + directions[i];									//移动后的点
        if (item.pos.y() <= 4)														//上方的
        {
            if (ptNew.x() >= 3 && ptNew.x() <= 5 && ptNew.y()>=0 && ptNew.y() <= 2)		//移动后在上棋盘的(3,0)~(5,2)田字内
            {

            }
            else
            {
                continue;
            }
        }
        else
        {
            if (ptNew.x() >= 3 && ptNew.x() <= 5 && ptNew.y()>=7 && ptNew.y() <= 9)		//移动后需仍在下半棋盘
            {

            }
            else
            {
                continue;
            }
        }
        chess item2;
        if (FindItemAtPoint(ptNew ,item2) && item.color == item2.color)
        {
            //终点是同色的棋子
            continue;
        }
        moveArea.append(ptNew);
    }
}
void MainWindow::getMove_PAO(chess item,QVector<QPoint>& moveArea)
{
    bool bFind = false;
    int x = item.pos.x() - 1;
    while(x>=0)
    {
        QPoint ptNew = QPoint(x,item.pos.y());
        chess item2;
        if (FindItemAtPoint(ptNew ,item2))
        {
            if (bFind)
            {
                //如果之前找到过一个点，那么这是第2个点
                if(item.color != item2.color)
                {
                    //如果这第2个点是异色的，那么是可以吃的
                    moveArea.append(ptNew);
                }
                break;
            }
            bFind = true;
            x--;
            continue;
        }
        if (!bFind)
        {
            moveArea.append(ptNew);
        }
        x--;

    }
    //右边
    bFind = false;
    x = item.pos.x() + 1;
    while(x<=8)
    {
        QPoint ptNew = QPoint(x,item.pos.y());
        chess item2;
        if (FindItemAtPoint(ptNew ,item2))
        {
            if (bFind)
            {
                //如果之前找到过一个点，那么这是第2个点
                if(item.color != item2.color)
                {
                    //如果这第2个点是异色的，那么是可以吃的
                    moveArea.append(ptNew);
                }
                break;
            }
            bFind = true;
            x++;
            continue;
        }
        if (!bFind)
        {
            moveArea.append(ptNew);
        }
        x++;

    }

    //上边
    bFind = false;
    int y = item.pos.y() - 1;
    while(y>=0)
    {
        QPoint ptNew = QPoint(item.pos.x(),y);
        chess item2;
        if (FindItemAtPoint(ptNew ,item2))
        {
            if (bFind)
            {
                //如果之前找到过一个点，那么这是第2个点
                if(item.color != item2.color)
                {
                    //如果这第2个点是异色的，那么是可以吃的
                    moveArea.append(ptNew);
                }
                break;
            }
            bFind = true;
            y--;
            continue;
        }
        if (!bFind)
        {
            moveArea.append(ptNew);
        }
        y--;

    }
    //下方
    bFind = false;
    y = item.pos.y() + 1;
    while(y<=9)
    {
        QPoint ptNew = QPoint(item.pos.x(),y);
        chess item2;
        if (FindItemAtPoint(ptNew ,item2))
        {
            if (bFind)
            {
                //如果之前找到过一个点，那么这是第2个点
                if(item.color != item2.color)
                {
                    //如果这第2个点是异色的，那么是可以吃的
                    moveArea.append(ptNew);
                }
                break;
            }
            bFind = true;
            y++;
            continue;
        }
        if (!bFind)
        {
            moveArea.append(ptNew);
        }
        y++;

    }
}
void MainWindow::getMove_BING(chess item,QVector<QPoint>& moveArea)
{
    QVector<QPoint> directions;

    if (item.color==RED)
    {
        directions.push_back(QPoint(0,-1));	//红色上移
        if (item.pos.y() < 5 )			//红色在下方，y<5就是已经过河，可以横向移动
        {
            directions.push_back(QPoint(-1,0));
            directions.push_back(QPoint(1,0));
        }
    }
    else
    {
        directions.push_back(QPoint(0,1));	//黑色下移
        if (item.pos.y() >= 5 )			//黑色在上方，y>=5就是已经过河，可以横向移动
        {
            directions.push_back(QPoint(-1,0));
            directions.push_back(QPoint(1,0));
        }
    }

    for (int i = 0; i<directions.size(); i++)
    {
        QPoint ptNew = item.pos + directions[i];									//移动后的点
        if (ptNew.x() >= 0 && ptNew.x() <= 8 && ptNew.y()>=0 && ptNew.y() <= 9)		//移动后需仍在棋盘
        {

        }
        else
        {
            continue;
        }
        chess item2;
        if (FindItemAtPoint(ptNew ,item2) && item.color == item2.color)
        {
            //终点是同色的棋子
            continue;
        }
        moveArea.append(ptNew);
    }

}
void MainWindow::getMove_SHI(chess item,QVector<QPoint>& moveArea)
{
    QVector<QPoint> directions;
    directions.push_back(QPoint(-1,-1));
    directions.push_back(QPoint(1,-1));
    directions.push_back(QPoint(1,1));
    directions.push_back(QPoint(-1,1));

    for (int i = 0; i<directions.size(); i++)
    {
        QPoint ptNew = item.pos + directions[i];									//移动后的点
        if (item.pos.y() <= 4)														//上方的
        {
            if (ptNew.x() >= 3 && ptNew.x() <= 5 && ptNew.y()>=0 && ptNew.y() <= 2)		//移动后在上棋盘的(3,0)~(5,2)田字内
            {

            }
            else
            {
                continue;
            }
        }
        else
        {
            if (ptNew.x() >= 3 && ptNew.x() <= 5 && ptNew.y()>=7 && ptNew.y() <= 9)		//移动后需仍在下半棋盘
            {

            }
            else
            {
                continue;
            }
        }


        chess item2;

        if (FindItemAtPoint(ptNew ,item2) && item.color == item2.color)
        {
            //终点是同色的棋子
            continue;
        }
        moveArea.append(ptNew);
    }
}

bool MainWindow::FindItemAtPoint(QPoint pt,chess& item)
{
    for (int i = 0; i<my_chess.size(); i++)
    {
        if (my_chess[i].pos == pt)
        {
            item = my_chess[i];
            return true;
        }
    }
    return false;
}



void MainWindow::on_pushButton_clicked()
{
    if(Local_color==BLACK)
    {
        tcpsocket->disconnectFromHost();
        initchess();
        ui->pushButton->setEnabled(connectd);
        ui->information->clear();
        QMessageBox::information(this,"","success！！！");
    }
    else
    {
        tcpserver->close();
        initchess();
        ui->pushButton->setEnabled(connectd);
        ui->information->clear();
        QMessageBox::information(this,"","success！！！");
    }
}
