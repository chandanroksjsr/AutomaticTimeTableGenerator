
#include<iostream>
#include<fstream>

using namespace std;

//�f�[�^���[�h�⏕�֐�
int Road(ifstream &ifs, char *Str, int limit);

int RoadSubjects(char *FileName);			//�Ȗڃf�[�^��ǂݍ���

//�O���[�v�e�[�u���ǂݍ���
int	RoadTeacherGroup(char *FileName);		//�����O���[�v�e�[�u��
int	RoadRoomGroup(char *FileName);			//�����O���[�v�e�[�u��
int	RoadClassGroup(char *FileName);			//�N���X�O���[�v�e�[�u��
int	RoadEvaluationTable(char *FileName);	//�]���̂��߂̃f�[�^�e�[�u��
int	RoadEvaluationAtb(char *FileName);		//�]���f�[�^�ǂݍ���

//�z�u�ςݎ��Ԋ��ǂݍ���
int	RoadSubTable(char *FileName);			//�z�u�ςݎ��Ԋ��ǂݍ���