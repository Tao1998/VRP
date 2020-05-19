#include "StdAfx.h"
#include ".\ant.h"

CAnt::CAnt(void)
{
	memset(m_nPath,0,sizeof(m_nPath));
	m_nPathCount=0; //·����ĵ����
}

CAnt::~CAnt(void)
{
}

//��ʼ��
void CAnt::Init()
{
	//=== ������ɷ���˳�� ==============================================

	//�����óɰ�ѭ�򷢳�
	for (int i=0;i<CAR_COUNT;i++) 
	{
		m_CarOrderAry[i]=i;
	}

	//Ȼ�������������������λ�õĳ��������ҷ���˳��
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
		   
	//==����ÿ�����Ѿ��߹��ĳ��ȡ��Ѿ����ص������������������г�ʱ��Ϊ0===============================================
	for (int i=0;i<CAR_COUNT;i++) 
	{
		m_CarAry[i].dbMovedLength=0.0;
		m_CarAry[i].dbMovedWeight=0.0;

		m_CarAry[i].dbMovedTime=0.0;
		m_CarAry[i].nSendCount=0;
	}

	//==���õ�ǰ�����еĵ�1������������====================================
	m_nCurCarIndex=0; 

	//==����ȫ������Ϊû��ȥ��===============================================
	for (int i=0;i<=CITY_COUNT;i++)
	{
		m_AllowedCity[i]=1;
	}

	//==����·��Ϊ��===============================================
	for (int i=0;i<=N_MAX_PATH;i++)
	{
		m_nPath[N_MAX_PATH]=0;
	}
	m_nPath[0]=m_CarOrderAry[0]+1+CITY_COUNT; //�ѵ�1�����ı�ż���·��
	m_nPathCount=1; //·����ĵ����Ϊ1����Ϊ����վΪ��ʼ��

	//==�����߹��ĳ�������Ϊ0===============================================
	m_nCityCount=0;

	//==���õ�ǰ���ڳ���Ϊ0 (0��������վ)===============================================
	m_nCurCity=0;

	//==�����߹���·������Ϊ���ֵ===============================================
	m_dbPathLength=DB_MAX;

	//==����ѡ�����===========================================================
	m_dbQ=Q_Max; //������Ϊ���ֵ��ÿ��������ɣ����ֵ���ᶯ̬�ı��
	                                //�ı�ԭ��Ϊ�����ŵ������������ӣ��ɴ��С�ٱ�󣬾��ǳ��ڴ��м�С�����ڴ�

	//==����ʧ�ܱ�־�ü�===========================================================
	m_blSearchFail=false;

}

