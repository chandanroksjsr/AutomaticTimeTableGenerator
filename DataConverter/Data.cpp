
#include"Data.h"



//�f�[�^���[�h�⏕�֐�
int Road(ifstream &ifs, char *Str, int limit)
{
	int			c;
	int			i		= 0;

	//�R�����g�s�Ƌ󔒍s��ǂݔ�΂�
	while(1)
	{
		Str[i]	= ifs.get();

		switch(Str[i])
		{
		case EOF:
			return -1;

		//�R�����g�s����ы󔒂̓ǂݔ�΂�
		case '#':
			while((c = ifs.get()) != '\n')
				;
			break;

		case ' ':
			Str[i]	= ifs.get();
			break;

		case '\t':
		case ',':
		case '\n':
			Str[i]	= '\0';
			break;
		}

		if(Str[i] == '\0')
			break;

		if((Str[i] != '#') && (Str[i] != ' '))
			i++;

		if(i >= (limit - 2))
		{
			//�ǂݔ�΂�����
			while(1)
			{
				c	= ifs.get();

				if(c == ',')
					break;

				else if(c == '\t')
					break;

				else if(c == '\n')
					break;
			}


			Str[i]	= '\0';
			break;
		}
	}
	return i;
}

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
			return -1;

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

		if((Str[i] != '#') && (Str[i] != ' '))
			i++;
	}
	return atoi(Str);
}


//�W�����͂���f�[�^���擾
int Road(int *Flag)
{
	int			c;
	int			i		= 0;
	char		Str[512];

	*Flag	= 0;

	//�R�����g�s�Ƌ󔒍s��ǂݔ�΂�
	while(1)
	{
		Str[i]	= cin.get();

		switch(Str[i])
		{
		case 'q':
			return -3;

		//�R�����g�s����ы󔒂̓ǂݔ�΂�
		case '#':
			while((c = cin.get()) != '\n')
				;
			break;

		case ' ':
			break;

		case '\t':
		case ',':
			Str[i]	= '\0';
			break;

		case '\n':
			Str[i]	= '\0';
			*Flag	= 1;
			break;
		}

		if(Str[i] == '\0')
			break;

		if((Str[i] != '#') && (Str[i] != ' '))
			i++;
	}
	return atoi(Str);
}

//�d���`�F�b�N�p�ɃL�[����������
struct STR
{
	char			Str[32];
	unsigned int	Key;
};


//�O���[�v�̖�����0��ǉ����邽�߂̕⏕�֐�
int	RoadGroup(ifstream &ifs, int ItemsAGroup, short *Group)
{
	int		i;
	int		j	= 0;
	int		c;
	int		Flag	= 0;

	char	Str[128];

	for(i = 0; i < ItemsAGroup; i++)
		Group[i]	= 0;

	i = 0;

	//�R�����g�s�Ƌ󔒍s��ǂݔ�΂�
	while(1)
	{
		Str[i]	= ifs.get();

		switch(Str[i])
		{
		case EOF:
			return -1;

		//�R�����g�s����ы󔒂̓ǂݔ�΂�
		case '#':
			while((c = ifs.get()) != '\n')
				;
			break;

		case ' ':
			break;

		case '\t':
		case ',':
			Str[i]	= '\0';
			Group[j++]	= atoi(Str);
			Flag	= 1;
			i		= 0;
			break;

		case '\n':
			Str[i]	= '\0';
			Group[j++]	= atoi(Str);
			break;
		}

		if(Str[i] == '\0')
			break;

		if(Flag)
			Flag	= 0;

		else if(Str[i] != '#')
			i++;
	}

	return 0;
}

//�v�f���J�E���g
int	Count(char *FileName)
{
	int			i	= 1;
	int			c;

	int			Flag	= 0;

	ifstream	ifs;

	ifs.open(FileName);
	if(ifs == NULL)
		return -1;

	printf("001:");

	//�R�����g�s�Ƌ󔒍s��ǂݔ�΂�
	while(1)
	{
		c	= ifs.get();

		switch(c)
		{
		case EOF:
			Flag	= 1;
			break;

		//�R�����g�s����ы󔒂̓ǂݔ�΂�
		case '#':
			while((c = ifs.get()) != '\n')
				;
			break;

		case ' ':
			break;

		case '\t':
		case ',':
			putchar('\t');
			break;

		case '\n':
			putchar('\n');
			i++;
			printf("%03d:", i);
			break;

		default:
			putchar(c);
		}

		if(Flag)
			break;
	}
	ifs.close();
	return 0;
}

//�Ȗ�ID����Ȗږ����擾
int	GetSubjectName(char *FileName, char (*Subjects)[32])
{
	ifstream	ifs;
	int			temp;
	int			Num_Elem;
	int			i;

	ifs.open(FileName);

	if(ifs == NULL)
		return -1;

	//�v�f��
	temp	= Road(ifs);

	if(temp <= 0)
	{
		ifs.close();
		return -1;
	}
	Num_Elem	= temp;

	for(i = 0; i < Num_Elem; i++)
	{
		temp	= Road(ifs, Subjects[i], 32);

//		for(int j = strlen(Subjects[i]); j < 15; j++)
//			Subjects[i][j]	= ' ';

//		Subjects[i][15]	= '\0';
/*
		if(temp < 0)
		{
			ifs.close();
			return -1;
		}
*/
	}

	ifs.close();
	return Num_Elem;
}



