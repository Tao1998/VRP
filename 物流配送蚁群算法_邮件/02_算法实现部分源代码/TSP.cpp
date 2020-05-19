#include "StdAfx.h"
#include ".\tsp.h"

CTSP::CTSP(void)
{
	m_pdbTempAry=Create2DArray<double>(N_MAX_CITY_COUNT+1,N_MAX_CITY_COUNT+1);
}

CTSP::~CTSP(void)
{
	Free2DArray(m_pdbTempAry,N_MAX_CITY_COUNT+1);
}


//�ָ��㷨����ΪĬ��ֵ
void CTSP::SetParameterDefault()
{
	//�Ȱѳ��������ͳ�����������ΪĬ��

	CAR_COUNT=5; //���ó�����
	CITY_COUNT=20; //���ó�������

	//��Ⱥ�㷨����
	ALPHA=1.0; //
	BETA=2.0; // 
	ANT_COUNT=CITY_COUNT*3/5; //�������� 
	if (ANT_COUNT == 0)
	{
		ANT_COUNT=1;
	}

	IT_COUNT=500; //��������

	ROU_MAX=0.95;  //��Ϣ�ش��ݲ����� (1-ROU)������Ϣ�صĻӷ��ٶ�
	ROU_MIN=0.2;  //��Ϣ�ش��ݲ�������Сֵ����ֹ˥����0
	ROU_REDU=0.95; //��Ϣ�ش��ݲ�����˥���ٶ�


	//���ó��кͳ�����Ϣ
	for (int i=0;i<CAR_COUNT;i++)
	{
		g_CarAry[i].dbMaxLength=50.0;
		g_CarAry[i].dbMaxWeight=8.0;
		g_CarAry[i].dbSpeed=1.0;
	}

	g_CityAry[0].dbX=14.5;g_CityAry[0].dbY=13.0;g_CityAry[0].dbW=0.0; //���͵�

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

	//�����������м����
	CalCityDistance();

}


