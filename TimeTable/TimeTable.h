

#include"GeneticAlgorithm.h"
#include<time.h>


#define DEBUG			0	//デバッグモード
#define	MONITOR			0	//モニタリング
#define	DEBUG_IG		0	//初期集団生成関数デバッグ
#define DEBUG_AT		0	//時間割配置関数の詳細デバッグモード
#define	DEBUG_EVA		0	//評価関数の詳細デバッグモード
#define	DEBUG_CO		0	//交叉関数のデバッグ
#define	DUMMY			0	//ダミーデータで動作テスト
#define	CHECK_DATABASE	0	//データ登録のモニタリング
#define	CHK				0


//Return valueの定義
#define ALLOCATION_FAILURE	-1	//通常の配置不能
#define DEFECTIVE_OF_GENE	-2	//遺伝子の欠陥で配置不能になった場合
#define	INFINIT_ROOP		-3	//無限ループに陥って停止した場合
#define	UNKNOWN				-4	//不明なエラー




//科目データ
struct SUBJECT{
	short	ID;					//科目ID

	char	Units;				//一コマの時間数
	char	LecturesAWeek;		//一週間の時間数
	char	AllocationTable[3];	//そのコマを配置可能な曜日、時間のビット列

	short	Teachers;			//教員グループ
	short	Rooms;				//使用する教室のグループ	
	short	Classes;			//その授業を受講するクラスのグループ
	short	EvaluationAtb;		//評価属性のグループ
};


//評価に使うデータ
struct EVALUATION_ATTRIBUTES{
	char	AllocationTable[20];	//配置によって評価をするための配列

	//教室の重複の許しを考慮するパラメーターが必要
};

struct D_WORD
{
	short	MSB;
	short	LSB;
};

union INTEGER
{
	struct	D_WORD	S_Val;
	int				Value;
};



class TIME_TABLE : public GENETIC_POOL
{
private:
	//時間割
	short	TimeTable[NUM_CLASS][LECTURES_A_WEEK];
	short	SubTable[NUM_CLASS][LECTURES_A_WEEK];	//配置済みのコマを保持

#if DEBUG
	short	FingPrt[NUM_CLASS][LECTURES_A_WEEK];	//遺伝子チェック用のフィンガープリント
#endif

	//科目配列
	SUBJECT	SubjectTable[NUM_SUBJECT + 1];

	//時間割配置テーブル
	EVALUATION_ATTRIBUTES	AllocTable[NUM_SUBJECT * ATTRIBUTES_A_GROUP];

	//初期集団生成のためのランダムソートメソッド
	void	RandSort(short* a, int min, int max);
	int		RandPertition(short* a, int min, int max);

	//グループテーブル
	short	Teachers[NUM_TEACHER_GROUP][TEACHERS_A_GROUP];	//教員グループ
	short	Rooms[NUM_ROOM_GROUP][ROOMS_A_GROUP];			//教室グループ
	short	Classes[NUM_CLASS_GROUP][CLASSES_A_GROUP];		//クラスグループ
	short	Attributes[NUM_SUBJECT][ATTRIBUTES_A_GROUP];	//評価属性グループ

	int		ArrangeTable(const short *Gene);				//遺伝子から時間割を作成する関数

	//計算メソッド
	int			Evaluation(short *Gene);	//遺伝子の評価メソッド
	OPERATION	Selection(int *a, int *b);	//選択関数

	//遺伝子操作
	int	Crossover(short *PA, short *PB, short *CA, short *CB);	//交叉関数
	int	Mutation(short *PA, short *PB, short *CA, short *CB);	//突然変異

#if DEBUG
	//遺伝子検査
	int	CheckGene(short *Gene);
#endif

	//データベース管理
	int	Num_Teacher;	//登録された教員の数
	int	Num_Class;		//登録された教室の数
	int	Num_Subject;	//登録された科目数
	int	Num_Room;		//登録された教室の数
	int	Num_AtbGrp;		//登録された評価属性グループの数
	int	Num_Attributes;	//登録された評価属性の数

	int	RoadDatabase();		//データを読み込み登録するメソッド

public:
	//初期集団生成
	int	InitGenePool();

	//遺伝子のスコアを返す
	int	GetScore(short *Gene);

	//遺伝子から生成された時間割を取得
	int	GetTimeTable(short (*Table)[LECTURES_A_WEEK], short *Gene);

	//コンストラクタ
	TIME_TABLE(int Generation);
};

