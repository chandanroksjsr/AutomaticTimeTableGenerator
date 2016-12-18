

#include"GeneticAlgorithm.h"
#include<time.h>


#define DEBUG			0	//�f�o�b�O���[�h
#define	MONITOR			0	//���j�^�����O
#define	DEBUG_IG		0	//�����W�c�����֐��f�o�b�O
#define DEBUG_AT		0	//���Ԋ��z�u�֐��̏ڍ׃f�o�b�O���[�h
#define	DEBUG_EVA		0	//�]���֐��̏ڍ׃f�o�b�O���[�h
#define	DEBUG_CO		0	//�����֐��̃f�o�b�O
#define	DUMMY			0	//�_�~�[�f�[�^�œ���e�X�g
#define	CHECK_DATABASE	0	//�f�[�^�o�^�̃��j�^�����O
#define	CHK				0


//Return value�̒�`
#define ALLOCATION_FAILURE	-1	//�ʏ�̔z�u�s�\
#define DEFECTIVE_OF_GENE	-2	//��`�q�̌��ׂŔz�u�s�\�ɂȂ����ꍇ
#define	INFINIT_ROOP		-3	//�������[�v�Ɋׂ��Ē�~�����ꍇ
#define	UNKNOWN				-4	//�s���ȃG���[




//�Ȗڃf�[�^
struct SUBJECT{
	short	ID;					//�Ȗ�ID

	char	Units;				//��R�}�̎��Ԑ�
	char	LecturesAWeek;		//��T�Ԃ̎��Ԑ�
	char	AllocationTable[3];	//���̃R�}��z�u�\�ȗj���A���Ԃ̃r�b�g��

	short	Teachers;			//�����O���[�v
	short	Rooms;				//�g�p���鋳���̃O���[�v	
	short	Classes;			//���̎��Ƃ���u����N���X�̃O���[�v
	short	EvaluationAtb;		//�]�������̃O���[�v
};


//�]���Ɏg���f�[�^
struct EVALUATION_ATTRIBUTES{
	char	AllocationTable[20];	//�z�u�ɂ���ĕ]�������邽�߂̔z��

	//�����̏d���̋������l������p�����[�^�[���K�v
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
	//���Ԋ�
	short	TimeTable[NUM_CLASS][LECTURES_A_WEEK];
	short	SubTable[NUM_CLASS][LECTURES_A_WEEK];	//�z�u�ς݂̃R�}��ێ�

#if DEBUG
	short	FingPrt[NUM_CLASS][LECTURES_A_WEEK];	//��`�q�`�F�b�N�p�̃t�B���K�[�v�����g
#endif

	//�Ȗڔz��
	SUBJECT	SubjectTable[NUM_SUBJECT + 1];

	//���Ԋ��z�u�e�[�u��
	EVALUATION_ATTRIBUTES	AllocTable[NUM_SUBJECT * ATTRIBUTES_A_GROUP];

	//�����W�c�����̂��߂̃����_���\�[�g���\�b�h
	void	RandSort(short* a, int min, int max);
	int		RandPertition(short* a, int min, int max);

	//�O���[�v�e�[�u��
	short	Teachers[NUM_TEACHER_GROUP][TEACHERS_A_GROUP];	//�����O���[�v
	short	Rooms[NUM_ROOM_GROUP][ROOMS_A_GROUP];			//�����O���[�v
	short	Classes[NUM_CLASS_GROUP][CLASSES_A_GROUP];		//�N���X�O���[�v
	short	Attributes[NUM_SUBJECT][ATTRIBUTES_A_GROUP];	//�]�������O���[�v

	int		ArrangeTable(const short *Gene);				//��`�q���玞�Ԋ����쐬����֐�

	//�v�Z���\�b�h
	int			Evaluation(short *Gene);	//��`�q�̕]�����\�b�h
	OPERATION	Selection(int *a, int *b);	//�I���֐�

	//��`�q����
	int	Crossover(short *PA, short *PB, short *CA, short *CB);	//�����֐�
	int	Mutation(short *PA, short *PB, short *CA, short *CB);	//�ˑR�ψ�

#if DEBUG
	//��`�q����
	int	CheckGene(short *Gene);
#endif

	//�f�[�^�x�[�X�Ǘ�
	int	Num_Teacher;	//�o�^���ꂽ�����̐�
	int	Num_Class;		//�o�^���ꂽ�����̐�
	int	Num_Subject;	//�o�^���ꂽ�Ȗڐ�
	int	Num_Room;		//�o�^���ꂽ�����̐�
	int	Num_AtbGrp;		//�o�^���ꂽ�]�������O���[�v�̐�
	int	Num_Attributes;	//�o�^���ꂽ�]�������̐�

	int	RoadDatabase();		//�f�[�^��ǂݍ��ݓo�^���郁�\�b�h

public:
	//�����W�c����
	int	InitGenePool();

	//��`�q�̃X�R�A��Ԃ�
	int	GetScore(short *Gene);

	//��`�q���琶�����ꂽ���Ԋ����擾
	int	GetTimeTable(short (*Table)[LECTURES_A_WEEK], short *Gene);

	//�R���X�g���N�^
	TIME_TABLE(int Generation);
};

