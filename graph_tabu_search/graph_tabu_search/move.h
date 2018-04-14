#pragma once
#ifndef __MOVE_H__
#define __MOVE_H__
#include"graph.h"

int *find_move(Graph a, int ** adj, int ** tabu, int * sol, int num, int iter, int best_sol, int fun);   //找到最好的邻域动作

int make_move(Graph a, int ** adj, int ** tabu, int * sol, int iter, int * move, int fun);    //做邻域动作

#endif