
#include<stdio.h>
#include"Main.h"
#include"TimeTable.h"

//エントリーポイント
int main(void)
{
	TIME_TABLE	*App;	//時間割作成クラス
	short		TimeTable[NUM_CLASS][LECTURES_A_WEEK];	//時間割
	short		GenePool[POPULATION][GENE_LENGTH];		//遺伝子プール

	int			i;
	int			j;
//	int			k;

	int			max;
	int			mean;
	int			total;
	int			generation;


	App	= new TIME_TABLE(5000);

	if(App == NULL)
		printf("Falure!\n");

	//遺伝子プール初期化
	if(App->InitGenePool() < 0)
		return -1;

	printf("Generation\tMax Score\tMean Score\tTotal Score\n");

	//計算実行
	while(!App->Calculate())
	{
		max			= App->GetMaxScore();
		mean		= App->GetMeanScore();
		total		= App->GetTotal();
		generation	= App->GetGeneration();

		printf("%d\t%d\t%d\t%d\n", generation, max, mean, total);
	}
	max			= App->GetMaxScore();
	mean		= App->GetMeanScore();
	total		= App->GetTotal();
	generation	= App->GetGeneration();
	printf("%d\t%d\t%d\t%d\n", generation, max, mean, total);

	//時間割表示
	App->GetBestGene(GenePool);
	App->GetTimeTable(TimeTable, GenePool[0]);

	printf("Score：%d\n", App->GetScore(GenePool[0]));
	for(i = 0; i < NUM_CLASS; i++)
	{
		for(j = 0; j < LECTURES_A_WEEK; j++)
			printf("%03d\t", TimeTable[i][j]);

		putchar('\n');
	}
	putchar('\n');

/*
	App->GetGenePool(GenePool);

	for(i = 0; i < POPULATION; i++)
	{
		App->GetTimeTable(TimeTable, GenePool[i]);

		for(j = 0; j < NUM_CLASS; j++)
		{
			printf("クラス%d\n", j + 1);
			for(k = 0; k < LECTURES_A_WEEK; k++)
			{
				printf("%02d", TimeTable[j][k]);

			if(((k % LECTURES_A_DAY) == (LECTURES_A_DAY - 1)) && (k != 1))
			{
				putchar('|');
				putchar('|');
			}

			else
				putchar(',');
			}
			putchar('\n');
		}

		putchar('\n');
	}
*/

	return 0;
}