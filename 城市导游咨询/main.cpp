#include"UDgraph.h"
#include"func.h"
using namespace std;

UDgraph  graph;  //ȫ�ֶ�����
int main()
{
	while(true) {
		UDgraph lc_graph;  //�ֲ�����������ȡ�µ�����
		graph = lc_graph;  //�����ݴ���ȫ�ֶ���
		menu();
		admin();
	}
	system("pause");
	return 0;
}