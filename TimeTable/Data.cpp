
#include"Data.h"

const int	RD_SUBJECTS		= 1;
const int	RD_TEACHERS		= 2;
const int	RD_ROOMS		= 3;
const int	RD_CLASSES		= 4;
const int	RD_ATB_GRP		= 5;
const int	RD_ATTRIBUTES	= 6;
const int	RD_SUB_TABLE	= 7;

//�f�[�^��ǂݍ���œo�^
int TIME_TABLE::RoadDatabase()
{
	char	Flag	= 0;
	char	Str[512];

	while(Flag != 0x3f)
	{
		cin.getline(Str, 512);

		switch(atoi(Str))
		{
		case RD_SUBJECTS:
			//�Ȗڃf�[�^�o�^
			if((Num_Subject = RoadSubjects(SubjectTable)) <= 0)
			{
				printf("Subject data registration error.\n");
				return -1;
			}
			Flag	|= 1;
			break;

		case RD_TEACHERS:
			//�����O���[�v�f�[�^�o�^
			if((Num_Teacher = RoadTeacherGroup(Teachers)) <= 0)
			{
				printf("Teacher data registration error.\n");
				return -1;
			}
			Flag	|= 2;
			break;

		case RD_ROOMS:
			//�����O���[�v�f�[�^�o�^
			if((Num_Room = RoadRoomGroup(Rooms)) <= 0)
			{
				printf("Room data ragistration error.\n");
				return -1;
			}
			Flag	|= 4;
			break;

		case RD_CLASSES:
			//�N���X�O���[�v�f�[�^�o�^
			if((Num_Class = RoadClassGroup(Classes)) <= 0)
			{
				printf("Class data registration error.\n");
				return -1;
			}
			Flag	|= 8;
			break;

		case RD_ATB_GRP:
			//�]�������O���[�v�f�[�^�o�^
			if((Num_AtbGrp	= RoadEvaluationTable(Attributes)) <= 0)
			{
				printf("Evaluation Table registration error.\n");
				return -1;
			}
			Flag	|= 16;
			break;

		case RD_ATTRIBUTES:
			//�]�������f�[�^�o�^
			if((Num_Attributes	= RoadEvaluationAtb(AllocTable)) <= 0)
			{
				printf("Evaluation data registration error.\n");
				return -1;
			}
			Flag	|= 32;
			break;

		case RD_SUB_TABLE:
			//�z�u�ς݂̎��Ԋ��f�[�^
			if(RoadSubTable(SubTable) < 0)
			{
				printf("Time table roading error\n");
				return -1;
			}
			break;

		default:
			printf("Invalid command.\n");
		}
	}

#if CHECK_DATABASE
	int		i;
	int		j;

	printf("Monitoring Subject Database\n");
/*
	//ID�̏ƍ�
	for(i = 1; i < (Num_Subject + 1); i++)
		printf("%d, %d\n", i, SubjectTable[i].ID);
*/
#if MONITOR
	getch();
#endif

	//�Ȗڃf�[�^
	for(i = 1; i < (Num_Subject + 1); i++)
	{
		//�ꂱ�܂̎��Ԑ�
		printf("%02d, ", SubjectTable[i].Units);

		//��T�Ԃ̃R�}��
		printf("%02d, ", SubjectTable[i].LecturesAWeek);

		//�z�u�\�e�[�u��
		printf("%d, ", SubjectTable[i].AllocationTable[0]);

		//�����O���[�v
		printf("%02d, ", SubjectTable[i].Teachers);

		//�����O���[�v
		printf("%02d, ", SubjectTable[i].Rooms);

		//�N���X�O���[�v
		printf("%02d, ", SubjectTable[i].Classes);

		//�]������
		printf("%02d\n", SubjectTable[i].EvaluationAtb);
	}
#if MONITOR
	getch();
#endif
	//�����O���[�v�e�[�u��
	printf("Monitoring Teachers Group Table\n");
	for(i = 1; i < (Num_Teacher + 1); i++)
	{
		for(j = 0; j < TEACHERS_A_GROUP; j++)
			printf("%02d, ", Teachers[i][j]);

		putchar('\n');
	}
#if MONITOR
	getch();
#endif

	//�����O���[�v�e�[�u��
	printf("Monitoring Room Group Table\n");
	for(i = 1; i < (Num_Room + 1); i++)
	{
		for(j = 0; j < ROOMS_A_GROUP; j++)
			printf("%02d, ", Rooms[i][j]);

		putchar('\n');
	}
#if MONITOR
	getch();
#endif

	//�N���X�O���[�v�e�[�u��
	printf("Monitoring Class Group Table\n");
	for(i = 1; i < (Num_Class + 1); i++)
	{
		for(j = 0; j < CLASSES_A_GROUP; j++)
			printf("%02d, ", Classes[i][j]);

		putchar('\n');
	}
#if MONITOR
	getch();
#endif

	//�]�������O���[�v�e�[�u��
	printf("Monitoring Evaluatino Group Table\n");
	for(i = 1; i < (Num_AtbGrp + 1); i++)
	{
		for(j = 0; j < ATTRIBUTES_A_GROUP; j++)
			printf("%02d, ", Attributes[i][j]);

		putchar('\n');
	}
#if MONITOR
	getch();
#endif

	//�]�������f�[�^
	printf("Monitoring Evaluation Attributes\n");
	for(i = 1; i < (Num_Attributes + 1); i++)
	{
		for(j = 0; j < (LECTURES_A_WEEK / 2); j++)
			printf("%02d, ", AllocTable[i].AllocationTable[j]);

		putchar('\n');
	}
#if MONITOR
	getch();
#endif

	//�z�u�ςݎ��Ԋ�
	printf("Monitoring sub table\n");
	for(i = 0; i < NUM_CLASS; i++)
	{
		for(j = 0; j < LECTURES_A_WEEK; j++)
		{
			printf("%03d", SubTable[i][j]);

			if(j != (LECTURES_A_WEEK - 1))
				putchar('\t');
		}
		putchar('\n');
	}
#if MONITOR
	getch();

#else
	return -1;
#endif


#endif

#if CHK
	int	i;
	int	temp;
	int	Prev	= 0;

	for(i = 1; i < (Num_Subject + 1); i++)
	{
		temp	= SubjectTable[i].Classes;

		if(temp != Prev)
			putchar('\n');

		printf("%d, ", i);

		Prev	= temp;
	}

	return -1;
#endif

	return 0;
}



