#pragma once
#ifndef __GRAPH_H__
#define __GRAPH_H__
#include<string>
using namespace std;

struct Graph {                //����ͼ�Ľṹͼ
	int vexnum, arcnum;		//�������ͻ���
	int ** arcs;			//�ڽӾ���
};

Graph read_test(string loc);        //���ļ��ж���ͼ

#endif