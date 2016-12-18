
#include"Data.h"

const int	RD_SUBJECTS		= 1;
const int	RD_TEACHERS		= 2;
const int	RD_ROOMS		= 3;
const int	RD_CLASSES		= 4;
const int	RD_ATB_GRP		= 5;
const int	RD_ATTRIBUTES	= 6;
const int	RD_SUB_TABLE	= 7;

//データを読み込んで登録
int TIME_TABLE::RoadDatabase()
{
	char	Flag	= 0;
	char	Str[512];

	while(Flag != 0x3f)
	{
		cin.getline(Str, 512);

		switch(atoi(Str))
		{
		case RD_SUBJECTS:
			//科目データ登録
			if((Num_Subject = RoadSubjects(SubjectTable)) <= 0)
			{
				printf("Subject data registration error.\n");
				return -1;
			}
			Flag	|= 1;
			break;

		case RD_TEACHERS:
			//教官グループデータ登録
			if((Num_Teacher = RoadTeacherGroup(Teachers)) <= 0)
			{
				printf("Teacher data registration error.\n");
				return -1;
			}
			Flag	|= 2;
			break;

		case RD_ROOMS:
			//教室グループデータ登録
			if((Num_Room = RoadRoomGroup(Rooms)) <= 0)
			{
				printf("Room data ragistration error.\n");
				return -1;
			}
			Flag	|= 4;
			break;

		case RD_CLASSES:
			//クラスグループデータ登録
			if((Num_Class = RoadClassGroup(Classes)) <= 0)
			{
				printf("Class data registration error.\n");
				return -1;
			}
			Flag	|= 8;
			break;

		case RD_ATB_GRP:
			//評価属性グループデータ登録
			if((Num_AtbGrp	= RoadEvaluationTable(Attributes)) <= 0)
			{
				printf("Evaluation Table registration error.\n");
				return -1;
			}
			Flag	|= 16;
			break;

		case RD_ATTRIBUTES:
			//評価属性データ登録
			if((Num_Attributes	= RoadEvaluationAtb(AllocTable)) <= 0)
			{
				printf("Evaluation data registration error.\n");
				return -1;
			}
			Flag	|= 32;
			break;

		case RD_SUB_TABLE:
			//配置済みの時間割データ
			if(RoadSubTable(SubTable) < 0)
			{
				printf("Time table roading error\n");
				return -1;
			}
			break;

		default:
			printf("Invalid command.\n");
		}
	}

#if CHECK_DATABASE
	int		i;
	int		j;

	printf("Monitoring Subject Database\n");
/*
	//IDの照合
	for(i = 1; i < (Num_Subject + 1); i++)
		printf("%d, %d\n", i, SubjectTable[i].ID);
*/
#if MONITOR
	getch();
#endif

	//科目データ
	for(i = 1; i < (Num_Subject + 1); i++)
	{
		//一こまの時間数
		printf("%02d, ", SubjectTable[i].Units);

		//一週間のコマ数
		printf("%02d, ", SubjectTable[i].LecturesAWeek);

		//配置可能テーブル
		printf("%d, ", SubjectTable[i].AllocationTable[0]);

		//教員グループ
		printf("%02d, ", SubjectTable[i].Teachers);

		//教室グループ
		printf("%02d, ", SubjectTable[i].Rooms);

		//クラスグループ
		printf("%02d, ", SubjectTable[i].Classes);

		//評価属性
		printf("%02d\n", SubjectTable[i].EvaluationAtb);
	}
#if MONITOR
	getch();
#endif
	//教員グループテーブル
	printf("Monitoring Teachers Group Table\n");
	for(i = 1; i < (Num_Teacher + 1); i++)
	{
		for(j = 0; j < TEACHERS_A_GROUP; j++)
			printf("%02d, ", Teachers[i][j]);

		putchar('\n');
	}
#if MONITOR
	getch();
#endif

	//教室グループテーブル
	printf("Monitoring Room Group Table\n");
	for(i = 1; i < (Num_Room + 1); i++)
	{
		for(j = 0; j < ROOMS_A_GROUP; j++)
			printf("%02d, ", Rooms[i][j]);

		putchar('\n');
	}
#if MONITOR
	getch();
#endif

	//クラスグループテーブル
	printf("Monitoring Class Group Table\n");
	for(i = 1; i < (Num_Class + 1); i++)
	{
		for(j = 0; j < CLASSES_A_GROUP; j++)
			printf("%02d, ", Classes[i][j]);

		putchar('\n');
	}
#if MONITOR
	getch();
#endif

	//評価属性グループテーブル
	printf("Monitoring Evaluatino Group Table\n");
	for(i = 1; i < (Num_AtbGrp + 1); i++)
	{
		for(j = 0; j < ATTRIBUTES_A_GROUP; j++)
			printf("%02d, ", Attributes[i][j]);

		putchar('\n');
	}
#if MONITOR
	getch();
#endif

	//評価属性データ
	printf("Monitoring Evaluation Attributes\n");
	for(i = 1; i < (Num_Attributes + 1); i++)
	{
		for(j = 0; j < (LECTURES_A_WEEK / 2); j++)
			printf("%02d, ", AllocTable[i].AllocationTable[j]);

		putchar('\n');
	}
#if MONITOR
	getch();
#endif

	//配置済み時間割
	printf("Monitoring sub table\n");
	for(i = 0; i < NUM_CLASS; i++)
	{
		for(j = 0; j < LECTURES_A_WEEK; j++)
		{
			printf("%03d", SubTable[i][j]);

			if(j != (LECTURES_A_WEEK - 1))
				putchar('\t');
		}
		putchar('\n');
	}
#if MONITOR
	getch();

#else
	return -1;
#endif


#endif

#if CHK
	int	i;
	int	temp;
	int	Prev	= 0;

	for(i = 1; i < (Num_Subject + 1); i++)
	{
		temp	= SubjectTable[i].Classes;

		if(temp != Prev)
			putchar('\n');

		printf("%d, ", i);

		Prev	= temp;
	}

	return -1;
#endif

	return 0;
}



