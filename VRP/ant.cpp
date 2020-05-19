#include ".\ant.h"
#include<string.h>
#include<QDebug>
CAnt::CAnt(void)
{
    memset(m_nPath,0,sizeof(m_nPath));
    m_nPathCount=0; //路径里的点个数
}

CAnt::~CAnt(void)
{
}

//初始化
void CAnt::Init()
{
    //=== 随机生成发车顺序 ==============================================

    //先设置成按循序发车
    for (int i=0;i<CAR_COUNT;i++)
    {
        m_CarOrderAry[i]=i;
    }

    //然后随机交换数组中两个位置的车辆，打乱发车顺序
    int nTemp1=0;
    int nTemp2=0;
    int nTemp=0;
    for (int i=0;i<CAR_COUNT*2;i++)
    {
        nTemp1=rnd(0,CAR_COUNT);
        nTemp2=rnd(0,CAR_COUNT);
        if (nTemp1 != nTemp2)
        {
            nTemp=m_CarOrderAry[nTemp1];
            m_CarOrderAry[nTemp1]=m_CarOrderAry[nTemp2];
            m_CarOrderAry[nTemp2]=nTemp;
        }
    }

    //==设置每辆车已经走过的长度、已经配载的重量、发车次数、行程时间为0===============================================
    for (int i=0;i<CAR_COUNT;i++)
    {
        m_CarAry[i].dbMovedLength=0.0;
        m_CarAry[i].dbMovedWeight=0.0;

        m_CarAry[i].dbMovedTime=0.0;
        m_CarAry[i].nSendCount=0;//发车次数
    }

    //==设置当前车队中的第1辆车进行派送====================================
    m_nCurCarIndex=0;

    //==设置全部城市为没有去过===============================================
    for (int i=0;i<=CITY_COUNT;i++)
    {
        m_AllowedCity[i]=1;
    }

    //==设置路径为空===============================================
    for (int i=0;i<=N_MAX_PATH;i++)
    {
        m_nPath[N_MAX_PATH]=0;
    }
    m_nPath[0]=m_CarOrderAry[0]+1+CITY_COUNT; //把第1辆车的编号加入路径（遗传算法编码）
    m_nPathCount=1; //路径里的点个数为1，因为配送站为开始点

    //==设置走过的城市数量为0===============================================
    m_nCityCount=0;

    //==设置当前所在城市为0 (0代表配送站)===============================================
    m_nCurCity=0;

    //==设置走过的路径长度为最大值===============================================
    m_dbPathLength=DB_MAX;

    //==设置选择策略===========================================================
    m_dbQ=Q_Max; //先设置为最大值，每次搜索完成，这个值都会动态改变的
                                    //改变原则为，随着迭代次数的增加，由大变小再变大，就是初期大，中间小，后期大

    //==搜索失败标志置假===========================================================
    m_blSearchFail=false;

}

