#include ".\tsp.h"
#include<math.h>
#include<string.h>
#include<QDebug>
#include<cstdlib>
#include<ctime>

CTSP::CTSP(void)
{
    m_pdbTempAry=Create2DArray<double>(N_MAX_CITY_COUNT+1,N_MAX_CITY_COUNT+1);
}

CTSP::~CTSP(void)
{
    Free2DArray(m_pdbTempAry,N_MAX_CITY_COUNT+1);
}

//设置配送点坐标为随机值
void CTSP::SetParameterRandom()
{
    qDebug()<<"SetParameterRandom";
    //先把城市数量和车辆数量设置为默认

    //CAR_COUNT=5; //设置车辆数
    situation=0;

    //蚁群算法参数
    ALPHA=1.0; //
    BETA=2.0; //
    //ANT_COUNT=CITY_COUNT*3/5; //蚂蚁数量
    if (ANT_COUNT == 0)
    {
        ANT_COUNT=1;
    }

    //IT_COUNT=1000; //迭代次数

    ROU_MAX=0.95;  //信息素传递参数， (1-ROU)就是信息素的挥发速度
    ROU_MIN=0.2;  //信息素传递参数的最小值，防止衰减到0
    ROU_REDU=0.95; //信息素传递参数的衰减速度


    //设置城市和车辆信息
    /*
    for (int i=0;i<CAR_COUNT;i++)
    {
        g_CarAry[i].dbMaxLength=50.0;
        g_CarAry[i].dbMaxWeight=8.0;
        g_CarAry[i].dbSpeed=1.0;
    }
    */



    g_CityAry[0].dbX=(rnd(0.0,100.0))/5;g_CityAry[0].dbY=(rnd(0.0,100.0))/5;g_CityAry[0].dbW=0.0; //配送站

    for(int i=1;i<=CITY_COUNT;i++)
    {
        g_CityAry[i].dbX=(rnd(0.0,100.0))/5;
        g_CityAry[i].dbY=(rnd(0.0,100.0))/5;
        g_CityAry[i].dbW=(rnd(0.0,10.0))/5;
        if(g_CityAry[i].dbW>MAX_CITYWEIGHT)
            MAX_CITYWEIGHT=g_CityAry[i].dbW;
        qDebug()<<"X:"<<g_CityAry[i].dbX<<"  Y:"<<g_CityAry[i].dbY;
    }

    // min—max标准化 美化GUI 让点落在中心区域
    int dbx_max=g_CityAry[0].dbX, dbx_min=g_CityAry[0].dbX,dby_max=g_CityAry[0].dbY, dby_min=g_CityAry[0].dbY;
    for(int i=0;i<=CITY_COUNT;i++)
    {
        if(g_CityAry[i].dbX<dbx_min)
            dbx_min = g_CityAry[i].dbX;
        if(g_CityAry[i].dbX>dbx_max)
            dbx_max = g_CityAry[i].dbX;
        if(g_CityAry[i].dbY<dby_min)
            dby_min = g_CityAry[i].dbY;
        if(g_CityAry[i].dbY>dby_max)
            dby_max = g_CityAry[i].dbY;
    }
    int dbx_d = dbx_max-dbx_min, dby_d = dby_max-dby_min;
    for(int i=0;i<=CITY_COUNT;i++)
    {
        g_CityAry[i].dbX_draw = (g_CityAry[i].dbX-dbx_min) / dbx_d * 100;
        g_CityAry[i].dbY_draw = (g_CityAry[i].dbY-dby_min) / dby_d * 100;
    }

    //计算两两城市间距离
    CalCityDistance();

}

void CTSP::GetCarData()
{
    int idx = 0;
    int id=0;
    for(int i=0;i<TYPE_COUNT;i++)
    {
        for(int j=0;j<CAR_TYPE_COUNT[i];j++)
        {
            g_CarAry[idx].dbMaxLength=CAR_TYPE_MAX_LENGTH[i];
            g_CarAry[idx].dbMaxWeight=CAR_TYPE_MAX_WEIGHT[i];
            g_CarAry[idx].dbSpeed=1.0;
            id=idx;
            qDebug()<<QString::number(id, 10)<<" "<<CAR_TYPE_MAX_WEIGHT[i]<<" "<<CAR_TYPE_MAX_WEIGHT[i];
            idx++;
        }
    }
}

