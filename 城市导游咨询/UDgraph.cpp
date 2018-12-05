#include"UDgraph.h"
#include<fstream>

using std::getline;
UDgraph::UDgraph() //���캯��,���붥����Ϣ���ڽӾ���
{
	//ͨ���ļ���ȡ����
	std::ifstream in;
	in.open("vertexInfo.txt",std::ios_base::in);
	if(!in.is_open()) {
		cout<<"�������ļ�ʧ�ܣ���ȷ���ļ��Ƿ���ڻ����Ƿ�ɶ���"<<endl;
		abort();
	}
	vertex tmpNode;
	//cout<<"�����뾰������ơ�λ�á����(ÿ��һ����Ϣ,������н���)��"<<endl;
	tmpNode.number = 0;
	getline(in,tmpNode.name);
	getline(in,tmpNode.position);
	getline(in,tmpNode.summary);
	while(in.good()) {
		node.push_back(tmpNode);  //�����¾���
		tmpNode.number++;
		getline(in,tmpNode.name);
		getline(in,tmpNode.position);
		getline(in,tmpNode.summary);
	}
	in.clear();  //������״̬
	in.close();  //�رչ����ļ�
		
	//��þ������
	auto nodeNum = node.size();
	//�����ڽӾ���Ĵ�С
	adjMatrix.resize(nodeNum);
	for(size_t i = 0;i<adjMatrix.size();++i)
		adjMatrix[i].resize(nodeNum);
	//��ʼ���ڽӾ���
	for(size_t i = 0;i<adjMatrix.size();++i)
		for(size_t j = 0;j<adjMatrix[i].size();++j)
			if(i==j)
				adjMatrix[i][j] = 0;
			else
				adjMatrix[i][j] = INFINITY;
	//�����������֮��Ĺ�ϵ�����ڽӾ����Ȩֵ
	int src,des;
	double weight;
	std::ifstream in2;
	in.open("adjInfo.txt",std::ios_base::in);  //�洢�ڽӾ�����ļ�

	if(!in2.is_open()) {
		cout<<"�������ļ�ʧ�ܣ���ȷ���ļ��Ƿ���ڻ����Ƿ�ɶ���"<<endl;
		abort();
	}

	while(in2.good()) {
		in2>>src>>des>>weight;
		adjMatrix[src][des] = adjMatrix[des][src] = weight;
	}
	in2.clear();  //������״̬
	in2.close();  //�ر��ļ�
}  //end
   /***************����Ա����******************/
