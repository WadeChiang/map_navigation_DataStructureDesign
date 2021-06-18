#pragma once
#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "log.h"
#define LOCANUM 40
#define MAXC 30000
#define SEARCH_DIS 150


using namespace std;

struct edge {
    unsigned to_loca;
	double crowding;
	bool cycle;
	double distance;
};

struct Loca {
	string name;
	struct edge path[6];
	string info;
	int path_num;
} ;

int index(int i, int j);
void initgraph(Loca *loc);
void init_name_info(Loca *loc,int which);
void init_distance(Loca *loc,int which);
vector<int> Dj(Loca *loc,int x, int y);
vector<int> Dj_crowd(Loca *loc,int x, int y);
vector<int> Dj_muti(Loca *loc,int* mid, int min_num, int x, int y);
vector<int> Dj_cyc(Loca *loc,int x, int y, int speed);
vector<int> search(Loca *loc,int x);