//为当前汽车，选择下一个城市
//注意！编号为0的城市是配送站，不列在选择范围内
//返回值 为城市编号
//如果返回为0，表示当前车需要返回配送站，重新派车队中的下一辆车
int CAnt::ChooseNextCity()
{

    int nSelectedCity=-1; //返回结果，先暂时把其设置为-1

    int nCarNo=m_CarOrderAry[m_nCurCarIndex]; //得到当前那辆车在派送

    //==============================================================================
    //计算当前城市和没去过的城市之间的信息素总和
    double dbTotal=0.0;
    double prob[N_MAX_CITY_COUNT+1]; // 保存城市被选中的概率

    for (int i=1;i<=CITY_COUNT;i++)
    {
        if (m_AllowedCity[i] == 1) //城市没去过
        {
            //如果有硬时间窗限制，检查一下是否把该城市列入选择对象
            if (g_nHTW == 1)
            {
                //如果车辆从当前城市达到该城市，超过时间窗限制，则设置其选择概率值为0，不进行选择
                if (m_CarAry[nCarNo].dbMovedTime+g_distance[m_nCurCity][i]/g_CarAry[nCarNo].dbSpeed > g_CityAry[i].dbTE)
                {
                    prob[i]=0.0;
                }
                else
                {
                    prob[i]=g_Prob[m_nCurCity][i]/g_CityAry[i].dbTE; //加入时间窗的影响
                }
            }
            else
            {
                prob[i]=g_Prob[m_nCurCity][i];  //先使用查表法，得到从当前城市到该城市的选择概率值
                                                                              //两两城市间的选择概率值，已经在每次更新完环境信息素后计算好
            }

            dbTotal=dbTotal+prob[i];  //累加信息素，得到总和


        }
        else //城市去过了，设置其选择概率值为0
        {
            prob[i]=0.0;
        }
    }

    //==============================================================================
    //确定选择下一个城市的策略
    double dbTactic=rnd(0.0,1.0);
    double dbTemp=-1.0;

    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    //经过测试表明，应该是始终使用探索性搜索的效果要好一些
    //如果要使用确定性搜索和探索性搜索随机选择的策略，注释掉这一行
    //dbTactic=1.0;
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    if (dbTactic < m_dbQ) //确定性搜索，就是哪个城市的概率最大就选那个
    {
        for (int i=1;i<=CITY_COUNT;i++)
        {
            if (m_AllowedCity[i] == 1) //城市没去过
            {
                if (prob[i] > dbTemp) //找里面概率最大的，记下城市编号
                {
                    nSelectedCity=i;
                    dbTemp=prob[i];
                }
            }
        }

    }
    else //探索性搜索，就是传说中的轮盘选择^_^
    {
        if (dbTotal > 0.0) //总的信息素值大于0
        {
            dbTemp=rnd(0.0,dbTotal); //取一个随机数

            for (int i=1;i<=CITY_COUNT;i++)
            {
                if (m_AllowedCity[i] == 1) //城市没去过
                {
                    dbTemp=dbTemp-prob[i]; //这个操作相当于转动轮盘，如果对轮盘选择不熟悉，仔细考虑一下
                    if (dbTemp < 0.0) //轮盘停止转动，记下城市编号，直接跳出循环
                    {
                        nSelectedCity=i;
                        break;
                    }
                }
            }
        }
    }

    //==============================================================================
    //如果城市间的信息素非常小 ( 小到比double能够表示的最小的数字还要小 )
    //那么由于浮点运算的误差原因，上面计算的概率总和可能为0
    //会出现经过上述操作，没有城市被选择出来
    //出现这种情况，就把第一个没去过的城市作为返回结果
    if (nSelectedCity == -1)
    {
        for (int i=1;i<=CITY_COUNT;i++)
        {
            if (m_AllowedCity[i] == 1) //城市没去过
            {
                nSelectedCity=i;
                break;
            }
        }
    }

    //==============================================================================
    //选择出了下一个城市，还不可以直接返回结果
    //还要判断下面两个条件
    //1>车辆到达这个城市再返回配送站是否超过了车辆的最大行程
    //2>车辆到达这个城市的配重是否超过了车辆的最大载重量


    //超过最大载重了，返回配送站
    if (m_CarAry[nCarNo].dbMovedWeight+g_CityAry[nSelectedCity].dbW > g_CarAry[nCarNo].dbMaxWeight)
    {
        return 0;
    }

    //超过最大行程了，返回配送站
    if (m_CarAry[nCarNo].dbMovedLength+g_distance[m_nCurCity][nSelectedCity]+g_distance[nSelectedCity][0] >g_CarAry[nCarNo].dbMaxLength)
    {
        return 0;
    }

    //==============================================================================
    //如果有时间窗限制，还要判断到达时间是否在时间窗的截止时间之前

    if (g_nHTW == 1) //硬时间窗限制
    {
        //超过时间窗限制，直接返回配送站
        if (m_CarAry[nCarNo].dbMovedTime+g_distance[m_nCurCity][nSelectedCity]/g_CarAry[nCarNo].dbSpeed > g_CityAry[nSelectedCity].dbTE)
        {
            return 0;
        }
    }
    else if (g_nHTW == 2) //软时间窗限制，暂时不实现
    {
    }

    //==============================================================================
    //返回结果

    if(op1==0&&op2==0){
        if(nSelectedCity==6){
            op3=0;
        }
        else {
            op1=1;
            op2=1;
        }
    }
    if(op1==0&&op2==0&&op3==0){
        if(nCarNo==0){
            //qDebug()<<"蚂蚁找到了";
            qDebug()<<m_CarAry[nCarNo].dbMovedLength+g_distance[m_nCurCity][nSelectedCity]+g_distance[nSelectedCity][0];
            qDebug()<<g_CarAry[nCarNo].dbMaxLength<<" "<<nCarNo;
        }
        op1=1;
        op2=1;
        op3=1;
    }
    if(op1==0)
    {
        if(nSelectedCity==13){
            op2=0;
        }
        else {
            op1=1;
        }
    }
    if(nSelectedCity==16)
    {
        op1=0;
    }



    return nSelectedCity;
}