//Ϊ��ǰ������ѡ����һ������
//ע�⣡���Ϊ0�ĳ���������վ��������ѡ��Χ��
//����ֵ Ϊ���б��
//�������Ϊ0����ʾ��ǰ����Ҫ��������վ�������ɳ����е���һ����
int CAnt::ChooseNextCity()
{

	int nSelectedCity=-1; //���ؽ��������ʱ��������Ϊ-1

	int nCarNo=m_CarOrderAry[m_nCurCarIndex]; //�õ���ǰ������������

	//==============================================================================
	//���㵱ǰ���к�ûȥ���ĳ���֮�����Ϣ���ܺ�
	double dbTotal=0.0;	
	double prob[N_MAX_CITY_COUNT+1]; // ������б�ѡ�еĸ���

	for (int i=1;i<=CITY_COUNT;i++)
	{
		if (m_AllowedCity[i] == 1) //����ûȥ��
		{
			//�����Ӳʱ�䴰���ƣ����һ���Ƿ�Ѹó�������ѡ�����
			if (g_nHTW == 1)
			{
				//��������ӵ�ǰ���дﵽ�ó��У�����ʱ�䴰���ƣ���������ѡ�����ֵΪ0��������ѡ��
				if (m_CarAry[nCarNo].dbMovedTime+g_distance[m_nCurCity][i]/g_CarAry[nCarNo].dbSpeed > g_CityAry[i].dbTE)
				{
					prob[i]=0.0;
				}
				else
				{
					prob[i]=g_Prob[m_nCurCity][i]/g_CityAry[i].dbTE; //����ʱ�䴰��Ӱ��
				}
			}
			else
			{
				prob[i]=g_Prob[m_nCurCity][i];  //��ʹ�ò�����õ��ӵ�ǰ���е��ó��е�ѡ�����ֵ
				                                                              //�������м��ѡ�����ֵ���Ѿ���ÿ�θ����껷����Ϣ�غ�����			
			}

			dbTotal=dbTotal+prob[i];  //�ۼ���Ϣ�أ��õ��ܺ�


		}
		else //����ȥ���ˣ�������ѡ�����ֵΪ0
		{
			prob[i]=0.0;
		}
	}

	//==============================================================================
	//ȷ��ѡ����һ�����еĲ���
	double dbTactic=rnd(0.0,1.0);
	double dbTemp=-1.0;

	//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	//�������Ա�����Ӧ����ʼ��ʹ��̽����������Ч��Ҫ��һЩ
	//���Ҫʹ��ȷ����������̽�����������ѡ��Ĳ��ԣ�ע�͵���һ��
	dbTactic=1.0;
	//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

	if (dbTactic < m_dbQ) //ȷ���������������Ǹ����еĸ�������ѡ�Ǹ�
	{
		for (int i=1;i<=CITY_COUNT;i++)
		{
			if (m_AllowedCity[i] == 1) //����ûȥ��
			{
				if (prob[i] > dbTemp) //������������ģ����³��б��
				{
					nSelectedCity=i;
					dbTemp=prob[i];
				}
			}
		}

	}
	else //̽�������������Ǵ�˵�е�����ѡ��^_^
	{
		if (dbTotal > 0.0) //�ܵ���Ϣ��ֵ����0
		{
			dbTemp=rnd(0.0,dbTotal); //ȡһ�������

			for (int i=1;i<=CITY_COUNT;i++)
			{
				if (m_AllowedCity[i] == 1) //����ûȥ��
				{
					dbTemp=dbTemp-prob[i]; //��������൱��ת�����̣����������ѡ����Ϥ����ϸ����һ��
					if (dbTemp < 0.0) //����ֹͣת�������³��б�ţ�ֱ������ѭ��
					{
						nSelectedCity=i;
						break;
					}
				}
			}
		}
	}

	//==============================================================================
	//������м����Ϣ�طǳ�С ( С����double�ܹ���ʾ����С�����ֻ�ҪС )
	//��ô���ڸ�����������ԭ���������ĸ����ܺͿ���Ϊ0
	//����־�������������û�г��б�ѡ�����
	//��������������Ͱѵ�һ��ûȥ���ĳ�����Ϊ���ؽ��
	if (nSelectedCity == -1)
	{
		for (int i=1;i<=CITY_COUNT;i++)
		{
			if (m_AllowedCity[i] == 1) //����ûȥ��
			{
				nSelectedCity=i;
				break;
			}
		}
	}

	//==============================================================================
	//ѡ�������һ�����У���������ֱ�ӷ��ؽ��
	//��Ҫ�ж�������������
	//1>����������������ٷ�������վ�Ƿ񳬹��˳���������г�
	//2>��������������е������Ƿ񳬹��˳��������������


	//������������ˣ���������վ
	if (m_CarAry[nCarNo].dbMovedWeight+g_CityAry[nSelectedCity].dbW > g_CarAry[nCarNo].dbMaxWeight)
	{
		return 0;
	}

	//��������г��ˣ���������վ
	if (m_CarAry[nCarNo].dbMovedLength+g_distance[m_nCurCity][nSelectedCity]+g_distance[nSelectedCity][0] >g_CarAry[nCarNo].dbMaxLength)
	{
		return 0;
	}

	//==============================================================================
	//�����ʱ�䴰���ƣ���Ҫ�жϵ���ʱ���Ƿ���ʱ�䴰�Ľ�ֹʱ��֮ǰ

	if (g_nHTW == 1) //Ӳʱ�䴰����
	{
		//����ʱ�䴰���ƣ�ֱ�ӷ�������վ
		if (m_CarAry[nCarNo].dbMovedTime+g_distance[m_nCurCity][nSelectedCity]/g_CarAry[nCarNo].dbSpeed > g_CityAry[nSelectedCity].dbTE)
		{
			return 0;
		}
	}
	else if (g_nHTW == 2) //��ʱ�䴰���ƣ���ʱ��ʵ��
	{
	}

	//==============================================================================
	//���ؽ��
	return nSelectedCity;
}

