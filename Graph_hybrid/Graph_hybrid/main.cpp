#include<iostream>
#include<time.h>
#include<fstream>
#include"Graph.h"
#include"Intialize.h"
#include"Move.h"
#include"Crossover.h"
using namespace std;

int main()
{

	Graph graph;
	int num_color, popu = 5, iter = 20000;								//��ɫ��num_color,population=5,LS�ĵ�����������
	string filename;                                                 //�ļ���
	int best_solu[2] = {-1,1000000};                           //��¼��ý��λ�ú�Ŀ�꺯��ֵ

	cout << "Please input the name of file��";
	getline(cin, filename);
	cout << "Please input the number of colors��";
	cin >> num_color;

	graph = read_test(filename);                               //����ͼ
	
	ifstream infile("..\\log.csv");                           //�ж���־�ļ��Ƿ����,д��־�ļ�
	if (!infile.good())                                         //�ļ�������
	{
		infile.close();
		ofstream outFile;                                //д�ļ�
		outFile.open("..\\log.csv", ios::out);
		outFile << "Currenttime" << ',' << "Instance" << ',' << "Num_color" << ',' <<"Populaiton"<<","<< "LS_Iter" << "," <<"Cross_step"<<","<< "fun" << ',' << "Spend_time" << endl;
		outFile.close();
	}

	int **sol = intialize_sol(graph, num_color, popu);				//����һ��population

	double times=0;                                                   //��¼����ʱ��
	
	for (int i = 0; i < popu; i++)									//��population�е�ÿ������н�������
	{
		int fun = num_conflict(graph, sol[i]);                   
		int **adjacent_table = intialize_adj_table(graph, num_color, sol[i]);	
		int **tabu_tenure = intialize_tabu_table(graph, num_color);		

		int j = 0;                                                  //��¼�ֲ���������                                                  
		int best = 10000;    

		clock_t startTime, endTime;                                     
		startTime = clock();

		while (j < iter)
		{
			int *move = find_move(graph, adjacent_table, tabu_tenure, sol[i], num_color, j, best, fun);  
			fun = make_move(graph, adjacent_table, tabu_tenure, sol[i],j, move, fun);
			if (fun < best) best = fun;             
			delete[] move;
			j++;
		}

		endTime = clock();
		times+=(double)(endTime - startTime) / CLOCKS_PER_SEC;

		
		for (int m = 0; m < graph.vexnum; m++) {            
			delete[] adjacent_table[m];
			delete[] tabu_tenure[m];
		}
		delete[] adjacent_table;
		delete[] tabu_tenure;
	}

	int cross_step=0;                                           //��¼���沽��

	while(best_solu[1]>0)
	{
		
		int one, two;                          //��¼��������������λ��
		one = two = -1;

		srand((unsigned)time(NULL));
		while (one == two)                      //��population���������������н������(�������Ŷ���ƥ���㷨�Ҳ�����Ľ�)
		{
			one = rand() % popu;
			two = rand() % popu;
		}

		int one_f = num_conflict(graph, sol[one]);          //�����������е�Ŀ�꺯��ֵ
		int two_f = num_conflict(graph, sol[two]);

		if (one_f > two_f)                               //best_solu��¼�������нϲ�Ľ�
		{
			best_solu[0] = one;
			best_solu[1] = one_f;
		}
		else
		{
			best_solu[0] = two;
			best_solu[1] = two_f;
		}

		int * crossover_sol = cross_sol(graph, sol[one], sol[two], num_color);
	
		int fun = num_conflict(graph, crossover_sol);                                 //�Խ�������ó��Ľ���оֲ�����
		int **adjacent_table = intialize_adj_table(graph, num_color, crossover_sol);
		int **tabu_tenure = intialize_tabu_table(graph,num_color);

		int j = 0;
		int best = 10000;

		clock_t startTime, endTime;
		startTime = clock();

		while (j < iter)
		{
			int *move = find_move(graph, adjacent_table, tabu_tenure, crossover_sol, num_color, j, best, fun);
			fun = make_move(graph, adjacent_table, tabu_tenure, crossover_sol, j, move, fun);
			if (fun < best) best = fun;
			delete[] move;
			if (fun == 0)break;
			j++;
		}

		endTime = clock();
		times+=(double)(endTime - startTime) / CLOCKS_PER_SEC;

		if (fun < best_solu[1])                             //Pool updating
		{
			int * p = sol[best_solu[0]];
			sol[best_solu[0]] = crossover_sol;
			crossover_sol = NULL;
			best_solu[1] = fun;
			delete[] p;
		}

		for (int i = 0; i < graph.vexnum; i++) {
			delete[] adjacent_table[i];
			delete[] tabu_tenure[i];
		}
		delete[] adjacent_table;
		delete[] tabu_tenure;
		delete[] crossover_sol;

		if (best_solu[1] == 0)break;
		if (cross_step > 10000)break;

		cross_step++;

	}

	string	current_time = getTime();
	
	ofstream outFile;                                //д�ļ�
	outFile.open("..\\log.csv", ios::app);
	outFile << current_time << ',' << filename << ',' << num_color << ',' << popu << ',' << iter << "," << cross_step << "," << best_solu[1] << ',' << times << "s" << endl;
	outFile.close();
		
	cout <<"���沽���� "<< cross_step << endl;
	cout << "����Ŀ�꺯��ֵ��ǣ� " << best_solu[0] << endl;
	cout << "����Ŀ�꺯��ֵ�� " << best_solu[1] << endl;

	for (int i = 0; i < popu; i++)delete[] sol[i];              //�ͷſռ�
	delete[] sol;
	for (int i = 0; i < graph.vexnum; i++)delete[] graph.arcs[i];
	delete[] graph.arcs;

	return 0;

}