//蚂蚁在城市间移动
void CAnt::Move()
{
    //选择下一个城市
    int nNextCityNo=ChooseNextCity();

    //当前是哪辆车在派送
    int nCarNo=m_CarOrderAry[m_nCurCarIndex];


    //如果需要返回配送点
    if (nNextCityNo == 0)
    {
        //设置当前车辆已经走过的路径和已经配载的重量为0，以再次派送
        m_CarAry[nCarNo].dbMovedLength=0.0;
        m_CarAry[nCarNo].dbMovedWeight=0.0;

        //当前车的发车次数增加1
        m_CarAry[nCarNo].nSendCount=m_CarAry[nCarNo].nSendCount+1;

        //如果有时间窗，还需要增加行程时间
        if (g_nHTW > 0) //硬和软时间窗一样处理
        {
            //当前车的行程时间再加上返回配送站需要的时间
            m_CarAry[nCarNo].dbMovedTime=m_CarAry[nCarNo].dbMovedTime+g_distance[m_nCurCity][0]/g_CarAry[nCarNo].dbSpeed;
        }

        //当前城市设置为配送站
        m_nCurCity=0;

        //派下一辆车出发
        m_nCurCarIndex++;
        if (m_nCurCarIndex ==CAR_COUNT)
        {
            m_nCurCarIndex=0;
        }

        //把下一车辆的编号加入路径
        int nNextCarNo=m_CarOrderAry[m_nCurCarIndex]; //下一辆车的编号
        m_nPath[m_nPathCount]=nNextCarNo+1+CITY_COUNT+CAR_COUNT*m_CarAry[nNextCarNo].nSendCount;//遗传算法编码，第一辆车+城市数量+车辆编号+第几次为该车

        //路径里的点个数加1
        m_nPathCount++;

    }
    else //可以移动到下一城市
    {
        //改变这辆车已经行使的路径长度和配送的货物总重量
        m_CarAry[nCarNo].dbMovedLength=m_CarAry[nCarNo].dbMovedLength+g_distance[m_nCurCity][nNextCityNo];
        m_CarAry[nCarNo].dbMovedWeight=m_CarAry[nCarNo].dbMovedWeight+g_CityAry[nNextCityNo].dbW;

        //如果有时间窗，还需要增加行程时间
        if (g_nHTW == 1) //硬时间窗
        {
            //当前车的行程时间再加上到达下一城市需要的时间
            m_CarAry[nCarNo].dbMovedTime=m_CarAry[nCarNo].dbMovedTime+g_distance[m_nCurCity][nNextCityNo]/g_CarAry[nCarNo].dbSpeed;

            //如果提前到达，则需要等待时间窗，行程时间设置成时间窗开始时间
            if (m_CarAry[nCarNo].dbMovedTime < g_CityAry[nNextCityNo].dbTB)
            {
                m_CarAry[nCarNo].dbMovedTime = g_CityAry[nNextCityNo].dbTB;
            }

            //行程时间还需要加上服务时间
            m_CarAry[nCarNo].dbMovedTime = m_CarAry[nCarNo].dbMovedTime + g_CityAry[nNextCityNo].dbTS;
        }
        else if (g_nHTW == 2) //软时间窗，暂时不实现
        {
        }

        //改变当前所在城市
        m_nCurCity=nNextCityNo;

        //设置该城市为去过了
        m_AllowedCity[nNextCityNo]=0;

        //去过的城市数量加1
        m_nCityCount++;

        //把城市编号加入路径
        m_nPath[m_nPathCount]=nNextCityNo;

        //路径中的点个数加1
        m_nPathCount++;

    }

}

//计算走过的路径总长度
void CAnt::CalPathLen()
{

    m_dbPathLength=0.0; //先把总长度清0

    //计算路径总长度
    int m=0;
    int n=0;
    for (int i=1;i<m_nPathCount;i++)
    {
        m=m_nPath[i];
        n=m_nPath[i-1];

        if (m>CITY_COUNT) //表示这个点是配送站（即为车辆编号）
        {
            m=0;
        }
        if (n>CITY_COUNT) //表示这个点是配送站（即为车辆编号）
        {
            n=0;
        }

        m_dbPathLength=m_dbPathLength+g_distance[m][n];
    }

    //加上最后返回配送站的长度
    m_dbPathLength=m_dbPathLength+g_distance[m][0];

}


//搜索路径，派送所有城市
//注意！运行之前，必须先调用Init()，
void CAnt::Search()
{

    //记录连续返回配送站的次数
    int nBackCount=0;

    //派送所有城市
    while (m_nCityCount < CITY_COUNT)
    {

        Move(); //开始移动

        if (m_nCurCity == 0) //如果下一个城市移动到配送站，则累加次数
        {
            nBackCount++;

            //如果连续返回的次数大于车辆数，表示所有车都选择了一次，但是没有车能够被派出
            //就认为派送是失败的，无法进行派送
            if (nBackCount > CAR_COUNT)
            {
                m_blSearchFail=true;
                break;
            }
        }
        else //如果下一个城市不是配送站，归0
        {
            nBackCount=0;
        }

        //如果路径点个数大于最大个数，认为派送失败
        if (m_nPathCount >= N_MAX_PATH)
        {
            m_blSearchFail=true;
            break;
        }
    }


    //如果找到解，计算走过的路径总长度
    if (m_blSearchFail == false)
    {
        CalPathLen();
    }

}
