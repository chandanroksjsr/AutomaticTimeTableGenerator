
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
using namespace std;


//データロード補助関数
int Road(ifstream &ifs);

//テキストの重複削除と要素数カウント
int Road(ifstream &ifs, char *Str, int limit);