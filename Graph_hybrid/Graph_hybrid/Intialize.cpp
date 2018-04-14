#include<time.h>
#include"Graph.h"
#include"Intialize.h"
#pragma warning( disable : 4996 )
using namespace std;

//���������ʼ��
int ** intialize_sol(Graph a, int number,int population)
{
	int **sol = new int*[population];
	srand((unsigned)time(NULL));
	for (int i = 0; i < population; i++)
	{
		sol[i] = new int[a.vexnum];
		for (int j = 0; j < a.vexnum; j++)sol[i][j] = rand() % number;
	}
	return sol;
}

//��ʼ�����˱�
int ** intialize_adj_table(Graph b, int num, int * sol) {
	int ** table = new int*[b.vexnum];
	for (int i = 0; i < b.vexnum; i++)
	{
		table[i] = new int[num];
		for (int j = 0; j < num; j++)
		{
			table[i][j] = 0;
			for (int k = 0; k < b.vexnum; k++)         //������j��ɫ�ĵ�����i��������������+1
			{
				if (k == i)continue;
				if ((sol[k] == j) && (b.arcs[i][k] == 1))table[i][j]++;
			}
		}
	}
	return table;
}

//����Ŀ�꺯��ֵ
int num_conflict(Graph b, int * sol)
{
	int num = 0;
	for (int i = 0; i < b.vexnum; i++)
		for (int j = 0; j < b.vexnum; j++)if ((b.arcs[i][j] == 1) && (sol[i] == sol[j]))num++;
	return num / 2;
}

//��ʼ�����ɱ�
int **intialize_tabu_table(Graph c, int num) {

	int ** table = new int*[c.vexnum];
	for (int i = 0; i < c.vexnum; i++)
	{
		table[i] = new int[num];
		for (int j = 0; j < num; j++) table[i][j] = 0;    //���ɱ��ʼֵΪ0
	}
	return table;
}

//��ȡ��ǰʱ�䲢��ʽ�����
string getTime()              
{
	time_t timep;
	time(&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	return tmp;
}