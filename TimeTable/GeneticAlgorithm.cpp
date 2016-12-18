
#include"GeneticAlgorithm.h"


GENETIC_POOL::GENETIC_POOL(int Generation)
{
	//ポインタを初期化
	lpParent	= Pool1;
	lpChild		= Pool2;

	//ステータスを初期化
	MaxGeneration				= Generation;
	MaxScore					= 0;
	MeanScore					= 0;
	TotalScore					= 0;
	GENETIC_POOL::Generation	= 0;

	//乱数の種を初期化
	srand((unsigned)time(NULL));
}

int	cmp(const void *a, const void *b)
{
	if(*(short*)a == *(short*)b)
		return 0;

	else if(*(short*)a < *(short*)b)
		return -1;

	else
		return 1;
}


//一世代計算
int	GENETIC_POOL::Calculate()
{
	int			i;				//ループ変数

	int			PA;				//親となる遺伝子の要素番号を保持
	int			PB;				//

	OPERATION	op;				//操作

	int			Score1;			//遺伝子の評価点を一時的に保持
	int			Score2;			//

	int			Sum	= 0;		//遺伝子全体の点数の総和
	int			Max	= -10000;	//最高得点を保持

	short		(*temp)[GENE_LENGTH];	//親と次世代のプールの入れ替えのための一時変数

static int	ErrorRate	= 0;

	//遺伝子プールをソート
	SortGenePool();

	//評価がもっとも高かった遺伝子を保存
	Copy(SortedPool[0], SortedPool[1], lpChild[0], lpChild[1]);
	Sum	+= GetScore(lpChild[0]);
	Sum	+= GetScore(lpChild[1]);

	Max	= GetScore(lpChild[0]);

	//遺伝子配列が埋まるまで計算
	for(i = 2; i < POPULATION; i += 2)
	{
		//操作を決定
		op	= Selection(&PA, &PB);

if((PA > POPULATION) || PA < 0)
{
printf("選択関数が無効な遺伝子をアドレスしました、\n");
return -1;
}

if((PB > POPULATION) || (PB < 0))
{
printf("選択関数が無効な遺伝子をアドレスしました\n");
return -1;
}

		//操作を実行(コピー、交叉、突然変異のどれか)
		switch(op)
		{
		case COPY:
			Copy(SortedPool[PA], SortedPool[PB], lpChild[i], lpChild[i + 1]);
			Score1	= GetScore(lpChild[i]);
			Score2	= GetScore(lpChild[i + 1]);
			break;

		case CROSSOVER:
			Crossover(SortedPool[PA], SortedPool[PB], lpChild[i], lpChild[i + 1]);
			Score1	= Evaluation(lpChild[i]);
			Score2	= Evaluation(lpChild[i + 1]);
			break;

		case MUTATE:
			Mutation(SortedPool[PA], SortedPool[PB], lpChild[i], lpChild[i + 1]);
			Score1	= Evaluation(lpChild[i]);
			Score2	= Evaluation(lpChild[i + 1]);
			break;

		default:
			return -1;
		}
/*
if(Score1 == -4)
return -1;

if(Score2 == -4)
return -1;
*/
if(Score1 == -20000)
	ErrorRate++;

if(Score2 == -20000)
	ErrorRate++;
/*
#if DEBUG
		switch(op)
		{
		case COPY:
			printf("Copied\n");
			break;

		case CROSSOVER:
			printf("Crossoverd\n");
			break;

		case MUTATE:
			printf("Mutated\n");
			break;

		default:
			printf("Unexpected operation occcured!\n");
			return -1;
		}

		//同じ要素が使われているかをチェック
		qsort(lpChild[i], GENE_LENGTH, sizeof(short), cmp);
		for(int j = 0; j < GENE_LENGTH; j++)
			printf("%02d, ", lpChild[i][j]);

		putchar('\n');
		putchar('\n');
#endif
*/
/*
#if DEBUG
		printf("Score1 = %d\nScore2 = %d\n", Score1, Score2);
		putchar('\n');
#endif
*/
		//最高得点の更新
		if(Score1 > Max)
			Max	= Score1;

		if(Score2 > Max)
			Max	= Score2;

		Sum	+= Score1 + Score2;
	}
	//親となるプールと次世代のプールを入れ替え
	temp		= lpParent;
	lpParent	= lpChild;
	lpChild		= temp;

	//最高点、平均点、総和、世代数を更新
	MaxScore	= Max;
	TotalScore	= Sum;
	MeanScore	= Sum / POPULATION;
	Generation++;
	
	//優良遺伝子を登録
	UpdateGene();

#if DEBUG
	printf("Error rate = %d, Population = %d\n", ErrorRate, POPULATION);
	printf("Generation = %d\n\n", Generation);
#endif

	ErrorRate	= 0;

	//終了判定
	if(Generation >= MaxGeneration)
		return 1;

	return 0;
}


