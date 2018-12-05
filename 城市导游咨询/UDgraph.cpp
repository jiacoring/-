#include"UDgraph.h"
#include<fstream>

using std::getline;
UDgraph::UDgraph() //构造函数,输入顶点信息和邻接矩阵
{
	//通过文件读取数据
	std::ifstream in;
	in.open("vertexInfo.txt",std::ios_base::in);
	if(!in.is_open()) {
		cout<<"打开数据文件失败，请确认文件是否存在或者是否可读。"<<endl;
		abort();
	}
	vertex tmpNode;
	//cout<<"请输入景点的名称、位置、简介(每行一条信息,输入空行结束)："<<endl;
	tmpNode.number = 0;
	getline(in,tmpNode.name);
	getline(in,tmpNode.position);
	getline(in,tmpNode.summary);
	while(in.good()) {
		node.push_back(tmpNode);  //插入新景点
		tmpNode.number++;
		getline(in,tmpNode.name);
		getline(in,tmpNode.position);
		getline(in,tmpNode.summary);
	}
	in.clear();  //重置流状态
	in.close();  //关闭关联文件
		
	//获得景点个数
	auto nodeNum = node.size();
	//设置邻接矩阵的大小
	adjMatrix.resize(nodeNum);
	for(size_t i = 0;i<adjMatrix.size();++i)
		adjMatrix[i].resize(nodeNum);
	//初始化邻接矩阵
	for(size_t i = 0;i<adjMatrix.size();++i)
		for(size_t j = 0;j<adjMatrix[i].size();++j)
			if(i==j)
				adjMatrix[i][j] = 0;
			else
				adjMatrix[i][j] = INFINITY;
	//读入各个景点之间的关系，即邻接矩阵的权值
	int src,des;
	double weight;
	std::ifstream in2;
	in.open("adjInfo.txt",std::ios_base::in);  //存储邻接矩阵的文件

	if(!in2.is_open()) {
		cout<<"打开数据文件失败，请确认文件是否存在或者是否可读。"<<endl;
		abort();
	}

	while(in2.good()) {
		in2>>src>>des>>weight;
		adjMatrix[src][des] = adjMatrix[des][src] = weight;
	}
	in2.clear();  //重置流状态
	in2.close();  //关闭文件
}  //end
   /***************管理员功能******************/
