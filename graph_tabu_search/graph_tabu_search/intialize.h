#pragma once
#ifndef __INTIALIZE_H__
#define __INTIALIZE_H__
#include"graph.h"

int * intialize_sol(Graph a, int number);    //初始化随机解

int ** intialize_adj_table(Graph b, int num, int * sol);      //初始化仇人表

int num_conflict(Graph b, int * sol);      //计算目标函数值

int **intialize_tabu_table(Graph c, int num);      //初始化禁忌表

string getTime();           //获取当前时间

#endif