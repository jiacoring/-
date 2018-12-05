/*
*	func.cpp
*	created on 2018.12
*/
//��������
#include"vertex.h"
#include<cstdlib>
#include"UDgraph.h"
#include"func.h"
//����<<

//�ⲿȫ�ֶ�������
extern UDgraph graph;

std::ostream & operator<<(std::ostream &os,vertex v)
{
	os<<"��ţ�"<<v.number<<endl;
	os<<"���ƣ�"<<v.name<<endl;
	os<<"λ�ã�"<<v.position<<endl;
	os<<"��飺"<<v.summary<<endl;
	return os;
}

//���˵�
void menu()
{
	while(1) {
		system("color f1");
		system("cls");
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"|                        �����е�����ѯϵͳ                         |"<<endl;
		cout<<"|        1.����Ա��¼                                               |"<<endl;
		cout<<"|        2.�û���¼                                                 |"<<endl;
		cout<<"|        3.�˳�                                                     |"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
	}
}
//�˳�����
void quit()
{
	std::exit(EXIT_SUCCESS);
}
//����Ա����ѡ�����
void admin()
{
	while(1) {
		system("color f1");
		system("cls");
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"|                        �����е�����ѯϵͳ                         |"<<endl;
		cout<<"|��ѡ��                                                           |"<<endl;
		cout<<"|        1.��Ӿ���                                                 |"<<endl;
		cout<<"|        2.ɾ������                                                 |"<<endl;
		cout<<"|        3.��Ӿ���                                                 |"<<endl;
		cout<<"|        4.�޸Ĺ�ϵ                                                 |"<<endl;
		cout<<"|        5.����                                                     |"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"����ѡ��";
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
//�û�����ѡ�����
void guest()
{
	while(1) {
		system("color f1");
		system("cls");
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"|                        �����е�����ѯϵͳ                         |"<<endl;
		cout<<"|��ѡ��                                                           |"<<endl;
		cout<<"|        1.��ѯ������Ϣ                                             |"<<endl;
		cout<<"|        2.��·                                                     |"<<endl;
		cout<<"|        3.�鿴�����ڽӹ�ϵ                                         |"<<endl;
		cout<<"|        4.����                                                     |"<<endl;
		cout<<"---------------------------------------------------------------------"<<endl;
		cout<<"����ѡ��";
		int choice;


	}
}