//�����������м����
void CTSP::CalCityDistance()
{
	//�����������м����
	double dbTemp=0.0;
	double db_x=0.0;
	double db_y=0.0;
	for (int i=0;i<=CITY_COUNT;i++)
	{
		for (int j=0;j<=CITY_COUNT;j++)  
		{
			//���ɶ��������������
			db_x=g_CityAry[i].dbX-g_CityAry[j].dbX;
			db_y=g_CityAry[i].dbY-g_CityAry[j].dbY;
			dbTemp=pow(db_x,2.0)+pow(db_y,2.0);

			if (g_blLenInt)
			{
				g_distance[i][j]=ROUND(pow(dbTemp,0.5));
			}
			else
			{
				g_distance[i][j]=pow(dbTemp,0.5);
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

//�õ�ָ���ֶε�ֵ
CString CTSP::GetFieldValue(CString strIniFile,CString strSection,CString strKey)
{
	char cValue[256];
	::GetPrivateProfileStringA(strSection,strKey,"",cValue,255,strIniFile);
	return CString(cValue);
}


//��ini�ļ���������
//�����������м����
//�˳�ʼ��,����㷨�Ĳ���û�иı�,ֻ��Ҫ����һ��
void CTSP::LoadDataFromIniFile(CString strIniFile)
{

	//���ⲿ�ı��ļ���ȡ����Ҫ������
	//ע��!����ٶ��ļ������ݶ�����ȷ��,���Զ������ݽ���У��,������ȷ���ı��ļ��е�������ȷ

	CITY_COUNT=atoi(GetFieldValue(strIniFile,"tsp_data","city_count"));
	ANT_COUNT=CITY_COUNT*3/5; //�������� 
	if (ANT_COUNT == 0) //����Ҫ��1ֻ����
	{
		ANT_COUNT=1;
	}


	//��ȡ��������
	CAR_COUNT=atoi(GetFieldValue(strIniFile,"tsp_data","car_count"));
	CString strField="";
	for (int i=0; i<CAR_COUNT;i++)
	{
		strField.Format("car_w_%d",i);
		g_CarAry[i].dbMaxWeight=atof(GetFieldValue(strIniFile,"car_data",strField));

		strField.Format("car_l_%d",i);
		g_CarAry[i].dbMaxLength=atof(GetFieldValue(strIniFile,"car_data",strField));

		strField.Format("car_s_%d",i);
		g_CarAry[i].dbSpeed=atof(GetFieldValue(strIniFile,"car_data",strField));

		if (g_CarAry[i].dbSpeed <=0.0)
		{
			g_CarAry[i].dbSpeed =1.0; //��ֹ��0���
		}
	}

	//��ȡ��������
	CString strTemp="";
	for (int i=0;i<=CITY_COUNT;i++)
	{
		strField.Format("city_x_%d",i);
		g_CityAry[i].dbX=atof(GetFieldValue(strIniFile,"city_data",strField));
		
		strField.Format("city_y_%d",i);
		g_CityAry[i].dbY=atof(GetFieldValue(strIniFile,"city_data",strField));

		strField.Format("city_w_%d",i);
		g_CityAry[i].dbW=atof(GetFieldValue(strIniFile,"city_data",strField));

		strField.Format("city_tb_%d",i);
		g_CityAry[i].dbTB=atof(GetFieldValue(strIniFile,"city_data",strField));

		strField.Format("city_te_%d",i);
		g_CityAry[i].dbTE=atof(GetFieldValue(strIniFile,"city_data",strField));

		strField.Format("city_ts_%d",i);
		g_CityAry[i].dbTS=atof(GetFieldValue(strIniFile,"city_data",strField));

		strTemp.Format("%.0f,%.0f,%.0f,%.0f,%.0f,%.0f\n",g_CityAry[i].dbX,g_CityAry[i].dbY,g_CityAry[i].dbW,g_CityAry[i].dbTB,g_CityAry[i].dbTE,g_CityAry[i].dbTS);
		TRACE0(strTemp);

	}
	
	//�����������м����
	CalCityDistance();

}

//��ʼ�����м����Ϣ��
void CTSP::Init()
{
	//��ʼ����Ϣ�ش��ݲ���
	m_dbRou=ROU_MAX;

	//===============================================================
	//���������Ϣ�غ���С��Ϣ��֮��ı�ֵ
	//dbTemp=pow(Pbest,1.0/(double)CITY_COUNT); //��Pbest��CITY_COUNT�η�
	double dbN=(double)(CITY_COUNT+1); //��Ϊ��������û�а�������վ�����Լ���1
	double dbTemp=exp(log(Pbest)/dbN); //��Pbest����
	//m_dbRatio=(1.0-dbTemp)/((dbN/2.0-1.0)*dbTemp);
	m_dbRatio=(2.0/dbTemp-2.0)/(dbN-2.0);

	//===============================================================
	//��ʼ��������Ϣ�أ������õ��㹻����ô��һ�ε�����ɺ󣬻����ó�MaxQ(1),Ȼ������ͻ�������������֮��
	for (int i=0;i<=CITY_COUNT;i++)
	{
		for (int j=0;j<=CITY_COUNT;j++)
		{
			g_Pheromone[i][j]=DBQ;
		}
	}

	//==================================================================
	//�����������м��ѡ�����ֵ
	for (int i=0;i<=CITY_COUNT;i++)
	{
		for (int j=0;j<=CITY_COUNT;j++)
		{
			g_Prob[i][j]=pow(g_Pheromone[i][j],ALPHA)*g_distance_BETA[i][j];
		}
	}


	//�Ȱ������������߹���·������Ϊһ���㹻���ֵ
	m_global_best_ant.m_dbPathLength=DB_MAX; //
	
	//��������Ϊ0
	m_nStep=0;

	//�Ƿ��Ǳ�����������·������Ϊfalse
	m_blVary=false;
	m_nVaryStep=0; //���������ѽ���Ĵ�������Ϊ0
	m_nVaryCount=0; //����ɹ��Ĵ���

}

//���»�����Ϣ��
void CTSP::UpdatePheromone(int nFlag)
{
	//��ʱ������Ϣ��	
	for (int i=0;i<=CITY_COUNT;i++)
	{
		for (int j=0;j<=CITY_COUNT;j++)
		{
			m_pdbTempAry[i][j]=0.0; //��ȫ������Ϊ0
		}
	}

	//==================================================================
	//��ȫ�����Ż��ߵ����������ϸ�����Ϣ��
	if (nFlag == 0)
	{
		m_temp_ant=m_iteration_best_ant;
	}
	else
	{
		m_temp_ant=m_global_best_ant;
	}

	double dbNewPheromone=1.0/m_temp_ant.m_dbPathLength; //�����µ���Ϣ��

	//==================================================================
	//���������µ���Ϣ��
	int m=0;
	int n=0;
	if (m_temp_ant.m_dbPathLength < DB_MAX) 
	{
		for (int j=1;j<m_temp_ant.m_nPathCount;j++)
		{
			m=m_temp_ant.m_nPath[j-1];
			n=m_temp_ant.m_nPath[j];
			if (m>CITY_COUNT) //������վ
			{
				m=0;
			}
			if (n>CITY_COUNT) //������վ
			{
				n=0;
			}
			m_pdbTempAry[m][n]=m_pdbTempAry[m][n]+dbNewPheromone;
			m_pdbTempAry[n][m]=m_pdbTempAry[m][n];
		}

		//�����к�����վ֮�����Ϣ��
		m_pdbTempAry[n][0]=m_pdbTempAry[n][0]+dbNewPheromone;
		m_pdbTempAry[0][n]=m_pdbTempAry[n][0];
	}

	//==================================================================
	//���»�����Ϣ��
	for (int i=0;i<=CITY_COUNT;i++)
	{
		for (int j=0;j<=CITY_COUNT;j++)
		{
			g_Pheromone[i][j]=g_Pheromone[i][j]*m_dbRou+m_pdbTempAry[i][j];  //���µĻ�����Ϣ�� = �������Ϣ�� + �����µ���Ϣ��
		}
	}

	//==================================================================
	//��黷����Ϣ���Ƿ񳬹���Χ
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
	// �����껷����Ϣ�غ󣬼����������м��ѡ�����ֵ
	// ��ǰ����ô浽�������������㷨�����ٶ�
	// ÿֻ������ѡ����һ�����е�ʱ��ֱ�Ӳ������Ϳ��ԣ��������ظ����м���
	for (int i=0;i<=CITY_COUNT;i++)
	{
		for (int j=0;j<=CITY_COUNT;j++)
		{
			g_Prob[i][j]=pow(g_Pheromone[i][j],ALPHA)*g_distance_BETA[i][j];
		}
	}



}

//����·��
void CTSP::Search()
{

	//===========================================================
	//��ձ���
	m_dbMinLength=DB_MAX; //������һ���㹻���ֵ

	for (int i=0;i<N_MAX_PATH;i++)
	{
		m_nBestPath[i]=0;
	}
	m_nBestPathCount=0; //���·����ĵ����


	//���·����ƽ��·������
	for (int i=0;i<N_MAX_IT_COUNT;i++)
	{
		g_dbPathLenAry[i]=DB_MAX;
	}
	memset(g_dbPathAvgLenAry,0,sizeof(g_dbPathAvgLenAry));

	//===========================================================
	//��ʼ����
	double dbMid=((double)IT_COUNT)/2.0;
	double dbTemp=0.0;
	double dbRate=0.0;
	double dbQ=0.0;

	int R=0; //��¼�������ٴ�û�н�����

	int nPercent=0; //����

	int nFlag=0; //��ȫ�ֻ��ǵ������Ž���»�����Ϣ��

	for (int i=0;i<IT_COUNT;i++) //�ڵ��������ڽ���ѭ��
	{

		//����ѡ����Ե�ֵQ
		dbTemp=abs((double)i-dbMid);
		dbRate=pow(dbTemp,Q_POWER)/pow(dbMid,Q_POWER);
		dbQ=Q_Min+(Q_Max-Q_Min)*dbRate;

		//����һ������
		for (int j=0;j<ANT_COUNT;j++)		
		{
			//�����ϳ�ʼ��
			m_cAntAry[j].Init(); 

			//����ѡ����Ե�ֵ
			m_cAntAry[j].m_dbQ=dbQ;

			//���Ͽ�ʼ����
			m_cAntAry[j].Search(); 

		}

		//�Ƿ��и��Ž���������򱣴�
		for (int j=0;j<ANT_COUNT;j++)		
		{			
			if (m_cAntAry[j].m_dbPathLength < m_dbMinLength)
			{
				m_dbMinLength=m_cAntAry[j].m_dbPathLength;
				m_nBestPathCount=m_cAntAry[j].m_nPathCount;

				m_nStep=i+1; //�����ǵڼ������������·��

				m_blVary=false;

				for (int k=0;k<m_nBestPathCount;k++)
				{
					m_nBestPath[k]=m_cAntAry[j].m_nPath[k];
				}

				R=0; //����н��������R��0�����¼���
			}


			//������������·��
			if (m_cAntAry[j].m_dbPathLength < g_dbPathLenAry[i])
			{
				g_dbPathLenAry[i]=m_cAntAry[j].m_dbPathLength;
			}
			
			//��¼����·������
			g_dbPathAvgLenAry[i]=g_dbPathAvgLenAry[i]+m_cAntAry[j].m_dbPathLength;

		}

		//���㱾�������·��ƽ������
		g_dbPathAvgLenAry[i]=g_dbPathAvgLenAry[i]/(double)ANT_COUNT;

		//�жϸ��»�����Ϣ�ر�־
		if (R >=  R_MAX) //�Ѿ��ܶ��û�н�����
		{
			nFlag=1;
			R=0; //R��0�����¼���
		}
		else
		{
			nFlag=0;
			R++;
		}

		//����ȫ���������Ϻ͵�������������
		m_iteration_best_ant.m_dbPathLength=DB_MAX; //����֮ǰ���õ����������ϵ�·������
		SaveBestAnt();

		//�������������ɹ���������·��
		if (Vary() == true)
		{
			m_dbMinLength=m_global_best_ant.m_dbPathLength;
			m_nBestPathCount=m_global_best_ant.m_nPathCount;
			for (int k=0;k<m_nBestPathCount;k++)
			{
				m_nBestPath[k]=m_global_best_ant.m_nPath[k];
			}

			m_nVaryStep=i+1; //�����ǵڼ���ʱ������������·��
			m_blVary=true;
			m_nVaryCount++;
		}


		//�������������ɹ���������·��
		if (Vary_3() == true)
		{
			m_dbMinLength=m_global_best_ant.m_dbPathLength;
			m_nBestPathCount=m_global_best_ant.m_nPathCount;
			for (int k=0;k<m_nBestPathCount;k++)
			{
				m_nBestPath[k]=m_global_best_ant.m_nPath[k];
			}

			m_nVaryStep=i+1; //�����ǵڼ���ʱ������������·��
			m_blVary=true;
			m_nVaryCount++;
		}

		//ȫ�������������һ�κ�,���»�����Ϣ��
		UpdatePheromone(nFlag); 
	
		//��ʾ��������
		nPercent++;
		g_pc->SetPos(nPercent*100/IT_COUNT);

	}

}


//����·���еĵ��ŵõ����ǵڼ�����
//���� [ 1, CAR_NUM ]
int CTSP::GetCarNo(int nNode)
{
	int nSendCount=(nNode-CITY_COUNT)/CAR_COUNT;

	return nNode-CITY_COUNT-nSendCount*CAR_COUNT+1;
}

//����ȫ���������Ϻ͵�����������
void CTSP::SaveBestAnt()
{
	//���汾���������������
	for (int m=0;m<ANT_COUNT;m++)		
	{			
		//����ȫ����������
		if (m_cAntAry[m].m_dbPathLength < m_global_best_ant.m_dbPathLength)
		{
			 m_global_best_ant=m_cAntAry[m];
		}

		//���������������
		if (m_cAntAry[m].m_dbPathLength < m_iteration_best_ant.m_dbPathLength)
		{
			 m_iteration_best_ant=m_cAntAry[m];
		}

	}

}

//�����������Ƿ����Ҫ��
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
	//������·���Ƿ��������

	int nCityNoNext=0;
	int nCityNoPrev=0;
	
	int nCarNo=-1;
	double dbL=0.0; //����
	double dbW=0.0; //����
	double dbT=0.0; //ʱ��

	//���泵�����г�ʱ��
	double dbTimeAry[N_MAX_CAR_COUNT];
	memset(dbTimeAry,0,sizeof(dbTimeAry));

	for (int i=0;i<ant.m_nPathCount;i++)
	{
		if (i == 0) //�Ǹտ�ʼ
		{
			nCarNo=GetCarNo(ant.m_nPath[0]);
			nCityNoNext=0;
			dbL=0.0;
			dbW=0.0;
			dbT=dbTimeAry[nCarNo-1];
			
		}
		else
		{
			nCityNoNext=ant.m_nPath[i];
			if (nCityNoNext > CITY_COUNT) //������վ�����ǰ���һ����
			{
				dbL=dbL+g_distance[nCityNoPrev][0]; //���Ϸ��ص�·��

				if (dbL>g_CarAry[nCarNo-1].dbMaxLength) //·����������
				{
					return false;
				}
				if (dbW>g_CarAry[nCarNo-1].dbMaxWeight) //������������
				{
					return false;
				}

				//���³����г�ʱ��
				dbTimeAry[nCarNo-1]=dbTimeAry[nCarNo-1]+g_distance[nCityNoPrev][0]/g_CarAry[nCarNo-1].dbSpeed;
		
				//׼�������һ����
				dbL=0.0;
				dbW=0.0;
				nCarNo=GetCarNo(nCityNoNext);
				dbT=dbTimeAry[nCarNo-1];
				nCityNoNext=0;

			}
			else //����һ����
			{
				dbW=dbW+g_CityAry[nCityNoNext].dbW;
				dbL=dbL+g_distance[nCityNoPrev][nCityNoNext];

				//��ʱ�䴰����鵽��ʱ���Ƿ����Ҫ��
				if (g_nHTW == 1) //Ӳʱ�䴰
				{
					//��������͵��ʱ��
					dbT=dbT+g_distance[nCityNoPrev][nCityNoNext]/g_CarAry[nCarNo-1].dbSpeed;

					if (dbT > g_CityAry[nCityNoNext].dbTE) //����ʱ�䳬��ʱ�䴰
					{
						return false;
					}
					else
					{
						if (dbT < g_CityAry[nCityNoNext].dbTB) //��ǰ����ʱ�䴰
						{
							dbT = g_CityAry[nCityNoNext].dbTB;
						}
						else //��ʱ�䴰�ڵ���
						{
						}
						dbT=dbT+g_CityAry[nCityNoNext].dbTS; //���Ϸ���ʱ��

						dbTimeAry[nCarNo-1]=dbT; //���³����г�ʱ��
					}

				}
				else if (g_nHTW == 2) //��ʱ�䴰��ʱ��ʵ��
				{
				}

			}

		}
	
		nCityNoPrev=nCityNoNext;
	}

	//========================================================
	//������һ��·��
	dbL=dbL+g_distance[nCityNoPrev][0]; //���Ϸ��ص�·��
	if (dbL>g_CarAry[nCarNo-1].dbMaxLength) //·����������
	{
		return false;
	}
	if (dbW>g_CarAry[nCarNo-1].dbMaxWeight) //������������
	{
		return false;
	}

	//========================================================
	return true;

}


//���������������������ϲ���һ���µ����ϣ����������ͱ���
//����������ķ���true
bool CTSP::Vary()
{
	//�����û�в�������������ϣ�ֱ���˳�
	if (m_global_best_ant.m_dbPathLength >= DB_MAX)
	{
		return false;
	}

	//����
	m_vary_ant=m_global_best_ant; 

	//���б���
	int nGeneLen=m_vary_ant.m_nPathCount; //·�����ĸ�����Ҳ���ǻ��򳤶�
	int nCount=rnd(0,CITY_COUNT); //��������������
	nCount=MAX(nCount,1); //���ٱ���1��

	int nP1=0;
	int nP2=0;
	int nTemp=0;

	int A=0;
	int B=0;
	int C=0;
	for (int i=0;i<nCount;i++)
	{
		//�����������λ��
		nP1=rnd(0,nGeneLen);
		nP2=rnd(0,nGeneLen);

		//�����������ͬһλ�ã��򲻽���
		if (nP1== nP2)
		{
			continue;
		}

		//��������ĵ����г����㣬�򲻽��н���
		if (m_vary_ant.m_nPath[nP1]>CITY_COUNT)
		{
			continue;
		}
		if (m_vary_ant.m_nPath[nP2]>CITY_COUNT)
		{
			continue;
		}

		//����Ⱦɫ��
		nTemp=m_vary_ant.m_nPath[nP1];
		m_vary_ant.m_nPath[nP1]=m_vary_ant.m_nPath[nP2];
		m_vary_ant.m_nPath[nP2]=nTemp;

		//ֻ����һ�Σ����Ҫ������Σ�ע�͵�����
		break; 
	}

	//������ɣ�����������ϵ�·������
	m_vary_ant.CalPathLen();

	//�������ϲ���ԭ���ĺã�ֱ���˳�
	if (m_vary_ant.m_dbPathLength >= m_global_best_ant.m_dbPathLength)
	{
		return false;
	}

	//===================================================
	//����������ϱ�ԭ��·���̣�����Ҫ��������
	//��Ϊ��������󣬳��е�˳�������
	//���ܵ���ĳ������������·�����ȴ���������г�
	//Ҳ���ܵ���ĳ�����������ĳ��е��������������ڳ������������
	//�������ֽ��ҲҪ�ų���
	if (CheckVaryAnt(m_vary_ant) == true) //������У����ƹ�ȥ
	{
		m_global_best_ant=m_vary_ant;
	}

	return true;

}

//���ñ���
bool CTSP::Vary_3()
{
	//�����û�в�������������ϣ�ֱ���˳�
	if (m_global_best_ant.m_dbPathLength >= DB_MAX)
	{
		return false;
	}

	//����
	m_vary_ant=m_global_best_ant; 

	//���б���
	int nGeneLen=m_vary_ant.m_nPathCount; //·�����ĸ�����Ҳ���ǻ��򳤶�

	//����������õĿ�ʼ�ͽ���λ��
	int nP1=rnd(1,nGeneLen);
	int nP2=nP1;
	while (nP2 == nP1)
	{
		nP2=rnd(1,nGeneLen);
	}
	int N1=MIN(nP1,nP2);
	int N2=MAX(nP1,nP2);

	//���е��ñ���
	int nTempAry[N_MAX_PATH];
	memcpy(nTempAry,m_vary_ant.m_nPath,sizeof(nTempAry));

	for (int i=N1;i<=N2;i++)
	{
		m_vary_ant.m_nPath[i]=nTempAry[N1+N2-i];
	}

	//������ɣ�����������ϵ�·������
	m_vary_ant.CalPathLen();

	//�������ϲ���ԭ���ĺã�ֱ���˳�
	if (m_vary_ant.m_dbPathLength >= m_global_best_ant.m_dbPathLength)
	{
		return false;
	}

	//===================================================
	//����������ϱ�ԭ��·���̣�����Ҫ��������
	//��Ϊ��������󣬳��е�˳�������
	//���ܵ���ĳ������������·�����ȴ���������г�
	//Ҳ���ܵ���ĳ�����������ĳ��е��������������ڳ������������
	//�������ֽ��ҲҪ�ų���
	if (CheckVaryAnt(m_vary_ant) == true) //������У����ƹ�ȥ
	{
		m_global_best_ant=m_vary_ant;
	}

	return true;

}

//����������ӱ�����ѡ������������ϲ���һ���µ����ϣ����������ͱ���
//����������ķ���true
bool CTSP::Vary_2()
{
	CAnt cNewAnt; //����һ���µ�����
	cNewAnt.m_dbPathLength=DB_MAX; //����·����������Ϊ�ܴ�

	int nBestAntIndex=0;
	for (int i=0;i<ANT_COUNT;i++) //�ұ���������������ϣ�����¼��λ��
	{
		if (m_cAntAry[i].m_dbPathLength < cNewAnt.m_dbPathLength)
		{
			cNewAnt=m_cAntAry[i];
			nBestAntIndex=i;
		}
	}


	//���б���
	int nGeneLen=cNewAnt.m_nPathCount; //·�����ĸ�����Ҳ���ǻ��򳤶�
	int nCount=rnd(0,CITY_COUNT); //��������������
	nCount=MAX(nCount,1); //���ٱ���1��

	int nP1=0;
	int nP2=0;
	int nTemp=0;

	for (int i=0;i<nCount;i++)
	{
		//�����������λ��
		nP1=rnd(0,nGeneLen);
		nP2=rnd(0,nGeneLen);

		//�����������ͬһλ�ã��򲻽���
		if (nP1== nP2)
		{
			continue;
		}

		//��������ĵ����г����㣬�򲻽��н���
		if (cNewAnt.m_nPath[nP1]>CITY_COUNT)
		{
			continue;
		}
		if (cNewAnt.m_nPath[nP2]>CITY_COUNT)
		{
			continue;
		}

		//����Ⱦɫ��
		nTemp=cNewAnt.m_nPath[nP1];
		cNewAnt.m_nPath[nP1]=cNewAnt.m_nPath[nP2];
		cNewAnt.m_nPath[nP2]=nTemp;

		//ֻ����һ�Σ����Ҫ������Σ�ע�͵�����
		//break; 
	}

	//������ɣ�����������ϵ�·������
	cNewAnt.CalPathLen();

	//�������ϲ���ԭ���ĺã�ֱ���˳�
	if (cNewAnt.m_dbPathLength >= m_cAntAry[nBestAntIndex].m_dbPathLength)
	{
		return false;
	}

	//===================================================
	//����������ϱ�ԭ��·���̣�����Ҫ��������
	//��Ϊ��������󣬳��е�˳�������
	//���ܵ���ĳ������������·�����ȴ���������г�
	//Ҳ���ܵ���ĳ�����������ĳ��е��������������ڳ������������
	//�������ֽ��ҲҪ�ų���
	if (CheckVaryAnt(cNewAnt) == true) //������У����ƹ�ȥ
	{
		m_cAntAry[nBestAntIndex]=cNewAnt;
	}

	return true;

}

//���深ֳ���ò���û��ʵ��
//ѡ�񱾴������źʹ��ŵ���ֻ���Ͻ��н��深ֳ
void CTSP::Propagate()
{
	//��������С��2��ֱ���˳�
	if (ANT_COUNT<2)
	{
		return;
	}

	//��������С��2��ֱ���˳�
	if (CITY_COUNT<2)
	{
		return;
	}

	//�ȶ����ϰ�·�����̽�������·����̵���ǰ�棬��ǰ��ֻ�������źʹ�������
	CAnt cTempAnt;
	for (int i=0;i<ANT_COUNT-1;i++) //ð������
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

	//��ʼ���深ֳ
	int nGeneLen=MIN(m_cAntAry[0].m_nPathCount,m_cAntAry[1].m_nPathCount); //�õ��������̳���

	 //�õ���Ҫ����Ŀ�ʼ�ͽ���λ��
	int a=rnd(1,nGeneLen);
	int b=a;
	while (b == a)
	{
		b=rnd(1,nGeneLen);
	}
	
	int N1=MIN(a,b);
	int N2=MAX(a,b);


	//������ֻ���ϣ����潻�深ֳ�������
	CAnt cAnt_0,cAnt_1; 
	cAnt_0=m_cAntAry[0];
	cAnt_1=m_cAntAry[1];

	////ȥ���ظ���Ⱦɫ��
	for (int i=1;i<cAnt_0.m_nPathCount;i++)
	{
		for (int j=N1;j<=N2;j++)
		{
			if (cAnt_0.m_nPath[i] == m_cAntAry[1].m_nPath[j]) //Ⱦɫ����ͬ
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
			if (cAnt_1.m_nPath[i] == m_cAntAry[0].m_nPath[j]) //Ⱦɫ����ͬ
			{
				cAnt_1.m_nPath[i]=-1;
				break;
			}
		}
	}

	//�����µ�Ⱦɫ��
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

	//����Ⱦɫ�壬�ѵ���-1��Ⱦɫ��ȥ�������¼���·�������
	memcpy(nTempAry,cAnt_0.m_nPath,sizeof(nTempAry));
	int nGeneCount=0;
	for (int i=0;i<cAnt_0.m_nPathCount;i++)
	{
		if (nTempAry[i] >=0) //��ЧȾɫ��
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
		if (nTempAry[i] >=0) //��ЧȾɫ��
		{
			cAnt_1.m_nPath[nGeneCount]=nTempAry[i];
			nGeneCount++;
		}
	}
	cAnt_1.m_nPathCount=nGeneCount;


	//�������źʹ�������
	//���������ϵ�·������
	if (CheckVaryAnt(cAnt_1) == true) //������Ч
	{
		cAnt_1.CalPathLen();

		if (cAnt_1.m_dbPathLength < m_cAntAry[1].m_dbPathLength)
		{
			m_cAntAry[1]=cAnt_1;

			if (m_cAntAry[1].m_dbPathLength < m_cAntAry[0].m_dbPathLength) //����滻�ˣ���������
			{
				cTempAnt=m_cAntAry[0];
				m_cAntAry[0]=m_cAntAry[1];
				m_cAntAry[1]=cTempAnt;
			}
		}

	}

	if (CheckVaryAnt(cAnt_0) == true) //������Ч
	{
		cAnt_0.CalPathLen();
		if (cAnt_0.m_dbPathLength < m_cAntAry[1].m_dbPathLength)
		{
			m_cAntAry[1]=cAnt_0;
		}

	}



}


//�õ���̰���㷨�߹���·������
double CTSP::GetGreedSearchLen()
{
	double dbLen=0.0; //���ó���Ϊ0
	int nCurCityNo=rnd(0,CITY_COUNT); //���ѡ��ǰ����
	int nNextCityNo=-1; //��һ�����еı��
	int nMovedCityCount=1; //�����߹��ĳ�������Ϊ1
	double dbTemp=DB_MAX; //��ʱ�����������м�ľ���

	int nAllowedCityAry[N_MAX_CITY_COUNT+1]; //ûȥ���ĳ����б�
	for (int i=0;i<=CITY_COUNT;i++)
	{
		nAllowedCityAry[i]=1;
	}
	nAllowedCityAry[nCurCityNo]=0;

	int nStartNo=nCurCityNo; //���³�������

	//CString strAll="";
	//CString strTemp="";
	//strAll.Format("%d",nStartNo);

	//��ʼ��̰���㷨����
	while (nMovedCityCount != CITY_COUNT+1)
	{
		//�������ñ�����ֵ
		nNextCityNo=-1;
		dbTemp=DB_MAX;

		//Ѱ���뵱ǰ��������ĳ���
		for (int i=0;i<=CITY_COUNT;i++)
		{
			if ((nAllowedCityAry[i]==1) && (g_distance[nCurCityNo][i] < dbTemp))
			{
				dbTemp=g_distance[nCurCityNo][i];
				nNextCityNo=i;
			}
		}

		//����·�����ȣ��ı䵱ǰ���У����³���ȥ���ı�־��ȥ���ĳ�������
		dbLen=dbLen+dbTemp;
		nCurCityNo=nNextCityNo;
		nAllowedCityAry[nNextCityNo]=0;
		nMovedCityCount++;

		//strTemp.Format(",%d",nNextCityNo);
		//strAll=strAll+strTemp;
	}

	dbLen=dbLen+g_distance[nCurCityNo][nStartNo]; //���ϴ����ͳ��з��س������·������

	//strAll=strAll+"\n";
	//TRACE0(strAll);

	return dbLen;

}


















