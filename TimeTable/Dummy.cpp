
#include"Data.h"

#if DUMMY

//デバッグ用に用意する定数
const int	SUBJECTS_A_CLASS	= 16;	//１クラスの科目数
const int	NUM_TEACHERS		= 30;	//教官の総数
const int	NUM_ROOMS			= 20;


//デバッグ用データ登録関数
int RoadSubjects(SUBJECT *Subjects)
{
	int		i	= 1;
	int		j;
	int		k;

	for(j = 0; j < NUM_CLASS; j++)
	{
		for(k = 0; k < SUBJECTS_A_CLASS; k++)
		{
			Subjects[i].ID				= i;
			Subjects[i].LecturesAWeek	= 2;
		//Subjects[i].Units			= 2;
			Subjects[i].Teachers		= i;
			Subjects[i].Rooms			= i;
			Subjects[i].Classes			= j + 1;

			if((k % SUBJECTS_A_CLASS) >= 14)
				Subjects[i].Units	= 3;

			else if((k % SUBJECTS_A_CLASS) ==13)
				Subjects[i].Units	= 5;

			else if((k % SUBJECTS_A_CLASS) >= 10)
				Subjects[i].Units	= 1;

			else
				Subjects[i].Units	= 2;

			i++;
		}
	}

	return --i;
}

//教官グループデータ登録
int	RoadTeacherGroup(short (*Teachers)[TEACHERS_A_GROUP])
{
	int		m;
	int		n;

	int		i;
/*
	for(m = 0; m < NUM_TEACHER_GROUP; m++)
	{
		//1グループに所属する教官の人数をランダムで決定
		n	= (rand() % 5) + 1;

		for(i = 0; i < n; i++)
			Teachers[m][i]	= rand() % NUM_TEACHERS;
	}

	return m;
*/

	for(m = 0; m < NUM_TEACHER_GROUP; m++)
	{
		for(n = 1; n < TEACHERS_A_GROUP; n++)
		{
			Teachers[m][n]	= 0;
		}
	}

	for(i = 0; i < NUM_TEACHER_GROUP; i++)
		Teachers[i][0]	= rand() % 500;
	
	return 1;
}

//教室グループ登録
int	RoadRoomGroup(short (*Rooms)[ROOMS_A_GROUP])
{
	int		a;

	int		m;

	for(m = 0; m < NUM_ROOM_GROUP; m++)
	{
		for(a = 1; a < ROOMS_A_GROUP; a++)
		{
			Rooms[m][a]	= 0;
		}

		Rooms[m][0]	= rand() % 1000;
	}

	return m;
}


//クラスグループ
int RoadClassGroup(short (*Classes)[CLASSES_A_GROUP])
{
	int	i;

	for(i = 1; i < (NUM_CLASS + 1); i++)
		Classes[i][0]	= i;

	return i;
}


//評価属性グループの読み込み
int	RoadEvaluationTable(short (*Attributes)[ATTRIBUTES_A_GROUP])
{
	int	i;

	for(i = 0; i < NUM_SUBJECT; i++)
		;

	return -1;
}



#endif
