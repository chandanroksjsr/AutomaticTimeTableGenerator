

#include"TimeTable.h"

const int	HEAP_SIZE	= 40;


/*
//初期集団生成
int	TIME_TABLE::InitGenePool()
{
	int		i;
	int		j;
	int		k;

	short	temp[GENE_LENGTH];	//ダミー配列

	for(i = 0; i < GENE_LENGTH; i++)
	{
		temp[i]	= 
*/


//ランダムソート
void TIME_TABLE::RandSort(short* a, int min, int max)
{
	//枢軸
	int	v;

	if(min >= max)
		return ;

	//枢軸から右と左に分ける。
	v = RandPertition(a, min, max);

	RandSort(a, min, v);
	RandSort(a, v + 1, max);
}


//クイックソートの分割関数
int	TIME_TABLE::RandPertition(short* a, int min, int max)
{
	//分割のためのポインタ
	int	i	= min - 1;
	int	j	= max;
	int	mid	= (min + max) / 2;
	
	short	pivot;				//枢軸
	short	temp;

	max--;

	pivot	= a[mid];

	//分割
	while(1)
	{
		//ポインタを右に動かす
		while((++i < max) && (rand() % 3))
			;

		//ポインタを左に動かす
		while((min < --j) && (rand() % 3))
			;

		//ループを抜ける条件
		if(i >= j)
			break;

		//要素の交換
		temp	= a[i];
		a[i]	= a[j];
		a[j]	= temp;
	}

	//枢軸を交換
	temp		= a[i];
	a[i]		= a[mid];
	a[mid]		= temp;

	return mid;
}


//コンストラクタ
TIME_TABLE::TIME_TABLE(int Generation) : GENETIC_POOL(Generation)
{
	int	i;
	int	j;

	Num_Subject	= 0;

	//優良個体を保持する配列のスコアを初期化
	for(i = 0; i < BEST; i++)
	{
		INTEGER	conv;

		conv.Value	= -50000;

		Superior[i][0]	= conv.S_Val.MSB;
		Superior[i][1]	= conv.S_Val.LSB;
	}

	//時間割を0に初期化
	for(i = 0; i < NUM_CLASS; i++)
	{
		for(j = 0; j < LECTURES_A_WEEK; j++)
		{
			TimeTable[i][j]	= 0;
			SubTable[i][j]	= 0;
		}
	}

	//配置済み科目テーブル初期化
	for(i = 0; i < NUM_SUBJECT; i++)
	{
		SubjectTable[i].ID		= 0;
		SubjectTable[i].Units	= 0;
	}

	//グループテーブルを初期化
	//教員グループ
	for(i = 0; i < NUM_TEACHER_GROUP; i++)
	{
		for(j = 0; j < TEACHERS_A_GROUP; j++)
			Teachers[i][j]	= 0;
	}

	//教員グループ
	for(i = 0; i < NUM_TEACHER_GROUP; i++)
	{
		for(j = 0; j < TEACHERS_A_GROUP; j++)
			Teachers[i][j]	= 0;
	}

	//教室グループ
	for(i = 0; i < NUM_ROOM_GROUP; i++)
	{
		for(j = 0; j < ROOMS_A_GROUP; j++)
			Rooms[i][j]	= 0;
	}

	//クラスグループ
	for(i = 0; i < (NUM_CLASS + 1); i++)
	{
		for(j = 0; j < CLASSES_A_GROUP; j++)
			Classes[i][j]	= 0;
	}

	//評価属性グループ
	for(i = 0; i < NUM_SUBJECT; i++)
	{
		for(j = 0; j < ATTRIBUTES_A_GROUP; j++)
			Attributes[i][j]	= 0;
	}

#if DEBUG
	printf("Constructor OK!\n");
#endif
}




