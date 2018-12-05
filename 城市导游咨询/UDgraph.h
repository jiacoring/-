/*
*	UDgraph.h
*	Created on 2018.12
*/
#ifndef UDGRAPH_H
#define UDGRAPG_H
#include"vertex.h"
#include<climits>
#define INFINITY DBL_MAX  

//无向网类
class UDgraph {
private:
	vector<vertex> node;  //顶点集
	vector<vector<double>> adjMatrix; 	//原始邻接矩阵
	vector<vector<double>> dis;  //保存最短可达距离
	vector<vector<int>> path;  //用来记录路径，路径即是序号，用int型
public:
	//外部方法
	UDgraph();  //构造函数,从文件读取顶点信息和邻接矩阵
	~UDgraph(){}  //析构函数
/***************管理员功能******************/
	void add();   //添加结点
	void del();   //删除结点
	void modifyVertex();   //修改结点信息
	void modifyRelation();   //修改结点之间的关系
/***************用户功能******************/
	void getInfo();  //查询景点信息
	void askWay();   //问路
/***************重载=、==******************/
	UDgraph operator=(UDgraph & graph);
	bool operator==(UDgraph &graph);
protected:
/***************内部方法******************/
	void floyd();  //核心算法floyd算法
	void displayPath(int i,int j);  //打印i到j的最短路径,i和j是下标  
};
#endif  //!UDGRAPG_H
