
#ifndef ANT_H
#define ANT_H
#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  类 说 明 :  蚁群算法实现类
//
//  作    者 :  wugsh
//
//  日    期 :  2010.04.20
//
//  版本说明 :  Ver1.00
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "common.h"
//定义蚂蚁类

class CAnt
{
public:
    CAnt(void);
    ~CAnt(void);

public:

    int m_CarOrderAry[N_MAX_CAR_COUNT];  //保存车辆的发车顺序，环游配送点前随机生成顺序

    ANT_VEHICLE m_CarAry[N_MAX_CAR_COUNT]; //车辆数组，保存车辆发车次数、走过行程、运送重量


    double m_dbQ; 	//[0,1)之间的浮点数，蚂蚁选择下一城市的时候使用的策略
                                    //如果生成的随机数 <   m_dbQ 则选择概率最大的城市作为下一城市（确定性搜索）
                                    //如果生成的随机数 >= m_dbQ 则对没去过的城市进行轮盘选择（探索性搜索）


    int m_AllowedCity[N_MAX_CITY_COUNT+1]; //没去过的城市，值为1表示没去过，为0表示去过了，配送站的编号为0，会重复去，不用管它。
    int m_nCityCount; //蚂蚁已经走过的城市数目
    int m_nCurCity; //当前在那个城市

    int m_nCurCarIndex; //当前是车队中的哪辆车在派送

    // 保存蚂蚁走过的路径
    // 注意！里面存的是 发车编号，城市编号，城市编号.......... 发车编号，城市编号，城市编号..........
    // 而不是单纯保存的城市编号，和传统的蚁群算法是有区别的
    int m_nPath[N_MAX_PATH];
    int m_nPathCount; //路径里的点个数

    double m_dbPathLength; //走过的路径长度

    bool m_blSearchFail; //搜索是否失败了

private:
    int ChooseNextCity(); //选择下一个城市
    void Move(); //蚂蚁在城市间移动

public:

    void Init(); //初始化
    void Search(); //搜索路径，派送所有城市
    void CalPathLen(); //计算走过的路径总长度

};

#endif // ANT_H