//初期集団生成
int	TIME_TABLE::InitGenePool()
{
	int		i;
	int		j;
	int		k;
	int		l;
	int		m;


	int		Units;
	int		Num;
	int		ClassID;

	int		GroupID;				//読み込んだクラスグループのＩDを保持

	int		n[NUM_CLASS];			//クラスごとにデータを読み込むためのポインタ

	int		ChkSubj[NUM_SUBJECT];	//配置済みの科目データを二重登録しない工夫

	//読み込んだ科目データを一旦保持
	short	Subjects[NUM_CLASS][LECTURES_A_WEEK];

#if DEBUG
	short	Table[LECTURES_A_WEEK];	//フィンガープリント作成用配列

	printf("Roading Database\n");
#endif

	//科目データおよびデータテーブルを読み込み
	if(RoadDatabase() == -1)
	{
		printf("Data entry error.\n");
		return -1;
	}

#if DEBUG
	printf("Initializing GenePool...\n");
#endif


	if(Num_Subject == 0)
	{
		printf("Data registration error!\n");
		return -1;
	}

	//ポインタを初期化
	for(i = 0; i < NUM_CLASS; i++)
		n[i]	= 0;

	//配置済みチェック用配列を初期化
	for(i = 0; i < NUM_SUBJECT; i++)
		ChkSubj[i]	= 0;

	//配置済み時間割を考慮
	for(i = 0;i < NUM_CLASS; i++)
	{
		//登録されてる科目数を算出
		int	count	= 0;
		for(j = 0; j < LECTURES_A_WEEK; j++)
		{
			if(SubTable[i][j] != 0)
				count++;

			if(SubTable[i][j] > 0)
			{
				ChkSubj[SubTable[i][j]]	+= SubjectTable[SubTable[i][j]].Units;

				count	+= (SubjectTable[SubTable[i][j]].Units - 1);
			}
		}

		//配置済みの箇所を-2で埋める
		for(int a = 0; a < count; a++)
			Subjects[i][n[i]++]	= -2;
	}

	//同時開講のクラスの配置済みを-2で埋める
	for(i = 0; i < NUM_SUBJECT; i++)
	{
		if(ChkSubj[i] > 0)
		{
			for(int a = 1; (Classes[SubjectTable[ChkSubj[i]].Classes][a] != 0) && (a < CLASSES_A_GROUP); a++)
			{
				for(int b = 0; b < ChkSubj[i]; b++)
				{
					int	temp;

					temp	= Classes[SubjectTable[ChkSubj[i]].Classes][a] - 1;
					Subjects[temp][n[temp]++]	= -2;
				}
			}
		}
	}

	//読み込んだ科目をクラスごとに割り振り
	for(i = 1; i < Num_Subject + 1; i++)
	{
		//クラスグループの読み込み
		GroupID	= SubjectTable[i].Classes;

		//授業時間およびクラスIDを取得
		Units	= SubjectTable[i].Units;
		Num		= SubjectTable[i].LecturesAWeek / Units;

		ClassID	= Classes[GroupID][0] - 1;

		Num	-= ChkSubj[i];

		//クラスごとに割り振って科目を配置
		for(int a = 0; a < Num; a++)
		{
			Subjects[ClassID][n[ClassID]++]	= i;

			//科目の合間を埋める
			for(j = 0; j < (Units - 1); j++)
				Subjects[ClassID][n[ClassID]++]	= -2;

			//同時開講を考慮
			if(Classes[GroupID][1] != 0)
			{
				int	temp;
				for(int b = 1; (Classes[GroupID][b] != 0) && (b < CLASSES_A_GROUP); b++)
				{
					temp	= Classes[GroupID][b] - 1;
					Subjects[temp][n[temp]++]	= -2;

					for(j = 0; j < (Units - 1); j++)
						Subjects[temp][n[temp]++]	= -2;
				}
			}
		}
	}

	//科目がない箇所を休憩で埋める
	for(i = 0; i < NUM_CLASS; i++)
	{
		for(; n[i] < LECTURES_A_WEEK; n[i]++)
			Subjects[i][n[i]]	= -1;
	}

	//作った時間割配列を遺伝子へそのままコピー
	for(i = 0; i < POPULATION; i++)
	{
		for(l = 0; l < SCORE_ARRAY; l++)
			Pool1[i][l]	= 0;

		for(j = 0; j < NUM_CLASS; j++)
		{
			for(k = 0; k < LECTURES_A_WEEK; k++)
				Pool1[i][l++]	= Subjects[j][k];
		}
	}

#if DEBUG_IG
	//登録された科目を表示
	for(int e = 0; e < NUM_CLASS; e++)
	{
		for(int g = 0; g < LECTURES_A_WEEK; g++)
			printf("%d, ", Subjects[e][g]);
		putchar('\n');
	}
	return -1;
#endif

#if DEBUG
	//遺伝子検査用フィンガープリント作成
	for(i = 0; i < NUM_CLASS; i++)
	{
		for(j = 0; j < LECTURES_A_WEEK; j++)
			Table[j]	= Subjects[i][j];

		qsort(Table, LECTURES_A_WEEK, sizeof(short), cmp);

		for(j = 0; j < LECTURES_A_WEEK; j++)
			FingPrt[i][j]	= Table[j];
	}

	for(i = 0 ; i < NUM_CLASS; i++)
	{
		for(j = 0; j < LECTURES_A_WEEK; j++)
			printf("%02d, ", Subjects[i][j]);

		putchar('\n');
	}

//	for(i = 0; i < POPULATION; i++)
//	{
//		qsort(Pool1[i], GENE_LENGTH, sizeof(short), cmp);
		for(j = SCORE_ARRAY; j < GENE_LENGTH; j++)
		{
			if(!((j - SCORE_ARRAY) % LECTURES_A_WEEK))
				putchar('\n');

			printf("%02d,", Pool1[0][j]);
		}

		putchar('\n');
		putchar('\n');
//	}
#endif


#if DEBUG
	printf("Initialize OK!\nRandom Sort started.\n");
#endif

	//遺伝子をランダムソート
	for(i = 0; i < POPULATION; i++)
	{
		for(j = 0; j < NUM_CLASS; j++)
		{
			m	= LECTURES_A_WEEK * j + SCORE_ARRAY;
			RandSort(Pool1[i], m, m + LECTURES_A_WEEK);
		}
	}

#if DEBUG
	for(i = 0; i < POPULATION; i++)
	{
		//遺伝子に欠陥がないかを検査
		if(CheckGene(Pool1[i]) == -1)
		{
			printf("Initializeing!\n");
			return -1;
		}
	}
#endif
/*
#if DEBUG
	for(i = 0; i < POPULATION; i++)
	{
		for(j = 0; j < GENE_LENGTH; j++)
		{
			if(lpParent[i][j] == 0)
			{
				if(j >= SCORE_ARRAY)
				{
					printf("Unexpected Value.\n");
					exit(1);
				}
			}

			if((j - SCORE_ARRAY) >= 0)
			{
				if(((j - SCORE_ARRAY) % LECTURES_A_WEEK) == 0)
					putchar('\n');
			}
			printf("%02d,", lpParent[i][j]);
		}

		putchar('\n');
		putchar('\n');
	}
	return -1;
#endif
*/
	//遺伝子に評価値を書き込み
	for(i = 0; i < POPULATION; i++)
		Evaluation(Pool1[i]);

	//return -1;

#if DEBUG
	printf("GenePool was initialized.\n");
#endif


	return 0;
}


//選択関数
OPERATION	TIME_TABLE::Selection(int *a, int *b)
{
	int		l;
	int		m;
	int		n;

	l	= rand() % 100;

	//上位30％の遺伝子が選ばれる確立（仮で50％）
	if(l < 50)
		m	= rand() % ((POPULATION * 30) / 100);

	//上位50%までに含まれる遺伝子が選ばれる確立(仮で20%)
	else if(l < (50 + 20))
		m	= ((POPULATION * 30) / 100) + (rand() % (POPULATION * 20) / 100);

	//上位80%以内に含まれている遺伝子（仮で5%）
	else if(l < (50 + 20 + 5))
		m	= ((POPULATION * 50) / 100) + (rand() % (POPULATION * 30) / 100);

	//下位20%に含まれている遺伝子が選ばれる確率（仮で25%）
	else
		m	= ((POPULATION * 80) / 100) + (rand() % (POPULATION * 20) / 100);

	*a	= m;

	l	= rand() % 100;

	//上位30％の遺伝子が選ばれる確立（仮で50％）
	if(l < 50)
		m	= rand() % ((POPULATION * 30) / 100);

	//上位50%までに含まれる遺伝子が選ばれる確立(仮で20%)
	else if(l < (50 + 20))
		m	= ((POPULATION * 30) / 100) + (rand() % (POPULATION * 20) / 100);

	//上位80%以内に含まれている遺伝子（仮で5%）
	else if(l < (50 + 20 + 5))
		m	= ((POPULATION * 50) / 100) + (rand() % (POPULATION * 30) / 100);

	//下位20%に含まれている遺伝子が選ばれる確率（仮で25%）
	else
		m	= ((POPULATION * 80) / 100) + (rand() % (POPULATION * 20) / 100);

	*b	= m;

	n	= rand() % 100;

	if(n < MUTATION_RATE)
		return MUTATE;

	else if(n < (MUTATION_RATE + CROSSOVER_RATE))
		return CROSSOVER;

	else
		return COPY;
}



