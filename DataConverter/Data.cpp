
#include"Data.h"



//データロード補助関数
int Road(ifstream &ifs, char *Str, int limit)
{
	int			c;
	int			i		= 0;

	//コメント行と空白行を読み飛ばし
	while(1)
	{
		Str[i]	= ifs.get();

		switch(Str[i])
		{
		case EOF:
			return -1;

		//コメント行および空白の読み飛ばし
		case '#':
			while((c = ifs.get()) != '\n')
				;
			break;

		case ' ':
			Str[i]	= ifs.get();
			break;

		case '\t':
		case ',':
		case '\n':
			Str[i]	= '\0';
			break;
		}

		if(Str[i] == '\0')
			break;

		if((Str[i] != '#') && (Str[i] != ' '))
			i++;

		if(i >= (limit - 2))
		{
			//読み飛ばし処理
			while(1)
			{
				c	= ifs.get();

				if(c == ',')
					break;

				else if(c == '\t')
					break;

				else if(c == '\n')
					break;
			}


			Str[i]	= '\0';
			break;
		}
	}
	return i;
}

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
			return -1;

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

		if((Str[i] != '#') && (Str[i] != ' '))
			i++;
	}
	return atoi(Str);
}


//標準入力からデータを取得
int Road(int *Flag)
{
	int			c;
	int			i		= 0;
	char		Str[512];

	*Flag	= 0;

	//コメント行と空白行を読み飛ばし
	while(1)
	{
		Str[i]	= cin.get();

		switch(Str[i])
		{
		case 'q':
			return -3;

		//コメント行および空白の読み飛ばし
		case '#':
			while((c = cin.get()) != '\n')
				;
			break;

		case ' ':
			break;

		case '\t':
		case ',':
			Str[i]	= '\0';
			break;

		case '\n':
			Str[i]	= '\0';
			*Flag	= 1;
			break;
		}

		if(Str[i] == '\0')
			break;

		if((Str[i] != '#') && (Str[i] != ' '))
			i++;
	}
	return atoi(Str);
}

//重複チェック用にキーを持つ文字列
struct STR
{
	char			Str[32];
	unsigned int	Key;
};


//グループの末尾に0を追加するための補助関数
int	RoadGroup(ifstream &ifs, int ItemsAGroup, short *Group)
{
	int		i;
	int		j	= 0;
	int		c;
	int		Flag	= 0;

	char	Str[128];

	for(i = 0; i < ItemsAGroup; i++)
		Group[i]	= 0;

	i = 0;

	//コメント行と空白行を読み飛ばし
	while(1)
	{
		Str[i]	= ifs.get();

		switch(Str[i])
		{
		case EOF:
			return -1;

		//コメント行および空白の読み飛ばし
		case '#':
			while((c = ifs.get()) != '\n')
				;
			break;

		case ' ':
			break;

		case '\t':
		case ',':
			Str[i]	= '\0';
			Group[j++]	= atoi(Str);
			Flag	= 1;
			i		= 0;
			break;

		case '\n':
			Str[i]	= '\0';
			Group[j++]	= atoi(Str);
			break;
		}

		if(Str[i] == '\0')
			break;

		if(Flag)
			Flag	= 0;

		else if(Str[i] != '#')
			i++;
	}

	return 0;
}

//要素数カウント
int	Count(char *FileName)
{
	int			i	= 1;
	int			c;

	int			Flag	= 0;

	ifstream	ifs;

	ifs.open(FileName);
	if(ifs == NULL)
		return -1;

	printf("001:");

	//コメント行と空白行を読み飛ばし
	while(1)
	{
		c	= ifs.get();

		switch(c)
		{
		case EOF:
			Flag	= 1;
			break;

		//コメント行および空白の読み飛ばし
		case '#':
			while((c = ifs.get()) != '\n')
				;
			break;

		case ' ':
			break;

		case '\t':
		case ',':
			putchar('\t');
			break;

		case '\n':
			putchar('\n');
			i++;
			printf("%03d:", i);
			break;

		default:
			putchar(c);
		}

		if(Flag)
			break;
	}
	ifs.close();
	return 0;
}

//科目IDから科目名を取得
int	GetSubjectName(char *FileName, char (*Subjects)[32])
{
	ifstream	ifs;
	int			temp;
	int			Num_Elem;
	int			i;

	ifs.open(FileName);

	if(ifs == NULL)
		return -1;

	//要素数
	temp	= Road(ifs);

	if(temp <= 0)
	{
		ifs.close();
		return -1;
	}
	Num_Elem	= temp;

	for(i = 0; i < Num_Elem; i++)
	{
		temp	= Road(ifs, Subjects[i], 32);

//		for(int j = strlen(Subjects[i]); j < 15; j++)
//			Subjects[i][j]	= ' ';

//		Subjects[i][15]	= '\0';
/*
		if(temp < 0)
		{
			ifs.close();
			return -1;
		}
*/
	}

	ifs.close();
	return Num_Elem;
}



