
#include"Data.h"
#include"main.h"



//データロード補助関数
int Road(ifstream &ifs)
{
	int			c;
	int			i		= 0;

	char		Str[512];

	//コメント行と空白行を読み飛ばし
	while(1)
	{
		Str[i]	= ifs.get();

		switch(Str[i])
		{
		case EOF:
			return EOF;

		//コメント行および空白の読み飛ばし
		case '#':
			while((c = ifs.get()) != '\n')
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


//科目データ読み出し
int	RoadSubjects(char *FileName)
{
	int			i;

	ifstream	ifs;

	int			temp;
	int			Num_Elem;	//データ数

	ifs.open(FileName);

	if(ifs == NULL)
	{
		printf("Subject data file open error.\n");
		return -1;
	}

	//科目読み込み
	printf("%d\n", RD_SUBJECTS);

	//登録されたデータの数を取得
	temp	= Road(ifs);

	if(temp <= 0)
	{
		ifs.close();
		return -1;
	}
	Num_Elem	= temp;
	printf("%d\n", Num_Elem);

	for(i = 0; i < Num_Elem; i++)
	{
		//１コマの時間数
		temp	= Road(ifs);

		if(temp == EOF)
			break;

		if(temp == 0)
		{
			ifs.close();
			return -1;
		}
		printf("%d\t", temp);

		//一週間の時間数
		temp	= Road(ifs);

		if(temp <= 0)
		{
			ifs.close();
			return -1;
		}
		printf("%d\t", temp);

		//配置可能な曜日
		temp	= Road(ifs);
		printf("%d\t", temp);

		//教員グループID
		temp	= Road(ifs);

		if(temp <= 0)
		{
			ifs.close();
			return -1;
		}
		printf("%d\t", temp);

		//教室グループID。0の場合は各クラスのホームルーム
		temp	= Road(ifs);

		if(temp < 0)
		{
			ifs.close();
			return -1;
		}
		printf("%d\t", temp);

		//クラスグループID
		temp	= Road(ifs);

		if(temp <= 0)
		{
			ifs.close();
			return -1;
		}
		printf("%d\t", temp);

		//評価属性のグループID
		temp	= Road(ifs);

		if(temp < 0)
		{
			ifs.close();
			return -1;
		}
		printf("%d\n", temp);
	}

	ifs.close();
	return Num_Elem;
}



//教員グループ読み込み
int	RoadTeacherGroup(char *FileName)
{
	int	i;
	int	j;

	int	temp;
	int	Num_Elem;

	ifstream	ifs;

	ifs.open(FileName);

	if(ifs == NULL)
		return -1;

	printf("%d\n", RD_TEACHERS);

	temp	= Road(ifs);

	if(temp <= 0)
	{
		ifs.close();
		return -1;
	}

	Num_Elem	= temp;
	printf("%d\n", Num_Elem);

	for(i = 1; i < Num_Elem + 1; i++)
	{
		//１グループ読み込み
		for(j = 0; j < TEACHERS_A_GROUP; j++)
		{
			temp	= Road(ifs);
			if(temp < 0)
			{
				ifs.close();
				return -1;
			}
			printf("%d", temp);

			if(j + 1 < TEACHERS_A_GROUP)
				putchar('\t');
		}
		putchar('\n');
	}

	ifs.close();
	return 0;
}


//教室グループ読み込み
int	RoadRoomGroup(char *FileName)
{
	int	i;
	int	j;

	int	temp;
	int	Num_Elem;

	ifstream	ifs;

	ifs.open(FileName);

	if(ifs == NULL)
		return -1;

	printf("%d\n", RD_ROOMS);

	temp	= Road(ifs);

	if(temp <= 0)
	{
		ifs.close();
		return -1;
	}

	Num_Elem	= temp;
	printf("%d\n", Num_Elem);

	if(temp <= 0)
	{
		ifs.close();
		return -1;
	}

	Num_Elem	= temp;

	for(i = 1; i < Num_Elem + 1; i++)
	{
		//１グループ読み込み
		for(j = 0; j < ROOMS_A_GROUP; j++)
		{
			temp	= Road(ifs);
			if(temp < 0)
			{
				ifs.close();
				return -1;
			}
			printf("%d", temp);
			if(j + 1 < ROOMS_A_GROUP)
				putchar('\t');
		}
		putchar('\n');
	}

	ifs.close();
	return 0;
}


//クラスグループ読み込み
int	RoadClassGroup(char *FileName)
{
	int	i;
	int	j;

	int	temp;
	int	Num_Elem;

	ifstream	ifs;

	ifs.open(FileName);

	if(ifs == NULL)
		return -1;

	printf("%d\n", RD_CLASSES);

	temp	= Road(ifs);

	if(temp <= 0)
	{
		ifs.close();
		return -1;
	}
	printf("%d\n", temp);
	Num_Elem	= temp;

	for(i = 1; i < Num_Elem + 1; i++)
	{
		//１グループ読み込み
		for(j = 0; j < CLASSES_A_GROUP; j++)
		{
			temp	= Road(ifs);
			if(temp < 0)
			{
				ifs.close();
				return -1;
			}
			printf("%d", temp);
			if(j + 1 < CLASSES_A_GROUP)
				putchar('\t');
		}
		putchar('\n');
	}

	ifs.close();
	return 0;
}


//評価データグループ読み込み
int	RoadEvaluationTable(char *FileName)
{
	int	i;
	int	j;

	int	temp;
	int	Num_Elem;

	ifstream	ifs;

	ifs.open(FileName);

	if(ifs == NULL)
		return -1;

	printf("%d\n", RD_ATB_GRP);

	temp	= Road(ifs);

	if(temp <= 0)
	{
		ifs.close();
		return -1;
	}

	Num_Elem	= temp;
	printf("%d\n", Num_Elem);

	for(i = 1; i < Num_Elem + 1; i++)
	{
		//１グループ読み込み
		for(j = 0; j < ATTRIBUTES_A_GROUP; j++)
		{
			temp	= Road(ifs);
			if(temp < 0)
			{
				ifs.close();
				return -1;
			}
			printf("%d", temp);
			if(j + 1 < ATTRIBUTES_A_GROUP)
				putchar('\t');
		}
		putchar('\n');
	}

	return 0;
}


//評価データグループ読み込み
int	RoadEvaluationAtb(char *FileName)
{
	int	i;
	int	j;

	int	temp;
	int	Num_Elem;

	ifstream	ifs;

	ifs.open(FileName);

	if(ifs == NULL)
		return -1;

	printf("%d\n", RD_ATTRIBUTES);

	temp	= Road(ifs);

	if(temp <= 0)
	{
		ifs.close();
		return -1;
	}

	Num_Elem	= temp;
	printf("%d\n", Num_Elem);

	for(i = 1; i < Num_Elem + 1; i++)
	{
		//１グループ読み込み
		for(j = 0; j < (LECTURES_A_WEEK / 2); j++)
		{
			temp	= Road(ifs);

			printf("%d", temp);
			if(j < ((LECTURES_A_WEEK / 2) - 1))
				putchar('\t');
		}
		putchar('\n');
	}

	return 0;
}


//配置済み時間割の読み込み
int	RoadSubTable(char *FileName)
{
	int			i;
	int			j;

	ifstream	ifs;

	ifs.open(FileName);

	if(ifs == NULL)
		return -1;

	printf("%d\n", RD_SUB_TABLE);

	for(i = 0; i < NUM_CLASS; i++)
	{
		for(j = 0; j < LECTURES_A_WEEK; j++)
		{
			printf("%d", Road(ifs));

			if(j != (LECTURES_A_WEEK - 1))
				putchar('\t');
		}
		putchar('\n');
	}
	ifs.close();

	return 0;
}
