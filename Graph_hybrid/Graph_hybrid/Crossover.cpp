#include<time.h>
#include"Graph.h"
#include"Crossover.h"
using namespace std;

int * cross_sol(Graph a, int * solone, int * soltwo, int num)     //实现两个解的交差算符
{
	
	int * sol_one = new int[num];
	int * sol_two = new int[num];                           //记录颜色独立集的个数
	int * sol1 = new int[a.vexnum];
	int * sol2 = new int[a.vexnum];
	int * cross_sol = new int[a.vexnum];                    //得到的交差算符解
	int best,flag;
	for (int i = 0; i<num; i++)
	{
		sol_one[i] = 0;
		sol_two[i] = 0;
	}
	for (int i = 0; i<a.vexnum; i++)
	{
		sol1[i] = solone[i];
		sol2[i] = soltwo[i];
		cross_sol[i] = -1;
		sol_one[sol1[i]]++;
		sol_two[sol2[i]]++;
	}


	for (int i = 0; i<num; i++)
	{
		flag = i % 2;
		if (flag == 0)
		{
			best = 0;
			for (int j = 1; j < num; j++)
				if (sol_two[j] > sol_two[best])best = j;
			sol_two[best] = -1;
			for (int k = 0; k < a.vexnum; k++)
			{
				if (sol2[k] == best)
				{
					cross_sol[k] = i;
					sol2[k] = -1;                   //回-1
					sol_one[sol1[k]]--;
					sol1[k] = -1;
				}
			}
		}
		else
		{
			best = 0;
			for (int j = 1; j < num; j++)
				if (sol_one[j] > sol_one[best])best = j;
			sol_one[best] = -1;
			for (int k = 0; k < a.vexnum; k++)
			{
				if (sol1[k] == best)
				{
					cross_sol[k] = i;
					sol1[k] = -1;                   //回-1
					sol_two[sol2[k]]--;
					sol2[k] = -1;
				}
			}
		}
	}

	for (int i = 0; i<a.vexnum; i++)
		if (cross_sol[i] == -1)
		{
			srand((unsigned)time(NULL));
			//cout << " 随机种子： " << (unsigned)time(NULL) << endl;
			cross_sol[i] = rand() % num;
		}

	delete[]sol_one;
	delete[]sol_two;
	delete[]sol1;
	delete[]sol2;

	return cross_sol;
}