//グループの末尾に0を追加して出力
int	Grouping(char *FileName, int ItemsAGroup)
{
	short		*Group;
	int			i;
	ifstream	ifs;

	Group	= new short[ItemsAGroup];

	ifs.open(FileName);

	if(ifs == 0)
		return -1;

	//書き出し
	while(RoadGroup(ifs, ItemsAGroup, Group) != -1)
	{
		for(i = 0; i < ItemsAGroup; i++)
		{
			printf("%d", Group[i]);
			if(i != (ItemsAGroup - 1))
				putchar('\t');
		}

		putchar('\n');
	}

	ifs.close();
	delete[]	Group;

	return 0;
}


//テキストの重複削除と要素数カウント
int	Remark(char	*FileName, int mode = 0)
{
	ifstream		ifs;
	int				temp;
	char			Str[32];
	int				Key;
	int				a;

	int				i	= 0;
	int				j;
	int				k;

	int				ans;

	//重複チェック用バッファ
	STR			Strings[256];

	//ファイルオープン
	ifs.open(FileName);

	if(ifs == NULL)
		return -1;

	while(1)
	{
		temp	= Road(ifs, Str, 128);
		if(temp	== -1)
			break;

		Key = 0;
		a	= 1;
		//Keyの値を計算
		for(j = 0; j < 4; j++)
		{
			for(k = 0; k < j; k++)
				a *= 256;

			Key	+= (unsigned)Str[j] * a;
		}

		Strings[i].Key	= Key;
		strcpy(Strings[i++].Str, Str);

		//重複のチェック
		for(j = 0; j < (i - 1); j++)
		{
			if(Strings[j].Key == Key)
			{
				ans	= 0;
				for(k = 0; Str[k] != '\0'; k++)
				{
					if(Str[k] != Strings[j].Str[k])
						ans++;
				}
				if(Strings[j].Str[k] != '\0')
					ans++;

				if(ans == 0)
					i--;
			}
		}
	}

	switch(mode)
	{
	//重複削除のみ
	case 0:
		printf("%d\n", i);
		for(j = 0; j < i; j++)
			printf("%s\n", Strings[j].Str);
		break;

	//ナンバリング
	case 1:
		printf("%d\n", i);
		for(j = 0; j < i; j++)
			printf("%03d:%s\n", j + 1, Strings[j].Str);
		break;
	}

	ifs.close();

	return 0;
}

//時間割をIDから文字情報に変換
int	GetSubjectInfo(char *FileName)
{
	char	Subjects[512][32];
	int		Units[512];
	int		Num_Elem;
	int		temp;
	int		a;

	int		i	= 0;

	ifstream	ifs;

	ifs.open("Subjects.txt");
	temp	= Road(ifs);
	Num_Elem	= temp;

	if(Num_Elem <= 0)
		return -1;

	for(int j = 0; j < Num_Elem; j++)
	{
		//授業の時間数を取り出し
		temp		= Road(ifs);
		Units[j]	= temp;

		temp	= Road(ifs);	//一週間のコマ数
		temp	= Road(ifs);	//配置可能テーブル
		temp	= Road(ifs);	//教員グループID
		temp	= Road(ifs);	//教室グループID
		temp	= Road(ifs);	//クラスグループID
		temp	= Road(ifs);	//評価属性テーブル
	}
	ifs.close();

	Num_Elem	= GetSubjectName(FileName, Subjects);
	if(Num_Elem <= 0)
		return -1;

	while(1)
	{
		temp	= Road(&a);

		if(temp == -3)
			break;

		if((temp > Num_Elem) || (temp < -2))
		{
			printf("%d", temp);
			printf("Invalid ID\n");
		}

		else// if(temp != 0)
			i++;

		if(temp == -2)
			printf("\t\t");

		if(temp > 0)
		{
			printf("%s\t", Subjects[temp - 1]);
			for(j = 1; j < Units[temp - 1]; j++)
				printf("\t");
		}

		else if(temp == -1)
			printf("休\t");

		if(a)
			putchar('\n');
	}

	return 0;
}

int	main(int argc, char *argv[])
{
	int	i	= 0;

	if(argc > 2)
	{
		if(atoi(argv[2]) == 2)
			Grouping(argv[1], atoi(argv[3]));

		else if(atoi(argv[2]) == 3)
			printf("%d\n", Count(argv[1]));

		else if(atoi(argv[2]) == 4)
			GetSubjectInfo(argv[1]);

		else if(atoi(argv[2]) == 5)
			Count(argv[1]);
		
		else
			Remark(argv[1], atoi(argv[2]));
	}

	else if(argc > 1)
		Remark(argv[1]);

	else
		return 0;

	return 0;
}



