
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include"Constant.h"



//遺伝子プール
class GENETIC_POOL{
private:
	//パラメーター
	int	MaxGeneration;							//最大世代数。この数に達したら計算を終了

	//遺伝子プールへのポインタ
	short	(*lpParent)[GENE_LENGTH];
	short	(*lpChild)[GENE_LENGTH];

	//動作状況管理
	int	MaxScore;								//その世代の遺伝子の最高評価点
	int	MeanScore;								//平均スコア
	int	TotalScore;								//遺伝子全体の評価値の合計値
	int	Generation;								//世代数

	//ソートメソッド
	void	Quick_Sort(short **a, int min, int max);
	int		Pertition(short **a, int min, int max);


protected:
	short	Superior[BEST][GENE_LENGTH];		//優良個体を保持する配列。保持する個体数を定数として設定

	//遺伝子管理
	short	Pool1[POPULATION][GENE_LENGTH];		//遺伝子配列
	short	Pool2[POPULATION][GENE_LENGTH];		//遺伝子配列
	short	*SortedPool[POPULATION];			//評価点の順番に並び替えられた遺伝子へのポインタ

	//計算メソッド
	virtual int			Evaluation(short *Gene)		= 0;	//遺伝子の評価メソッド
	virtual OPERATION	Selection(int *a, int *b)	= 0;	//選択関数

	//遺伝子操作(一回の操作で遺伝子二つ分を処理)
	int					Copy(short *PA, short *PB, short *CA, short *CB);				//遺伝子をコピー
	virtual int			Crossover(short *PA, short *PB, short *CA, short *CB)	= 0;	//交叉関数
	virtual int			Mutation(short *PA, short *PB, short *CA, short *CB)	= 0;	//突然変異

	//遺伝子の評価点を取得
	virtual int			GetScore(short *Gene)	= 0;

	int		SortGenePool();		//遺伝子プールをソート
	int		UpdateGene();		//優良遺伝子を登録

	//オブジェクト間代入を禁止
	GENETIC_POOL(const GENETIC_POOL &a);
	GENETIC_POOL& operator=(GENETIC_POOL &a);


public:
	GENETIC_POOL(int Generation);

	//初期集団生成
	virtual int			InitGenePool()				= 0;

	//一世代を計算
	int	Calculate();

	//遺伝子を保持したまま設定変更
	int	Reset();

	//ステータス監視	
	int	GetMaxScore(){return MaxScore;};					//最高点を取得
	int	GetMeanScore(){return MeanScore;};					//平均点を取得
	int	GetTotal(){return TotalScore;};						//遺伝子全体の得点を取得
	int	GetGeneration(){return Generation;};				//世代数を取得

	//遺伝子入れ替え系
	int	GetBestGene(short (*Gene)[GENE_LENGTH]);			//優良個体を取得
	int	GetGenePool(short (*Gene)[GENE_LENGTH]);			//遺伝子プールを取得
	int	SetGenePool(short (*Gene)[GENE_LENGTH]);			//遺伝子プールを入れ替え（グリッドとの連携）
};

int	cmp(const void *a, const void *b);