//�f�[�^���[�h�⏕�֐�
int Road()
{
	int			c;
	int			i		= 0;

	char		Str[512];

	//�R�����g�s�Ƌ󔒍s��ǂݔ�΂�
	while(1)
	{
		Str[i]	= cin.get();

		switch(Str[i])
		{
		case '\0':
			return -1;

		//�R�����g�s����ы󔒂̓ǂݔ�΂�
		case '#':
			while((c = cin.get()) != '\n')
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


//�Ȗڃf�[�^�o�^�֐�
int	RoadSubjects(SUBJECT *Subjects)
{
	int			i;

	int			temp;

	int			Num_Elem;	//�f�[�^��

	//�o�^���ꂽ�f�[�^�̐����擾
	temp	= Road();

	if(temp <= 0)
		return -1;

	Num_Elem	= temp;

	for(i = 0; i < Num_Elem; i++)
	{
		//ID�B�����Ŋ���U��
		Subjects[i + 1].ID	= i + 1;

		//�P�R�}�̎��Ԑ�
		temp	= Road();

		if(temp <= 0)
			return -1;

		Subjects[i + 1].Units	= temp;

		//��T�Ԃ̎��Ԑ�
		temp	= Road();

		if(temp <= 0)
			return -1;

		Subjects[i + 1].LecturesAWeek	= temp;

		//�z�u�\�e�[�u��
		temp	= Road();

		if(temp < 0)
			return -1;

//		Subjects[i + 1].AllocationTable	= temp;

		//�����O���[�vID
		temp	= Road();

		if(temp <= 0)
			return -1;

		Subjects[i + 1].Teachers	= temp;

		//�����O���[�vID�B0�̏ꍇ�͊e�N���X�̃z�[�����[��
		temp	= Road();

		if(temp < 0)
			return -1;

		Subjects[i + 1].Rooms	= temp;

		//�N���X�O���[�vID
		temp	= Road();

		if(temp <= 0)
			return -1;

		Subjects[i + 1].Classes	= temp;

		//�]�������̃O���[�vID
		temp	= Road();

		if(temp < 0)
			return -1;

		Subjects[i + 1].EvaluationAtb	= temp;
	}

	return Num_Elem;
}


//�����O���[�v�ǂݍ���
int	RoadTeacherGroup(short (*Teachers)[TEACHERS_A_GROUP])
{
	int	i;
	int	j;

	int	temp;
	int	Num_Elem;

	temp	= Road();

	if(temp <= 0)
		return -1;

	Num_Elem	= temp;

	for(i = 1; i < (Num_Elem + 1); i++)
	{
		//�P�O���[�v�ǂݍ���
		for(j = 0; j < TEACHERS_A_GROUP; j++)
		{
			temp	= Road();
			if(temp < 0)
				return -1;

			Teachers[i][j]	= temp;
		}
	}

	return Num_Elem;
}

//�����O���[�v�ǂݍ���
int	RoadRoomGroup(short (*Rooms)[ROOMS_A_GROUP])
{
	int	i;
	int	j;

	int	temp;
	int	Num_Elem;

	temp	= Road();

	if(temp <= 0)
		return -1;

	Num_Elem	= temp;

	for(i = 1; i < Num_Elem + 1; i++)
	{
		//�P�O���[�v�ǂݍ���
		for(j = 0; j < ROOMS_A_GROUP; j++)
		{
			temp	= Road();
			if(temp < 0)
				return -1;

			Rooms[i][j]	= temp;
		}
	}

	return Num_Elem;
}

//�N���X�O���[�v�ǂݍ���
int	RoadClassGroup(short (*Classes)[CLASSES_A_GROUP])
{
	int	i;
	int	j;

	int	temp;
	int	Num_Elem;

	temp	= Road();

	if(temp <= 0)
		return -1;

	Num_Elem	= temp;

	for(i = 1; i < Num_Elem + 1; i++)
	{
		//�P�O���[�v�ǂݍ���
		for(j = 0; j < CLASSES_A_GROUP; j++)
		{
			temp	= Road();
			if(temp < 0)
				return -1;

			Classes[i][j]	= temp;
		}
	}

	return Num_Elem;
}

//�]���f�[�^�O���[�v�ǂݍ���
int	RoadEvaluationTable(short (*Attributes)[ATTRIBUTES_A_GROUP])
{
	int	i;
	int	j;

	int	temp;
	int	Num_Elem;

	temp	= Road();
	Num_Elem	= temp;

	if(temp <= 0)
		return -1;

	for(i = 1; i < Num_Elem + 1; i++)
	{
		//�P�O���[�v�ǂݍ���
		for(j = 0; j < ATTRIBUTES_A_GROUP; j++)
		{
			temp	= Road();
			if(temp < 0)
				return -1;

			Attributes[i][j]	= temp;
		}
	}

	return Num_Elem;
}


//�]�������f�[�^�ǂݍ���
int	RoadEvaluationAtb(EVALUATION_ATTRIBUTES *AllocTable)
{
	int	i;
	int	j;

	int	temp;

	int	Num_Elem;

	temp	= Road();
	Num_Elem	= temp;

	if(temp <= 0)
		return -1;

	for(i = 1; i < (Num_Elem + 1); i++)
	{
		for(j = 0; j < (LECTURES_A_WEEK / 2); j++)
		{
			temp	= Road();

			AllocTable[i].AllocationTable[j]	= temp;
		}
	}

	return Num_Elem;
}

//�z�u�ςݎ��Ԋ��ǂݍ���
int	RoadSubTable(short (*TimeTable)[LECTURES_A_WEEK])
{
	int	i;
	int	j;

	//���Ԋ���ǂݏo��
	for(i = 0; i < NUM_CLASS; i++)
	{
		for(j = 0; j < LECTURES_A_WEEK; j++)
			TimeTable[i][j]	= Road();
	}

	return 0;
}
