

//���Ԋ��\�̑傫��
const int	LECTURES_A_DAY		= 8;							//����̎��Ɛ�
const int	SCHOOLDAY			= 5;							//��T�Ԃ̓o�Z��
const int	LECTURES_A_WEEK		= LECTURES_A_DAY * SCHOOLDAY;	//�P�N���X�̎��Ƃ̃R�}��
const int	NUM_CLASS			= 25;							//�����N���X��

const int	NUM_SUBJECT			= LECTURES_A_WEEK * NUM_CLASS;


//��`�q�֌W�̒萔
//��`�q��
const int	GENE_ARRAY			= NUM_SUBJECT;					//��`�q�z��̒���
const int	SCORE_ARRAY			= 4;							//�]���_���������ޔz��̑傫��
const int	GENE_LENGTH			= GENE_ARRAY + SCORE_ARRAY;		//��`�q�̑���
//const int	MAX_GENERATION		= 500;							//�v�Z���鐢�㐔

//��`�q�v�[���̑傫��
const int	POPULATION	= 256;

//�ێ�����D�ǈ�`�q�̐�
const int	BEST		= 20;

//��`�q�ɑ΂��鑀����
enum OPERATION{COPY = 0, CROSSOVER = 1, MUTATE = 2};

//��`�q�ɑ΂��鑀�삻�ꂼ�ꂪ���s�����m��
const int	MUTATION_RATE	= 10;
const int	CROSSOVER_RATE	= 75;
const int	COPY_RATE		= 15;

//�O���[�v�ɓo�^����鐔�̏��
const int	ROOMS_A_GROUP		= 5;
const int	TEACHERS_A_GROUP	= 20;
const int	CLASSES_A_GROUP		= 5;
const int	ATTRIBUTES_A_GROUP	= 5;

//�O���[�v��
const int	NUM_ROOM_GROUP		= NUM_SUBJECT;
const int	NUM_TEACHER_GROUP	= NUM_SUBJECT;
const int	NUM_CLASS_GROUP		= NUM_SUBJECT;

const int	MAX_TEACHER_NUM		= ROOMS_A_GROUP * NUM_ROOM_GROUP;
const int	MAX_ROOM_NUM		= TEACHERS_A_GROUP * NUM_TEACHER_GROUP;