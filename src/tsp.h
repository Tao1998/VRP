#ifndef TSP_H
#define TSP_H
#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  类 说 明 :  TSP类，蚁群算法和遗传算法相结合
//
//  作    者 :  wugsh
//
//  日    期 :  2010.04.20
//
//  版本说明 :  Ver1.00
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "common.h"
#include "Ant.h"

class CTSP
{
public:
    CTSP(void);
    ~CTSP(void);

private:
    double** m_pdbTempAry;	//临时保存信息素
    //CString GetFieldValue(CString strIniFile,CString strSection,CString strKey); //得到指定字段的值

private:
    double m_dbMaxQ; //城市间信息素的最大值
    double m_dbMinQ;  //城市间信息素的最小值
    double m_dbRatio; //信息素最大值和最小值之间的比值，提前计算好可以不必每次都计算


public:

    CAnt m_cAntAry[N_MAX_ANT_COUNT]; //定义蚂蚁数组

    CAnt m_global_best_ant; //保存全局最优秀的个体
    CAnt m_iteration_best_ant; //保存迭代最优蚂蚁
    CAnt m_vary_ant; //保存最优秀的个体变异产生的蚂蚁
    CAnt m_temp_ant; //临时蚂蚁，更新信息素的时候用

    double m_dbRou; //信息素传递参数，会动态改变的
    double m_dbMinLength; //路径最小长度

    int m_nBestPath[N_MAX_PATH]; //记录最佳路径
    int m_nBestPathCount; //最佳路径的点个数

    int m_nStep; //记下是第几代产生的最佳结果
    int m_nVaryStep; //记下变异产生的最佳结果的代数

    int m_nVaryCount; //变异成功的次数
    bool m_blVary; //最佳路径是否是变异产生的


public:

    void Init(); //初始化
    double Search(); //搜索佳路径里的点个数
    void SaveBestAnt(); //保存全局最优蚂蚁和迭代最优蚂蚁
    void UpdatePheromone(int nFlag); //更新环境信息素
    double GetGreedSearchLen(); //得到用贪心算法得到的路径长度

    //遗传算法部分
    void Propagate(); //交叉繁殖

    bool Vary(); //变异操作
    bool Vary_2(); //变异操作，另一种方式
    bool Vary_3(); //倒置变异

    bool CheckVaryAnt(CAnt ant);//检查变异蚂蚁是否符合要求

public:

    int GetCarNo(int nNode); //根据路径中的点编号得到这是第几辆车
    QString GetCarType(int nNode); //根据路径中的点编号得到车辆类型

    void CalCityDistance(); //计算两两城市间距离
    void SetParameterDefault(); //恢复算法参数为默认值

    void SetParameterRandom();//设置配送点坐标为随机值

    //void LoadDataFromIniFile(CString strIniFile); //从文本文件载入数据


};

#endif // TSP_H