//データロード補助関数
int Road()
{
	int			c;
	int			i		= 0;

	char		Str[512];

	//コメント行と空白行を読み飛ばし
	while(1)
	{
		Str[i]	= cin.get();

		switch(Str[i])
		{
		case '\0':
			return -1;

		//コメント行および空白の読み飛ばし
		case '#':
			while((c = cin.get()) != '\n')
				;
			break;

		case ' ':
			break;

		case '\t':
		case ',':
		case '\n':
			Str[i]	= '\0';
			break;
		}

		if(Str[i] == '\0')
			break;

		if(Str[i] != '#')
			i++;
	}
	return atoi(Str);
}


//科目データ登録関数
int	RoadSubjects(SUBJECT *Subjects)
{
	int			i;

	int			temp;

	int			Num_Elem;	//データ数

	//登録されたデータの数を取得
	temp	= Road();

	if(temp <= 0)
		return -1;

	Num_Elem	= temp;

	for(i = 0; i < Num_Elem; i++)
	{
		//ID。自動で割り振り
		Subjects[i + 1].ID	= i + 1;

		//１コマの時間数
		temp	= Road();

		if(temp <= 0)
			return -1;

		Subjects[i + 1].Units	= temp;

		//一週間の時間数
		temp	= Road();

		if(temp <= 0)
			return -1;

		Subjects[i + 1].LecturesAWeek	= temp;

		//配置可能テーブル
		temp	= Road();

		if(temp < 0)
			return -1;

//		Subjects[i + 1].AllocationTable	= temp;

		//教員グループID
		temp	= Road();

		if(temp <= 0)
			return -1;

		Subjects[i + 1].Teachers	= temp;

		//教室グループID。0の場合は各クラスのホームルーム
		temp	= Road();

		if(temp < 0)
			return -1;

		Subjects[i + 1].Rooms	= temp;

		//クラスグループID
		temp	= Road();

		if(temp <= 0)
			return -1;

		Subjects[i + 1].Classes	= temp;

		//評価属性のグループID
		temp	= Road();

		if(temp < 0)
			return -1;

		Subjects[i + 1].EvaluationAtb	= temp;
	}

	return Num_Elem;
}