//恢复算法参数为默认值
void CTSP::SetParameterDefault()
{
    //先把城市数量和车辆数量设置为默认

    CAR_COUNT=5; //设置车辆数
    CITY_COUNT=20; //设置城市数量
    situation=0;

    //蚁群算法参数
    ALPHA=1.0; //
    BETA=2.0; //
    //ANT_COUNT=CITY_COUNT*3/5; //蚂蚁数量
    if (ANT_COUNT == 0)
    {
        ANT_COUNT=1;
    }

    //IT_COUNT=1000; //迭代次数

    ROU_MAX=0.95;  //信息素传递参数， (1-ROU)就是信息素的挥发速度
    ROU_MIN=0.2;  //信息素传递参数的最小值，防止衰减到0
    ROU_REDU=0.95; //信息素传递参数的衰减速度


    //设置城市和车辆信息
    for (int i=0;i<CAR_COUNT;i++)
    {
        g_CarAry[i].dbMaxLength=50.0;
        g_CarAry[i].dbMaxWeight=8.0;
        g_CarAry[i].dbSpeed=1.0;
    }

    g_CityAry[0].dbX=14.5;g_CityAry[0].dbY=13.0;g_CityAry[0].dbW=0.0; //配送点

    g_CityAry[1].dbX=12.8;g_CityAry[1].dbY=8.5;g_CityAry[1].dbW=0.1;
    g_CityAry[2].dbX=18.4;g_CityAry[2].dbY=3.4;g_CityAry[2].dbW=0.4;
    g_CityAry[3].dbX=15.4;g_CityAry[3].dbY=16.6;g_CityAry[3].dbW=1.2;
    g_CityAry[4].dbX=18.9;g_CityAry[4].dbY=15.2;g_CityAry[4].dbW=1.5;
    g_CityAry[5].dbX=15.5;g_CityAry[5].dbY=11.6;g_CityAry[5].dbW=0.8;

    g_CityAry[6].dbX=3.9;g_CityAry[6].dbY=10.6;g_CityAry[6].dbW=1.3;
    g_CityAry[7].dbX=10.6;g_CityAry[7].dbY=7.6;g_CityAry[7].dbW=1.7;
    g_CityAry[8].dbX=8.6;g_CityAry[8].dbY=8.4;g_CityAry[8].dbW=0.6;
    g_CityAry[9].dbX=12.5;g_CityAry[9].dbY=2.1;g_CityAry[9].dbW=1.2;
    g_CityAry[10].dbX=13.8;g_CityAry[10].dbY=5.2;g_CityAry[10].dbW=0.4;

    g_CityAry[11].dbX=6.7;g_CityAry[11].dbY=16.9;g_CityAry[11].dbW=0.9;
    g_CityAry[12].dbX=14.8;g_CityAry[12].dbY=2.6;g_CityAry[12].dbW=1.3;
    g_CityAry[13].dbX=1.8;g_CityAry[13].dbY=8.7;g_CityAry[13].dbW=1.3;
    g_CityAry[14].dbX=17.1;g_CityAry[14].dbY=11.0;g_CityAry[14].dbW=1.9;
    g_CityAry[15].dbX=7.4;g_CityAry[15].dbY=1.0;g_CityAry[15].dbW=1.7;

    g_CityAry[16].dbX=0.2;g_CityAry[16].dbY=2.8;g_CityAry[16].dbW=1.1;
    g_CityAry[17].dbX=11.9;g_CityAry[17].dbY=19.8;g_CityAry[17].dbW=1.5;
    g_CityAry[18].dbX=13.2;g_CityAry[18].dbY=15.1;g_CityAry[18].dbW=1.6;
    g_CityAry[19].dbX=6.4;g_CityAry[19].dbY=5.6;g_CityAry[19].dbW=1.7;
    g_CityAry[20].dbX=9.6;g_CityAry[20].dbY=14.8;g_CityAry[20].dbW=1.5;

    // min—max标准化 美化GUI 让点落在中心区域
    int dbx_max=g_CityAry[0].dbX, dbx_min=g_CityAry[0].dbX,dby_max=g_CityAry[0].dbY, dby_min=g_CityAry[0].dbY;
    for(int i=0;i<=CITY_COUNT;i++)
    {
        if(g_CityAry[i].dbX<dbx_min)
            dbx_min = g_CityAry[i].dbX;
        if(g_CityAry[i].dbX>dbx_max)
            dbx_max = g_CityAry[i].dbX;
        if(g_CityAry[i].dbY<dby_min)
            dby_min = g_CityAry[i].dbY;
        if(g_CityAry[i].dbY>dby_max)
            dby_max = g_CityAry[i].dbY;
    }
    int dbx_d = dbx_max-dbx_min, dby_d = dby_max-dby_min;
    for(int i=0;i<=CITY_COUNT;i++)
    {
        g_CityAry[i].dbX_draw = (g_CityAry[i].dbX-dbx_min) / dbx_d * 100;
        g_CityAry[i].dbY_draw = (g_CityAry[i].dbY-dby_min) / dby_d * 100;
    }

    //计算两两城市间距离
    CalCityDistance();

}


//计算两两城市间距离
void CTSP::CalCityDistance()
{
    //计算两两城市间距离
    double dbTemp=0.0;
    double db_x=0.0;
    double db_y=0.0;
    for (int i=0;i<=CITY_COUNT;i++)
    {
        for (int j=0;j<=CITY_COUNT;j++)
        {
            //勾股定理计算两点间距离
            db_x=g_CityAry[i].dbX-g_CityAry[j].dbX;
            db_y=g_CityAry[i].dbY-g_CityAry[j].dbY;
            dbTemp=pow(db_x,2.0)+pow(db_y,2.0);

            if (g_blLenInt)
            {
                g_distance[i][j]=ROUND(pow(dbTemp,0.5));
                if(g_distance[i][j]>MAX_CITYLENGTH)
                    MAX_CITYLENGTH=g_distance[i][j];
            }
            else
            {
                g_distance[i][j]=pow(dbTemp,0.5);
                if(g_distance[i][j]>MAX_CITYLENGTH)
                    MAX_CITYLENGTH=g_distance[i][j];
            }

            if (i == j)
            {
                g_distance_BETA[i][j]=0.0;
            }
            else
            {
                g_distance_BETA[i][j]=pow(1.0/g_distance[i][j],BETA);
            }

        }
    }
}

//得到指定字段的值
//CString CTSP::GetFieldValue(CString strIniFile,CString strSection,CString strKey)
//{
//	char cValue[256];
//	::GetPrivateProfileStringA(strSection,strKey,"",cValue,255,strIniFile);
//	return CString(cValue);
//}


//从ini文件载入数据
//计算两两城市间距离
//此初始化,如果算法的参数没有改变,只需要调用一次
//void CTSP::LoadDataFromIniFile(CString strIniFile)
//{

//	//从外部文本文件读取所需要的数据
//	//注意!这里假定文件的数据都是正确的,不对读入数据进行校验,请自行确认文本文件中的数据正确

//	CITY_COUNT=atoi(GetFieldValue(strIniFile,"tsp_data","city_count"));
//	ANT_COUNT=CITY_COUNT*3/5; //蚂蚁数量
//	if (ANT_COUNT == 0) //最少要有1只蚂蚁
//	{
//		ANT_COUNT=1;
//	}


