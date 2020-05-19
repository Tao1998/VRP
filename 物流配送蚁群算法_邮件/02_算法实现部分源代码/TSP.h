#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  �� ˵ �� :  TSP�࣬��Ⱥ�㷨���Ŵ��㷨����
//
//  ��    �� :  wugsh
//
//  ��    �� :  2010.04.20
//
//  �汾˵�� :  Ver1.00    
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
	double** m_pdbTempAry;	//��ʱ������Ϣ��
	CString GetFieldValue(CString strIniFile,CString strSection,CString strKey); //�õ�ָ���ֶε�ֵ

private:
	double m_dbMaxQ; //���м���Ϣ�ص����ֵ
	double m_dbMinQ;  //���м���Ϣ�ص���Сֵ
	double m_dbRatio; //��Ϣ�����ֵ����Сֵ֮��ı�ֵ����ǰ����ÿ��Բ���ÿ�ζ�����

	double GetGreedSearchLen(); //�õ���̰���㷨�õ���·������
public:

	CAnt m_cAntAry[N_MAX_ANT_COUNT]; //������������

	CAnt m_global_best_ant; //����ȫ��������ĸ���
	CAnt m_iteration_best_ant; //���������������
	CAnt m_vary_ant; //����������ĸ���������������
	CAnt m_temp_ant; //��ʱ���ϣ�������Ϣ�ص�ʱ����

	double m_dbRou; //��Ϣ�ش��ݲ������ᶯ̬�ı��
	double m_dbMinLength; //·����С����

	int m_nBestPath[N_MAX_PATH]; //��¼���·��
	int m_nBestPathCount; //���·����ĵ����

	int m_nStep; //�����ǵڼ�����������ѽ��
	int m_nVaryStep; //���±����������ѽ���Ĵ���

	int m_nVaryCount; //����ɹ��Ĵ���
	bool m_blVary; //���·���Ƿ��Ǳ��������

public:

	void Init(); //��ʼ��
	void Search(); //����
	void SaveBestAnt(); //����ȫ���������Ϻ͵�����������
	void UpdatePheromone(int nFlag); //���»�����Ϣ��

	//�Ŵ��㷨����
	void Propagate(); //���深ֳ

	bool Vary(); //�������
	bool Vary_2(); //�����������һ�ַ�ʽ
	bool Vary_3(); //���ñ���

	bool CheckVaryAnt(CAnt ant);//�����������Ƿ����Ҫ��

public:

	int GetCarNo(int nNode); //����·���еĵ��ŵõ����ǵڼ�����

	void CalCityDistance(); //�����������м����
	void SetParameterDefault(); //�ָ��㷨����ΪĬ��ֵ

	void LoadDataFromIniFile(CString strIniFile); //���ı��ļ���������


};