//突然変異
int	TIME_TABLE::Mutation(short *PA, short *PB, short *CA, short *CB)
{
	//範囲を決めて範囲内をランダムソート

	//範囲を決定する変数
	int	Init;
	int	Dist;

	int	Offset;

	int	i;

	//遺伝子をコピー
	for(i = 0; i < GENE_LENGTH; i++)
	{
		CA[i]	= PA[i];
		CB[i]	= PB[i];
	}

	//最低5つの遺伝子は入れ替える
	Init	= rand() % (LECTURES_A_WEEK - 5);
	Dist	= rand() % (LECTURES_A_WEEK - Init - 5) + 5;

	for(i = 0; i < NUM_CLASS; i++)
	{
		Offset	= SCORE_ARRAY + i * LECTURES_A_WEEK;

		RandSort(CA, Offset + Init, Offset + Init + Dist);
	}


	Init	= rand() % (LECTURES_A_WEEK - 5);
	Dist	= rand() % (LECTURES_A_WEEK - Init - 5) + 5;

	for(i = 0; i < NUM_CLASS; i++)
	{
		Offset	= SCORE_ARRAY + i * LECTURES_A_WEEK;

		RandSort(CB, Offset + Init, Offset + Init + Dist);
	}

	return 0;
}


int	TIME_TABLE::Crossover(short *PA, short *PB, short *CA, short *CB)
{
	//ループ変数
	int		i;
	int		j;
	int		k;

	//一時変数
	int		a;
	int		b;
	int		c;
	int		d;

	//染色体を指すポインタ
	int		Pt;			//オフセット

	int		Distance;	//交叉点間の距離
	int		CP_A;		//交叉点
	int		CP_B;		//

	int		End;		//遺伝子（1クラス分）の終端

	//一時的に遺伝子の内容を保持
	short	temp_A[GENE_LENGTH];
	short	temp_B[GENE_LENGTH];

	//オフセット
	Pt	= SCORE_ARRAY;

#if DEBUG
	//遺伝子に欠陥がないかを検査
	if(CheckGene(PA) == -1)
	{
		printf("交叉前の親遺伝子に欠陥\n");
		return -1;
	}

	//遺伝子に欠陥がないかを検査
	if(CheckGene(PB) == -1)
	{
		printf("交叉前の親遺伝子に欠陥\n");
		return -1;
	}
#endif

	//クラスごとに遺伝子を交叉
	for(i = 0; i < NUM_CLASS; i++)
	{
		End	= Pt + LECTURES_A_WEEK;

		//交叉点の長さを決定
		Distance	= 4 + rand() % (LECTURES_A_WEEK - 4);

		//交叉点を決定
		CP_A		= Pt + rand() % (LECTURES_A_WEEK - Distance);
		CP_B		= Pt + rand() % (LECTURES_A_WEEK - Distance);

#if DEBUG_CO
		printf("オフセットの位置：%d\n", Pt);

		putchar('\n');

		printf("１クラスの終端：%d\n", End);

		printf("交叉点\n");
		printf("CP_A = %d\n", CP_A);
		printf("CP_B = %d\n", CP_B);
		printf("Distance = %d\n", Distance);

		putchar('\n');

		printf("交叉点の末尾\n");
		printf("遺伝子A：%d\n", CP_A + Distance);
		printf("遺伝子B：%d\n", CP_B + Distance);

		putchar('\n');
#endif
#if DEBUG
		if(((CP_A + Distance) > End) || (CP_A < SCORE_ARRAY))
		{
			printf("交叉点の設定ミス\n");
			return -1;
		}

		if(((CP_B + Distance) > End) || (CP_B < SCORE_ARRAY))
		{
			printf("交叉点の設定ミス\n");
			return -1;
		}
#endif

		//染色体をコピー
		for(j = 0; j < GENE_LENGTH; j++)
		{
			CA[j]		= PA[j];
			CB[j]		= PB[j];

			temp_A[j]	= PA[j];
			temp_B[j]	= PB[j];
		}

#if DEBUG_CO
		for(int g = 0; g < SCORE_ARRAY; g++)
			printf("%02d, ", CA[g]);

		putchar('\n');

		for(int g = SCORE_ARRAY; g < (LECTURES_A_WEEK + SCORE_ARRAY); g++)
			printf("%02d, ", CA[g + i * LECTURES_A_WEEK]);
		putchar('\n');
		getch();
#endif

		//交叉点の終端をセット
		a	= CP_A + Distance;
		b	= CP_B + Distance;

		//交叉点間の遺伝子をすべて0にセット
		for(j = CP_A; j < a; j++)
			CA[j]	= 0;

		for(j = CP_B; j < b; j++)
			CB[j]	= 0;

#if DEBUG_CO
		printf("交叉点間を0クリア\n");
		for(int g = 0; g < SCORE_ARRAY; g++)
			printf("%02d, ", CA[g]);

		putchar('\n');

		for(int g = SCORE_ARRAY; g < (LECTURES_A_WEEK + SCORE_ARRAY); g++)
			printf("%02d, ", CA[g + i * LECTURES_A_WEEK]);
		putchar('\n');
		getch();
#endif


		//等しい染色体の位置を入れ替えて移す作業
		for(j = 0; j < Distance; j++)
		{
			for(k = 0; k < Distance; k++)
			{
				if(((c = PA[CP_A + j]) > 0) && ((d = PB[CP_B + k]) > 0) && (c == d) && (temp_A[CP_A + j] != 0) && (temp_B[CP_B + k] != 0))
				{
					CA[CP_A + k]	= c;
					CB[CP_B + j]	= d;

					//入れ替えた場所をマーク
					temp_A[CP_A + j]	= 0;
					temp_B[CP_B + k]	= 0;
				}
			}
		}

#if DEBUG_CO
		printf("等しい遺伝子の入れ替え\n");
		for(int g = 0; g < SCORE_ARRAY; g++)
			printf("%02d, ", CA[g]);

		putchar('\n');

		for(int g = SCORE_ARRAY; g < (LECTURES_A_WEEK + SCORE_ARRAY); g++)
			printf("%02d, ", CA[g + i * LECTURES_A_WEEK]);
		putchar('\n');
		getch();
#endif
/*
#if DEBUG
		for(int a = 0; a < GENE_LENGTH; a++)
			printf("%d, ", CA[a]);

		putchar('\n');
		putchar('\n');

/*		for(int a = 0; a < GENE_LENGTH; a++)
			printf("%d, ", CB[a]);

		putchar('\n');
		putchar('\n');
		getch();
#endif
*/

		//それ以外の染色体を順番どおりコピー
		k = CP_A;
		for(j = 0; j < Distance; j++)
		{
			if(CA[CP_A + j] == 0)
			{
				while(temp_A[k] == 0)
					k++;

				CA[CP_A + j]	= temp_A[k++];
			}
		}

		k = CP_B;
		for(j = 0; j < Distance; j++)
		{
			if(CB[CP_B + j] == 0)
			{
				while(temp_B[k] == 0)
					k++;

				CB[CP_B + j]	= temp_B[k++];
			}
		}

#if DEBUG_CO
		printf("コピー作業\n");
		for(int g = 0; g < SCORE_ARRAY; g++)
			printf("%02d, ", CA[g]);

		putchar('\n');

		for(int g = SCORE_ARRAY; g < (LECTURES_A_WEEK + SCORE_ARRAY); g++)
			printf("%02d, ", CA[g + i * LECTURES_A_WEEK]);
		putchar('\n');
		getch();
#endif
/*
#if DEBUG
		printf("Parent\n");
		for(int a = 0; a < GENE_LENGTH; a++)
			printf("%d, ", PA[a]);

		putchar('\n');

		printf("Child\n");
		for(int a = 0; a < GENE_LENGTH; a++)
			printf("%d, ", CA[a]);

		putchar('\n');
		putchar('\n');

		getch();
#endif
		*/

		//オフセットを更新
		Pt	+= LECTURES_A_WEEK;
	}
#if DEBUG
	//遺伝子に欠陥がないかを検査
	if(CheckGene(CA) == -1)
	{
		printf("Crossover\n");
		return -1;
	}

	//遺伝子に欠陥がないかを検査
	if(CheckGene(CB) == -1)
	{
		printf("Crossover\n");
		return -1;
	}
#endif

	return 0;
}