void UDgraph::add()
{
	vertex tmpNode;

	cout<<"请输入景点名称：";
	cin>>tmpNode.name;
	cout<<"请输入景点位置：";
	cin>>tmpNode.position;
	cout<<"请输入景点简介：";
	getline(cin,tmpNode.summary);

	size_t num = node.size();  //获取当前景点总数
	tmpNode.number = num;
	node.push_back(tmpNode);  //将新添加的景点加入景点集

	//重新调整邻接矩阵的大小
	adjMatrix.resize(num+1);
	for(size_t i = 0;i<adjMatrix.size();++i)
		adjMatrix[i].resize(num+1);

	cout<<"以下是已经添加的景点："<<endl;
	for(vertex x : node) {
		cout<<x.number+1<<"."<<x.name<<"  ";
		if(x.number%3==0)
			cout<<endl;
	}
	cout<<endl;
	//初始化最后一行和最后一列的值
	for(size_t i = 0;i<adjMatrix.size();++i) {
		if(i==num)
			adjMatrix[i][num] = 0.0;
		else
			adjMatrix[i][num] = adjMatrix[num][i] = INFINITY;
	}

	cout<<"请输入新添加景点与其他景点之间的距离；"<<endl;
	cout<<"输入格式：如与景点1的距离，输入：1 distance"<<endl;
	cout<<"输入-1 -1结束。"<<endl;

	int fst = num,scd;
	double distance;  //fst与scd-1景点的距离dis
	//设置邻接矩阵中的值

	while(cin>>scd>>distance&&scd>0&&scd<=adjMatrix.size()) {
		adjMatrix[num][scd-1] = adjMatrix[scd-1][fst] = distance;
	}

	cin.ignore();
	cin.clear();

	//将新添加的数据写入文件
	std::ofstream fout("vertexInfo.txt",std::ios_base::app);  //景点追加在文件尾
	if(!fout.is_open()) {
		cout<<"文件打开失败，即将退出。"<<endl;
		return;
	}
	fout<<endl;  //重起一行
	fout<<tmpNode.name<<endl;
	fout<<tmpNode.position<<endl;
	fout<<tmpNode.summary;
	//关闭文件
	fout.flush();  //刷新流
	fout.close();
	//将邻接矩阵中的新值追加到文件
	std::ofstream fout2("adjInfo.txt",std::ios_base::app);
	for(size_t i = 0;i<adjMatrix.size();++i) {
		if(adjMatrix[i][num]!=INFINITY&&adjMatrix[i][num]!=0.0) {
			fout2<<endl;  //重起一行，避免和末尾数字无缝衔接
			fout<<i<<" "<<num<<num<<" "<<adjMatrix[i][num]<<endl;
		}			
	}
	flush(fout2);
	fout2.close();
}
//删除某个结点
void UDgraph::del()
{
	cout<<"以下是所有的景点及其编号："<<endl;
	for(vertex x : node) {
		cout<<x.number+1<<"."<<x.name<<"  ";
		if(x.number%3==0)
			cout<<endl;
	}
	cout<<endl;
	cout<<"请输入要删除的景点编号：";
	int delnum;
	if(cin>>delnum&&delnum>0&&delnum<=node.size()) {
		//处理顶点集
		for(auto ite = node.begin()+delnum;ite!=node.end();++ite) 
			*(ite-1) = *ite;   //将后续结点依次向前移动

		size_t oldsize = node.size();
		node.resize(oldsize-1);   //更新长度

		//将新的编号以及信息写入文件
		std::ofstream fout("vertexInfo.txt",std::ios_base::trunc);  //这里选择清除掉所有信息重新写入
		if(!fout.is_open()) {
			cout<<"文件打开失败，即将退出。"<<endl;
			return;
		}
		for(vertex x : node) {
			fout<<x.name<<endl;
			fout<<x.position<<endl;
			if(x.number==node.size()-1)
				fout<<x.summary;    //如果是最后一行，则不加换行符
			else
				fout<<x.summary<<endl;
		}
		flush(fout);
		fout.close();  //关闭文件

		//处理邻接矩阵
		for(size_t i=0;i<adjMatrix.size();++i)
			for(size_t j = 0;j<adjMatrix[i][j];++j) {
				if(i==delnum-1)
					adjMatrix[i][j] = DBL_MIN;   //将其标志为DBL_MIN
				if(j==delnum-1)
					adjMatrix[i][j] = DBL_MIN;
			}

		//写入文件，权值为0、INFINITY、INT_MIN的不写入
		std::ofstream fout2("adjInfo.txt",std::ios_base::trunc);  //文件清空以重新写入
		for(int i = 0;i<adjMatrix.size();++i)
			for(int j = 0;j<adjMatrix.size();++j)
				if(adjMatrix[i][j]!=INFINITY&&adjMatrix[i][j]!=DBL_MIN&&adjMatrix[i][j]!=0.0)
					fout2<<i<<" "<<j<<" "<<adjMatrix[i][j]<<endl;
		//写入完毕
		flush(fout2);
		fout2.close();
		//更新邻接矩阵的大小。
		//注：也可以不更新，在刷新后重新读取时会自动更新
		size_t oldAdjSize = adjMatrix.size();
		adjMatrix.resize(oldAdjSize-1);
		for(size_t i = 0;i<adjMatrix.size();++i)
			adjMatrix[i].resize(oldAdjSize-1);
	}
}
//修改景点信息
void UDgraph::modifyVertex()
{
	cout<<"以下是所有景点，请输入要修改的景点编号："<<endl;
	for(vertex x : node) {
		cout<<x.number+1<<"."<<x.name<<"  ";
		if(x.number%3==0)
			cout<<endl;
	}
	cout<<endl;

	cout<<"您的选择：";
	int choice;
	if(cin>>choice&&choice>0&&choice<=node.size()) {
		cout<<"请输入新的名称：";
		getline(cin,node[choice-1].name);
		cout<<"请输入新的位置：";
		getline(cin,node[choice-1].position);
		cout<<"请输入新的简介：";
		getline(cin,node[choice-1].summary);
	}
	//将新的顶点信息写入文件
	std::ofstream fout("vertex.Info",std::ios_base::trunc);
	for(vertex x : node) {
		fout<<x.name<<endl;
		fout<<x.position<<endl;
		if(x.number==node.size()-1)
			fout<<x.summary;
		else
			fout<<x.summary<<endl;
	}
	flush(fout);
	fout.close();
}
//修改景点之间的关系
void UDgraph::modifyRelation()
{
	cout<<"以下是所有景点，请输入要修改的景点编号以及它们之间新的距离："<<endl;
	for(vertex x : node) {
		cout<<x.number+1<<"."<<x.name<<"  ";
		if(x.number%3==0)
			cout<<endl;
	}
	cout<<endl;

	cout<<"输入格式：如景点1与景点2的新距离：1 2 newDistance"<<endl;
	cout<<"您的输入：";
	int src,des;
	double newDistance;
	if(cin>>src>>des>>newDistance&&src>0&&src<=node.size()&&des>0&&des<=node.size()&&src!=des&&newDistance>0.0) {
		adjMatrix[src-1][des-1] = adjMatrix[des-1][src-1] = newDistance;
	}

	//将新的矩阵写入文件
	std::ofstream fout("adjInfo.txt",std::ios_base::trunc);
	for(int i = 0;i<adjMatrix.size();++i)
		for(int j = 0;j<adjMatrix.size();++j)
			if(adjMatrix[i][j]!=INFINITY&&adjMatrix[i][j]!=INT_MIN&&adjMatrix[i][j]!=0)
				fout<<i<<" "<<j<<" "<<adjMatrix[i][j]<<endl;
	//写入完毕
	flush(fout);
	fout.close();
}
/***************用户功能******************/
//查询景点信息
void UDgraph::getInfo()
{
	cout<<"以下是所有景点，请输入要查询的景点编号："<<endl;
	for(vertex x : node) {
		cout<<x.number+1<<"."<<x.name<<"  ";
		if(x.number%3==0)
			cout<<endl;
	}
	cout<<endl;
	int choice;
	cout<<"您的选择：";
	if(cin>>choice&&choice>0&&choice<=node.size()) {
		cout<<"景点"<<choice<<"的信息如下："<<endl;
		cout<<"——————————————————————————"<<endl;
		cout<<node[choice-1];
		cout<<"——————————————————————————"<<endl;
	}
}
//问路
void UDgraph::askWay()
{
	cout<<"以下是所有景点，请输入要查询的景点编号："<<endl;
	for(vertex x : node) {
		cout<<x.number+1<<"."<<x.name<<"  ";
		if(x.number%3==0)
			cout<<endl;
	}
	cout<<endl;
	int src,des;
	cout<<"如查询景点1和3：输入1 3";
	if(cin>>src>>des&&src>0&&src<node.size()&&des>0&&des<node.size()) {
		floyd();
		displayPath(src-1,des-1);
	}
}