//	//读取车辆数据
//	CAR_COUNT=atoi(GetFieldValue(strIniFile,"tsp_data","car_count"));
//	CString strField="";
//	for (int i=0; i<CAR_COUNT;i++)
//	{
//		strField.Format("car_w_%d",i);
//		g_CarAry[i].dbMaxWeight=atof(GetFieldValue(strIniFile,"car_data",strField));

//		strField.Format("car_l_%d",i);
//		g_CarAry[i].dbMaxLength=atof(GetFieldValue(strIniFile,"car_data",strField));

//		strField.Format("car_s_%d",i);
//		g_CarAry[i].dbSpeed=atof(GetFieldValue(strIniFile,"car_data",strField));

//		if (g_CarAry[i].dbSpeed <=0.0)
//		{
//			g_CarAry[i].dbSpeed =1.0; //防止除0溢出
//		}
//	}

//	//读取城市数据
//	CString strTemp="";
//	for (int i=0;i<=CITY_COUNT;i++)
//	{
//		strField.Format("city_x_%d",i);
//		g_CityAry[i].dbX=atof(GetFieldValue(strIniFile,"city_data",strField));

//		strField.Format("city_y_%d",i);
//		g_CityAry[i].dbY=atof(GetFieldValue(strIniFile,"city_data",strField));

//		strField.Format("city_w_%d",i);
//		g_CityAry[i].dbW=atof(GetFieldValue(strIniFile,"city_data",strField));

//		strField.Format("city_tb_%d",i);
//		g_CityAry[i].dbTB=atof(GetFieldValue(strIniFile,"city_data",strField));

//		strField.Format("city_te_%d",i);
//		g_CityAry[i].dbTE=atof(GetFieldValue(strIniFile,"city_data",strField));

//		strField.Format("city_ts_%d",i);
//		g_CityAry[i].dbTS=atof(GetFieldValue(strIniFile,"city_data",strField));

//		strTemp.Format("%.0f,%.0f,%.0f,%.0f,%.0f,%.0f\n",g_CityAry[i].dbX,g_CityAry[i].dbY,g_CityAry[i].dbW,g_CityAry[i].dbTB,g_CityAry[i].dbTE,g_CityAry[i].dbTS);
//		TRACE0(strTemp);

//	}

//	//计算两两城市间距离
//	CalCityDistance();

//}

//初始化城市间的信息素
void CTSP::Init()
{
    //初始化信息素传递参数
    m_dbRou=ROU_MAX;//0.95

    //===============================================================
    //计算最大信息素和最小信息素之间的比值
    //dbTemp=pow(Pbest,1.0/(double)CITY_COUNT); //对Pbest开CITY_COUNT次方
    double dbN=(double)(CITY_COUNT+1); //因为城市数量没有包含配送站，所以加上1
    double dbTemp=exp(log(Pbest)/dbN); //对Pbest开方(最大最小蚂蚁群算法参数，蚂蚁一次搜索找到最优解的概率)
    //m_dbRatio=(1.0-dbTemp)/((dbN/2.0-1.0)*dbTemp);
    m_dbRatio=(2.0/dbTemp-2.0)/(dbN-2.0);

    //===============================================================
    //初始化环境信息素，先设置的足够大，那么第一次迭代完成后，会设置成MaxQ(1),然后往后就会限制在上下限之间
    for (int i=0;i<=CITY_COUNT;i++)
    {
        for (int j=0;j<=CITY_COUNT;j++)
        {
            g_Pheromone[i][j]=DBQ;
        }
    }

    //==================================================================
    //计算两两城市间的选择概率值
    for (int i=0;i<=CITY_COUNT;i++)
    {
        for (int j=0;j<=CITY_COUNT;j++)
        {
            g_Prob[i][j]=pow(g_Pheromone[i][j],ALPHA)*g_distance_BETA[i][j];//信息素为分子，可见性为分母
        }
    }


    //先把最优秀蚂蚁走过的路径设置为一个足够大的值
    m_global_best_ant.m_dbPathLength=DB_MAX; //10e9

    //代数设置为0
    m_nStep=0;

    //是否是变异产生的最佳路径设置为false
    m_blVary=false;
    m_nVaryStep=0; //变异产生最佳结果的代数设置为0
    m_nVaryCount=0; //变异成功的次数

}

