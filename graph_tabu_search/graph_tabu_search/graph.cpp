#include<fstream>  //ifstream
#include<iostream>
#include<sstream>
#include<fstream>  //ifstream
#include<sstream>
#include<string>     //包含getline()
#include"graph.h"
using namespace std;

Graph read_test(string loc)
{
	ifstream infile;				//打开相应文件
	string s = "..\\instances\\";
	infile.open(s + loc);
	if (!infile) cout << "error" << endl;

	Graph graph_color;				//初始化图
	string line, str;
	stringstream sstr;       //string->int类型
	int integer, ed1, ed2, i, j;

	while (getline(infile, line))      //getline(inf,s)是逐行读取inf中的文件信息
	{
		if (line[0] == 'p') {			//读入节点数和边数
			istringstream stream(line);
			for (i = 0; stream >> str; i++) {
				if ((i == 2) || (i == 3)) {
					sstr << str.c_str();
					sstr >> integer;
					if (i == 2) graph_color.vexnum = integer;
					else graph_color.arcnum = integer;
					sstr.clear();
				}
			}
			graph_color.arcs = new int*[graph_color.vexnum];      //定于图并初始化
			for (i = 0; i < graph_color.vexnum; i++) {
				graph_color.arcs[i] = new int[graph_color.vexnum];
				for (j = 0; j < graph_color.vexnum; j++)
					graph_color.arcs[i][j] = 0;
			}
		}

		if (line[0] == 'e') {                //读入有哪些边
			istringstream stream(line);
			for (i = 0; stream >> str; i++) {
				if ((i == 1) || (i == 2)) {
					sstr << str.c_str();
					sstr >> integer;
					if (i == 1) ed1 = integer;
					else ed2 = integer;
					sstr.clear();
				}
			}
			graph_color.arcs[ed1 - 1][ed2 - 1] = 1;
			graph_color.arcs[ed2 - 1][ed1 - 1] = 1;
		}
	}
	infile.close();
	return graph_color;
}