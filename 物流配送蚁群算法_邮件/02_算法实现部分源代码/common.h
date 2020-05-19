#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  
// ����ͷ�ļ�����������͹��ú���
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//���нṹ��
struct CITY
{
	double dbX; //X����
	double dbY; //Y����
	double dbW; //������������

	double dbTB; //ʱ�䴰��ʼʱ��
	double dbTE; //ʱ�䴰����ʱ��
	double dbTS; //����ʱ��

};

//�����ṹ��
struct VEHICLE
{
	double dbMaxLength; //��������г�
	double dbMaxWeight; //�����������
	double dbSpeed; //�����ٶ�
};

//���ϳ����ṹ��
struct ANT_VEHICLE
{
	//������ֵ��������վ��ʱ����0
	double dbMovedLength; //���������߹���·��
	double dbMovedWeight; //�����������͵�����

	//������ֵһֱ�ۼӣ���������վҲ����0
	double dbMovedTime;  //���������߹���ʱ��
	int nSendCount;                   //������������

};

const int N_MAX_CITY_COUNT=200; //���������� ( ����������վ )
const int N_MAX_ANT_COUNT=100; //�����������
const int N_MAX_CAR_COUNT=100;  //���������

const int N_MAX_IT_COUNT=10000; //����������

// �����߹���·�����ڵ����������������ԭ��Ϊ����Ҫ���� ���͵���+������
// �ڴ˽������õ��㹻��
const int N_MAX_PATH=1000;

const double DBQ=100.0;  //��Ϣ������
const double DB_MAX=10e9; //һ����־��

const double Pbest=0.05; //�����С����Ⱥ�㷨����������һ�������ҵ����Ž�ĸ���

//==========================================================================
const int R_MAX=5; //�������ٴ�û�н���������

const double Q_Min=0.2;  //ѡ����Ե���Сֵ
const double Q_Max=0.8;  //ѡ����Ե����ֵ
const double Q_POWER=1.0;  //ѡ����Եı仯����

//==========================================================================
extern int CAR_COUNT;  //��������
extern int CITY_COUNT;  //��������( ע�ⲻ��������վ!!! )

//��Ⱥ�㷨����
extern double ALPHA; //
extern double BETA; // 
extern int ANT_COUNT; //�������� 
extern int IT_COUNT; //��������

extern double ROU_MAX;  //��Ϣ�ش��ݲ����� (1-ROU)������Ϣ�صĻӷ��ٶ�
extern double ROU_MIN;  //��Ϣ�ش��ݲ�������Сֵ����ֹ˥����0
extern double ROU_REDU; //��Ϣ�ش��ݲ�����˥���ٶ�

extern double g_distance[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //�������м����
extern double g_Pheromone[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //�������м���Ϣ��

//���������ٶ�
extern double g_distance_BETA[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //�������м����
extern double g_Prob[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //�������м���Ϣ��

//���ⲿ�ı��ļ�����
extern VEHICLE g_CarAry[N_MAX_CAR_COUNT]; //��������г̺��������
extern CITY g_CityAry[N_MAX_CITY_COUNT+1]; //��¼ÿ�����е�����ͻ���������

extern CProgressCtrl* g_pc;

extern bool g_blLenInt; //�����Ƿ���������ȡ����
extern int g_nHTW; //���������Ƿ���ʱ�䴰���� 0 ��  1 Ӳʱ�䴰  2 ��ʱ�䴰

extern double g_dbPathLenAry[N_MAX_IT_COUNT]; //��¼�������·��,����¼10000��
extern double g_dbPathAvgLenAry[N_MAX_IT_COUNT]; //��¼������ƽ��·������

//���ú���
extern int rnd(int nLow,int nUpper);
extern double rnd(double dbLow,double dbUpper);
extern double ROUND(double dbX);
extern double MAX(double dbA,double dbB);
extern double MIN(double dbA,double dbB);
extern int MAX(int A,int B);
extern int MIN(int A,int B);

//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

//���嶯̬���ɶ�ά�����ģ��
template <class T> T** Create2DArray(int M,int N) 
{ 
 //   T** pAry=(T**)malloc(M*sizeof(T*));
 //   for (int i=0;i<M;i++)
 //   {
 //       *(pAry+i)=(T*)malloc(N*sizeof(T));
 //   }
//   return pAry;

	T **pAry=new T *[M];
	for (int i=0; i<M; i++) 
	{
		pAry[i] = new T[N];
	}

	return pAry;
}

//�����ͷŶ�̬���ɵĶ�ά�����ģ��
template <class T> void Free2DArray(T** pAry,int M)
{
	if (pAry == NULL)
	{
		return;
	}

	for (int i=0;i<M; i++) 
	{
		delete []pAry[i];
	}
	delete []pAry;
	pAry=NULL;

	//for (int i=0; i<M; i++) 
	//{
	//	delete *(pAry+i);
	//}
	//delete []pAry;
}

