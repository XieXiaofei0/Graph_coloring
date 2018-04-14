#include<iostream>
#include<time.h>
#include<fstream>  //ifstream
#include"graph.h"
#include"intialize.h"
#include"move.h"
using namespace std;

int main() {

	Graph graph;
	int num_color, num = 0;								//着色数num_color,num计算次数
	string filename;                                    //文件名

	cout << "Please input the name of file：";
	getline(cin, filename);
	cout << "Please input the number of colors：";
	cin >> num_color;

	graph = read_test(filename);                               //读入相应的图

	ifstream infile("..\\log.csv");                           //判断文件是否存在，写日志文件
	if (!infile.good())                                         //文件不存在
	{
		infile.close();
		ofstream outFile;                                //写文件
		outFile.open("..\\log.csv", ios::out);
		outFile << "Currenttime" << ',' << "Instance" << ',' << "Num_color" << ',' << "Iter" << "," << "fun" << ',' << "Spend_time" << endl;
		outFile.close();
	}

	while (num < 5) {

		int iter = 0;
		int *sol = intialize_sol(graph, num_color);							//随机产生初始解
		int fun = num_conflict(graph, sol);                      //计算目标函数
		int **adjacent_table = intialize_adj_table(graph, num_color, sol);	//初始化仇人表
		int **tabu_tenure = intialize_tabu_table(graph, num_color);		//初始化禁忌表

		int best = 10000;
		clock_t startTime, endTime;                                     //计算求得解的时间
		startTime = clock();

		while (fun>0)
		{
			int *move = find_move(graph, adjacent_table, tabu_tenure, sol, num_color, iter, best, fun);  //找到邻域动作中最好的解
			fun = make_move(graph, adjacent_table, tabu_tenure, sol, iter, move, fun); //更新目标函数的值
			if (fun < best) best = fun;               //记录历史最优解
			delete[] move;
			//if (fun == 0)   //进行正确性判断，仇人表
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

		cout << "     迭代次数:" << iter;
		cout << "      冲突边的数量:" << fun << endl;
		string   time = getTime();

		ofstream outFile;                                //写文件
		outFile.open("..\\log.csv", ios::app);
		outFile << time << ',' << filename << ',' << num_color << ',' << iter << "," << fun << ',' << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
		outFile.close();

		for (int i = 0; i < graph.vexnum; i++) {              //释放空间
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
