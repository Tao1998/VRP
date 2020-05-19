#include "stdafx.h"
#include "common.h"


int CAR_COUNT=5;  //��������
int CITY_COUNT=20; //�������� ( ����������վ )

//��Ⱥ�㷨����
double ALPHA=1.0; //
double BETA=2.0; // 
int ANT_COUNT=15; //�������� 
int IT_COUNT=500; //��������


double ROU_MAX=0.95;  //��Ϣ�ش��ݲ����� (1-ROU)������Ϣ�صĻӷ��ٶ�
double ROU_MIN=0.2;  //��Ϣ�ش��ݲ�������Сֵ����ֹ˥����0
double ROU_REDU=0.95; //��Ϣ�ش��ݲ�����˥���ٶ�

double g_distance[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //�������м����
double g_Pheromone[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //�������м���Ϣ��

//���������ٶ�
double g_distance_BETA[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //�������м����
double g_Prob[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //�������м���Ϣ��

VEHICLE g_CarAry[N_MAX_CAR_COUNT]; //����������г̡�������غ���ʻ�ٶ�
CITY g_CityAry[N_MAX_CITY_COUNT+1]; //��¼ÿ�����е�����

double g_dbPathLenAry[N_MAX_IT_COUNT]; //��¼�������·������,
double g_dbPathAvgLenAry[N_MAX_IT_COUNT]; //��¼������ƽ��·������

CProgressCtrl* g_pc; //������ָ��

bool g_blLenInt=false; //�����Ƿ���������ȡ����
int g_nHTW=0; //���������Ƿ���ʱ�䴰���� 0 ��  1 Ӳʱ�䴰  2 ��ʱ�䴰

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  �� ;������ָ����Χ�ڵ��������
//
//  ˵ ������
//
//  �� �ڣ�int nLow �����������
//                     int nUpper ������������
//
//  �� �أ�int ,��Χ��[nLow,nUpper)
//
/////////////
int rnd(int nLow,int nUpper)
{
	return nLow+(nUpper-nLow)*rand()/(RAND_MAX+1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  �� ;������ָ����Χ�ڵ����������
//
//  ˵ ������
//
//  �� �ڣ�double dbLow �����������
//                     double dbUpper �����������
//
//  �� �أ�double  ,��Χ��[dbLow,dbUpper)
//
/////////////
double rnd(double dbLow,double dbUpper)
{
	double dbTemp=rand()/((double)RAND_MAX+1.0);
	return dbLow+dbTemp*(dbUpper-dbLow);
}

//���ظ�������������ȡ����ĸ�����
double ROUND(double dbX)
{
	return (double)((int)(dbX+0.5));
}

//��������ȡ��
double MAX(double dbA,double dbB)
{
	if (dbA>dbB)
		return dbA;
	else
		return dbB;
}

//��������ȡС
double MIN(double dbA,double dbB)
{
	if (dbA>dbB)
		return dbB;
	else
		return dbA;
}

//������ȡ��
int MAX(int A,int B)
{
	if (A>B)
		return A;
	else
		return B;
}

//������ȡС
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
