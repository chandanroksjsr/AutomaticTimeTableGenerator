

#include"TimeTable.h"

const int	HEAP_SIZE	= 40;


/*
//�����W�c����
int	TIME_TABLE::InitGenePool()
{
	int		i;
	int		j;
	int		k;

	short	temp[GENE_LENGTH];	//�_�~�[�z��

	for(i = 0; i < GENE_LENGTH; i++)
	{
		temp[i]	= 
*/


//�����_���\�[�g
void TIME_TABLE::RandSort(short* a, int min, int max)
{
	//����
	int	v;

	if(min >= max)
		return ;

	//��������E�ƍ��ɕ�����B
	v = RandPertition(a, min, max);

	RandSort(a, min, v);
	RandSort(a, v + 1, max);
}


//�N�C�b�N�\�[�g�̕����֐�
int	TIME_TABLE::RandPertition(short* a, int min, int max)
{
	//�����̂��߂̃|�C���^
	int	i	= min - 1;
	int	j	= max;
	int	mid	= (min + max) / 2;
	
	short	pivot;				//����
	short	temp;

	max--;

	pivot	= a[mid];

	//����
	while(1)
	{
		//�|�C���^���E�ɓ�����
		while((++i < max) && (rand() % 3))
			;

		//�|�C���^�����ɓ�����
		while((min < --j) && (rand() % 3))
			;

		//���[�v�𔲂������
		if(i >= j)
			break;

		//�v�f�̌���
		temp	= a[i];
		a[i]	= a[j];
		a[j]	= temp;
	}

	//����������
	temp		= a[i];
	a[i]		= a[mid];
	a[mid]		= temp;

	return mid;
}


//�R���X�g���N�^
TIME_TABLE::TIME_TABLE(int Generation) : GENETIC_POOL(Generation)
{
	int	i;
	int	j;

	Num_Subject	= 0;

	//�D�ǌ̂�ێ�����z��̃X�R�A��������
	for(i = 0; i < BEST; i++)
	{
		INTEGER	conv;

		conv.Value	= -50000;

		Superior[i][0]	= conv.S_Val.MSB;
		Superior[i][1]	= conv.S_Val.LSB;
	}

	//���Ԋ���0�ɏ�����
	for(i = 0; i < NUM_CLASS; i++)
	{
		for(j = 0; j < LECTURES_A_WEEK; j++)
		{
			TimeTable[i][j]	= 0;
			SubTable[i][j]	= 0;
		}
	}

	//�z�u�ς݉Ȗڃe�[�u��������
	for(i = 0; i < NUM_SUBJECT; i++)
	{
		SubjectTable[i].ID		= 0;
		SubjectTable[i].Units	= 0;
	}

	//�O���[�v�e�[�u����������
	//�����O���[�v
	for(i = 0; i < NUM_TEACHER_GROUP; i++)
	{
		for(j = 0; j < TEACHERS_A_GROUP; j++)
			Teachers[i][j]	= 0;
	}

	//�����O���[�v
	for(i = 0; i < NUM_TEACHER_GROUP; i++)
	{
		for(j = 0; j < TEACHERS_A_GROUP; j++)
			Teachers[i][j]	= 0;
	}

	//�����O���[�v
	for(i = 0; i < NUM_ROOM_GROUP; i++)
	{
		for(j = 0; j < ROOMS_A_GROUP; j++)
			Rooms[i][j]	= 0;
	}

	//�N���X�O���[�v
	for(i = 0; i < (NUM_CLASS + 1); i++)
	{
		for(j = 0; j < CLASSES_A_GROUP; j++)
			Classes[i][j]	= 0;
	}

	//�]�������O���[�v
	for(i = 0; i < NUM_SUBJECT; i++)
	{
		for(j = 0; j < ATTRIBUTES_A_GROUP; j++)
			Attributes[i][j]	= 0;
	}

#if DEBUG
	printf("Constructor OK!\n");
#endif
}




//�����W�c����
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

	int		GroupID;				//�ǂݍ��񂾃N���X�O���[�v�̂hD��ێ�

	int		n[NUM_CLASS];			//�N���X���ƂɃf�[�^��ǂݍ��ނ��߂̃|�C���^

	int		ChkSubj[NUM_SUBJECT];	//�z�u�ς݂̉Ȗڃf�[�^���d�o�^���Ȃ��H�v

	//�ǂݍ��񂾉Ȗڃf�[�^����U�ێ�
	short	Subjects[NUM_CLASS][LECTURES_A_WEEK];