//更新环境信息素
void CTSP::UpdatePheromone(int nFlag)
{
    //临时保存信息素
    for (int i=0;i<=CITY_COUNT;i++)
    {
        for (int j=0;j<=CITY_COUNT;j++)
        {
            m_pdbTempAry[i][j]=0.0; //先全部设置为0
        }
    }

    //==================================================================
    //用全局最优或者迭代最优蚂蚁更新信息素
    if (nFlag == 0)
    {
        m_temp_ant=m_iteration_best_ant;//迭代最优
    }
    else
    {
        m_temp_ant=m_global_best_ant;//全局最优
    }

    double dbNewPheromone=1.0/m_temp_ant.m_dbPathLength; //新留下的信息素

    //==================================================================
    //计算新留下的信息素
    int m=0;
    int n=0;
    if (m_temp_ant.m_dbPathLength < DB_MAX)
    {
        for (int j=1;j<m_temp_ant.m_nPathCount;j++)
        {
            m=m_temp_ant.m_nPath[j-1];
            n=m_temp_ant.m_nPath[j];
            if (m>CITY_COUNT) //是配送站
            {
                m=0;
            }
            if (n>CITY_COUNT) //是配送站
            {
                n=0;
            }
            m_pdbTempAry[m][n]=m_pdbTempAry[m][n]+dbNewPheromone;
            m_pdbTempAry[n][m]=m_pdbTempAry[m][n];
        }

        //最后城市和配送站之间的信息素
        m_pdbTempAry[n][0]=m_pdbTempAry[n][0]+dbNewPheromone;
        m_pdbTempAry[0][n]=m_pdbTempAry[n][0];
    }

    //==================================================================
    //更新环境信息素
    for (int i=0;i<=CITY_COUNT;i++)
    {
        for (int j=0;j<=CITY_COUNT;j++)
        {
            g_Pheromone[i][j]=g_Pheromone[i][j]*m_dbRou+m_pdbTempAry[i][j];  //最新的环境信息素 = 留存的信息素 + 新留下的信息素
        }
    }

    //==================================================================
    //检查环境信息素是否超过范围
    m_dbMaxQ=(1.0/(1.0-m_dbRou))*(1.0/m_global_best_ant.m_dbPathLength);
    m_dbMinQ=m_dbMaxQ*m_dbRatio;

    for (int i=0;i<=CITY_COUNT;i++)
    {
        for (int j=0;j<=CITY_COUNT;j++)
        {
            if (g_Pheromone[i][j] > m_dbMaxQ)
            {
                g_Pheromone[i][j] = m_dbMaxQ;
            }

            if (g_Pheromone[i][j] < m_dbMinQ)
            {
                g_Pheromone[i][j] = m_dbMinQ;
            }

        }
    }

    //==================================================================
    // 更新完环境信息素后，计算两两城市间的选择概率值
    // 提前计算好存到数组里，可以提高算法运行速度
    // 每只蚂蚁在选择下一个城市的时候直接查这个表就可以，不必再重复进行计算
    for (int i=0;i<=CITY_COUNT;i++)
    {
        for (int j=0;j<=CITY_COUNT;j++)
        {
            g_Prob[i][j]=pow(g_Pheromone[i][j],ALPHA)*g_distance_BETA[i][j];
        }
    }



}

//搜索路径
double CTSP::Search()
{

    qDebug()<<"Search()";
    //===========================================================
    //清空变量
    m_dbMinLength=DB_MAX; //先设置一个足够大的值

    for (int i=0;i<N_MAX_PATH;i++)
    {
        m_nBestPath[i]=0;
    }
    m_nBestPathCount=0; //最佳路径里的点个数


    //各代最短路径和平均路径长度
    for (int i=0;i<N_MAX_IT_COUNT;i++)
    {
        g_dbPathLenAry[i]=DB_MAX;
    }
    memset(g_dbPathAvgLenAry,0,sizeof(g_dbPathAvgLenAry));//将平均路径清零

    //===========================================================
    //开始搜索
    double dbMid=((double)IT_COUNT)/2.0;//迭代次数
    double dbTemp=0.0;
    double dbRate=0.0;
    double dbQ=0.0;

    int R=0; //记录连续多少代没有进化了

    int nPercent=0; //进度

    int nFlag=0; //用全局还是迭代最优解更新环境信息素

    //qDebug()<<"开始迭代循环";
    for (int i=0;i<IT_COUNT;i++) //在迭代次数内进行循环
    {


        //计算选择策略的值Q
        dbTemp=abs((double)i-dbMid);
        dbRate=pow(dbTemp,Q_POWER)/pow(dbMid,Q_POWER);
        dbQ=Q_Min+(Q_Max-Q_Min)*dbRate;//算法初期dbq较大，进行确定性搜索；算法中期取较小值，进行探索式搜索，算法后期恢复初值（之所以取dbmid之缘由）

        //进行一次搜索
        for (int j=0;j<ANT_COUNT;j++)
        {
            //对蚂蚁初始化
            m_cAntAry[j].Init();

            //设置选择策略的值
            m_cAntAry[j].m_dbQ=dbQ;

            //蚂蚁开始搜索
            m_cAntAry[j].Search();
        }

        //是否有更优解产生，有则保存
        for (int j=0;j<ANT_COUNT;j++)
        {
            if (m_cAntAry[j].m_dbPathLength < m_dbMinLength)
            {
                m_dbMinLength=m_cAntAry[j].m_dbPathLength;
                m_nBestPathCount=m_cAntAry[j].m_nPathCount;

                m_nStep=i+1; //记下是第几代产生的最佳路径

                m_blVary=false;//最佳路径不是变异产生的

                for (int k=0;k<m_nBestPathCount;k++)
                {
                    m_nBestPath[k]=m_cAntAry[j].m_nPath[k];//输出结果1
                }

                R=0; //如果有进化，则把R置0，重新计数
            }


            //保存各代的最短路径
            if (m_cAntAry[j].m_dbPathLength < g_dbPathLenAry[i])
            {
                g_dbPathLenAry[i]=m_cAntAry[j].m_dbPathLength;
            }

            //记录下总路径长度
            g_dbPathAvgLenAry[i]=g_dbPathAvgLenAry[i]+m_cAntAry[j].m_dbPathLength;

        }

        //计算本代结果的路径平均长度
        g_dbPathAvgLenAry[i]=g_dbPathAvgLenAry[i]/(double)ANT_COUNT;

        //判断更新环境信息素标志
        if (R >=  R_MAX) //已经很多代没有进化了
        {
            nFlag=1;//全局最优解更新信息素
            R=0; //R置0，重新计数
        }
        else
        {
            nFlag=0;//迭代最优解更新信息素
            R++;
        }

        //保存全局最优蚂蚁和迭代最优秀蚂蚁
        m_iteration_best_ant.m_dbPathLength=DB_MAX; //保存之前重置迭代最优蚂蚁的路径长度（重置保证了局部最优）
        SaveBestAnt();

        //变异操作，如果成功保存最优路径
        if (Vary() == true)
        {
            m_dbMinLength=m_global_best_ant.m_dbPathLength;
            m_nBestPathCount=m_global_best_ant.m_nPathCount;
            for (int k=0;k<m_nBestPathCount;k++)
            {
                m_nBestPath[k]=m_global_best_ant.m_nPath[k];
            }

            m_nVaryStep=i+1; //记下是第几代时变异产生的最佳路径
            m_blVary=true;
            m_nVaryCount++;
        }


        //倒置变异操作，如果成功保存最优路径
        if (Vary_3() == true)
        {
            m_dbMinLength=m_global_best_ant.m_dbPathLength;
            m_nBestPathCount=m_global_best_ant.m_nPathCount;
            for (int k=0;k<m_nBestPathCount;k++)
            {
                m_nBestPath[k]=m_global_best_ant.m_nPath[k];
            }

            m_nVaryStep=i+1; //记下是第几代时变异产生的最佳路径
            m_blVary=true;
            m_nVaryCount++;
        }

        //全部蚂蚁搜索完后一次后,更新环境信息素
        UpdatePheromone(nFlag);

        //显示搜索进度
        nPercent++;
        //g_pc->SetPos(nPercent*100/IT_COUNT);//MFC绘图

    }
    qDebug()<<"迭代结束";

    best_ant_count=m_nBestPathCount;
    for (int p=0;p<m_nBestPathCount;p++) {
        best_ant[p]=m_nBestPath[p];//打印最佳路径
    }
    QString Path = "";
    for (int p=0;p<m_nBestPathCount;p++) {
        //qDebug()<<m_nBestPath[p];
        if(m_nBestPath[p]>CITY_COUNT)
        {
            Path += "["+QString::number(m_nBestPath[p])+"] ";//打印最佳路径
        }
        else{
            Path += QString::number(m_nBestPath[p])+" ";//打印最佳路径
        }

    }
    qDebug()<<Path;
    double temp=DB_MAX;
    for (int w=0;w<IT_COUNT;w++) {
        if(temp>g_dbPathLenAry[w])
            temp=g_dbPathLenAry[w];
    }
    qDebug()<<temp;
    return temp;

}


