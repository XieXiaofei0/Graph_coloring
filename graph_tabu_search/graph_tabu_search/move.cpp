#include"graph.h"
using namespace std;

//�ҵ���һ��Ҫ�ߵĶ���
int *find_move(Graph a, int ** adj, int ** tabu, int * sol, int num, int iter, int best_sol, int fun)
{

	int fun_change = 0;												//Ŀ�꺯���ı仯��
	int flag1 = 0, flag2 = 0;
	int best_tabu_num, best_notabu_num;
	double random_num;
	int *best_notabu_sol = new int[4];
	int *best_tabu_sol = new int[4];

	for (int i = 0; i < a.vexnum; i++)					   //�ֱ��ҵ����ɺͷǽ�������õĽ�
	{
		if (adj[i][sol[i]] > 0)
		{
			for (int j = 0; j < num; j++)
			{
				if (j != sol[i])
				{
					fun_change = adj[i][j] - adj[i][sol[i]];       //��������������
					if (iter < tabu[i][j])							//���ڽ���״̬
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
					else                                         //���ڷǽ���״̬
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

//����Ӧ�Ķ��������³��˱���ɱ��Ŀ�꺯��ֵ
int make_move(Graph a, int ** adj, int ** tabu, int * sol, int iter, int * move, int fun)
{
	int new_fun = 0;
	sol[move[0]] = move[2];             //���½�����ɫ
	new_fun = fun + move[3];				//����Ŀ�꺯��ֵ������ 
	tabu[move[0]][move[1]] = iter + new_fun + rand() % 10;		//���½��ɱ�
	for (int i = 0; i < a.vexnum; i++)						//���³��˱�
		if (a.arcs[move[0]][i] == 1)
		{
			adj[i][move[1]] --;
			adj[i][move[2]] ++;
		}
	return new_fun;
}
