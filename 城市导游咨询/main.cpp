#include"UDgraph.h"
#include"func.h"
using namespace std;

UDgraph  graph;  //全局对象定义
int main()
{
	while(true) {
		UDgraph lc_graph;  //局部对象，用来读取新的数据
		graph = lc_graph;  //将数据传到全局对象
		menu();
		admin();
	}
	system("pause");
	return 0;
}