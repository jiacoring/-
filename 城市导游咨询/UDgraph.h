/*
*	UDgraph.h
*	Created on 2018.12
*/
#ifndef UDGRAPH_H
#define UDGRAPG_H
#include"vertex.h"
#include<climits>
#define INFINITY DBL_MAX  

//��������
class UDgraph {
private:
	vector<vertex> node;  //���㼯
	vector<vector<double>> adjMatrix; 	//ԭʼ�ڽӾ���
	vector<vector<double>> dis;  //������̿ɴ����
	vector<vector<int>> path;  //������¼·����·��������ţ���int��
public:
	//�ⲿ����
	UDgraph();  //���캯��,���ļ���ȡ������Ϣ���ڽӾ���
	~UDgraph(){}  //��������
/***************����Ա����******************/
	void add();   //��ӽ��
	void del();   //ɾ�����
	void modifyVertex();   //�޸Ľ����Ϣ
	void modifyRelation();   //�޸Ľ��֮��Ĺ�ϵ
/***************�û�����******************/
	void getInfo();  //��ѯ������Ϣ
	void askWay();   //��·
/***************����=��==******************/
	UDgraph operator=(UDgraph & graph);
	bool operator==(UDgraph &graph);
protected:
/***************�ڲ�����******************/
	void floyd();  //�����㷨floyd�㷨
	void displayPath(int i,int j);  //��ӡi��j�����·��,i��j���±�  
};
#endif  //!UDGRAPG_H
