#pragma once
#ifndef __INTIALIZE_H__
#define __INTIALIZE_H__
#include"Graph.h"
//using namespace std;

int ** intialize_sol(Graph a, int number,int population);    //��ʼ�������

int ** intialize_adj_table(Graph b, int num, int * sol);      //��ʼ�����˱�

int num_conflict(Graph b, int * sol);      //����Ŀ�꺯��ֵ

int **intialize_tabu_table(Graph c, int num);      //��ʼ�����ɱ�

string getTime();           //��ȡ��ǰʱ��

#endif