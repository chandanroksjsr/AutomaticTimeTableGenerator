
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include"Constant.h"



//��`�q�v�[��
class GENETIC_POOL{
private:
	//�p�����[�^�[
	int	MaxGeneration;							//�ő吢�㐔�B���̐��ɒB������v�Z���I��

	//��`�q�v�[���ւ̃|�C���^
	short	(*lpParent)[GENE_LENGTH];
	short	(*lpChild)[GENE_LENGTH];

	//����󋵊Ǘ�
	int	MaxScore;								//���̐���̈�`�q�̍ō��]���_
	int	MeanScore;								//���σX�R�A
	int	TotalScore;								//��`�q�S�̂̕]���l�̍��v�l
	int	Generation;								//���㐔

	//�\�[�g���\�b�h
	void	Quick_Sort(short **a, int min, int max);
	int		Pertition(short **a, int min, int max);


protected:
	short	Superior[BEST][GENE_LENGTH];		//�D�ǌ̂�ێ�����z��B�ێ�����̐���萔�Ƃ��Đݒ�

	//��`�q�Ǘ�
	short	Pool1[POPULATION][GENE_LENGTH];		//��`�q�z��
	short	Pool2[POPULATION][GENE_LENGTH];		//��`�q�z��
	short	*SortedPool[POPULATION];			//�]���_�̏��Ԃɕ��ёւ���ꂽ��`�q�ւ̃|�C���^

	//�v�Z���\�b�h
	virtual int			Evaluation(short *Gene)		= 0;	//��`�q�̕]�����\�b�h
	virtual OPERATION	Selection(int *a, int *b)	= 0;	//�I���֐�

	//��`�q����(���̑���ň�`�q���������)
	int					Copy(short *PA, short *PB, short *CA, short *CB);				//��`�q���R�s�[
	virtual int			Crossover(short *PA, short *PB, short *CA, short *CB)	= 0;	//�����֐�
	virtual int			Mutation(short *PA, short *PB, short *CA, short *CB)	= 0;	//�ˑR�ψ�

	//��`�q�̕]���_���擾
	virtual int			GetScore(short *Gene)	= 0;

	int		SortGenePool();		//��`�q�v�[�����\�[�g
	int		UpdateGene();		//�D�ǈ�`�q��o�^

	//�I�u�W�F�N�g�ԑ�����֎~
	GENETIC_POOL(const GENETIC_POOL &a);
	GENETIC_POOL& operator=(GENETIC_POOL &a);


public:
	GENETIC_POOL(int Generation);

	//�����W�c����
	virtual int			InitGenePool()				= 0;

	//�ꐢ����v�Z
	int	Calculate();

	//��`�q��ێ������܂ܐݒ�ύX
	int	Reset();

	//�X�e�[�^�X�Ď�	
	int	GetMaxScore(){return MaxScore;};					//�ō��_���擾
	int	GetMeanScore(){return MeanScore;};					//���ϓ_���擾
	int	GetTotal(){return TotalScore;};						//��`�q�S�̂̓��_���擾
	int	GetGeneration(){return Generation;};				//���㐔���擾

	//��`�q����ւ��n
	int	GetBestGene(short (*Gene)[GENE_LENGTH]);			//�D�ǌ̂��擾
	int	GetGenePool(short (*Gene)[GENE_LENGTH]);			//��`�q�v�[�����擾
	int	SetGenePool(short (*Gene)[GENE_LENGTH]);			//��`�q�v�[�������ւ��i�O���b�h�Ƃ̘A�g�j
};

int	cmp(const void *a, const void *b);