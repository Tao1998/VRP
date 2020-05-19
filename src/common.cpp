#include "common.h"
#include<math.h>
#include<string.h>
#include<stdlib.h>

int CAR_COUNT=5;  //车辆数量
int CARA_COUNT=5;  //车辆A数量
int CARB_COUNT=5;  //车辆B数量
int MAXA_WEIGHT=5; //车辆A的最大载重
int MAXB_WEIGHT=8; //车辆B的最大载重
int MAX_WEIGHT=0;  //车辆最大载重
double MAX_CITYWEIGHT=0;//城市最大载重
int CITY_COUNT=20; //城市数量 ( 不包含配送站 )
int MAXA_LENGTH=50;  //车辆A最大行驶距离
int MAXB_LENGTH=50;  //车辆B最大行驶距离
int MAX_LENGTH=0;    //车辆最大行驶距离
double MAX_CITYLENGTH=0;//城市之间最大距离

//蚁群算法参数
double ALPHA=1.0; //
double BETA=2.0; //
int ANT_COUNT=12; //蚂蚁数量
int IT_COUNT=1000; //迭代次数


double ROU_MAX=0.95;  //信息素传递参数， (1-ROU)就是信息素的挥发速度
double ROU_MIN=0.2;  //信息素传递参数的最小值，防止衰减到0
double ROU_REDU=0.95; //信息素传递参数的衰减速度

int situation=0;

double g_distance[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //两两城市间距离
double g_Pheromone[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //两两城市间信息素

//查表法，提高速度
double g_distance_BETA[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //两两城市间距离
double g_Prob[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //两两城市间信息素

VEHICLE g_CarAry[N_MAX_CAR_COUNT]; //车辆的最大行程、最大载重和行驶速度
CITY g_CityAry[N_MAX_CITY_COUNT+1]; //记录每个城市的坐标

double g_dbPathLenAry[N_MAX_IT_COUNT]; //记录各代最短路径长度,
double g_dbPathAvgLenAry[N_MAX_IT_COUNT]; //记录各代的平均路径长度

int best_ant[N_MAX_CITY_COUNT];
int best_ant_count;

//CProgressCtrl* g_pc; //进度条指针MFC

bool g_blLenInt=false; //距离是否四舍五入取整数
int g_nHTW=0; //物流配送是否有时间窗限制 0 无  1 硬时间窗  2 软时间窗

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  用 途：返回指定范围内的随机整数
//
//  说 明：无
//
//  接 口：int nLow 随机数的下限
//                     int nUpper 随整数的上限
//
//  返 回：int ,范围是[nLow,nUpper)
//
/////////////
int rnd(int nLow,int nUpper)
{
    return nLow+(nUpper-nLow)*rand()/(RAND_MAX+1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  用 途：返回指定范围内的随机浮点数
//
//  说 明：无
//
//  接 口：double dbLow 随机数的下限
//                     double dbUpper 随机数的上限
//
//  返 回：double  ,范围是[dbLow,dbUpper)
//
/////////////
double rnd(double dbLow,double dbUpper)
{
    double dbTemp=rand()/((double)RAND_MAX+1.0);
    return dbLow+dbTemp*(dbUpper-dbLow);
}

//返回浮点数四舍五入取整后的浮点数
double ROUND(double dbX)
{
    return (double)((int)(dbX+0.5));
}

//两浮点数取大
double MAX(double dbA,double dbB)
{
    if (dbA>dbB)
        return dbA;
    else
        return dbB;
}

//两浮点数取小
double MIN(double dbA,double dbB)
{
    if (dbA>dbB)
        return dbB;
    else
        return dbA;
}

//两整数取大
int MAX(int A,int B)
{
    if (A>B)
        return A;
    else
        return B;
}

//两整数取小
int MIN(int A,int B)
{
    if (A>B)
        return B;
    else
        return A;
}

QColor intColor(int index, int hues, int values, int maxValue, int minValue, int maxHue, int minHue, int sat, int alpha)
{
    /*
    Creates a QColor from a single index. Useful for stepping through a predefined list of colors.

    The argument *index* determines which color from the set will be returned. All other arguments determine what the set of predefined colors will be

    Colors are chosen by cycling across hues while varying the value (brightness).
    By default, this selects from a list of 9 hues.*/
    int ind = index % (hues * values);
    int indh = ind % hues;
    int indv = ind / hues;
    int v;
    if (values > 1)
        v = minValue + indv * ((maxValue-minValue) / (values-1));
    else
        v = maxValue;
    int h = minHue + (indh * (maxHue-minHue)) / hues;

    QColor c = QColor();
    c.setHsv(h, sat, v);
    c.setAlpha(alpha);
    return c;
}
//unsigned __int64 GetCycleCount()
//{
//	__asm _emit 0x0F;
//	__asm _emit 0x31;
//}
