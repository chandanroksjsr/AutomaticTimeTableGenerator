
#include"TimeTable.h"
#include<iostream>
#include<fstream>

using namespace std;

//科目データのやりとりのためのインターフェイス


int RoadSubjects(SUBJECT *Subjects);								//科目データを読み込む

//グループテーブル読み込み
int	RoadTeacherGroup(short (*Teachers)[TEACHERS_A_GROUP]);			//教官グループテーブル
int	RoadRoomGroup(short (*Rooms)[ROOMS_A_GROUP]);					//教室グループテーブル
int	RoadClassGroup(short (*Classes)[CLASSES_A_GROUP]);				//クラスグループテーブル
int	RoadEvaluationTable(short (*Attributes)[ATTRIBUTES_A_GROUP]);	//評価のためのデータテーブル
int	RoadEvaluationAtb(EVALUATION_ATTRIBUTES *AllocTable);			//評価属性データ

int	RoadSubTable(short (*TimeTable)[LECTURES_A_WEEK]);				//配置済み時間割データ