//根据路径中的点编号得到这是第几辆车
//返回 [ 1, CAR_COUNT ]
int CTSP::GetCarNo(int nNode)
{
    int nSendCount=(nNode-CITY_COUNT-1)/CAR_COUNT;

    return nNode-CITY_COUNT-nSendCount*CAR_COUNT;
}

QString CTSP::GetCarType(int nNode)
{
    int car_No = GetCarNo(nNode) - 1; // [1 CAR_COUNT]
    int i=0;
    while(i<TYPE_COUNT){
        if(car_No<CAR_TYPE_COUNT[i]){
            return CAR_TYPE_NAME[i];
        }
        else{
            car_No -= CAR_TYPE_COUNT[i];
            i++;
        }
    }
    return "error";
}

//保存全局最优蚂蚁和迭代最优蚂蚁
void CTSP::SaveBestAnt()
{
    //保存本代中最优秀的蚂蚁
    for (int m=0;m<ANT_COUNT;m++)
    {
        //保存全局最优蚂蚁
        if (m_cAntAry[m].m_dbPathLength < m_global_best_ant.m_dbPathLength)
        {
             m_global_best_ant=m_cAntAry[m];
        }

        //保存迭代最优蚂蚁
        if (m_cAntAry[m].m_dbPathLength < m_iteration_best_ant.m_dbPathLength)
        {
             m_iteration_best_ant=m_cAntAry[m];
        }

    }

}