//�����ڳ��м��ƶ�
void CAnt::Move()
{
	//ѡ����һ������
	int nNextCityNo=ChooseNextCity();

	//��ǰ��������������
	int nCarNo=m_CarOrderAry[m_nCurCarIndex];

	//�����Ҫ�������͵�
	if (nNextCityNo == 0)
	{
		//���õ�ǰ�����Ѿ��߹���·�����Ѿ����ص�����Ϊ0�����ٴ�����
		m_CarAry[nCarNo].dbMovedLength=0.0;
		m_CarAry[nCarNo].dbMovedWeight=0.0;
		
		//��ǰ���ķ�����������1
		m_CarAry[nCarNo].nSendCount=m_CarAry[nCarNo].nSendCount+1;

		//�����ʱ�䴰������Ҫ�����г�ʱ��
		if (g_nHTW > 0) //Ӳ����ʱ�䴰һ������
		{
			//��ǰ�����г�ʱ���ټ��Ϸ�������վ��Ҫ��ʱ��
			m_CarAry[nCarNo].dbMovedTime=m_CarAry[nCarNo].dbMovedTime+g_distance[m_nCurCity][0]/g_CarAry[nCarNo].dbSpeed;
		}

		//��ǰ��������Ϊ����վ
		m_nCurCity=0; 

		//����һ��������
		m_nCurCarIndex++;
		if (m_nCurCarIndex ==CAR_COUNT)
		{
			m_nCurCarIndex=0;
		}

		//����һ�����ı�ż���·��
		int nNextCarNo=m_CarOrderAry[m_nCurCarIndex]; //��һ�����ı��
		m_nPath[m_nPathCount]=nNextCarNo+1+CITY_COUNT+CAR_COUNT*m_CarAry[nNextCarNo].nSendCount;

		//·����ĵ������1
		m_nPathCount++; 

	}
	else //�����ƶ�����һ����
	{
		//�ı��������Ѿ���ʹ��·�����Ⱥ����͵Ļ���������
		m_CarAry[nCarNo].dbMovedLength=m_CarAry[nCarNo].dbMovedLength+g_distance[m_nCurCity][nNextCityNo]; 
		m_CarAry[nCarNo].dbMovedWeight=m_CarAry[nCarNo].dbMovedWeight+g_CityAry[nNextCityNo].dbW;

		//�����ʱ�䴰������Ҫ�����г�ʱ��
		if (g_nHTW == 1) //Ӳʱ�䴰
		{
			//��ǰ�����г�ʱ���ټ��ϵ�����һ������Ҫ��ʱ��
			m_CarAry[nCarNo].dbMovedTime=m_CarAry[nCarNo].dbMovedTime+g_distance[m_nCurCity][nNextCityNo]/g_CarAry[nCarNo].dbSpeed;

			//�����ǰ�������Ҫ�ȴ�ʱ�䴰���г�ʱ�����ó�ʱ�䴰��ʼʱ��
			if (m_CarAry[nCarNo].dbMovedTime < g_CityAry[nNextCityNo].dbTB)
			{
				m_CarAry[nCarNo].dbMovedTime = g_CityAry[nNextCityNo].dbTB;
			}

			//�г�ʱ�仹��Ҫ���Ϸ���ʱ��
			m_CarAry[nCarNo].dbMovedTime = m_CarAry[nCarNo].dbMovedTime + g_CityAry[nNextCityNo].dbTS;
		}
		else if (g_nHTW == 2) //��ʱ�䴰����ʱ��ʵ��
		{
		}

		//�ı䵱ǰ���ڳ���
		m_nCurCity=nNextCityNo;

		//���øó���Ϊȥ����
		m_AllowedCity[nNextCityNo]=0;

		//ȥ���ĳ���������1
		m_nCityCount++;

		//�ѳ��б�ż���·��
		m_nPath[m_nPathCount]=nNextCityNo;

		//·���еĵ������1
		m_nPathCount++; 

	}

}

//�����߹���·���ܳ���
void CAnt::CalPathLen()
{

	m_dbPathLength=0.0; //�Ȱ��ܳ�����0

	//����·���ܳ���
	int m=0;
	int n=0;
	for (int i=1;i<m_nPathCount;i++)
	{
		m=m_nPath[i];
		n=m_nPath[i-1];

		if (m>CITY_COUNT) //��ʾ�����������վ
		{
			m=0;
		}
		if (n>CITY_COUNT) //��ʾ�����������վ
		{
			n=0;
		}

		m_dbPathLength=m_dbPathLength+g_distance[m][n];
	}

	//������󷵻�����վ�ĳ���
	m_dbPathLength=m_dbPathLength+g_distance[m][0];

}


//����·�����������г���
//ע�⣡����֮ǰ�������ȵ���Init()��
void CAnt::Search()
{

	//��¼������������վ�Ĵ���
	int nBackCount=0;

	//�������г���
	while (m_nCityCount < CITY_COUNT)
	{

		Move(); //��ʼ�ƶ�

		if (m_nCurCity == 0) //�����һ�������ƶ�������վ�����ۼӴ���
		{
			nBackCount++;
			
			//����������صĴ������ڳ���������ʾ���г���ѡ����һ�Σ�����û�г��ܹ����ɳ�
			//����Ϊ������ʧ�ܵģ��޷���������
			if (nBackCount > CAR_COUNT)
			{
				m_blSearchFail=true;
				break;
			}
		}
		else //�����һ�����в�������վ����0
		{
			nBackCount=0;
		}

		//���·���������������������Ϊ����ʧ��
		if (m_nPathCount >= N_MAX_PATH)
		{
			m_blSearchFail=true;
			break;
		}
	}


	//����ҵ��⣬�����߹���·���ܳ���
	if (m_blSearchFail == false)
	{
		CalPathLen();
	}

}
