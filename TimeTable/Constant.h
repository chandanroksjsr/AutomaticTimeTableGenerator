

//時間割表の大きさ
const int	LECTURES_A_DAY		= 8;							//一日の授業数
const int	SCHOOLDAY			= 5;							//一週間の登校日
const int	LECTURES_A_WEEK		= LECTURES_A_DAY * SCHOOLDAY;	//１クラスの授業のコマ数
const int	NUM_CLASS			= 25;							//扱うクラス数

const int	NUM_SUBJECT			= LECTURES_A_WEEK * NUM_CLASS;


//遺伝子関係の定数
//遺伝子長
const int	GENE_ARRAY			= NUM_SUBJECT;					//遺伝子配列の長さ
const int	SCORE_ARRAY			= 4;							//評価点を書き込む配列の大きさ
const int	GENE_LENGTH			= GENE_ARRAY + SCORE_ARRAY;		//遺伝子の総長
//const int	MAX_GENERATION		= 500;							//計算する世代数

//遺伝子プールの大きさ
const int	POPULATION	= 256;

//保持する優良遺伝子の数
const int	BEST		= 20;

//遺伝子に対する操作を列挙
enum OPERATION{COPY = 0, CROSSOVER = 1, MUTATE = 2};

//遺伝子に対する操作それぞれが実行される確率
const int	MUTATION_RATE	= 10;
const int	CROSSOVER_RATE	= 75;
const int	COPY_RATE		= 15;

//グループに登録される数の上限
const int	ROOMS_A_GROUP		= 5;
const int	TEACHERS_A_GROUP	= 20;
const int	CLASSES_A_GROUP		= 5;
const int	ATTRIBUTES_A_GROUP	= 5;

//グループ数
const int	NUM_ROOM_GROUP		= NUM_SUBJECT;
const int	NUM_TEACHER_GROUP	= NUM_SUBJECT;
const int	NUM_CLASS_GROUP		= NUM_SUBJECT;

const int	MAX_TEACHER_NUM		= ROOMS_A_GROUP * NUM_ROOM_GROUP;
const int	MAX_ROOM_NUM		= TEACHERS_A_GROUP * NUM_TEACHER_GROUP;