#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  
// 公共头文件，定义变量和公用函数
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//城市结构体
struct CITY
{
	double dbX; //X坐标
	double dbY; //Y坐标
	double dbW; //货物需求重量

	double dbTB; //时间窗开始时间
	double dbTE; //时间窗结束时间
	double dbTS; //服务时间

};

//车辆结构体
struct VEHICLE
{
	double dbMaxLength; //车辆最大行程
	double dbMaxWeight; //车辆最大载重
	double dbSpeed; //车辆速度
};

//蚂蚁车辆结构体
struct ANT_VEHICLE
{
	//这两个值返回配送站的时候会归0
	double dbMovedLength; //车辆派送走过的路程
	double dbMovedWeight; //车辆派送运送的重量

	//这两个值一直累加，返回配送站也不归0
	double dbMovedTime;  //车辆派送走过的时间
	int nSendCount;                   //车辆发车次数

};

const int N_MAX_CITY_COUNT=200; //最大城市数量 ( 不包含配送站 )
const int N_MAX_ANT_COUNT=100; //最大蚂蚁数量
const int N_MAX_CAR_COUNT=100;  //最大车辆数量

const int N_MAX_IT_COUNT=10000; //最大迭代次数

// 蚂蚁走过的路径最大节点个数，这个数定义的原则为至少要大于 配送点数+车辆数
// 在此将其设置的足够大。
const int N_MAX_PATH=1000;

const double DBQ=100.0;  //信息素总量
const double DB_MAX=10e9; //一个标志数

const double Pbest=0.05; //最大最小蚂蚁群算法参数，蚂蚁一次搜索找到最优解的概率

//==========================================================================
const int R_MAX=5; //连续多少次没有进化的上限

const double Q_Min=0.2;  //选择策略的最小值
const double Q_Max=0.8;  //选择策略的最大值
const double Q_POWER=1.0;  //选择策略的变化趋势

//==========================================================================
extern int CAR_COUNT;  //车辆数量
extern int CITY_COUNT;  //城市数量( 注意不包括配送站!!! )

//蚁群算法参数
extern double ALPHA; //
extern double BETA; // 
extern int ANT_COUNT; //蚂蚁数量 
extern int IT_COUNT; //迭代次数

extern double ROU_MAX;  //信息素传递参数， (1-ROU)就是信息素的挥发速度
extern double ROU_MIN;  //信息素传递参数的最小值，防止衰减到0
extern double ROU_REDU; //信息素传递参数的衰减速度

extern double g_distance[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //两两城市间距离
extern double g_Pheromone[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //两两城市间信息素

//查表法，提高速度
extern double g_distance_BETA[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //两两城市间距离
extern double g_Prob[N_MAX_CITY_COUNT+1][N_MAX_CITY_COUNT+1]; //两两城市间信息素

//从外部文本文件读入
extern VEHICLE g_CarAry[N_MAX_CAR_COUNT]; //车的最大行程和最大载重
extern CITY g_CityAry[N_MAX_CITY_COUNT+1]; //记录每个城市的坐标和货物需求量

extern CProgressCtrl* g_pc;

extern bool g_blLenInt; //距离是否四舍五入取整数
extern int g_nHTW; //物流配送是否有时间窗限制 0 无  1 硬时间窗  2 软时间窗

extern double g_dbPathLenAry[N_MAX_IT_COUNT]; //记录各代最短路径,最多记录10000代
extern double g_dbPathAvgLenAry[N_MAX_IT_COUNT]; //记录各代的平均路径长度

//公用函数
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

//定义动态生成二维数组的模板
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

//定义释放动态生成的二维数组的模板
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

