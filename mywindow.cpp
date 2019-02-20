#include "mywindow.h"
#include "ui_mywindow.h"
#include "carbasemessage.h"
#include "carequipmentmessage.h"

#include <QDebug>
#include <QUrl>
#include <QList>
#include <QString>
#include <QVariant>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

mywindow::mywindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mywindow)
{
    ui->setupUi(this);
    /*--andy-20180730-*/
    //实例化
    m_NetManger=new QNetworkAccessManager(this);

    //获取车辆列表槽函数
    // QObject::connect(m_NetManger, SIGNAL(finished(QNetworkReply*)),this,SLOT(GetCarList(QNetworkReply*)));

    //获取车载装备信息槽函数
    QObject::connect(m_NetManger, SIGNAL(finished(QNetworkReply*)),this,SLOT(GetManGPS(QNetworkReply*)));

    //获取车辆列表 ----url
    // QUrl url("http://47.95.145.109:8304/business/fire-engine/details");

    //获取车辆Id为1388的车载装备信息
   // QUrl url(CreateUrl("25"));

    //测试人员位置信息接口
    QUrl url("http://223.255.20.34:8686/handLocation/get");

    //访问接口
    m_Reply=m_NetManger->get(QNetworkRequest(url));
    /*------end------*/

}

mywindow::~mywindow()
{
    delete ui;
}
//通过ID获取车载装备信息
QString mywindow::CreateUrl(QString str)
{
    QString s1 = "http://47.93.125.232:8304/business/fire-engine/equips-details/";
    QString s3 = s1+str;
    return s3;
}
//获取基础车辆列表
void mywindow::GetCarList(QNetworkReply *m_Reply)
{
    m_Reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    m_Reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    if (m_Reply->error() == QNetworkReply::NoError)
    {
        //接收数据
        QByteArray bytes = m_Reply->readAll();

        //数据解析
        QJsonDocument doc = QJsonDocument::fromJson(bytes);
        QJsonObject json_obj = doc.object();
        QJsonValue val = json_obj["dataList"];
        QJsonArray array = val.toArray();
        CarBaseMessage *cbm = new CarBaseMessage();

        for(int i =0;i<array.count();i++)
        {
            val = array[i];
            QJsonObject obj = val.toObject();

            //所属中队
            val = obj["companyName"];
            cbm->CompanyName=val.toString();
            qDebug()<<cbm->CompanyName;
            // 车辆类型
            val = obj["fireEngineCategory"];
            cbm->FireEngineCategory=val.toString();
            qDebug()<<cbm->FireEngineCategory;
            //车牌号码
            val = obj["fireEngineNum"];
            cbm->FireEngineNum=val.toString();
            qDebug()<<cbm->FireEngineNum;
            //车辆唯一ID
            val = obj["fireEngineId"];
            cbm->FireEngineId =QString::number(val.toInt());
            qDebug()<<cbm->FireEngineId;
        }
    }
    else
    {
        QString str = m_Reply->errorString();
        qDebug()<<str;
    }
    m_Reply->deleteLater();
}
//获取车载装备信息
void mywindow::GetCarEquipmentMessage(QNetworkReply *m_Reply)
{
    m_Reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    m_Reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    if (m_Reply->error() == QNetworkReply::NoError)
    {
        //接收数据
        QByteArray bytes = m_Reply->readAll();

        //数据解析
        QJsonDocument doc = QJsonDocument::fromJson(bytes);
        QJsonObject json_obj = doc.object();

        QJsonValue val = json_obj["dataList"];
        QJsonObject obj = val.toObject();
        QJsonValue car = obj["fireEngineId"];
        QString carId = QString::number(car.toInt());
        //qDebug()<<"车辆Id:"<<carId;

        QJsonValue equipmentMessage = obj["equipDetails"];
        QJsonArray array = equipmentMessage.toArray();

        //qDebug()<<"数组长度："<<array.count();
        CarEquipmentMessage *cem = new CarEquipmentMessage();
        QString s = "";
        for(int i =0;i<array.count();i++)
        {
            val = array[i];
            QJsonObject obj = val.toObject();
            //车辆ID
            cem->Id = carId;
            //装备名称
            val = obj["equipName"];
            cem->EquipName=val.toString();
            //qDebug()<< cem->EquipName;

            s+=cem->EquipName;
            //装备编号
            val = obj["equipNum"];
            cem->EquipNum=val.toString();
            //qDebug()<< cem->EquipNum;
            s+=cem->EquipNum;
            //当前状态
            val = obj["state"];
            cem->State=QString::number(val.toInt());
            s+=cem->State;
            //qDebug()<< cem->State;
            s+="\\";
        }
        qDebug()<<s;
    }
    else
    {
        QString str = m_Reply->errorString();
        qDebug()<<str;
    }

    m_Reply->deleteLater();
}
//
void mywindow::GetManGPS(QNetworkReply *m_Reply)
{
    m_Reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    m_Reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    if (m_Reply->error() == QNetworkReply::NoError)
    {
        //接收数据
        QByteArray bytes = m_Reply->readAll();
        qDebug()<<bytes;
        //数据解析
//        QJsonDocument doc = QJsonDocument::fromJson(bytes);
//        QJsonObject json_obj = doc.object();
//        QJsonValue val = json_obj["data"];
//        QJsonArray array = val.toArray();
//        CarBaseMessage *cbm = new CarBaseMessage();

//        for(int i =0;i<array.count();i++)
//        {
//            val = array[i];
//            QJsonObject obj = val.toObject();

//            //所属中队
//            val = obj["companyName"];
//            cbm->CompanyName=val.toString();
//            qDebug()<<cbm->CompanyName;
//            // 车辆类型
//            val = obj["fireEngineCategory"];
//            cbm->FireEngineCategory=val.toString();
//            qDebug()<<cbm->FireEngineCategory;
//            //车牌号码
//            val = obj["fireEngineNum"];
//            cbm->FireEngineNum=val.toString();
//            qDebug()<<cbm->FireEngineNum;
//            //车辆唯一ID
//            val = obj["fireEngineId"];
//            cbm->FireEngineId =QString::number(val.toInt());
//            qDebug()<<cbm->FireEngineId;
//        }
    }
    else
    {
        QString str = m_Reply->errorString();
        qDebug()<<str;
    }
    m_Reply->deleteLater();
}
