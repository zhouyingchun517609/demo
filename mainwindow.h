#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMouseEvent>
#include <QPixmap>
#include<QString>
#include<QVector>
#include<QPaintEvent>
#include<QPainter>
#include"chess.h"
#include<QLabel>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *event);//鼠标按键消息重写
    void initchess();                        //初始化棋子数据
    void paintEvent(QPaintEvent *event);        //绘图消息重写
    void DrawItem(QPainter& painter, chess item );//绘制棋子
    void Drawframe(QPainter& painter,QPoint p);//绘制选定框
    void colorchange(COLOR & c);

    bool FindItemAtPoint(QPoint pt,chess& item);
    void recolor(COLOR c);

    void GetMoveArea(QVector<QPoint>& moveArea,int posid);
    void getMove_JU(chess item,QVector<QPoint>& moveArea);
    void getMove_MA(chess item,QVector<QPoint>& moveArea);
    void getMove_XIANG(chess item,QVector<QPoint>& moveArea);
    void getMove_KING(chess item,QVector<QPoint>& moveArea);
    void getMove_PAO(chess item,QVector<QPoint>& moveArea);
    void getMove_BING(chess item,QVector<QPoint>& moveArea);
    void getMove_SHI(chess item,QVector<QPoint>& moveArea);


    void ReadInformation();
    void connectToServer();


    bool startstyle();
    bool entername();
    void gameend();

private slots:
    void on_start_clicked();
    void ConnectToClient();

    void on_emits_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<chess> my_chess;
    bool isstart;
    bool isselected;
    int posid;
    COLOR isorder;
    COLOR Local_color;
    QString name;
    QTcpServer * tcpserver=nullptr;
    QTcpSocket * tcpsocket=nullptr;
    bool connectd;
};

#endif // MAINWINDOW_H
