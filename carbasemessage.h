#ifndef CARBASEMESSAGE_H
#define CARBASEMESSAGE_H

#include <QString>

//车辆基本信息
class CarBaseMessage{

public:
    QString CompanyName; //所属中队
    QString FireEngineCategory; // 车辆类型
    QString FireEngineNum; //车牌号码
    QString FireEngineId; //车辆唯一ID
};

//车载装备信息
class CarEquipmentMessage{

public:
    QString Id; //车辆ID
    QString EquipName; //装备名称
    QString EquipNum; //装备数量
    QString State; //当前状态

};


#endif // CARBASEMESSAGE_H