//�O���[�v�̖�����0��ǉ����ďo��
int	Grouping(char *FileName, int ItemsAGroup)
{
	short		*Group;
	int			i;
	ifstream	ifs;

	Group	= new short[ItemsAGroup];

	ifs.open(FileName);

	if(ifs == 0)
		return -1;

	//�����o��
	while(RoadGroup(ifs, ItemsAGroup, Group) != -1)
	{
		for(i = 0; i < ItemsAGroup; i++)
		{
			printf("%d", Group[i]);
			if(i != (ItemsAGroup - 1))
				putchar('\t');
		}

		putchar('\n');
	}

	ifs.close();
	delete[]	Group;

	return 0;
}


//�e�L�X�g�̏d���폜�Ɨv�f���J�E���g
int	Remark(char	*FileName, int mode = 0)
{
	ifstream		ifs;
	int				temp;
	char			Str[32];
	int				Key;
	int				a;

	int				i	= 0;
	int				j;
	int				k;

	int				ans;

	//�d���`�F�b�N�p�o�b�t�@
	STR			Strings[256];

	//�t�@�C���I�[�v��
	ifs.open(FileName);

	if(ifs == NULL)
		return -1;

	while(1)
	{
		temp	= Road(ifs, Str, 128);
		if(temp	== -1)
			break;

		Key = 0;
		a	= 1;
		//Key�̒l���v�Z
		for(j = 0; j < 4; j++)
		{
			for(k = 0; k < j; k++)
				a *= 256;

			Key	+= (unsigned)Str[j] * a;
		}

		Strings[i].Key	= Key;
		strcpy(Strings[i++].Str, Str);

		//�d���̃`�F�b�N
		for(j = 0; j < (i - 1); j++)
		{
			if(Strings[j].Key == Key)
			{
				ans	= 0;
				for(k = 0; Str[k] != '\0'; k++)
				{
					if(Str[k] != Strings[j].Str[k])
						ans++;
				}
				if(Strings[j].Str[k] != '\0')
					ans++;

				if(ans == 0)
					i--;
			}
		}
	}

	switch(mode)
	{
	//�d���폜�̂�
	case 0:
		printf("%d\n", i);
		for(j = 0; j < i; j++)
			printf("%s\n", Strings[j].Str);
		break;

	//�i���o�����O
	case 1:
		printf("%d\n", i);
		for(j = 0; j < i; j++)
			printf("%03d:%s\n", j + 1, Strings[j].Str);
		break;
	}

	ifs.close();

	return 0;
}

//���Ԋ���ID���當�����ɕϊ�
int	GetSubjectInfo(char *FileName)
{
	char	Subjects[512][32];
	int		Units[512];
	int		Num_Elem;
	int		temp;
	int		a;

	int		i	= 0;

	ifstream	ifs;

	ifs.open("Subjects.txt");
	temp	= Road(ifs);
	Num_Elem	= temp;

	if(Num_Elem <= 0)
		return -1;

	for(int j = 0; j < Num_Elem; j++)
	{
		//���Ƃ̎��Ԑ������o��
		temp		= Road(ifs);
		Units[j]	= temp;

		temp	= Road(ifs);	//��T�Ԃ̃R�}��
		temp	= Road(ifs);	//�z�u�\�e�[�u��
		temp	= Road(ifs);	//�����O���[�vID
		temp	= Road(ifs);	//�����O���[�vID
		temp	= Road(ifs);	//�N���X�O���[�vID
		temp	= Road(ifs);	//�]�������e�[�u��
	}
	ifs.close();

	Num_Elem	= GetSubjectName(FileName, Subjects);
	if(Num_Elem <= 0)
		return -1;

	while(1)
	{
		temp	= Road(&a);

		if(temp == -3)
			break;

		if((temp > Num_Elem) || (temp < -2))
		{
			printf("%d", temp);
			printf("Invalid ID\n");
		}

		else// if(temp != 0)
			i++;

		if(temp == -2)
			printf("\t\t");

		if(temp > 0)
		{
			printf("%s\t", Subjects[temp - 1]);
			for(j = 1; j < Units[temp - 1]; j++)
				printf("\t");
		}

		else if(temp == -1)
			printf("�x\t");

		if(a)
			putchar('\n');
	}

	return 0;
}

int	main(int argc, char *argv[])
{
	int	i	= 0;

	if(argc > 2)
	{
		if(atoi(argv[2]) == 2)
			Grouping(argv[1], atoi(argv[3]));

		else if(atoi(argv[2]) == 3)
			printf("%d\n", Count(argv[1]));

		else if(atoi(argv[2]) == 4)
			GetSubjectInfo(argv[1]);

		else if(atoi(argv[2]) == 5)
			Count(argv[1]);
		
		else
			Remark(argv[1], atoi(argv[2]));
	}

	else if(argc > 1)
		Remark(argv[1]);

	else
		return 0;

	return 0;
}



