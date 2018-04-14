#include"graph.h"
using namespace std;

//找到下一步要走的动作
int *find_move(Graph a, int ** adj, int ** tabu, int * sol, int num, int iter, int best_sol, int fun)
{

	int fun_change = 0;												//目标函数的变化量
	int flag1 = 0, flag2 = 0;
	int best_tabu_num, best_notabu_num;
	double random_num;
	int *best_notabu_sol = new int[4];
	int *best_tabu_sol = new int[4];

	for (int i = 0; i < a.vexnum; i++)					   //分别找到禁忌和非禁忌中最好的解
	{
		if (adj[i][sol[i]] > 0)
		{
			for (int j = 0; j < num; j++)
			{
				if (j != sol[i])
				{
					fun_change = adj[i][j] - adj[i][sol[i]];       //邻域动作增量评估
					if (iter < tabu[i][j])							//处于禁忌状态
					{
						if (flag1 == 0)
						{
							best_tabu_sol[0] = i;
							best_tabu_sol[1] = sol[i];
							best_tabu_sol[2] = j;
							best_tabu_sol[3] = fun_change;
							best_tabu_num = 1;
							flag1 = 1;
						}
						else
						{
							if (fun_change < best_tabu_sol[3])
							{
								best_tabu_sol[0] = i;
								best_tabu_sol[1] = sol[i];
								best_tabu_sol[2] = j;
								best_tabu_sol[3] = fun_change;
							}
							else
							{
								if (fun_change == best_tabu_sol[3])
								{
									best_tabu_num++;
									//srand((unsigned)time(NULL));
									random_num = rand() / double(RAND_MAX);
									if (random_num < ((double)1 / (double)best_tabu_num))
									{
										best_tabu_sol[0] = i;
										best_tabu_sol[1] = sol[i];
										best_tabu_sol[2] = j;
									}
								}
							}
						}
					}
					else                                         //处于非禁忌状态
					{
						if (flag2 == 0)
						{
							best_notabu_sol[0] = i;
							best_notabu_sol[1] = sol[i];
							best_notabu_sol[2] = j;
							best_notabu_sol[3] = fun_change;
							best_notabu_num = 1;
							flag2 = 1;
						}
						else
						{
							if (fun_change < best_notabu_sol[3])
							{
								best_notabu_sol[0] = i;
								best_notabu_sol[1] = sol[i];
								best_notabu_sol[2] = j;
								best_notabu_sol[3] = fun_change;
							}
							else
							{
								if (fun_change == best_notabu_sol[3])
								{
									best_notabu_num++;
									//srand((unsigned)time(NULL));
									random_num = rand() / double(RAND_MAX);
									if (random_num < ((double)1 / (double)best_notabu_num))
									{
										best_notabu_sol[0] = i;
										best_notabu_sol[1] = sol[i];
										best_notabu_sol[2] = j;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if (flag1 == 0)
	{
		delete[] best_tabu_sol;
		return best_notabu_sol;
	}
	else
	{
		if (flag2 == 1)
		{
			if ((best_tabu_sol[3] < best_notabu_sol[3]) && ((best_tabu_sol[3] + fun) < best_sol))
			{
				delete[] best_notabu_sol;
				return best_tabu_sol;
			}
			else
			{
				delete[] best_tabu_sol;
				return best_notabu_sol;
			}
		}
	}
}

//做相应的动作并更新仇人表禁忌表和目标函数值
int make_move(Graph a, int ** adj, int ** tabu, int * sol, int iter, int * move, int fun)
{
	int new_fun = 0;
	sol[move[0]] = move[2];             //更新结点的颜色
	new_fun = fun + move[3];				//更新目标函数值并返回 
	tabu[move[0]][move[1]] = iter + new_fun + rand() % 10;		//更新禁忌表
	for (int i = 0; i < a.vexnum; i++)						//更新仇人表
		if (a.arcs[move[0]][i] == 1)
		{
			adj[i][move[1]] --;
			adj[i][move[2]] ++;
		}
	return new_fun;
}
