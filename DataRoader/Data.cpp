
#include"Data.h"
#include"main.h"



//�f�[�^���[�h�⏕�֐�
int Road(ifstream &ifs)
{
	int			c;
	int			i		= 0;

	char		Str[512];

	//�R�����g�s�Ƌ󔒍s��ǂݔ�΂�
	while(1)
	{
		Str[i]	= ifs.get();

		switch(Str[i])
		{
		case EOF:
			return EOF;

		//�R�����g�s����ы󔒂̓ǂݔ�΂�
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

		if(Str[i] != '#')
			i++;
	}

	return atoi(Str);
}


//�Ȗڃf�[�^�ǂݏo��
int	RoadSubjects(char *FileName)
{
	int			i;

	ifstream	ifs;

	int			temp;
	int			Num_Elem;	//�f�[�^��

	ifs.open(FileName);

	if(ifs == NULL)
	{
		printf("Subject data file open error.\n");
		return -1;
	}

	//�Ȗړǂݍ���
	printf("%d\n", RD_SUBJECTS);

	//�o�^���ꂽ�f�[�^�̐����擾
	temp	= Road(ifs);

	if(temp <= 0)
	{
		ifs.close();
		return -1;
	}
	Num_Elem	= temp;
	printf("%d\n", Num_Elem);

	for(i = 0; i < Num_Elem; i++)
	{
		//�P�R�}�̎��Ԑ�
		temp	= Road(ifs);

		if(temp == EOF)
			break;

		if(temp == 0)
		{
			ifs.close();
			return -1;
		}
		printf("%d\t", temp);

		//��T�Ԃ̎��Ԑ�
		temp	= Road(ifs);

		if(temp <= 0)
		{
			ifs.close();
			return -1;
		}
		printf("%d\t", temp);

		//�z�u�\�ȗj��
		temp	= Road(ifs);
		printf("%d\t", temp);

		//�����O���[�vID
		temp	= Road(ifs);

		if(temp <= 0)
		{
			ifs.close();
			return -1;
		}
		printf("%d\t", temp);

		//�����O���[�vID�B0�̏ꍇ�͊e�N���X�̃z�[�����[��
		temp	= Road(ifs);

		if(temp < 0)
		{
			ifs.close();
			return -1;
		}
		printf("%d\t", temp);

		//�N���X�O���[�vID
		temp	= Road(ifs);

		if(temp <= 0)
		{
			ifs.close();
			return -1;
		}
		printf("%d\t", temp);

		//�]�������̃O���[�vID
		temp	= Road(ifs);

		if(temp < 0)
		{
			ifs.close();
			return -1;
		}
		printf("%d\n", temp);
	}

	ifs.close();
	return Num_Elem;
}



//�����O���[�v�ǂݍ���
int	RoadTeacherGroup(char *FileName)
{
	int	i;
	int	j;

	int	temp;
	int	Num_Elem;

	ifstream	ifs;

	ifs.open(FileName);

	if(ifs == NULL)
		return -1;

	printf("%d\n", RD_TEACHERS);

	temp	= Road(ifs);

	if(temp <= 0)
	{
		ifs.close();
		return -1;
	}

	Num_Elem	= temp;
	printf("%d\n", Num_Elem);

	for(i = 1; i < Num_Elem + 1; i++)
	{
		//�P�O���[�v�ǂݍ���
		for(j = 0; j < TEACHERS_A_GROUP; j++)
		{
			temp	= Road(ifs);
			if(temp < 0)
			{
				ifs.close();
				return -1;
			}
			printf("%d", temp);

			if(j + 1 < TEACHERS_A_GROUP)
				putchar('\t');
		}
		putchar('\n');
	}

	ifs.close();
	return 0;
}


//�����O���[�v�ǂݍ���
int	RoadRoomGroup(char *FileName)
{
	int	i;
	int	j;

	int	temp;
	int	Num_Elem;

	ifstream	ifs;

	ifs.open(FileName);

	if(ifs == NULL)
		return -1;

	printf("%d\n", RD_ROOMS);

	temp	= Road(ifs);

	if(temp <= 0)
	{
		ifs.close();
		return -1;
	}

	Num_Elem	= temp;
	printf("%d\n", Num_Elem);

	if(temp <= 0)
	{
		ifs.close();
		return -1;
	}

	Num_Elem	= temp;

	for(i = 1; i < Num_Elem + 1; i++)
	{
		//�P�O���[�v�ǂݍ���
		for(j = 0; j < ROOMS_A_GROUP; j++)
		{
			temp	= Road(ifs);
			if(temp < 0)
			{
				ifs.close();
				return -1;
			}
			printf("%d", temp);
			if(j + 1 < ROOMS_A_GROUP)
				putchar('\t');
		}
		putchar('\n');
	}

	ifs.close();
	return 0;
}


//�N���X�O���[�v�ǂݍ���
int	RoadClassGroup(char *FileName)
{
	int	i;
	int	j;

	int	temp;
	int	Num_Elem;

	ifstream	ifs;

	ifs.open(FileName);

	if(ifs == NULL)
		return -1;

	printf("%d\n", RD_CLASSES);

	temp	= Road(ifs);

	if(temp <= 0)
	{
		ifs.close();
		return -1;
	}
	printf("%d\n", temp);
	Num_Elem	= temp;

	for(i = 1; i < Num_Elem + 1; i++)
	{
		//�P�O���[�v�ǂݍ���
		for(j = 0; j < CLASSES_A_GROUP; j++)
		{
			temp	= Road(ifs);
			if(temp < 0)
			{
				ifs.close();
				return -1;
			}
			printf("%d", temp);
			if(j + 1 < CLASSES_A_GROUP)
				putchar('\t');
		}
		putchar('\n');
	}

	ifs.close();
	return 0;
}


//�]���f�[�^�O���[�v�ǂݍ���
int	RoadEvaluationTable(char *FileName)
{
	int	i;
	int	j;

	int	temp;
	int	Num_Elem;

	ifstream	ifs;

	ifs.open(FileName);

	if(ifs == NULL)
		return -1;

	printf("%d\n", RD_ATB_GRP);

	temp	= Road(ifs);

	if(temp <= 0)
	{
		ifs.close();
		return -1;
	}

	Num_Elem	= temp;
	printf("%d\n", Num_Elem);

	for(i = 1; i < Num_Elem + 1; i++)
	{
		//�P�O���[�v�ǂݍ���
		for(j = 0; j < ATTRIBUTES_A_GROUP; j++)
		{
			temp	= Road(ifs);
			if(temp < 0)
			{
				ifs.close();
				return -1;
			}
			printf("%d", temp);
			if(j + 1 < ATTRIBUTES_A_GROUP)
				putchar('\t');
		}
		putchar('\n');
	}

	return 0;
}


//�]���f�[�^�O���[�v�ǂݍ���
int	RoadEvaluationAtb(char *FileName)
{
	int	i;
	int	j;

	int	temp;
	int	Num_Elem;

	ifstream	ifs;

	ifs.open(FileName);

	if(ifs == NULL)
		return -1;

	printf("%d\n", RD_ATTRIBUTES);

	temp	= Road(ifs);

	if(temp <= 0)
	{
		ifs.close();
		return -1;
	}

	Num_Elem	= temp;
	printf("%d\n", Num_Elem);

	for(i = 1; i < Num_Elem + 1; i++)
	{
		//�P�O���[�v�ǂݍ���
		for(j = 0; j < (LECTURES_A_WEEK / 2); j++)
		{
			temp	= Road(ifs);

			printf("%d", temp);
			if(j < ((LECTURES_A_WEEK / 2) - 1))
				putchar('\t');
		}
		putchar('\n');
	}

	return 0;
}


//�z�u�ςݎ��Ԋ��̓ǂݍ���
int	RoadSubTable(char *FileName)
{
	int			i;
	int			j;

	ifstream	ifs;

	ifs.open(FileName);

	if(ifs == NULL)
		return -1;

	printf("%d\n", RD_SUB_TABLE);

	for(i = 0; i < NUM_CLASS; i++)
	{
		for(j = 0; j < LECTURES_A_WEEK; j++)
		{
			printf("%d", Road(ifs));

			if(j != (LECTURES_A_WEEK - 1))
				putchar('\t');
		}
		putchar('\n');
	}
	ifs.close();

	return 0;
}