//コピー
int	GENETIC_POOL::Copy(short *PA, short *PB, short *CA, short *CB)
{
	int	i;

	for(i = 0; i < GENE_LENGTH; i++)
	{
		CA[i]	= PA[i];
		CB[i]	= PB[i];
	}

	return 0;
}



//優良遺伝子を登録するメソッド
int	GENETIC_POOL::UpdateGene()
{
	int		i = 0;
	int		j = 0;
	int		k = 0;
	short	*temp[BEST];

	SortGenePool();

	while(i < BEST)
	{
		if(GetScore(SortedPool[j]) > GetScore(Superior[k]))
		{
			temp[i]	= SortedPool[j];
			i++;
			j++;
		}

		else
		{
			temp[i]	= Superior[k];
			i++;
			k++;
		}
	}

	for(i = 0; i < BEST; i++)
	{
		for(j = 0; j < GENE_LENGTH; j++)
			Superior[i][j]	= temp[i][j];
	}

	return 0;
}



//ソートメソッド
int	GENETIC_POOL::SortGenePool()
{
	int	i;

	//遺伝子のアドレスをコピー
	for(i = 0; i < POPULATION; i++)
		SortedPool[i]	= lpParent[i];

	//ソート
	Quick_Sort(SortedPool, 0, POPULATION);

	return 0;
}


//遺伝子取得
int	GENETIC_POOL::GetGenePool(short (*Gene)[GENE_LENGTH])
{
	int	i;
	int	j;

	for(i = 0; i < POPULATION; i++)
	{
		for(j = 0; j < GENE_LENGTH; j++)
			Gene[i][j]	= SortedPool[i][j];
	}

	return 0;
}

//優良遺伝子取得
int	GENETIC_POOL::GetBestGene(short (*Gene)[GENE_LENGTH])
{
	int i;
	int	j;

	for(i = 0; i < BEST; i++)
	{
		for(j = 0; j < GENE_LENGTH; j++)
			Gene[i][j]	= Superior[i][j];
	}

	return 0;
}


//クイックソート
void GENETIC_POOL::Quick_Sort(short** a, int min, int max)
{
	//枢軸
	int	v;

	if(min >= max)
		return ;

	//枢軸から右と左に分ける。
	v = Pertition(a, min, max);

	Quick_Sort(a, min, v);
	Quick_Sort(a, v + 1, max);
}


//クイックソートの分割関数
int	GENETIC_POOL::Pertition(short** a, int min, int max)
{
	//分割のためのポインタ
	int	i	= min - 1;
	int	j	= max;
	int	mid	= (min + max) / 2;
	
	short*	pivot;				//枢軸
	short*	temp;

	max--;

	//枢軸の選択。もともと降順に並んでいる確立が高いため。
	if(GetScore(a[min]) > GetScore(a[mid]))
	{
		//min > mid > max(元々降順に並んでいることを考慮して)
		if(GetScore(a[mid]) > GetScore(a[max]))
		{
			pivot	= a[mid];

			temp	= a[mid];
			a[mid]	= a[max];
			a[max]	= temp;
		}

		//min > max > mid
		else if(GetScore(a[min]) > GetScore(a[max]))
			pivot	= a[max];

		//max > min > mid
		else
		{
			pivot	= a[min];

			temp	= a[min];
			a[min]	= a[max];
			a[max]	= temp;
		}
	}

	else
	{
		//mid > min > max
		if(GetScore(a[min]) > GetScore(a[max]))
		{
			pivot	= a[min];

			temp	= a[min];
			a[min]	= a[max];
			a[max]	= temp;
		}

		//max > mid > min
		else if(GetScore(a[max]) > GetScore(a[mid]))
		{
			pivot	= a[mid];

			temp	= a[mid];
			a[mid]	= a[max];
			a[max]	= temp;
		}

		//mid > max > min
		else
			pivot	= a[max];
	}


	//分割
	while(1)
	{
		//ポインタを右に動かす
		while(GetScore(a[++i]) > GetScore(pivot))
			;

		//ポインタを左に動かす
		while((i < --j) && (GetScore(pivot) >= GetScore(a[j])))
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
	a[i]		= a[max];
	a[max]	= temp;

	return i;
}