void UDgraph::add()
{
	vertex tmpNode;

	cout<<"�����뾰�����ƣ�";
	cin>>tmpNode.name;
	cout<<"�����뾰��λ�ã�";
	cin>>tmpNode.position;
	cout<<"�����뾰���飺";
	getline(cin,tmpNode.summary);

	size_t num = node.size();  //��ȡ��ǰ��������
	tmpNode.number = num;
	node.push_back(tmpNode);  //������ӵľ�����뾰�㼯

	//���µ����ڽӾ���Ĵ�С
	adjMatrix.resize(num+1);
	for(size_t i = 0;i<adjMatrix.size();++i)
		adjMatrix[i].resize(num+1);

	cout<<"�������Ѿ���ӵľ��㣺"<<endl;
	for(vertex x : node) {
		cout<<x.number+1<<"."<<x.name<<"  ";
		if(x.number%3==0)
			cout<<endl;
	}
	cout<<endl;
	//��ʼ�����һ�к����һ�е�ֵ
	for(size_t i = 0;i<adjMatrix.size();++i) {
		if(i==num)
			adjMatrix[i][num] = 0.0;
		else
			adjMatrix[i][num] = adjMatrix[num][i] = INFINITY;
	}

	cout<<"����������Ӿ�������������֮��ľ��룻"<<endl;
	cout<<"�����ʽ�����뾰��1�ľ��룬���룺1 distance"<<endl;
	cout<<"����-1 -1������"<<endl;

	int fst = num,scd;
	double distance;  //fst��scd-1����ľ���dis
	//�����ڽӾ����е�ֵ

	while(cin>>scd>>distance&&scd>0&&scd<=adjMatrix.size()) {
		adjMatrix[num][scd-1] = adjMatrix[scd-1][fst] = distance;
	}

	cin.ignore();
	cin.clear();

	//������ӵ�����д���ļ�
	std::ofstream fout("vertexInfo.txt",std::ios_base::app);  //����׷�����ļ�β
	if(!fout.is_open()) {
		cout<<"�ļ���ʧ�ܣ������˳���"<<endl;
		return;
	}
	fout<<endl;  //����һ��
	fout<<tmpNode.name<<endl;
	fout<<tmpNode.position<<endl;
	fout<<tmpNode.summary;
	//�ر��ļ�
	fout.flush();  //ˢ����
	fout.close();
	//���ڽӾ����е���ֵ׷�ӵ��ļ�
	std::ofstream fout2("adjInfo.txt",std::ios_base::app);
	for(size_t i = 0;i<adjMatrix.size();++i) {
		if(adjMatrix[i][num]!=INFINITY&&adjMatrix[i][num]!=0.0) {
			fout2<<endl;  //����һ�У������ĩβ�����޷��ν�
			fout<<i<<" "<<num<<num<<" "<<adjMatrix[i][num]<<endl;
		}			
	}
	flush(fout2);
	fout2.close();
}
//ɾ��ĳ�����
void UDgraph::del()
{
	cout<<"���������еľ��㼰���ţ�"<<endl;
	for(vertex x : node) {
		cout<<x.number+1<<"."<<x.name<<"  ";
		if(x.number%3==0)
			cout<<endl;
	}
	cout<<endl;
	cout<<"������Ҫɾ���ľ����ţ�";
	int delnum;
	if(cin>>delnum&&delnum>0&&delnum<=node.size()) {
		//�����㼯
		for(auto ite = node.begin()+delnum;ite!=node.end();++ite) 
			*(ite-1) = *ite;   //���������������ǰ�ƶ�

		size_t oldsize = node.size();
		node.resize(oldsize-1);   //���³���

		//���µı���Լ���Ϣд���ļ�
		std::ofstream fout("vertexInfo.txt",std::ios_base::trunc);  //����ѡ�������������Ϣ����д��
		if(!fout.is_open()) {
			cout<<"�ļ���ʧ�ܣ������˳���"<<endl;
			return;
		}
		for(vertex x : node) {
			fout<<x.name<<endl;
			fout<<x.position<<endl;
			if(x.number==node.size()-1)
				fout<<x.summary;    //��������һ�У��򲻼ӻ��з�
			else
				fout<<x.summary<<endl;
		}
		flush(fout);
		fout.close();  //�ر��ļ�

		//�����ڽӾ���
		for(size_t i=0;i<adjMatrix.size();++i)
			for(size_t j = 0;j<adjMatrix[i][j];++j) {
				if(i==delnum-1)
					adjMatrix[i][j] = DBL_MIN;   //�����־ΪDBL_MIN
				if(j==delnum-1)
					adjMatrix[i][j] = DBL_MIN;
			}

		//д���ļ���ȨֵΪ0��INFINITY��INT_MIN�Ĳ�д��
		std::ofstream fout2("adjInfo.txt",std::ios_base::trunc);  //�ļ����������д��
		for(int i = 0;i<adjMatrix.size();++i)
			for(int j = 0;j<adjMatrix.size();++j)
				if(adjMatrix[i][j]!=INFINITY&&adjMatrix[i][j]!=DBL_MIN&&adjMatrix[i][j]!=0.0)
					fout2<<i<<" "<<j<<" "<<adjMatrix[i][j]<<endl;
		//д�����
		flush(fout2);
		fout2.close();
		//�����ڽӾ���Ĵ�С��
		//ע��Ҳ���Բ����£���ˢ�º����¶�ȡʱ���Զ�����
		size_t oldAdjSize = adjMatrix.size();
		adjMatrix.resize(oldAdjSize-1);
		for(size_t i = 0;i<adjMatrix.size();++i)
			adjMatrix[i].resize(oldAdjSize-1);
	}
}
//�޸ľ�����Ϣ
void UDgraph::modifyVertex()
{
	cout<<"���������о��㣬������Ҫ�޸ĵľ����ţ�"<<endl;
	for(vertex x : node) {
		cout<<x.number+1<<"."<<x.name<<"  ";
		if(x.number%3==0)
			cout<<endl;
	}
	cout<<endl;

	cout<<"����ѡ��";
	int choice;
	if(cin>>choice&&choice>0&&choice<=node.size()) {
		cout<<"�������µ����ƣ�";
		getline(cin,node[choice-1].name);
		cout<<"�������µ�λ�ã�";
		getline(cin,node[choice-1].position);
		cout<<"�������µļ�飺";
		getline(cin,node[choice-1].summary);
	}
	//���µĶ�����Ϣд���ļ�
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
//�޸ľ���֮��Ĺ�ϵ
void UDgraph::modifyRelation()
{
	cout<<"���������о��㣬������Ҫ�޸ĵľ������Լ�����֮���µľ��룺"<<endl;
	for(vertex x : node) {
		cout<<x.number+1<<"."<<x.name<<"  ";
		if(x.number%3==0)
			cout<<endl;
	}
	cout<<endl;

	cout<<"�����ʽ���羰��1�뾰��2���¾��룺1 2 newDistance"<<endl;
	cout<<"�������룺";
	int src,des;
	double newDistance;
	if(cin>>src>>des>>newDistance&&src>0&&src<=node.size()&&des>0&&des<=node.size()&&src!=des&&newDistance>0.0) {
		adjMatrix[src-1][des-1] = adjMatrix[des-1][src-1] = newDistance;
	}

	//���µľ���д���ļ�
	std::ofstream fout("adjInfo.txt",std::ios_base::trunc);
	for(int i = 0;i<adjMatrix.size();++i)
		for(int j = 0;j<adjMatrix.size();++j)
			if(adjMatrix[i][j]!=INFINITY&&adjMatrix[i][j]!=INT_MIN&&adjMatrix[i][j]!=0)
				fout<<i<<" "<<j<<" "<<adjMatrix[i][j]<<endl;
	//д�����
	flush(fout);
	fout.close();
}
/***************�û�����******************/
//��ѯ������Ϣ
void UDgraph::getInfo()
{
	cout<<"���������о��㣬������Ҫ��ѯ�ľ����ţ�"<<endl;
	for(vertex x : node) {
		cout<<x.number+1<<"."<<x.name<<"  ";
		if(x.number%3==0)
			cout<<endl;
	}
	cout<<endl;
	int choice;
	cout<<"����ѡ��";
	if(cin>>choice&&choice>0&&choice<=node.size()) {
		cout<<"����"<<choice<<"����Ϣ���£�"<<endl;
		cout<<"����������������������������������������������������"<<endl;
		cout<<node[choice-1];
		cout<<"����������������������������������������������������"<<endl;
	}
}
//��·
void UDgraph::askWay()
{
	cout<<"���������о��㣬������Ҫ��ѯ�ľ����ţ�"<<endl;
	for(vertex x : node) {
		cout<<x.number+1<<"."<<x.name<<"  ";
		if(x.number%3==0)
			cout<<endl;
	}
	cout<<endl;
	int src,des;
	cout<<"���ѯ����1��3������1 3";
	if(cin>>src>>des&&src>0&&src<node.size()&&des>0&&des<node.size()) {
		floyd();
		displayPath(src-1,des-1);
	}
}

/*******************�ڲ�����********************/
//floyd�㷨
void UDgraph::floyd()
{
	dis = adjMatrix;  //��ԭʼ����ֵ��dis
	//����path�Ĵ�С
	path.resize(node.size());
	for(size_t i = 0;i<node.size();++i)
		path[i].resize(node.size());
	//��ʼ��path
	for(size_t i = 0;i<node.size();++i)
		for(size_t j = 0;j<node.size();++j)
			path[i][j] =j;  //�����ֵΪ�����ߵ��յ�,һ��˼·��һ�ֳ�ʼ����ʽ

	for(int k=0;k<node.size();++k)
		for(int i=0;i<node.size();++i)
			for(int j = 0;j<node.size();++j) {
				if(dis[i][j]>dis[i][k]+dis[k][j]) {
					dis[i][j] = dis[i][k]+dis[k][j];
					path[i][j] = path[i][k];
				}
				if(dis[i][j]==dis[i][k]+dis[k][j]) {   //���ɳ�֮��ľ�����ȣ���ѡ����С��
					path[i][j] = path[i][j]<path[i][k] ? path[i][j] : path[i][k];
				}
			}
}

//��ӡi��j֮������·��
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