//检查变异蚂蚁是否符合要求
bool CTSP::CheckVaryAnt(CAnt ant)
{

    //test
    //[4] 5 14 4 3 18   [3] 10 12 2 9 15 19 8   [2] 1 7 16 13 6 11 20   [5] 17
    //m_vary_ant.m_nPathCount =24;

    //m_vary_ant.m_nPath[0]=24;
    //m_vary_ant.m_nPath[1]=5;
    //m_vary_ant.m_nPath[2]=14;
    //m_vary_ant.m_nPath[3]=4;
    //m_vary_ant.m_nPath[4]=3;
    //m_vary_ant.m_nPath[5]=18;

    //m_vary_ant.m_nPath[6]=23;
    //m_vary_ant.m_nPath[7]=10;
    //m_vary_ant.m_nPath[8]=2;
    //m_vary_ant.m_nPath[9]=12;
    //m_vary_ant.m_nPath[10]=9;
    //m_vary_ant.m_nPath[11]=15;
    //m_vary_ant.m_nPath[12]=19;
    //m_vary_ant.m_nPath[13]=8;

    //m_vary_ant.m_nPath[14]=22;
    //m_vary_ant.m_nPath[15]=1;
    //m_vary_ant.m_nPath[16]=7;
    //m_vary_ant.m_nPath[17]=16;
    //m_vary_ant.m_nPath[18]=13;
    //m_vary_ant.m_nPath[19]=6;
    //m_vary_ant.m_nPath[20]=11;
    //m_vary_ant.m_nPath[21]=20;

    //m_vary_ant.m_nPath[22]=25;
    //m_vary_ant.m_nPath[23]=17;
    //检查各条路径是否符合条件

    int nCityNoNext=0;//当前基因
    int nCityNoPrev=0;//前驱基因

    int nCarNo=-1;
    double dbL=0.0; //长度
    double dbW=0.0; //重量
    double dbT=0.0; //时间

    //保存车辆的行程时间
    double dbTimeAry[N_MAX_CAR_COUNT];
    memset(dbTimeAry,0,sizeof(dbTimeAry));//将车辆的行驶时间清零

    for (int i=0;i<ant.m_nPathCount;i++)
    {
        if (i == 0) //是刚开始
        {
            nCarNo=GetCarNo(ant.m_nPath[0]);//第一辆车的编号
            nCityNoNext=0;
            dbL=0.0;
            dbW=0.0;
            dbT=dbTimeAry[nCarNo-1];

        }
        else
        {
            nCityNoNext=ant.m_nPath[i];
            if (nCityNoNext > CITY_COUNT) //当前是配送站，检查前面的一辆车
            {
                dbL=dbL+g_distance[nCityNoPrev][0]; //加上返回的路径

                if (dbL>g_CarAry[nCarNo-1].dbMaxLength) //路径超过限制
                {
                    return false;
                }
                if (dbW>g_CarAry[nCarNo-1].dbMaxWeight) //重量超过限制
                {
                    return false;
                }

                //更新车辆行程时间
                dbTimeAry[nCarNo-1]=dbTimeAry[nCarNo-1]+g_distance[nCityNoPrev][0]/g_CarAry[nCarNo-1].dbSpeed;

                //准备检查下一辆车
                dbL=0.0;
                dbW=0.0;
                nCarNo=GetCarNo(nCityNoNext);
                dbT=dbTimeAry[nCarNo-1];
                nCityNoNext=0;

            }
            else //是下一城市
            {
                dbW=dbW+g_CityAry[nCityNoNext].dbW;
                dbL=dbL+g_distance[nCityNoPrev][nCityNoNext];

                //有时间窗，检查到达时间是否符合要求
                if (g_nHTW == 1) //硬时间窗
                {
                    //到达该配送点的时间
                    dbT=dbT+g_distance[nCityNoPrev][nCityNoNext]/g_CarAry[nCarNo-1].dbSpeed;

                    if (dbT > g_CityAry[nCityNoNext].dbTE) //到达时间超过时间窗
                    {
                        return false;
                    }
                    else
                    {
                        if (dbT < g_CityAry[nCityNoNext].dbTB) //提前到达时间窗
                        {
                            dbT = g_CityAry[nCityNoNext].dbTB;
                        }
                        else //在时间窗内到达
                        {
                        }
                        dbT=dbT+g_CityAry[nCityNoNext].dbTS; //加上服务时间

                        dbTimeAry[nCarNo-1]=dbT; //更新车辆行程时间
                    }

                }
                else if (g_nHTW == 2) //软时间窗暂时不实现
                {
                }

            }

        }

        nCityNoPrev=nCityNoNext;
    }

    //========================================================
    //检查最后一条路径
    dbL=dbL+g_distance[nCityNoPrev][0]; //加上返回的路径
    if (dbL>g_CarAry[nCarNo-1].dbMaxLength) //路径超过限制
    {
        return false;
    }
    if (dbW>g_CarAry[nCarNo-1].dbMaxWeight) //重量超过限制
    {
        return false;
    }

    //========================================================
    return true;

}


//变异操作，从最优秀的蚂蚁产生一个新的蚂蚁，如果更优秀就保存
//产生更优秀的返回true
bool CTSP::Vary()
{
    //如果还没有产生最优秀的蚂蚁，直接退出
    if (m_global_best_ant.m_dbPathLength >= DB_MAX)
    {
        return false;
    }

    //复制
    m_vary_ant=m_global_best_ant;

    //进行变异
    int nGeneLen=m_vary_ant.m_nPathCount; //路径里点的个数，也就是基因长度
    int nCount=rnd(0,CITY_COUNT); //随机产生变异次数
    nCount=MAX(nCount,1); //至少变异1次

    int nP1=0;
    int nP2=0;
    int nTemp=0;

    for (int i=0;i<nCount;i++)
    {
        //随机产生交换位置
        nP1=rnd(0,nGeneLen);
        nP2=rnd(0,nGeneLen);

        //如果产生的是同一位置，则不交换
        if (nP1== nP2)
        {
            continue;
        }

        //如果交换的点中有出发点，则不进行交换
        if (m_vary_ant.m_nPath[nP1]>CITY_COUNT)
        {
            continue;
        }
        if (m_vary_ant.m_nPath[nP2]>CITY_COUNT)
        {
            continue;
        }

        //交换染色体
        nTemp=m_vary_ant.m_nPath[nP1];
        m_vary_ant.m_nPath[nP1]=m_vary_ant.m_nPath[nP2];
        m_vary_ant.m_nPath[nP2]=nTemp;

        //只交换一次，如果要交换多次，注释掉这行
        break;
    }

    //变异完成，计算变异蚂蚁的路径长度
    m_vary_ant.CalPathLen();

    //变异蚂蚁不比原来的好，直接退出
    if (m_vary_ant.m_dbPathLength >= m_global_best_ant.m_dbPathLength)
    {
        return false;
    }

    //===================================================
    //如果变异蚂蚁比原来路径短，还需要检查可行性
    //因为变异操作后，城市的顺序打乱了
    //可能导致某个车辆经过的路径长度大于其最大行程
    //也可能导致某个车辆经过的城市的配载总重量大于车辆的最大载重
    //对于这种结果也要排除掉
    if (CheckVaryAnt(m_vary_ant) == true) //如果可行，复制过去
    {
        m_global_best_ant=m_vary_ant;
    }

    return true;

}

