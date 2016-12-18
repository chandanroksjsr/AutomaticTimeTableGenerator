
#include"GeneticAlgorithm.h"


GENETIC_POOL::GENETIC_POOL(int Generation)
{
	//�|�C���^��������
	lpParent	= Pool1;
	lpChild		= Pool2;

	//�X�e�[�^�X��������
	MaxGeneration				= Generation;
	MaxScore					= 0;
	MeanScore					= 0;
	TotalScore					= 0;
	GENETIC_POOL::Generation	= 0;

	//�����̎��������
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


//�ꐢ��v�Z
int	GENETIC_POOL::Calculate()
{
	int			i;				//���[�v�ϐ�

	int			PA;				//�e�ƂȂ��`�q�̗v�f�ԍ���ێ�
	int			PB;				//

	OPERATION	op;				//����

	int			Score1;			//��`�q�̕]���_���ꎞ�I�ɕێ�
	int			Score2;			//

	int			Sum	= 0;		//��`�q�S�̂̓_���̑��a
	int			Max	= -10000;	//�ō����_��ێ�

	short		(*temp)[GENE_LENGTH];	//�e�Ǝ�����̃v�[���̓���ւ��̂��߂̈ꎞ�ϐ�

static int	ErrorRate	= 0;

	//��`�q�v�[�����\�[�g
	SortGenePool();

	//�]���������Ƃ�����������`�q��ۑ�
	Copy(SortedPool[0], SortedPool[1], lpChild[0], lpChild[1]);
	Sum	+= GetScore(lpChild[0]);
	Sum	+= GetScore(lpChild[1]);

	Max	= GetScore(lpChild[0]);

	//��`�q�z�񂪖��܂�܂Ōv�Z
	for(i = 2; i < POPULATION; i += 2)
	{
		//���������
		op	= Selection(&PA, &PB);

if((PA > POPULATION) || PA < 0)
{
printf("�I���֐��������Ȉ�`�q���A�h���X���܂����A\n");
return -1;
}

if((PB > POPULATION) || (PB < 0))
{
printf("�I���֐��������Ȉ�`�q���A�h���X���܂���\n");
return -1;
}

		//��������s(�R�s�[�A�����A�ˑR�ψق̂ǂꂩ)
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

		//�����v�f���g���Ă��邩���`�F�b�N
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
		//�ō����_�̍X�V
		if(Score1 > Max)
			Max	= Score1;

		if(Score2 > Max)
			Max	= Score2;

		Sum	+= Score1 + Score2;
	}
	//�e�ƂȂ�v�[���Ǝ�����̃v�[�������ւ�
	temp		= lpParent;
	lpParent	= lpChild;
	lpChild		= temp;

	//�ō��_�A���ϓ_�A���a�A���㐔���X�V
	MaxScore	= Max;
	TotalScore	= Sum;
	MeanScore	= Sum / POPULATION;
	Generation++;
	
	//�D�ǈ�`�q��o�^
	UpdateGene();

#if DEBUG
	printf("Error rate = %d, Population = %d\n", ErrorRate, POPULATION);
	printf("Generation = %d\n\n", Generation);
#endif

	ErrorRate	= 0;

	//�I������
	if(Generation >= MaxGeneration)
		return 1;

	return 0;
}


//�R�s�[
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



//�D�ǈ�`�q��o�^���郁�\�b�h
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



//�\�[�g���\�b�h
int	GENETIC_POOL::SortGenePool()
{
	int	i;

	//��`�q�̃A�h���X���R�s�[
	for(i = 0; i < POPULATION; i++)
		SortedPool[i]	= lpParent[i];

	//�\�[�g
	Quick_Sort(SortedPool, 0, POPULATION);

	return 0;
}


//��`�q�擾
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

//�D�ǈ�`�q�擾
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


//�N�C�b�N�\�[�g
void GENETIC_POOL::Quick_Sort(short** a, int min, int max)
{
	//����
	int	v;

	if(min >= max)
		return ;

	//��������E�ƍ��ɕ�����B
	v = Pertition(a, min, max);

	Quick_Sort(a, min, v);
	Quick_Sort(a, v + 1, max);
}


//�N�C�b�N�\�[�g�̕����֐�
int	GENETIC_POOL::Pertition(short** a, int min, int max)
{
	//�����̂��߂̃|�C���^
	int	i	= min - 1;
	int	j	= max;
	int	mid	= (min + max) / 2;
	
	short*	pivot;				//����
	short*	temp;

	max--;

	//�����̑I���B���Ƃ��ƍ~���ɕ���ł���m�����������߁B
	if(GetScore(a[min]) > GetScore(a[mid]))
	{
		//min > mid > max(���X�~���ɕ���ł��邱�Ƃ��l������)
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


	//����
	while(1)
	{
		//�|�C���^���E�ɓ�����
		while(GetScore(a[++i]) > GetScore(pivot))
			;

		//�|�C���^�����ɓ�����
		while((i < --j) && (GetScore(pivot) >= GetScore(a[j])))
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
	a[i]		= a[max];
	a[max]	= temp;

	return i;
}