//科目配置の待ち行列に入れるデータ
struct SUBJ{
	short	ID;		//科目ID、データを保持
	short	Units;	//授業時間
};

//ヒープに要素を挿入、削除するためのサブルーチン
void	downheap(struct SUBJ *a, int n)
{
	int	i;
	int	j;

	short	Key;
	short	Val;

	//移動する要素の値をコピー
	Val	= a[1].ID;
	Key	= a[1].Units;

	//根から始めて節iが子を持っている限り繰り返す
	i = 1;
	while(i <= (n / 2))
	{
		//節iの子のうちの大きいほうを節jとする
		j	= i * 2;
		if((j + 1 <= n) && (a[j].Units < a[j + 1].Units))
			j++;

		if(Key >= a[j].Units)
			break;

		//節iと節jの値を交換し、節jに着目
		a[i].ID		= a[j].ID;
		a[i].Units	= a[j].Units;
		i = j;
	}

	//要素を正しい位置に挿入
	a[i].ID		= Val;
	a[i].Units	= Key;
}


void	upheap(struct SUBJ *a, int x)
{
	short	Val;
	short	Key;

	Val	= a[x].ID;
	Key	= a[x].Units;


	//要素が根まで来ていなくて、かつ親が子より小さい間繰り返す
	while((x > 1) && (a[x / 2].Units > Key))
	{
		//親の値を子に移す
		a[x].ID		= a[x / 2].ID;
		a[x].Units	= a[x / 2].Units;

		x /= 2;
	}

	a[x].ID		= Val;
	a[x].Units	= Key;
}


//要素の取り出し
int	DeleteMin(short *ID, short *Units, struct SUBJ *a, int *n)
{
	//ヒープが空ならリターン
	if(*n < 1)
		return 1;

	*ID		= a[1].ID;
	*Units	= a[1].Units;

	a[1].ID		= a[*n].ID;
	a[1].Units	= a[(*n)--].Units;

	downheap(a, *n);
//printf("Dequeue, %d\n\n", *ID);
	return 0;
}

//要素の挿入
int	Insert(short ID, int Units, struct SUBJ *a, int *n)
{
	//ヒープがいっぱいになっていないかを確認
	if(*n >= HEAP_SIZE)
		return 1;

	a[++(*n)].ID	= ID;
	a[*n].Units		= Units;

	upheap(a, *n);
//printf("Enqueue, %d\n\n", ID);
	return 0;
}