//倒置变异
bool CTSP::Vary_3()
{
    //如果还没有产生最优秀的蚂蚁，直接退出
    if (m_global_best_ant.m_dbPathLength >= DB_MAX)
    {
        return false;
    }

    //复制
    m_vary_ant=m_global_best_ant;

    //进行变异
    int nGeneLen=m_vary_ant.m_nPathCount; //路径里点的个数，也就是基因长度

    //随机产生倒置的开始和结束位置
    int nP1=rnd(1,nGeneLen);
    int nP2=nP1;
    while (nP2 == nP1)
    {
        nP2=rnd(1,nGeneLen);
    }
    int N1=MIN(nP1,nP2);
    int N2=MAX(nP1,nP2);

    //进行倒置变异
    int nTempAry[N_MAX_PATH];
    memcpy(nTempAry,m_vary_ant.m_nPath,sizeof(nTempAry));//数组赋值操作

    for (int i=N1;i<=N2;i++)
    {
        m_vary_ant.m_nPath[i]=nTempAry[N1+N2-i];
    }

    //变异完成，计算变异蚂蚁的路径长度
    m_vary_ant.CalPathLen();

    //变异蚂蚁不比原来的好，直接退出
    if (m_vary_ant.m_dbPathLength >= m_global_best_ant.m_dbPathLength)
    {
        return false;
    }

    //===================================================
    //如果变异蚂蚁比原来路径短，还需要检查可行性
    //因为变异操作后，城市的顺序打乱了
    //可能导致某个车辆经过的路径长度大于其最大行程
    //也可能导致某个车辆经过的城市的配载总重量大于车辆的最大载重
    //对于这种结果也要排除掉
    if (CheckVaryAnt(m_vary_ant) == true) //如果可行，复制过去
    {
        m_global_best_ant=m_vary_ant;
    }

    return true;

}

//变异操作，从本代中选择最优秀的蚂蚁产生一个新的蚂蚁，如果更优秀就保存（该操作没有实现）
//产生更优秀的返回true
bool CTSP::Vary_2()
{
    CAnt cNewAnt; //定义一个新的蚂蚁
    cNewAnt.m_dbPathLength=DB_MAX; //把其路径长度设置为很大

    int nBestAntIndex=0;
    for (int i=0;i<ANT_COUNT;i++) //找本代中最优秀的蚂蚁，并记录下位置
    {
        if (m_cAntAry[i].m_dbPathLength < cNewAnt.m_dbPathLength)
        {
            cNewAnt=m_cAntAry[i];
            nBestAntIndex=i;
        }
    }


    //进行变异
    int nGeneLen=cNewAnt.m_nPathCount; //路径里点的个数，也就是基因长度
    int nCount=rnd(0,CITY_COUNT); //随机产生变异次数
    nCount=MAX(nCount,1); //至少变异1次

    int nP1=0;
    int nP2=0;
    int nTemp=0;

    for (int i=0;i<nCount;i++)
    {
        //随机产生交换位置
        nP1=rnd(0,nGeneLen);
        nP2=rnd(0,nGeneLen);

        //如果产生的是同一位置，则不交换
        if (nP1== nP2)
        {
            continue;
        }

        //如果交换的点中有出发点，则不进行交换
        if (cNewAnt.m_nPath[nP1]>CITY_COUNT)
        {
            continue;
        }
        if (cNewAnt.m_nPath[nP2]>CITY_COUNT)
        {
            continue;
        }

        //交换染色体
        nTemp=cNewAnt.m_nPath[nP1];
        cNewAnt.m_nPath[nP1]=cNewAnt.m_nPath[nP2];
        cNewAnt.m_nPath[nP2]=nTemp;

        //只交换一次，如果要交换多次，注释掉这行
        //break;
    }

    //变异完成，计算变异蚂蚁的路径长度
    cNewAnt.CalPathLen();

    //变异蚂蚁不比原来的好，直接退出
    if (cNewAnt.m_dbPathLength >= m_cAntAry[nBestAntIndex].m_dbPathLength)
    {
        return false;
    }

    //===================================================
    //如果变异蚂蚁比原来路径短，还需要检查可行性
    //因为变异操作后，城市的顺序打乱了
    //可能导致某个车辆经过的路径长度大于其最大行程
    //也可能导致某个车辆经过的城市的配载总重量大于车辆的最大载重
    //对于这种结果也要排除掉
    if (CheckVaryAnt(cNewAnt) == true) //如果可行，复制过去
    {
        m_cAntAry[nBestAntIndex]=cNewAnt;
    }

    return true;

}

