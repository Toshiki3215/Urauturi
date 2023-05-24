#pragma once
#include <math.h>
#include <time.h>
#include "mapchip.h"
#define MAX_BULLET	1
#define PI		3.14159

// ----- ----- 列挙体 ----- ----- 
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

// ----- ----- 構造体 ----- ----- 

//プレイヤー
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

//プレイヤー、マウスポインター
Player pointer =
{
	16,
	16,
	5,
	0,
	0
};

//エネミー
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

//ゴール
typedef struct Goal
{
	int x;
	int y;
	int w;
	int h;
}Goal;

//チュートリアルのゴール
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


//ステージ選択画面(ドア)
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

// ----- ----- その他変数 ----- ----- 

//仮スピード
int provisionalSpeed = 4;
int provisionalJumpSpeed = 1;

//プレイヤーのマップチップ座標
//左上
int leftTopX = (player.x - player.r) / blockSize;
int leftTopY = (player.y - player.r) / blockSize;
//左下
int leftBottomX = (player.x - player.r) / blockSize;
int leftBottomY = (player.y + player.r - 1) / blockSize;
//右上
int rightTopX = (player.x + player.r - 1) / blockSize;
int rightTopY = (player.y - player.r) / blockSize;
//右下
int rightBottomX = (player.x + player.r - 1) / blockSize;
int rightBottomY = (player.y + player.r - 1) / blockSize;

//重力
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

//仮値
int i;

//自機と敵機の接触
bool PEcollision = 0;

//ゴールとの当たり判定
bool GLcollision = 0;
bool isGoal = 0;

//マウス
int mouseX;
int mouseY;

//ジャンプ用変数
int jumpspeed = 16;
int isJump = 0;
int playerBottomY = 0;
int playerBottomMapY = 0;
int playerTopY = 0;
int playerTopMapY = 0;

//アニメーション用変数
int playerAnimationTimer = 25;

//アニメーションフラグ
bool isAnimation = 0;
int peraAnimeTimer = 42;

bool isReverseAnimation = 0;

int tekisutoTimer = 20;

//エネミーフラグ
bool isEnemy = 0;

//リセットフラグ
bool isReset = 0;

bool isDoorAnime[5] = {0};
int doorAnimeTimer = 70;

//シーン切り替え(99 = タイトル,0 = ステージ選択,1 or 2 = チュートリアルステージ)
int scene = 99;

//文字の色
const int cr = GetColor(0, 0, 0);

// ----- ----- 関数 ----- ----- 
//ゴールの当たり判定
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
