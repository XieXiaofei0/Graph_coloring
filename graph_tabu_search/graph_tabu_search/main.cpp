#include<iostream>
#include<time.h>
#include<fstream>  //ifstream
#include"graph.h"
#include"intialize.h"
#include"move.h"
using namespace std;

int main() {

	Graph graph;
	int num_color, num = 0;								//��ɫ��num_color,num�������
	string filename;                                    //�ļ���

	cout << "Please input the name of file��";
	getline(cin, filename);
	cout << "Please input the number of colors��";
	cin >> num_color;

	graph = read_test(filename);                               //������Ӧ��ͼ

	ifstream infile("..\\log.csv");                           //�ж��ļ��Ƿ���ڣ�д��־�ļ�
	if (!infile.good())                                         //�ļ�������
	{
		infile.close();
		ofstream outFile;                                //д�ļ�
		outFile.open("..\\log.csv", ios::out);
		outFile << "Currenttime" << ',' << "Instance" << ',' << "Num_color" << ',' << "Iter" << "," << "fun" << ',' << "Spend_time" << endl;
		outFile.close();
	}

	while (num < 5) {

		int iter = 0;
		int *sol = intialize_sol(graph, num_color);							//���������ʼ��
		int fun = num_conflict(graph, sol);                      //����Ŀ�꺯��
		int **adjacent_table = intialize_adj_table(graph, num_color, sol);	//��ʼ�����˱�
		int **tabu_tenure = intialize_tabu_table(graph, num_color);		//��ʼ�����ɱ�

		int best = 10000;
		clock_t startTime, endTime;                                     //������ý��ʱ��
		startTime = clock();

		while (fun>0)
		{
			int *move = find_move(graph, adjacent_table, tabu_tenure, sol, num_color, iter, best, fun);  //�ҵ�����������õĽ�
			fun = make_move(graph, adjacent_table, tabu_tenure, sol, iter, move, fun); //����Ŀ�꺯����ֵ
			if (fun < best) best = fun;               //��¼��ʷ���Ž�
			delete[] move;
			//if (fun == 0)   //������ȷ���жϣ����˱�
			//{
			//	int flag = 1;
			//		for (int i = 0; i<graph.vexnum; i++)
			//			if (adjacent_table[i][sol[i]] > 0)
			//			{
			//				flag = 0;
			//				break;
			//			}
			//	if (flag == 0)cout << "error!" << endl;
			//}
			if (iter >= 20000000)break;
			iter++;
		}

		endTime = clock();
		cout << "Totle Time : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s";

		cout << "     ��������:" << iter;
		cout << "      ��ͻ�ߵ�����:" << fun << endl;
		string   time = getTime();

		ofstream outFile;                                //д�ļ�
		outFile.open("..\\log.csv", ios::app);
		outFile << time << ',' << filename << ',' << num_color << ',' << iter << "," << fun << ',' << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
		outFile.close();

		for (int i = 0; i < graph.vexnum; i++) {              //�ͷſռ�
			delete[] adjacent_table[i];
			delete[] tabu_tenure[i];
		}
		delete[] adjacent_table;
		delete[] tabu_tenure;
		delete[] sol;
		num++;
	}
	for (int i = 0; i < graph.vexnum; i++)delete[] graph.arcs[i];
	delete[] graph.arcs;
	return 0;
}
