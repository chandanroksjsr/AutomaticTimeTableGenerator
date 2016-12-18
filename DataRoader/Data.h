
#include<iostream>
#include<fstream>

using namespace std;

//データロード補助関数
int Road(ifstream &ifs, char *Str, int limit);

int RoadSubjects(char *FileName);			//科目データを読み込む

//グループテーブル読み込み
int	RoadTeacherGroup(char *FileName);		//教官グループテーブル
int	RoadRoomGroup(char *FileName);			//教室グループテーブル
int	RoadClassGroup(char *FileName);			//クラスグループテーブル
int	RoadEvaluationTable(char *FileName);	//評価のためのデータテーブル
int	RoadEvaluationAtb(char *FileName);		//評価データ読み込み

//配置済み時間割読み込み
int	RoadSubTable(char *FileName);			//配置済み時間割読み込み