#if DEBUG
	short	Table[LECTURES_A_WEEK];	//�t�B���K�[�v�����g�쐬�p�z��

	printf("Roading Database\n");
#endif

	//�Ȗڃf�[�^����уf�[�^�e�[�u����ǂݍ���
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

	//�|�C���^��������
	for(i = 0; i < NUM_CLASS; i++)
		n[i]	= 0;

	//�z�u�ς݃`�F�b�N�p�z���������
	for(i = 0; i < NUM_SUBJECT; i++)
		ChkSubj[i]	= 0;

	//�z�u�ςݎ��Ԋ����l��
	for(i = 0;i < NUM_CLASS; i++)
	{
		//�o�^����Ă�Ȗڐ����Z�o
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

		//�z�u�ς݂̉ӏ���-2�Ŗ��߂�
		for(int a = 0; a < count; a++)
			Subjects[i][n[i]++]	= -2;
	}

	//�����J�u�̃N���X�̔z�u�ς݂�-2�Ŗ��߂�
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

	//�ǂݍ��񂾉Ȗڂ��N���X���ƂɊ���U��
	for(i = 1; i < Num_Subject + 1; i++)
	{
		//�N���X�O���[�v�̓ǂݍ���
		GroupID	= SubjectTable[i].Classes;

		//���Ǝ��Ԃ���уN���XID���擾
		Units	= SubjectTable[i].Units;
		Num		= SubjectTable[i].LecturesAWeek / Units;

		ClassID	= Classes[GroupID][0] - 1;

		Num	-= ChkSubj[i];

		//�N���X���ƂɊ���U���ĉȖڂ�z�u
		for(int a = 0; a < Num; a++)
		{
			Subjects[ClassID][n[ClassID]++]	= i;

			//�Ȗڂ̍��Ԃ𖄂߂�
			for(j = 0; j < (Units - 1); j++)
				Subjects[ClassID][n[ClassID]++]	= -2;

			//�����J�u���l��
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

	//�Ȗڂ��Ȃ��ӏ����x�e�Ŗ��߂�
	for(i = 0; i < NUM_CLASS; i++)
	{
		for(; n[i] < LECTURES_A_WEEK; n[i]++)
			Subjects[i][n[i]]	= -1;
	}

	//��������Ԋ��z�����`�q�ւ��̂܂܃R�s�[
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
	//�o�^���ꂽ�Ȗڂ�\��
	for(int e = 0; e < NUM_CLASS; e++)
	{
		for(int g = 0; g < LECTURES_A_WEEK; g++)
			printf("%d, ", Subjects[e][g]);
		putchar('\n');
	}
	return -1;
#endif

#if DEBUG
	//��`�q�����p�t�B���K�[�v�����g�쐬
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

	//��`�q�������_���\�[�g
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
		//��`�q�Ɍ��ׂ��Ȃ���������
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
	//��`�q�ɕ]���l����������
	for(i = 0; i < POPULATION; i++)
		Evaluation(Pool1[i]);

	//return -1;

#if DEBUG
	printf("GenePool was initialized.\n");
#endif


	return 0;
}


//�I���֐�
OPERATION	TIME_TABLE::Selection(int *a, int *b)
{
	int		l;
	int		m;
	int		n;

	l	= rand() % 100;

	//���30���̈�`�q���I�΂��m���i����50���j
	if(l < 50)
		m	= rand() % ((POPULATION * 30) / 100);

	//���50%�܂łɊ܂܂���`�q���I�΂��m��(����20%)
	else if(l < (50 + 20))
		m	= ((POPULATION * 30) / 100) + (rand() % (POPULATION * 20) / 100);

	//���80%�ȓ��Ɋ܂܂�Ă����`�q�i����5%�j
	else if(l < (50 + 20 + 5))
		m	= ((POPULATION * 50) / 100) + (rand() % (POPULATION * 30) / 100);

	//����20%�Ɋ܂܂�Ă����`�q���I�΂��m���i����25%�j
	else
		m	= ((POPULATION * 80) / 100) + (rand() % (POPULATION * 20) / 100);

	*a	= m;

	l	= rand() % 100;

	//���30���̈�`�q���I�΂��m���i����50���j
	if(l < 50)
		m	= rand() % ((POPULATION * 30) / 100);

	//���50%�܂łɊ܂܂���`�q���I�΂��m��(����20%)
	else if(l < (50 + 20))
		m	= ((POPULATION * 30) / 100) + (rand() % (POPULATION * 20) / 100);

	//���80%�ȓ��Ɋ܂܂�Ă����`�q�i����5%�j
	else if(l < (50 + 20 + 5))
		m	= ((POPULATION * 50) / 100) + (rand() % (POPULATION * 30) / 100);

	//����20%�Ɋ܂܂�Ă����`�q���I�΂��m���i����25%�j
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



//�ˑR�ψ�
int	TIME_TABLE::Mutation(short *PA, short *PB, short *CA, short *CB)
{
	//�͈͂����߂Ĕ͈͓��������_���\�[�g

	//�͈͂����肷��ϐ�
	int	Init;
	int	Dist;

	int	Offset;

	int	i;

	//��`�q���R�s�[
	for(i = 0; i < GENE_LENGTH; i++)
	{
		CA[i]	= PA[i];
		CB[i]	= PB[i];
	}

	//�Œ�5�̈�`�q�͓���ւ���
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
	//���[�v�ϐ�
	int		i;
	int		j;
	int		k;

	//�ꎞ�ϐ�
	int		a;
	int		b;
	int		c;
	int		d;

	//���F�̂��w���|�C���^
	int		Pt;			//�I�t�Z�b�g

	int		Distance;	//�����_�Ԃ̋���
	int		CP_A;		//�����_
	int		CP_B;		//

	int		End;		//��`�q�i1�N���X���j�̏I�[

	//�ꎞ�I�Ɉ�`�q�̓��e��ێ�
	short	temp_A[GENE_LENGTH];
	short	temp_B[GENE_LENGTH];

	//�I�t�Z�b�g
	Pt	= SCORE_ARRAY;

#if DEBUG
	//��`�q�Ɍ��ׂ��Ȃ���������
	if(CheckGene(PA) == -1)
	{
		printf("�����O�̐e��`�q�Ɍ���\n");
		return -1;
	}

	//��`�q�Ɍ��ׂ��Ȃ���������
	if(CheckGene(PB) == -1)
	{
		printf("�����O�̐e��`�q�Ɍ���\n");
		return -1;
	}
#endif

	//�N���X���ƂɈ�`�q������
	for(i = 0; i < NUM_CLASS; i++)
	{
		End	= Pt + LECTURES_A_WEEK;

		//�����_�̒���������
		Distance	= 4 + rand() % (LECTURES_A_WEEK - 4);

		//�����_������
		CP_A		= Pt + rand() % (LECTURES_A_WEEK - Distance);
		CP_B		= Pt + rand() % (LECTURES_A_WEEK - Distance);

#if DEBUG_CO
		printf("�I�t�Z�b�g�̈ʒu�F%d\n", Pt);

		putchar('\n');

		printf("�P�N���X�̏I�[�F%d\n", End);

		printf("�����_\n");
		printf("CP_A = %d\n", CP_A);
		printf("CP_B = %d\n", CP_B);
		printf("Distance = %d\n", Distance);

		putchar('\n');

		printf("�����_�̖���\n");
		printf("��`�qA�F%d\n", CP_A + Distance);
		printf("��`�qB�F%d\n", CP_B + Distance);

		putchar('\n');
#endif
#if DEBUG
		if(((CP_A + Distance) > End) || (CP_A < SCORE_ARRAY))
		{
			printf("�����_�̐ݒ�~�X\n");
			return -1;
		}

		if(((CP_B + Distance) > End) || (CP_B < SCORE_ARRAY))
		{
			printf("�����_�̐ݒ�~�X\n");
			return -1;
		}
#endif

		//���F�̂��R�s�[
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

		//�����_�̏I�[���Z�b�g
		a	= CP_A + Distance;
		b	= CP_B + Distance;

		//�����_�Ԃ̈�`�q�����ׂ�0�ɃZ�b�g
		for(j = CP_A; j < a; j++)
			CA[j]	= 0;

		for(j = CP_B; j < b; j++)
			CB[j]	= 0;

#if DEBUG_CO
		printf("�����_�Ԃ�0�N���A\n");
		for(int g = 0; g < SCORE_ARRAY; g++)
			printf("%02d, ", CA[g]);

		putchar('\n');

		for(int g = SCORE_ARRAY; g < (LECTURES_A_WEEK + SCORE_ARRAY); g++)
			printf("%02d, ", CA[g + i * LECTURES_A_WEEK]);
		putchar('\n');
		getch();
#endif


		//���������F�̂̈ʒu�����ւ��Ĉڂ����
		for(j = 0; j < Distance; j++)
		{
			for(k = 0; k < Distance; k++)
			{
				if(((c = PA[CP_A + j]) > 0) && ((d = PB[CP_B + k]) > 0) && (c == d) && (temp_A[CP_A + j] != 0) && (temp_B[CP_B + k] != 0))
				{
					CA[CP_A + k]	= c;
					CB[CP_B + j]	= d;

					//����ւ����ꏊ���}�[�N
					temp_A[CP_A + j]	= 0;
					temp_B[CP_B + k]	= 0;
				}
			}
		}

#if DEBUG_CO
		printf("��������`�q�̓���ւ�\n");
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

		//����ȊO�̐��F�̂����Ԃǂ���R�s�[
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
		printf("�R�s�[���\n");
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

		//�I�t�Z�b�g���X�V
		Pt	+= LECTURES_A_WEEK;
	}
#if DEBUG
	//��`�q�Ɍ��ׂ��Ȃ���������
	if(CheckGene(CA) == -1)
	{
		printf("Crossover\n");
		return -1;
	}

	//��`�q�Ɍ��ׂ��Ȃ���������
	if(CheckGene(CB) == -1)
	{
		printf("Crossover\n");
		return -1;
	}
#endif

	return 0;
}


//�Ȗڔz�u�̑҂��s��ɓ����f�[�^
struct SUBJ{
	short	ID;		//�Ȗ�ID�A�f�[�^��ێ�
	short	Units;	//���Ǝ���
};

//�q�[�v�ɗv�f��}���A�폜���邽�߂̃T�u���[�`��
void	downheap(struct SUBJ *a, int n)
{
	int	i;
	int	j;

	short	Key;
	short	Val;

	//�ړ�����v�f�̒l���R�s�[
	Val	= a[1].ID;
	Key	= a[1].Units;

	//������n�߂Đ�i���q�������Ă������J��Ԃ�
	i = 1;
	while(i <= (n / 2))
	{
		//��i�̎q�̂����̑傫���ق����j�Ƃ���
		j	= i * 2;
		if((j + 1 <= n) && (a[j].Units < a[j + 1].Units))
			j++;

		if(Key >= a[j].Units)
			break;

		//��i�Ɛ�j�̒l���������A��j�ɒ���
		a[i].ID		= a[j].ID;
		a[i].Units	= a[j].Units;
		i = j;
	}

	//�v�f�𐳂����ʒu�ɑ}��
	a[i].ID		= Val;
	a[i].Units	= Key;
}


void	upheap(struct SUBJ *a, int x)
{
	short	Val;
	short	Key;

	Val	= a[x].ID;
	Key	= a[x].Units;


	//�v�f�����܂ŗ��Ă��Ȃ��āA���e���q��菬�����ԌJ��Ԃ�
	while((x > 1) && (a[x / 2].Units > Key))
	{
		//�e�̒l���q�Ɉڂ�
		a[x].ID		= a[x / 2].ID;
		a[x].Units	= a[x / 2].Units;

		x /= 2;
	}

	a[x].ID		= Val;
	a[x].Units	= Key;
}


//�v�f�̎��o��
int	DeleteMin(short *ID, short *Units, struct SUBJ *a, int *n)
{
	//�q�[�v����Ȃ烊�^�[��
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

//�v�f�̑}��
int	Insert(short ID, int Units, struct SUBJ *a, int *n)
{
	//�q�[�v�������ς��ɂȂ��Ă��Ȃ������m�F
	if(*n >= HEAP_SIZE)
		return 1;

	a[++(*n)].ID	= ID;
	a[*n].Units		= Units;

	upheap(a, *n);
//printf("Enqueue, %d\n\n", ID);
	return 0;
}

//���Ԋ��z�u�֐�
int	TIME_TABLE::ArrangeTable(const short *Gene)
{
	//���[�v�ϐ�
	int	w;				//�T����
	int	d;				//������
	int	td;				//������Ƃ̎���
	int	t;				//����

	int	Offset;			//��`�q�̈ʒu���|�C���g

	int	Prev	= 0;	//��O�̎��Ԃ�ێ�

	int	i		= SCORE_ARRAY;	//��`�q���|�C���e�B���O
	int	j;				//

	int		Blank	= 0;	//���Ƃ̋󔒂��ꎞ�I�ɕێ�
	int		Blank_1	= 0;	//
	int		EndFlag	= 0;	//�������[�v���p�t���O
	int		Flag	= 0;	//�x�e�z�u�̃t���O
	int		Flag_1	= 0;

	short	temp;		//�ꎞ�I�ɉȖ�ID��ێ�

	short		SubArray[HEAP_SIZE];	//�z�u��ۗ������Ȗڂ�ێ�
	struct SUBJ	Heap[HEAP_SIZE + 1];	//�q�[�v���\��

	int		n	= 0;			//�q�[�v�̍Ō����ێ�
	int		m	= 0;			//�\���̔z��̃|�C���^

	short	Chrom[GENE_LENGTH];	//��`�q���R�s�[���ĕێ�


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


	//���Ԋ���������
	for(i = 0; i < NUM_CLASS; i++)
	{
		for(j = 0; j < LECTURES_A_WEEK; j++)
			TimeTable[i][j]	= SubTable[i][j];
	}
	i	= SCORE_ARRAY;

	//��`�q���R�s�[���ĕێ�
	for(int a = 0; a < GENE_LENGTH; a++)
		Chrom[a]	= Gene[a];

#if DEBUG
	//��`�q�Ɍ��ׂ��Ȃ���������
	if(CheckGene(Chrom) == -1)
	{
		printf("�ǂݍ��܂ꂽ��`�q�Ɍ��ׂ�����܂�\n");
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


	//�N���X���Ɓi�T���Ɓj�̔z�u
	for(w = 0; w < NUM_CLASS; w++)
	{
		//�P�N���X�̔z�u���I��������_�Ŏ��Ԃ̃|�C���^��������
		t		= 0;
		Flag_1	= 0;

#if DEBUG
	if(Blank != 0)
	{
		printf("�x�e��z�u������Ă��܂���B\n%d\n\n", Blank);
		return -4;
	}

	if((m > 0) | (n > 0))
	{
		printf("Queue���g���؂�Ă��܂���B\n");
		return -4;
	}
#endif

		//�����Ƃ̔z�u
		for(d = 0; d < SCHOOLDAY; d++)
		{
			//�I�t�Z�b�g�̌v�Z
			Offset	= SCORE_ARRAY + LECTURES_A_WEEK * w + LECTURES_A_DAY * d;
			td		= 0;
			Flag	= 0;

			//���Ԋ��̓ǂݍ��݂Ɣz�u
			while(td < LECTURES_A_DAY)
			{
#if DEBUG_AT
	printf("�N���X%d, %d����, %d���Ԗڂ̔z�u\n", w + 1, d + 1, td + 1);
#endif

				//�z�u�����ɐi�ނ��󔒂̐��ɕω��������
				if((t != Prev) || (Blank_1 != Blank))
				{
					//�f�[�^���ޔ�����Ă���ꍇ�̓q�[�v���\�z
					if(m > 0)
					{
//printf("�q�[�v���\�z���܂���\n");
//printf("�q�[�v�ɓo�^���ꂽ�f�[�^�̌��F%d\n", m);
//getch();

						//�q�[�v�Ƀf�[�^��o�^
						for(m--; m >= 0; m--)
							Insert(SubjectTable[SubArray[m]].ID, SubjectTable[SubArray[m]].Units, Heap, &n);

						m		= 0;
					}
					EndFlag	= 0;	//�z�u�����ɐi�߂΃t���O���폜
				}

				//���ԃf�[�^�X�V
				Prev	= t;

				//�󔒂̕ω��f�[�^�X�V
				Blank_1	= Blank;

				//���łɔz�u�ς݂łȂ������`�F�b�N
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
						//printf("td�̒l\nt%d, td%d\n", t, td);
						//printf("�z�u����ȖځF%d\n���Ԑ��F%d\n\n", temp, SubjectTable[temp].Units);
						//printf("��`�q�ԍ��F%d\n�ǂݍ��܂ꂽ��`�q�F%d\nBlank�F%d\nQueue�F%d\nHeap �F%d\n", i, temp, Blank, m, n);
						
						return -4;
					}
				}

				//�z�u
				else
				{
					int	g	= 0;

					//�z�u�ς݂��`�F�b�N
					for(int e = 1; (td + e) < LECTURES_A_DAY; e++)
					{
						if((TimeTable[w][t + e] != 0) && (g == 0))
								g	= (LECTURES_A_DAY - (td + e));
					}

					//�x�e���Ԃ̔z�u
					if((Blank >= (LECTURES_A_DAY - td)) && (g == 0))
					{
						//�x�e���Ԃ𖄂߂�
						for(; LECTURES_A_DAY > td; td++)
						{
//printf("Blank�F%d, LECTURES_A_DAY - td - 1�F%d, td�F%d\n\n", Blank, LECTURES_A_DAY - td - 1, td);
							TimeTable[w][t]	= -1;
							Blank--;
							t++;
						}
						temp	= -3;
					}
//printf("\nBlankC:%d\n\n", Blank);

					//Blank����łȂ��V���ڈȍ~�Ȃ�x�e��D�悵�Ĕz�u
					else if((Blank == 1) && (td >= 6) && (g == 0) && (Flag_1 == 0))
					{
						//��`�q��T�����ċx�e��z�u
						a = i;
						while(1)
						{
							//�I�[�܂ŒT�����I�������烊�^�[��
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

								//�v�f�̓���ւ�
								Chrom[a]	= -2;
								Blank--;
								temp	= -3;
								break;
							}
							a++;
						}
					}

					//�q�[�v��D�悵�ď���
					else if((n > 0) || (i == (LECTURES_A_WEEK * (w + 1) + SCORE_ARRAY)))
					{
//printf("�q�[�v�����p����܂���\n");
//printf("�q�[�v�ɓo�^���ꂽ�f�[�^��%d\n", n);
						short	a;	//�����̃_�~�[

						//��`�q���P�N���X���ǂ݂����Ă�����q�[�v����f�[�^�����o��
						if(n == 0)
						{
							//�ޔ�����Ă���f�[�^���Ȃ��A�x�e���Ԃ��g���؂��Ă�����z�u�s�\�Ɣ��f
							if(m == 0)
							{
								//�x�e��z�u
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
//printf("w�F%d, t�F%d, Blank�F%d\n", w, t, Blank, td);
								}

								else
									return ALLOCATION_FAILURE;
							}

							//�q�[�v���č\�z���Ĕz�u
							else if(EndFlag == 0)
							{
								//�q�[�v�Ƀf�[�^��o�^
								for(m--; m >= 0; m--)
									Insert(SubjectTable[SubArray[m]].ID, SubjectTable[SubArray[m]].Units, Heap, &n);

								EndFlag	= 1;	//�������[�v����t���O
								m		= 0;

								//�q�[�v����f�[�^��ǂݍ���
								DeleteMin(&temp, &a, Heap, &n);
							}

							else
								return INFINIT_ROOP;

						}

						else
						{
							//�q�[�v����f�[�^��ǂݍ���
							DeleteMin(&temp, &a, Heap, &n);
						}
#if DEBUG_AT
	printf("�q�[�v������o���ꂽ��`�q�F%d\n", temp);
#endif
					}	

					else
					{
//printf("��`�q����ǂݍ���\n");

						//���ƃf�[�^����`�q����ǂݍ���
						while(1)
						{
#if DEBUG_AT
	printf("��`�q�ԍ��F%d\n", i);
#endif
							if(i == (LECTURES_A_WEEK * (w + 1) + SCORE_ARRAY))
							{
								temp	= -3;
								break;
							}

							//-2��ǂݔ�΂�
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
	printf("��`�q�ԍ�%d\n", i);
#endif
							return DEFECTIVE_OF_GENE;
						}
					}


#if DEBUG_AT
	printf("��`�q�ԍ��F%d\n�ǂݍ��܂ꂽ��`�q�F%d\nBlank�F%d\nQueue�F%d\nHeap �F%d\n", i, temp, Blank, m, n);
#endif

					if(temp == -3)
						;
			
					//�x�e���Ԃ̏���
					else if(temp == -1)
					{
						Blank++;

						if(Blank >= (LECTURES_A_DAY - td))
						{
							if(!g)
							{
								//�x�e���Ԃ𖄂߂�
								for(; LECTURES_A_DAY > td; td++)
								{
									TimeTable[w][t]	= -1;
									Blank--;
									t++;
								}
							}
						}

						//�V���ڈȍ~�Ȃ炻�̏�Ŕz�u
						else if((td >= 6) && (Flag_1 == 0))
						{
							if(g == 0)
							{
								int	a;

								//��`�q��T�����ċx�e��z�u
								a = i;
								while(1)
								{
									//�I�[�܂ŒT�����I�������牽�����Ȃ�
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

						//5, 6���̔z�u�ł��x�e���Q�ȏ㗭�܂��Ă�����x�e���ɔz�u
						else if((Blank >= 2) && (td >= 4) && (g == 0) && (Flag == 0) && (Flag_1 == 0))
						{
							a	= i;
							while(1)
							{
								//�I�[�܂ŒT�����I�������烊�^�[��
								if(a == (LECTURES_A_WEEK * (w + 1) + SCORE_ARRAY))
								{
									Flag_1	= 1;
									Flag	= 1;
									break;
								}

								else if(Chrom[a] == -1)
								{
									//�v�f�̓���ւ�
									Chrom[a]	= -2;
									Blank++;
								}

								if(Blank >= (LECTURES_A_DAY - td))
								{
									//�x�e���Ԃ𖄂߂�
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

					//�ǂݍ��܂ꂽ��`�q�̒l���`�F�b�N
					else if((temp < 0) || (temp > Num_Subject))
					{
printf("%d\n", temp);
printf("Unexpected value roaded.\n");
//return -4;
						return DEFECTIVE_OF_GENE;
					}

					//�x�e�ȊO�̔z�u
					else
					{
#if DEBUG_AT
	printf("�z�u����ȖځF%d\n���Ԑ��F%d\n\n", temp, SubjectTable[temp].Units);
#endif
						//�z�u���悤�Ƃ���Ȗڂ����܂�Ȃ��ꍇ
						if((LECTURES_A_DAY - g) - (SubjectTable[temp].Units + td) < 0)
						{
							//�f�[�^����U�ʂ̏ꏊ�ɑޔ�
							SubArray[m++]	= temp;
//printf("����Ɏ��܂�Ȃ��傫���Ȃ̂őޔ����܂���\n");
//printf("�q�[�v�ɓ��ꂽ�f�[�^�F%d\n", temp);
						}

						//����Ԃ̏���
						else if(SubjectTable[temp].Units % 2)
						{
//printf("�����\n");
							//���̓��Ō�̎��ƂȂ�z�u
							if((Blank >= (LECTURES_A_DAY - (td + SubjectTable[temp].Units))) && (g == 0))
							{
								TimeTable[w][t]	= temp;

								//�����J�u�̉Ȗڂ̔z�u
								if(Classes[SubjectTable[temp].Classes][1] != 0)
								{
									for(int a = 1; (Classes[SubjectTable[temp].Classes][a] != 0) && (a < CLASSES_A_GROUP); a++)
										TimeTable[Classes[SubjectTable[temp].Classes][a]][t]	= temp;
								}
								t	+= SubjectTable[temp].Units;
								td	+= SubjectTable[temp].Units;

								//�x�e���Ԃ𖄂߂�
								for(; LECTURES_A_DAY > td; td++)
								{
									TimeTable[w][t]	= -1;
									Blank--;
									t++;
								}
//printf("\nBlankB:%d\n\n", Blank);
							}
							
							//��R�}�̎��Ƃ͗D��I�Ƀy�A�ɂȂ���̂�T��
							else if(SubjectTable[temp].Units == 1)
							{
								//��`�q�̍Ō�܂ŒT��
								j = i;
								while(1)
								{
									//�I�[�܂ŒT�����I��������
									if(j == (LECTURES_A_WEEK * (w + 1) + SCORE_ARRAY))
									{
										//�L���[��T��
										if(m != 0)
										{
											int		a	= 0;

											while(1)
											{
												if(a >= m)
												{
													//�f�[�^��ޔ����ă��[�v�𔲂���
													SubArray[m++]	= temp;
													break;
												}

												//����Ԃ̃y�A��T��
												else if(SubjectTable[SubArray[a]].Units % 2)
												{
													//����Ɏ��܂�΂��̂܂ܔz�u
													if((SubjectTable[SubArray[a]].Units + SubjectTable[temp].Units) <= (LECTURES_A_DAY - td - g))
													{
														TimeTable[w][t]								= temp;
														TimeTable[w][t + SubjectTable[temp].Units]	= SubArray[a];

														//�����J�u�̉Ȗڂ̔z�u
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

									//�y�A��������Δz�u
									else if(SubjectTable[Chrom[j]].Units == 1)
									{
										TimeTable[w][t]		= temp;
										TimeTable[w][t + 1]	= Chrom[j];

										//�����J�u�̉Ȗڂ̔z�u
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
//printf("�y�A���������̂Ŕz�u\n");
										
										if(i == j)
										{
											if(i < (LECTURES_A_WEEK * (w + 1) + SCORE_ARRAY))
												i++;

											Chrom[j]	= Chrom[i];		//�v�f�̓���ւ�
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

							//�g�ݍ��킹�\�ȃy�A���L���[����T��
							else
							{
								//�L���[��T��
								if(m != 0)
								{
									int		a	= 0;

									while(1)
									{
										if(a >= m)
										{
											//�f�[�^��ޔ����ă��[�v�𔲂���
											SubArray[m++]	= temp;
											break;
										}

										//����Ԃ̃y�A��T��
										else if(SubjectTable[SubArray[a]].Units % 2)
										{
											//����Ɏ��܂�΂��̂܂ܔz�u
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

						//�ʏ�̎���
						else
						{
							TimeTable[w][t]	= temp;

							//�����J�u�̉Ȗڂ̔z�u
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
	printf("��`�q�ԍ��F%d\n�ǂݍ��܂ꂽ��`�q�F%d\nBlank�F%d\nQueue�F%d\nHeap �F%d\n", i, temp, Blank, m, n);
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

	int	NegativeScore	= 0;			//�]���_
	int	PositiveScore	= 0;
	int	Score;

	int	Result;					//�G���[�̔���

	INTEGER	conv;		//int��short����ɕ���

	//�d���̃`�F�b�N�̂��߂̔z��
	char	Flag_1[MAX_TEACHER_NUM];
	char	Flag_2[MAX_ROOM_NUM];

	//�����J�u���l��
	char	Flag_3[NUM_SUBJECT];

	//��`�q���玞�Ԋ��𐶐�
	if((Result = ArrangeTable(Gene)) < 0)
	{
#if DEBUG
		switch(Result)
		{
		case ALLOCATION_FAILURE:
			printf("�z�u�s�\\n");
			break;

		case DEFECTIVE_OF_GENE:
			printf("��`�q�̌��ׂɂ��z�u�𒆎~\n");
			break;

		case INFINIT_ROOP:
			printf("�������[�v�Ɋׂ����̂Ŕz�u�𒆎~���܂���\n");
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

	//�����A�����̃_�u����`�F�b�N
	for(i = 0; i < LECTURES_A_WEEK; i++)
	{
		//�z���������
		for(l = 0; l < MAX_TEACHER_NUM; l++)
			Flag_1[l]	= 0;

		for(l = 0; l < MAX_ROOM_NUM; l++)
			Flag_2[l]	= 0;

		for(l = 0; l < NUM_SUBJECT; l++)
			Flag_3[l]	= 0;

		for(j = 0; j < NUM_CLASS; j++)
		{
			//�����J�u�Ȗڂ��l��
			if((TimeTable[j][i] > 0) && (Flag_3[TimeTable[j][i]] == 0))
			{
				GroupID_1	= SubjectTable[TimeTable[j][i]].Teachers;
				GroupID_2	= SubjectTable[TimeTable[j][i]].Rooms;

				Flag_3[TimeTable[j][i]]	= 1;

				for(k = 0; Teachers[GroupID_1][k] != 0; k++)
					Flag_1[Teachers[GroupID_1][k]]++;

				//�e�N���X�̃z�[�����[�����g���ꍇ���l��
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

		//�������������X�g����d�����`�F�b�N
		for(k = 0; k < MAX_TEACHER_NUM; k++)
		{
			//�d��������Ε]�����}�C�i�X
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
		//�]�������e�[�u������]�����Z�o
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
						//printf("�����ԍ�%d, �X�R�A%d, ", Attributes[EvaGrp][c], AllocTable[Attributes[EvaGrp][c]].AllocationTable[b / 2]);
					}
					//putchar('\n');
					//getch();
				}
			}
		}
	}

	//�X�R�A����`�q�ɏ�������
	Gene[2]	= NegativeScore;
	Gene[3]	= PositiveScore;

	Score		= -200 * NegativeScore + PositiveScore;
	conv.Value	= Score;

	Gene[0]	= conv.S_Val.MSB;
	Gene[1]	= conv.S_Val.LSB;

	return Score;
}




//���Ԋ��f�[�^�o�͊֐�
int	TIME_TABLE::GetTimeTable(short (*Table)[LECTURES_A_WEEK], short *Gene)
{
	int	i;
	int	j;

	//���Ԋ��쐬
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

//��`�q�����֐�
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




