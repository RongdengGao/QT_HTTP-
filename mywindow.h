#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace Ui {
class mywindow;
class CarBaseMessage;
}



class mywindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mywindow(QWidget *parent = 0);
    ~mywindow();

    /*--andy-20180706-*/

    QString NAME;  //用于接受useid 对应的姓名

    QNetworkReply *m_Reply;
    QNetworkAccessManager *m_NetManger;
    /*-----end--------*/
private:
    Ui::mywindow *ui;

private slots:
    //获取车辆列表，基本属性
    void GetCarList(QNetworkReply *m_Reply);
    //获取车辆装备信息
    void GetCarEquipmentMessage(QNetworkReply *m_Reply);
    //传参合成新的url
    QString CreateUrl(QString str);
    //
    void GetManGPS(QNetworkReply *m_Reply);
};




#endif // MYWINDOW_H