//時間割配置関数
int	TIME_TABLE::ArrangeTable(const short *Gene)
{
	//ループ変数
	int	w;				//週ごと
	int	d;				//日ごと
	int	td;				//一日ごとの時間
	int	t;				//時間

	int	Offset;			//遺伝子の位置をポイント

	int	Prev	= 0;	//一個前の時間を保持

	int	i		= SCORE_ARRAY;	//遺伝子をポインティング
	int	j;				//

	int		Blank	= 0;	//授業の空白を一時的に保持
	int		Blank_1	= 0;	//
	int		EndFlag	= 0;	//無限ループ回避用フラグ
	int		Flag	= 0;	//休憩配置のフラグ
	int		Flag_1	= 0;

	short	temp;		//一時的に科目IDを保持

	short		SubArray[HEAP_SIZE];	//配置を保留した科目を保持
	struct SUBJ	Heap[HEAP_SIZE + 1];	//ヒープを構成

	int		n	= 0;			//ヒープの最後尾を保持
	int		m	= 0;			//予備の配列のポインタ

	short	Chrom[GENE_LENGTH];	//遺伝子をコピーして保持


#if DEBUG_AT
	printf("Gene\n");

	for(i = 0; i < NUM_CLASS; i++)
	{
		for(j = 0; j < LECTURES_A_WEEK; j++)
		{
//			if(Gene[j + (LECTURES_A_WEEK * i) + SCORE_ARRAY] < 0)
//				printf("  , ");

//			else
				printf("%02d, ", Gene[j + (LECTURES_A_WEEK * i) + SCORE_ARRAY]);
		}

		putchar('\n');
	}

	putchar('\n');
	putchar('\n');
#if MONITOR
	getch();
#endif

	int		debug	= 0;
#endif


	//時間割を初期化
	for(i = 0; i < NUM_CLASS; i++)
	{
		for(j = 0; j < LECTURES_A_WEEK; j++)
			TimeTable[i][j]	= SubTable[i][j];
	}
	i	= SCORE_ARRAY;

	//遺伝子をコピーして保持
	for(int a = 0; a < GENE_LENGTH; a++)
		Chrom[a]	= Gene[a];

#if DEBUG
	//遺伝子に欠陥がないかを検査
	if(CheckGene(Chrom) == -1)
	{
		printf("読み込まれた遺伝子に欠陥があります\n");
		qsort(Chrom, GENE_LENGTH, sizeof(short), cmp);
		for(j = SCORE_ARRAY; j < GENE_LENGTH; j++)
		{
			if(!((j - SCORE_ARRAY) % LECTURES_A_WEEK))
				putchar('\n');

			printf("%02d,", Chrom[j]);
		}
		putchar('\n');
		return DEFECTIVE_OF_GENE;
	}
#endif


	//クラスごと（週ごと）の配置
	for(w = 0; w < NUM_CLASS; w++)
	{
		//１クラスの配置が終わった時点で時間のポインタを初期化
		t		= 0;
		Flag_1	= 0;

#if DEBUG
	if(Blank != 0)
	{
		printf("休憩を配置しきれていません。\n%d\n\n", Blank);
		return -4;
	}

	if((m > 0) | (n > 0))
	{
		printf("Queueを使い切れていません。\n");
		return -4;
	}
#endif

		//日ごとの配置
		for(d = 0; d < SCHOOLDAY; d++)
		{
			//オフセットの計算
			Offset	= SCORE_ARRAY + LECTURES_A_WEEK * w + LECTURES_A_DAY * d;
			td		= 0;
			Flag	= 0;

			//時間割の読み込みと配置
			while(td < LECTURES_A_DAY)
			{
#if DEBUG_AT
	printf("クラス%d, %d日目, %d時間目の配置\n", w + 1, d + 1, td + 1);
#endif

				//配置が次に進むか空白の数に変化があれば
				if((t != Prev) || (Blank_1 != Blank))
				{
					//データが退避されている場合はヒープを構築
					if(m > 0)
					{
//printf("ヒープを構築しました\n");
//printf("ヒープに登録されたデータの個数：%d\n", m);
//getch();

						//ヒープにデータを登録
						for(m--; m >= 0; m--)
							Insert(SubjectTable[SubArray[m]].ID, SubjectTable[SubArray[m]].Units, Heap, &n);

						m		= 0;
					}
					EndFlag	= 0;	//配置が次に進めばフラグを削除
				}

				//時間データ更新
				Prev	= t;

				//空白の変化データ更新
				Blank_1	= Blank;

				//すでに配置済みでないかをチェック
				if(TimeTable[w][t] != 0)
				{
					while((TimeTable[w][t] != 0) && (td < LECTURES_A_DAY))
					{
						if(TimeTable[w][t] == -1)
						{
							t++;
							td++;
						}

						else
						{
							td	+= SubjectTable[TimeTable[w][t]].Units;
							t	+= SubjectTable[TimeTable[w][t]].Units;
						}
					}

					if(td > 8)
					{
						//printf("tdの値\nt%d, td%d\n", t, td);
						//printf("配置する科目：%d\n時間数：%d\n\n", temp, SubjectTable[temp].Units);
						//printf("遺伝子番号：%d\n読み込まれた遺伝子：%d\nBlank：%d\nQueue：%d\nHeap ：%d\n", i, temp, Blank, m, n);
						
						return -4;
					}
				}

				//配置
				else
				{
					int	g	= 0;

					//配置済みをチェック
					for(int e = 1; (td + e) < LECTURES_A_DAY; e++)
					{
						if((TimeTable[w][t + e] != 0) && (g == 0))
								g	= (LECTURES_A_DAY - (td + e));
					}

					//休憩時間の配置
					if((Blank >= (LECTURES_A_DAY - td)) && (g == 0))
					{
						//休憩時間を埋める
						for(; LECTURES_A_DAY > td; td++)
						{
//printf("Blank：%d, LECTURES_A_DAY - td - 1：%d, td：%d\n\n", Blank, LECTURES_A_DAY - td - 1, td);
							TimeTable[w][t]	= -1;
							Blank--;
							t++;
						}
						temp	= -3;
					}
//printf("\nBlankC:%d\n\n", Blank);

					//Blankが空でなく７限目以降なら休憩を優先して配置
					else if((Blank == 1) && (td >= 6) && (g == 0) && (Flag_1 == 0))
					{
						//遺伝子を探索して休憩を配置
						a = i;
						while(1)
						{
							//終端まで探索が終了したらリターン
							if(a == (LECTURES_A_WEEK * (w + 1) + SCORE_ARRAY))
							{
								Flag_1	= 1;
								temp	= -3;
								break;
							}

							else if(Chrom[a] == -1)
							{
								TimeTable[w][t++]	= -1;
								TimeTable[w][t++]	= -1;

								td	+= 2;

								//要素の入れ替え
								Chrom[a]	= -2;
								Blank--;
								temp	= -3;
								break;
							}
							a++;
						}
					}

					//ヒープを優先して処理
					else if((n > 0) || (i == (LECTURES_A_WEEK * (w + 1) + SCORE_ARRAY)))
					{
//printf("ヒープが利用されました\n");
//printf("ヒープに登録されたデータ数%d\n", n);
						short	a;	//引数のダミー

						//遺伝子を１クラス分読みきっていたらヒープからデータを取り出し
						if(n == 0)
						{
							//退避されているデータがなく、休憩時間を使い切っていたら配置不能と判断
							if(m == 0)
							{
								//休憩を配置
								if((Blank > 0) && (g == 0))
								{
									while(((Blank > 0) && (LECTURES_A_DAY > td)))
									{
										TimeTable[w][t]	= -1;
										Blank--;
										t++;
										td++;
									}
									temp	= -3;
//printf("w：%d, t：%d, Blank：%d\n", w, t, Blank, td);
								}

								else
									return ALLOCATION_FAILURE;
							}

							//ヒープを再構築して配置
							else if(EndFlag == 0)
							{
								//ヒープにデータを登録
								for(m--; m >= 0; m--)
									Insert(SubjectTable[SubArray[m]].ID, SubjectTable[SubArray[m]].Units, Heap, &n);

								EndFlag	= 1;	//無限ループ回避フラグ
								m		= 0;

								//ヒープからデータを読み込み
								DeleteMin(&temp, &a, Heap, &n);
							}

							else
								return INFINIT_ROOP;

						}

						else
						{
							//ヒープからデータを読み込み
							DeleteMin(&temp, &a, Heap, &n);
						}
#if DEBUG_AT
	printf("ヒープから取り出された遺伝子：%d\n", temp);
#endif
					}	

					else
					{
//printf("遺伝子から読み込み\n");

						//授業データを遺伝子から読み込み
						while(1)
						{
#if DEBUG_AT
	printf("遺伝子番号：%d\n", i);
#endif
							if(i == (LECTURES_A_WEEK * (w + 1) + SCORE_ARRAY))
							{
								temp	= -3;
								break;
							}

							//-2を読み飛ばし
							else if((temp = Chrom[i]) == -2)
							{	
								if(i < (LECTURES_A_WEEK * (w + 1) + SCORE_ARRAY))
									i++;

								else
								{
									temp	= -3;
									break;
								}
							}

							else
								break;
						}

						if(i < (LECTURES_A_WEEK * (w + 1) + SCORE_ARRAY))
							i++;

						if((temp == 0) || (temp < -3))
						{
#if DEBUG
	printf("NULL value!\n");
	printf("遺伝子番号%d\n", i);
#endif
							return DEFECTIVE_OF_GENE;
						}
					}


#if DEBUG_AT
	printf("遺伝子番号：%d\n読み込まれた遺伝子：%d\nBlank：%d\nQueue：%d\nHeap ：%d\n", i, temp, Blank, m, n);
#endif

					if(temp == -3)
						;
			
					//休憩時間の処理
					else if(temp == -1)
					{
						Blank++;

						if(Blank >= (LECTURES_A_DAY - td))
						{
							if(!g)
							{
								//休憩時間を埋める
								for(; LECTURES_A_DAY > td; td++)
								{
									TimeTable[w][t]	= -1;
									Blank--;
									t++;
								}
							}
						}

						//７限目以降ならその場で配置
						else if((td >= 6) && (Flag_1 == 0))
						{
							if(g == 0)
							{
								int	a;

								//遺伝子を探索して休憩を配置
								a = i;
								while(1)
								{
									//終端まで探索が終了したら何もしない
									if(a == (LECTURES_A_WEEK * (w + 1) + SCORE_ARRAY))
									{
										Flag_1	= 1;
										break;
									}

									else if(Chrom[a] == -1)
									{
										TimeTable[w][t++]	= -1;
										TimeTable[w][t++]	= -1;

										td	+= 2;

										Chrom[a]	= -2;

										Blank--;
										break;
									}
									a++;
								}
							}
						}

						//5, 6限の配置でも休憩が２個以上溜まっていたら休憩を先に配置
						else if((Blank >= 2) && (td >= 4) && (g == 0) && (Flag == 0) && (Flag_1 == 0))
						{
							a	= i;
							while(1)
							{
								//終端まで探索が終了したらリターン
								if(a == (LECTURES_A_WEEK * (w + 1) + SCORE_ARRAY))
								{
									Flag_1	= 1;
									Flag	= 1;
									break;
								}

								else if(Chrom[a] == -1)
								{
									//要素の入れ替え
									Chrom[a]	= -2;
									Blank++;
								}

								if(Blank >= (LECTURES_A_DAY - td))
								{
									//休憩時間を埋める
									for(; LECTURES_A_DAY > td; td++)
									{
										TimeTable[w][t]	= -1;
										Blank--;
										t++;
									}
									break;
								}
								a++;
							}
							if(Blank)
								Flag	= 1;
						}
					}

					//読み込まれた遺伝子の値をチェック
					else if((temp < 0) || (temp > Num_Subject))
					{
printf("%d\n", temp);
printf("Unexpected value roaded.\n");
//return -4;
						return DEFECTIVE_OF_GENE;
					}

					//休憩以外の配置
					else
					{
#if DEBUG_AT
	printf("配置する科目：%d\n時間数：%d\n\n", temp, SubjectTable[temp].Units);
#endif
						//配置しようとする科目が収まらない場合
						if((LECTURES_A_DAY - g) - (SubjectTable[temp].Units + td) < 0)
						{
							//データを一旦別の場所に退避
							SubArray[m++]	= temp;
//printf("一日に収まらない大きさなので退避しました\n");
//printf("ヒープに入れたデータ：%d\n", temp);
						}

						//奇数時間の処理
						else if(SubjectTable[temp].Units % 2)
						{
//printf("奇数時間\n");
							//その日最後の授業なら配置
							if((Blank >= (LECTURES_A_DAY - (td + SubjectTable[temp].Units))) && (g == 0))
							{
								TimeTable[w][t]	= temp;

								//同時開講の科目の配置
								if(Classes[SubjectTable[temp].Classes][1] != 0)
								{
									for(int a = 1; (Classes[SubjectTable[temp].Classes][a] != 0) && (a < CLASSES_A_GROUP); a++)
										TimeTable[Classes[SubjectTable[temp].Classes][a]][t]	= temp;
								}
								t	+= SubjectTable[temp].Units;
								td	+= SubjectTable[temp].Units;

								//休憩時間を埋める
								for(; LECTURES_A_DAY > td; td++)
								{
									TimeTable[w][t]	= -1;
									Blank--;
									t++;
								}
//printf("\nBlankB:%d\n\n", Blank);
							}
							
							//一コマの授業は優先的にペアになるものを探す
							else if(SubjectTable[temp].Units == 1)
							{
								//遺伝子の最後まで探索
								j = i;
								while(1)
								{
									//終端まで探索が終了したら
									if(j == (LECTURES_A_WEEK * (w + 1) + SCORE_ARRAY))
									{
										//キューを探索
										if(m != 0)
										{
											int		a	= 0;

											while(1)
											{
												if(a >= m)
												{
													//データを退避してループを抜ける
													SubArray[m++]	= temp;
													break;
												}

												//奇数時間のペアを探索
												else if(SubjectTable[SubArray[a]].Units % 2)
												{
													//一日に収まればそのまま配置
													if((SubjectTable[SubArray[a]].Units + SubjectTable[temp].Units) <= (LECTURES_A_DAY - td - g))
													{
														TimeTable[w][t]								= temp;
														TimeTable[w][t + SubjectTable[temp].Units]	= SubArray[a];

														//同時開講の科目の配置
														if(Classes[SubjectTable[temp].Classes][1] != 0)
														{
															for(int c = 1; (Classes[SubjectTable[temp].Classes][c] != 0) && (c < CLASSES_A_GROUP); c++)
																TimeTable[Classes[SubjectTable[temp].Classes][c] - 1][t]	= temp;
														}
														t	+= SubjectTable[temp].Units;
														td	+= SubjectTable[temp].Units;

														if(Classes[SubjectTable[SubArray[a]].Classes][1] != 0)
														{
															for(int c = 1; (Classes[SubjectTable[temp].Classes][c] != 0) && (c < CLASSES_A_GROUP); c++)
																TimeTable[Classes[SubjectTable[SubArray[a]].Classes][c] - 1][t]	= SubArray[a];
														}
														t	+= SubjectTable[SubArray[a]].Units;
														td	+= SubjectTable[SubArray[a]].Units;

														
														if(m == 1)
															m	= 0;

														else if(a == (m - 1))
															m--;

														else
															SubArray[a]	= SubArray[--m];

														break;
													}
												}
												a++;
											}
											break;
										}

										else
										{
											SubArray[m++]	= temp;
											break;
										}
									}

									//ペアが見つかれば配置
									else if(SubjectTable[Chrom[j]].Units == 1)
									{
										TimeTable[w][t]		= temp;
										TimeTable[w][t + 1]	= Chrom[j];

										//同時開講の科目の配置
										if(Classes[SubjectTable[temp].Classes][1] != 0)
										{
											for(int a = 1; (Classes[SubjectTable[temp].Classes][a] != 0) && (a < CLASSES_A_GROUP); a++)
												TimeTable[Classes[SubjectTable[temp].Classes][a] - 1][t]	= temp;
										}
										t++;
										td++;

										if(Classes[SubjectTable[Chrom[j]].Classes][1] != 0)
										{
											for(int a = 1; Classes[SubjectTable[temp].Classes][a] != 0; a++)
												TimeTable[Classes[SubjectTable[temp].Classes][a] - 1][t]	= Chrom[j];
										}
										t++;
										td++;
//printf("ペアを見つけたので配置\n");
										
										if(i == j)
										{
											if(i < (LECTURES_A_WEEK * (w + 1) + SCORE_ARRAY))
												i++;

											Chrom[j]	= Chrom[i];		//要素の入れ替え
										}

										else
										{
											Chrom[j]	= Chrom[i];

											if(i < (LECTURES_A_WEEK * (w + 1) + SCORE_ARRAY))
												i++;
										}

										break;
									}
									j++;
								}
							}

							//組み合わせ可能なペアをキューから探す
							else
							{
								//キューを探索
								if(m != 0)
								{
									int		a	= 0;

									while(1)
									{
										if(a >= m)
										{
											//データを退避してループを抜ける
											SubArray[m++]	= temp;
											break;
										}

										//奇数時間のペアを探索
										else if(SubjectTable[SubArray[a]].Units % 2)
										{
											//一日に収まればそのまま配置
											if((SubjectTable[SubArray[a]].Units + SubjectTable[temp].Units) <= (LECTURES_A_DAY - td))
											{
												TimeTable[w][t]								= temp;
												TimeTable[w][t + SubjectTable[temp].Units]	= SubArray[a];

												t	+= SubjectTable[temp].Units + SubjectTable[SubArray[a]].Units;
												td	+= SubjectTable[temp].Units + SubjectTable[SubArray[a]].Units;

												if(m == 1)
													m	= 0;

												else if(a == (m - 1))
													m--;

												else
													SubArray[a]	= SubArray[--m];

												break;
											}
										}
										a++;
									}
								}

								else
									SubArray[m++]	= temp;
							}
						}

						//通常の授業
						else
						{
							TimeTable[w][t]	= temp;

							//同時開講の科目の配置
							if(Classes[SubjectTable[temp].Classes][1] != 0)
							{
								for(int a = 1; (Classes[SubjectTable[temp].Classes][a] != 0) && (a < CLASSES_A_GROUP); a++)
									TimeTable[Classes[SubjectTable[temp].Classes][a] - 1][t]	= temp;
							}
							t	+= SubjectTable[temp].Units;
							td	+= SubjectTable[temp].Units;
						}
					}
				}

#if DEBUG_AT
	if(TimeTable[w][t]	== -2)
	{
		printf("Error!\nm = %d, n = %d, i = %d, t = %d, td = %d\n", m, m, i, t, td);
#if MONITOR
		getch();
#endif
	}

	for(int a = 0; a < NUM_CLASS; a++)
	{
		for(int b = 0; b < LECTURES_A_WEEK; b++)
			printf("%02d, ", TimeTable[a][b]);

		putchar('\n');
	}
	putchar('\n');
#if MONITOR
	getch();
#endif
	printf("遺伝子番号：%d\n読み込まれた遺伝子：%d\nBlank：%d\nQueue：%d\nHeap ：%d\n", i, temp, Blank, m, n);
#endif

			}
		}
	}

	return 0;
}