/*******************内部方法********************/
//floyd算法
void UDgraph::floyd()
{
	dis = adjMatrix;  //将原始矩阵赋值给dis
	//设置path的大小
	path.resize(node.size());
	for(size_t i = 0;i<node.size();++i)
		path[i].resize(node.size());
	//初始化path
	for(size_t i = 0;i<node.size();++i)
		for(size_t j = 0;j<node.size();++j)
			path[i][j] =j;  //矩阵初值为各个边的终点,一种思路的一种初始化方式

	for(int k=0;k<node.size();++k)
		for(int i=0;i<node.size();++i)
			for(int j = 0;j<node.size();++j) {
				if(dis[i][j]>dis[i][k]+dis[k][j]) {
					dis[i][j] = dis[i][k]+dis[k][j];
					path[i][j] = path[i][k];
				}
				if(dis[i][j]==dis[i][k]+dis[k][j]) {   //和松弛之后的距离相等，则选择编号小的
					path[i][j] = path[i][j]<path[i][k] ? path[i][j] : path[i][k];
				}
			}
}

//打印i到j之间的最短路径
void UDgraph::displayPath(int i,int j)
{

}

UDgraph UDgraph::operator=(UDgraph & graph)
{
	if(graph==*this)
		return *this;

}
bool UDgraph::operator==(UDgraph & graph)
{
	if()
}
