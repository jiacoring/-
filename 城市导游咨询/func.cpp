/*
*	func.cpp
*	created on 2018.12
*/
//辅助函数
#include"vertex.h"
#include<cstdlib>
#include"UDgraph.h"
#include"func.h"
//重载<<

//外部全局对象声明
extern UDgraph graph;

std::ostream & operator<<(std::ostream &os,vertex v)
{
	os<<"编号："<<v.number<<endl;
	os<<"名称："<<v.name<<endl;
	os<<"位置："<<v.position<<endl;
	os<<"简介："<<v.summary<<endl;
	return os;
}

//主菜单
void menu()
{
	while(1) {
		system("color f1");
		system("cls");
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"|                        西安市导游咨询系统                         |"<<endl;
		cout<<"|        1.管理员登录                                               |"<<endl;
		cout<<"|        2.用户登录                                                 |"<<endl;
		cout<<"|        3.退出                                                     |"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
	}
}
//退出函数
void quit()
{
	std::exit(EXIT_SUCCESS);
}
//管理员功能选择界面
void admin()
{
	while(1) {
		system("color f1");
		system("cls");
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"|                        西安市导游咨询系统                         |"<<endl;
		cout<<"|请选择：                                                           |"<<endl;
		cout<<"|        1.添加景点                                                 |"<<endl;
		cout<<"|        2.删除景点                                                 |"<<endl;
		cout<<"|        3.添加景点                                                 |"<<endl;
		cout<<"|        4.修改关系                                                 |"<<endl;
		cout<<"|        5.返回                                                     |"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"您的选择：";
		int choice;
		switch(choice)
		{
		case 1:
			graph.add();
			break;
		case 2:
			graph.del();
			break;
		case 3:
			graph.modifyVertex();
			break;
		case 4:
			graph.modifyRelation(); 
			break;
		default:
			return;
		}
	}
}
//用户功能选择界面
void guest()
{
	while(1) {
		system("color f1");
		system("cls");
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"|                        西安市导游咨询系统                         |"<<endl;
		cout<<"|请选择：                                                           |"<<endl;
		cout<<"|        1.查询景点信息                                             |"<<endl;
		cout<<"|        2.问路                                                     |"<<endl;
		cout<<"|        3.查看景点邻接关系                                         |"<<endl;
		cout<<"|        4.返回                                                     |"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"您的选择：";
		int choice;


	}
}