//交叉繁殖，该操作没有实现
//选择本代中最优和次优的两只蚂蚁进行交叉繁殖
void CTSP::Propagate()
{
    //蚂蚁数量小于2，直接退出
    if (ANT_COUNT<2)
    {
        return;
    }

    //城市数量小于2，直接退出
    if (CITY_COUNT<2)
    {
        return;
    }

    //先对蚂蚁按路径长短进行排序，路径最短的在前面，则前两只就是最优和次优蚂蚁
    CAnt cTempAnt;
    for (int i=0;i<ANT_COUNT-1;i++) //冒泡排序
    {
        for (int j=i+1;j<ANT_COUNT;j++)
        {
            if (m_cAntAry[i].m_dbPathLength > m_cAntAry[j].m_dbPathLength)
            {
                cTempAnt=m_cAntAry[i];
                m_cAntAry[i]=m_cAntAry[j];
                m_cAntAry[j]=cTempAnt;
            }
        }
    }

    //开始交叉繁殖
    int nGeneLen=MIN(m_cAntAry[0].m_nPathCount,m_cAntAry[1].m_nPathCount); //得到基因的最短长度

     //得到需要交叉的开始和结束位置
    int a=rnd(1,nGeneLen);
    int b=a;
    while (b == a)
    {
        b=rnd(1,nGeneLen);
    }

    int N1=MIN(a,b);
    int N2=MAX(a,b);


    //定义两只蚂蚁，保存交叉繁殖后的蚂蚁
    CAnt cAnt_0,cAnt_1;
    cAnt_0=m_cAntAry[0];
    cAnt_1=m_cAntAry[1];

    ////去掉重复的染色体
    for (int i=1;i<cAnt_0.m_nPathCount;i++)
    {
        for (int j=N1;j<=N2;j++)
        {
            if (cAnt_0.m_nPath[i] == m_cAntAry[1].m_nPath[j]) //染色体相同
            {
                cAnt_0.m_nPath[i]=-1;
                break;
            }
        }
    }

    for (int i=1;i<cAnt_1.m_nPathCount;i++)
    {
        for (int j=N1;j<=N2;j++)
        {
            if (cAnt_1.m_nPath[i] == m_cAntAry[0].m_nPath[j]) //染色体相同
            {
                cAnt_1.m_nPath[i]=-1;
                break;
            }
        }
    }

    //插入新的染色体
    int nTempAry[N_MAX_PATH];

    memcpy(nTempAry,cAnt_0.m_nPath,sizeof(nTempAry));
    cAnt_0.m_nPathCount=cAnt_0.m_nPathCount+N2-N1+1;
    for (int i=0;i<cAnt_0.m_nPathCount;i++)
    {
        if (i<N1)
        {
            cAnt_0.m_nPath[i]=nTempAry[i];
        }
        if ((i>=N1) && (i<=N2))
        {
            cAnt_0.m_nPath[i]=m_cAntAry[1].m_nPath[i];
        }
        if (i>N2)
        {
            cAnt_0.m_nPath[i]=nTempAry[i-N2+N1-1];
        }
    }

    memcpy(nTempAry,cAnt_1.m_nPath,sizeof(nTempAry));
    cAnt_1.m_nPathCount=cAnt_1.m_nPathCount+N2-N1+1;
    for (int i=0;i<cAnt_1.m_nPathCount;i++)
    {
        if (i<N1)
        {
            cAnt_1.m_nPath[i]=nTempAry[i];
        }
        if ((i>=N1) && (i<=N2))
        {
            cAnt_1.m_nPath[i]=m_cAntAry[0].m_nPath[i];
        }
        if (i>N2)
        {
            cAnt_1.m_nPath[i]=nTempAry[i-N2+N1-1];
        }
    }

    //整理染色体，把等于-1的染色体去掉，重新计算路径点个数
    memcpy(nTempAry,cAnt_0.m_nPath,sizeof(nTempAry));
    int nGeneCount=0;
    for (int i=0;i<cAnt_0.m_nPathCount;i++)
    {
        if (nTempAry[i] >=0) //有效染色体
        {
            cAnt_0.m_nPath[nGeneCount]=nTempAry[i];
            nGeneCount++;
        }
    }
    cAnt_0.m_nPathCount=nGeneCount;

    //
    memcpy(nTempAry,cAnt_1.m_nPath,sizeof(nTempAry));
    nGeneCount=0;
    for (int i=0;i<cAnt_1.m_nPathCount;i++)
    {
        if (nTempAry[i] >=0) //有效染色体
        {
            cAnt_1.m_nPath[nGeneCount]=nTempAry[i];
            nGeneCount++;
        }
    }
    cAnt_1.m_nPathCount=nGeneCount;


    //保存最优和次优蚂蚁
    //计算新蚂蚁的路径长度
    if (CheckVaryAnt(cAnt_1) == true) //蚂蚁有效
    {
        cAnt_1.CalPathLen();

        if (cAnt_1.m_dbPathLength < m_cAntAry[1].m_dbPathLength)
        {
            m_cAntAry[1]=cAnt_1;

            if (m_cAntAry[1].m_dbPathLength < m_cAntAry[0].m_dbPathLength) //如果替换了，重新排序
            {
                cTempAnt=m_cAntAry[0];
                m_cAntAry[0]=m_cAntAry[1];
                m_cAntAry[1]=cTempAnt;
            }
        }

    }

    if (CheckVaryAnt(cAnt_0) == true) //蚂蚁有效
    {
        cAnt_0.CalPathLen();
        if (cAnt_0.m_dbPathLength < m_cAntAry[1].m_dbPathLength)
        {
            m_cAntAry[1]=cAnt_0;
        }

    }



}


//得到用贪心算法走过的路径长度
double CTSP::GetGreedSearchLen()
{
    double dbLen=0.0; //设置长度为0
    int nCurCityNo=rnd(0,CITY_COUNT); //随机选择当前城市
    int nNextCityNo=-1; //下一个城市的编号
    int nMovedCityCount=1; //设置走过的城市数量为1
    double dbTemp=DB_MAX; //临时保存两个城市间的距离

    int nAllowedCityAry[N_MAX_CITY_COUNT+1]; //没去过的城市列表
    for (int i=0;i<=CITY_COUNT;i++)
    {
        nAllowedCityAry[i]=1;
    }
    nAllowedCityAry[nCurCityNo]=0;

    int nStartNo=nCurCityNo; //记下出发城市

    //CString strAll="";
    //CString strTemp="";
    //strAll.Format("%d",nStartNo);

    //开始用贪心算法搜索
    while (nMovedCityCount != CITY_COUNT+1)
    {
        //重新设置变量数值
        nNextCityNo=-1;//下一个城市的编号
        dbTemp=DB_MAX;//10e9

        //寻找离当前城市最近的城市
        for (int i=0;i<=CITY_COUNT;i++)
        {
            if ((nAllowedCityAry[i]==1) && (g_distance[nCurCityNo][i] < dbTemp))
            {
                dbTemp=g_distance[nCurCityNo][i];
                nNextCityNo=i;
            }
        }

        //更新路径长度，改变当前城市，更新城市去过的标志和去过的城市数量
        dbLen=dbLen+dbTemp;
        nCurCityNo=nNextCityNo;
        nAllowedCityAry[nNextCityNo]=0;
        nMovedCityCount++;

        //strTemp.Format(",%d",nNextCityNo);
        //strAll=strAll+strTemp;
    }

    dbLen=dbLen+g_distance[nCurCityNo][nStartNo]; //加上从最后就城市返回出发点的路径长度

    //strAll=strAll+"\n";
    //TRACE0(strAll);

    return dbLen;

}


















