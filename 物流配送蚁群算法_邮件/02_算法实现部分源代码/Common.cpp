#include "stdafx.h"
#include "common.h"


int CAR_COUNT=5;  //车辆数量
int CITY_COUNT=20; //城市数量 ( 不包含配送站 )

//蚁群算法参数
double ALPHA=1.0; //
double BETA=2.0; // 
int ANT_COUNT=15; //蚂蚁数量 
int IT_COUNT=500; //迭代次数


double ROU_MAX=0.95;  //信息素传递参数， (1-ROU)就是信息素的挥发速度
double ROU_MIN=0.2;  //信息素传递参数的最小值，防止衰减到0
double ROU_REDU=0.95; //信息素传递参数的衰减速度

double g_distance[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //两两城市间距离
double g_Pheromone[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //两两城市间信息素

//查表法，提高速度
double g_distance_BETA[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //两两城市间距离
double g_Prob[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //两两城市间信息素

VEHICLE g_CarAry[N_MAX_CAR_COUNT]; //车辆的最大行程、最大载重和行驶速度
CITY g_CityAry[N_MAX_CITY_COUNT+1]; //记录每个城市的坐标

double g_dbPathLenAry[N_MAX_IT_COUNT]; //记录各代最短路径长度,
double g_dbPathAvgLenAry[N_MAX_IT_COUNT]; //记录各代的平均路径长度

CProgressCtrl* g_pc; //进度条指针

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

//unsigned __int64 GetCycleCount()
//{
//	__asm _emit 0x0F;
//	__asm _emit 0x31;
//}
