
#include"TimeTable.h"
#include<iostream>
#include<fstream>

using namespace std;

//�Ȗڃf�[�^�̂��Ƃ�̂��߂̃C���^�[�t�F�C�X


int RoadSubjects(SUBJECT *Subjects);								//�Ȗڃf�[�^��ǂݍ���

//�O���[�v�e�[�u���ǂݍ���
int	RoadTeacherGroup(short (*Teachers)[TEACHERS_A_GROUP]);			//�����O���[�v�e�[�u��
int	RoadRoomGroup(short (*Rooms)[ROOMS_A_GROUP]);					//�����O���[�v�e�[�u��
int	RoadClassGroup(short (*Classes)[CLASSES_A_GROUP]);				//�N���X�O���[�v�e�[�u��
int	RoadEvaluationTable(short (*Attributes)[ATTRIBUTES_A_GROUP]);	//�]���̂��߂̃f�[�^�e�[�u��
int	RoadEvaluationAtb(EVALUATION_ATTRIBUTES *AllocTable);			//�]�������f�[�^

int	RoadSubTable(short (*TimeTable)[LECTURES_A_WEEK]);				//�z�u�ςݎ��Ԋ��f�[�^