int	TIME_TABLE::GetScore(short *Gene)
{
	INTEGER	conv;

	conv.S_Val.MSB	= Gene[0];
	conv.S_Val.LSB	= Gene[1];

	return conv.Value;
}


int TIME_TABLE::Evaluation(short *Gene)
{
	int	i;
	int	j;
	int	k;
	int	l;

	int	GroupID_1;
	int	GroupID_2;

	int	EvaGrp;

	int	NegativeScore	= 0;			//評価点
	int	PositiveScore	= 0;
	int	Score;

	int	Result;					//エラーの判定

	INTEGER	conv;		//intをshort二つ分に分割

	//重複のチェックのための配列
	char	Flag_1[MAX_TEACHER_NUM];
	char	Flag_2[MAX_ROOM_NUM];

	//同時開講を考慮
	char	Flag_3[NUM_SUBJECT];

	//遺伝子から時間割を生成
	if((Result = ArrangeTable(Gene)) < 0)
	{
#if DEBUG
		switch(Result)
		{
		case ALLOCATION_FAILURE:
			printf("配置不能\n");
			break;

		case DEFECTIVE_OF_GENE:
			printf("遺伝子の欠陥により配置を中止\n");
			break;

		case INFINIT_ROOP:
			printf("無限ループに陥ったので配置を中止しました\n");
			break;

		default:
			printf("Unknown error!!\n");
			printf("Error code = %d\n", Result);
//			return UNKNOWN;
		}
#endif
		Score		= -20000;
		conv.Value	= Score;
		Gene[0]		= conv.S_Val.MSB;
		Gene[1]		= conv.S_Val.LSB;
		return -20000;
	}

	//教官、教室のダブりをチェック
	for(i = 0; i < LECTURES_A_WEEK; i++)
	{
		//配列を初期化
		for(l = 0; l < MAX_TEACHER_NUM; l++)
			Flag_1[l]	= 0;

		for(l = 0; l < MAX_ROOM_NUM; l++)
			Flag_2[l]	= 0;

		for(l = 0; l < NUM_SUBJECT; l++)
			Flag_3[l]	= 0;

		for(j = 0; j < NUM_CLASS; j++)
		{
			//同時開講科目を考慮
			if((TimeTable[j][i] > 0) && (Flag_3[TimeTable[j][i]] == 0))
			{
				GroupID_1	= SubjectTable[TimeTable[j][i]].Teachers;
				GroupID_2	= SubjectTable[TimeTable[j][i]].Rooms;

				Flag_3[TimeTable[j][i]]	= 1;

				for(k = 0; Teachers[GroupID_1][k] != 0; k++)
					Flag_1[Teachers[GroupID_1][k]]++;

				//各クラスのホームルームを使う場合を考慮
				if(GroupID_2 != 0)
				{
					for(k = 0; Rooms[GroupID_2][k] != 0; k++)
						Flag_2[Rooms[GroupID_2][k]]++;
				}


#if DEBUG_EVA
	printf("GroupID2 = %d\n", GroupID_2);
	printf("TimeTable[%02d][%02d] = %d, Teachers ID = %d, RoomID = %d\n", j, i, TimeTable[j][i], Teachers[GroupID_1][0], Rooms[GroupID_2][0]);
//	getch();
#endif

			}
		}

		//数えあげたリストから重複をチェック
		for(k = 0; k < MAX_TEACHER_NUM; k++)
		{
			//重複があれば評価をマイナス
			if(Flag_1[k] > 1)
				NegativeScore	+= Flag_1[k] - 1;
		}

		for(k = 0; k < MAX_ROOM_NUM; k++)
		{
			if(Flag_2[k] > 1)
				NegativeScore	+= Flag_2[k] - 1;
		}

#if DEBUG_EVA
	for(int a = 0; a < MAX_TEACHER_NUM; a++)
	{
		if(Flag_1[a] != 0)
			printf("Flag_1[%03d] = %d\n" ,a, Flag_1[a]);
	}

	for(int a = 0; a < MAX_ROOM_NUM; a++)
	{
		if(Flag_2[a] != 0)
			printf("Flag_2[%03d] = %d\n", a, Flag_2[a]);
	}
	putchar('\n');

	printf("NegativeScore = %d\n", NegativeScore);
	getch();
#endif

		PositiveScore	= 0;
		//評価属性テーブルから評価を算出
		for(int a = 0; a < NUM_CLASS; a++)
		{
			for(int b = 0; b < LECTURES_A_WEEK; b++)
			{
				if(TimeTable[a][b] > 0)
				{
					EvaGrp	= SubjectTable[TimeTable[a][b]].EvaluationAtb;

					for(int c = 0; (Attributes[EvaGrp][c] != 0) && (c < ATTRIBUTES_A_GROUP); c++)
					{
						PositiveScore	+= (int)AllocTable[Attributes[EvaGrp][c]].AllocationTable[b / 2];
						//printf("属性番号%d, スコア%d, ", Attributes[EvaGrp][c], AllocTable[Attributes[EvaGrp][c]].AllocationTable[b / 2]);
					}
					//putchar('\n');
					//getch();
				}
			}
		}
	}

	//スコアを遺伝子に書き込み
	Gene[2]	= NegativeScore;
	Gene[3]	= PositiveScore;

	Score		= -200 * NegativeScore + PositiveScore;
	conv.Value	= Score;

	Gene[0]	= conv.S_Val.MSB;
	Gene[1]	= conv.S_Val.LSB;

	return Score;
}




//時間割データ出力関数
int	TIME_TABLE::GetTimeTable(short (*Table)[LECTURES_A_WEEK], short *Gene)
{
	int	i;
	int	j;

	//時間割作成
	if(ArrangeTable(Gene) == -1)
		return 1;

	for(i = 0; i < NUM_CLASS; i++)
	{
		for(j = 0; j < LECTURES_A_WEEK; j++)
			Table[i][j]	= TimeTable[i][j];
	}

	return 0;
}


#if DEBUG

//遺伝子検査関数
int	TIME_TABLE::CheckGene(short *Gene)
{
	int		i;
	int		j;

	short	Table[LECTURES_A_WEEK];

	for(i = 0; i < NUM_CLASS; i++)
	{
		for(j = 0; j < LECTURES_A_WEEK; j++)
			Table[j]	= Gene[SCORE_ARRAY + i * LECTURES_A_WEEK + j];

		qsort(Table, LECTURES_A_WEEK, sizeof(short), cmp);

		for(j = 0; j < LECTURES_A_WEEK; j++)
		{
			if(Table[j]	!= FingPrt[i][j])
				return -1;
		}
	}

	return 0;
}

#endif