//教員グループ読み込み
int	RoadTeacherGroup(short (*Teachers)[TEACHERS_A_GROUP])
{
	int	i;
	int	j;

	int	temp;
	int	Num_Elem;

	temp	= Road();

	if(temp <= 0)
		return -1;

	Num_Elem	= temp;

	for(i = 1; i < (Num_Elem + 1); i++)
	{
		//１グループ読み込み
		for(j = 0; j < TEACHERS_A_GROUP; j++)
		{
			temp	= Road();
			if(temp < 0)
				return -1;

			Teachers[i][j]	= temp;
		}
	}

	return Num_Elem;
}

//教室グループ読み込み
int	RoadRoomGroup(short (*Rooms)[ROOMS_A_GROUP])
{
	int	i;
	int	j;

	int	temp;
	int	Num_Elem;

	temp	= Road();

	if(temp <= 0)
		return -1;

	Num_Elem	= temp;

	for(i = 1; i < Num_Elem + 1; i++)
	{
		//１グループ読み込み
		for(j = 0; j < ROOMS_A_GROUP; j++)
		{
			temp	= Road();
			if(temp < 0)
				return -1;

			Rooms[i][j]	= temp;
		}
	}

	return Num_Elem;
}

//クラスグループ読み込み
int	RoadClassGroup(short (*Classes)[CLASSES_A_GROUP])
{
	int	i;
	int	j;

	int	temp;
	int	Num_Elem;

	temp	= Road();

	if(temp <= 0)
		return -1;

	Num_Elem	= temp;

	for(i = 1; i < Num_Elem + 1; i++)
	{
		//１グループ読み込み
		for(j = 0; j < CLASSES_A_GROUP; j++)
		{
			temp	= Road();
			if(temp < 0)
				return -1;

			Classes[i][j]	= temp;
		}
	}

	return Num_Elem;
}

//評価データグループ読み込み
int	RoadEvaluationTable(short (*Attributes)[ATTRIBUTES_A_GROUP])
{
	int	i;
	int	j;

	int	temp;
	int	Num_Elem;

	temp	= Road();
	Num_Elem	= temp;

	if(temp <= 0)
		return -1;

	for(i = 1; i < Num_Elem + 1; i++)
	{
		//１グループ読み込み
		for(j = 0; j < ATTRIBUTES_A_GROUP; j++)
		{
			temp	= Road();
			if(temp < 0)
				return -1;

			Attributes[i][j]	= temp;
		}
	}

	return Num_Elem;
}


//評価属性データ読み込み
int	RoadEvaluationAtb(EVALUATION_ATTRIBUTES *AllocTable)
{
	int	i;
	int	j;

	int	temp;

	int	Num_Elem;

	temp	= Road();
	Num_Elem	= temp;

	if(temp <= 0)
		return -1;

	for(i = 1; i < (Num_Elem + 1); i++)
	{
		for(j = 0; j < (LECTURES_A_WEEK / 2); j++)
		{
			temp	= Road();

			AllocTable[i].AllocationTable[j]	= temp;
		}
	}

	return Num_Elem;
}

//配置済み時間割読み込み
int	RoadSubTable(short (*TimeTable)[LECTURES_A_WEEK])
{
	int	i;
	int	j;

	//時間割を読み出し
	for(i = 0; i < NUM_CLASS; i++)
	{
		for(j = 0; j < LECTURES_A_WEEK; j++)
			TimeTable[i][j]	= Road();
	}

	return 0;
}
