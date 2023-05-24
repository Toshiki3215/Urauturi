#pragma once
#include <math.h>
#include <time.h>
#include "mapchip.h"
#define MAX_BULLET	1
#define PI		3.14159

// ----- ----- �񋓑� ----- ----- 
enum MapInfo
{
	NONE,
	STAGE,
	BLOCK,
	NEEDL,
	YOKOLASER,
	TATELASER,
	LASERPOINT_X,
	LASERPOINT_Y
};

// ----- ----- �\���� ----- ----- 

//�v���C���[
typedef struct Player
{
	int x;
	int y;
	int r;
	int speedX;
	int speedY;
	int isAllive;
}Player;

Player player =
{
	96,
	480,
	16,
	0,
	0,
	1
};

int oldPlayerFront = 0;
int oldPlayerBack = 0;

//�v���C���[�A�}�E�X�|�C���^�[
Player pointer =
{
	16,
	16,
	5,
	0,
	0
};

//�G�l�~�[
typedef struct Enemy
{
	int x;
	int y;
	int x2;
	int y2;
	int r;
	int speedX;
	int speedY;
	bool flag;
	double angle;
}Enemy;

Enemy enemy =
{
	1450,
	800,
	32,
	32,
	16,
	4,
	4,
	0,
	0
};

//�S�[��
typedef struct Goal
{
	int x;
	int y;
	int w;
	int h;
}Goal;

//�`���[�g���A���̃S�[��
Goal cGoal =
{
	1568,
	416,
	32,
	64
};

Goal goal =
{
	1504,
	736,
	32,
	64
};

Goal goal2 =
{
	224,
	864,
	32,
	64
};


//�X�e�[�W�I�����(�h�A)
typedef struct Gate
{
	int startX;
	int endX;
}Gate;

Gate door[5] =
{
	{32,96},
	{320,384},
	{640,704},
	{992,1056},
	{1408,1472}
};

int doorStartY = 512;
int doorEndY = 640;

// ----- ----- ���̑��ϐ� ----- ----- 

//���X�s�[�h
int provisionalSpeed = 4;
int provisionalJumpSpeed = 1;

//�v���C���[�̃}�b�v�`�b�v���W
//����
int leftTopX = (player.x - player.r) / blockSize;
int leftTopY = (player.y - player.r) / blockSize;
//����
int leftBottomX = (player.x - player.r) / blockSize;
int leftBottomY = (player.y + player.r - 1) / blockSize;
//�E��
int rightTopX = (player.x + player.r - 1) / blockSize;
int rightTopY = (player.y - player.r) / blockSize;
//�E��
int rightBottomX = (player.x + player.r - 1) / blockSize;
int rightBottomY = (player.y + player.r - 1) / blockSize;

//�d��
int g = 0;
bool isGravity = 1;
int jumpCount = 2;
int jumpHeight = 0;
int playerBottomYInfo;
int playerBottomYMaptip;
int playerBottomYHeightPlus;
int playerBottomYMaptipPlus;
int playerTopYInfo;
int playerTopYMaptip;
int playerTopYHeight;

//���l
int i;

//���@�ƓG�@�̐ڐG
bool PEcollision = 0;

//�S�[���Ƃ̓����蔻��
bool GLcollision = 0;
bool isGoal = 0;

//�}�E�X
int mouseX;
int mouseY;

//�W�����v�p�ϐ�
int jumpspeed = 16;
int isJump = 0;
int playerBottomY = 0;
int playerBottomMapY = 0;
int playerTopY = 0;
int playerTopMapY = 0;

//�A�j���[�V�����p�ϐ�
int playerAnimationTimer = 25;

//�A�j���[�V�����t���O
bool isAnimation = 0;
int peraAnimeTimer = 42;

bool isReverseAnimation = 0;

int tekisutoTimer = 20;

//�G�l�~�[�t���O
bool isEnemy = 0;

//���Z�b�g�t���O
bool isReset = 0;

bool isDoorAnime[5] = {0};
int doorAnimeTimer = 70;

//�V�[���؂�ւ�(99 = �^�C�g��,0 = �X�e�[�W�I��,1 or 2 = �`���[�g���A���X�e�[�W)
int scene = 99;

//�����̐F
const int cr = GetColor(0, 0, 0);

// ----- ----- �֐� ----- ----- 
//�S�[���̓����蔻��
bool GetGLcollision(Goal goal, Player player)
{
	if (goal.x <= player.x + player.r && player.x - player.r <= goal.x + goal.w)
	{
		if (goal.y < player.y + player.r && player.y - player.r <= goal.y + goal.h)
		{
			return 1;
		}
	}
	return 0;
}
