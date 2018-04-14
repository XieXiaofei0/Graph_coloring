#pragma once
#ifndef __GRAPH_H__
#define __GRAPH_H__
#include<string>
#include<time.h>
using namespace std;

struct Graph {                //定义图的结构图
	int vexnum, arcnum;		//顶点数和弧数
	int ** arcs;			//邻接矩阵
};

Graph read_test(string loc);        //从文件中读入图函数

#endif