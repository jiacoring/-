/*
*	vertex.h
*	created on 2018.12
*	author: jiaruigang
*/
#ifndef VERTEX_H
#define VERTEX_H
#include<iostream>
#include<string>
#include<vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

class vertex {
public:
	int number;  //���
	string name;  //����
	string position;  //λ��
	string summary;  //���

	vertex(){}
	vertex(int number_m,string  name_m,string position_m,string summary_m):number(number_m),name(name_m),position(position_m),summary(summary_m){}
	~vertex(){}

	friend std::ostream & operator<<(std::ostream &os,vertex v);  
};
#endif  //!VERTEX_H
