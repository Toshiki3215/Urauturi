#include "DxLib.h"
#include "Window.h"
#include "struct.h"
#include "mapchip.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {

	WindowSetteings();

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	//�u���b�N���\�[�X
	int block = LoadGraph("picture/Block.png");
	int block2 = LoadGraph("picture/Stage.png");
	int uraBlock = LoadGraph("picture/StageUra.png");
	int block3 = LoadGraph("picture/EnemyBlock.png");

	//�{
	int bookTex = LoadGraph("picture/book.png");

	//���[�U�[���\�[�X
	int laserpointX = LoadGraph("picture/ink.png");
	int laserpointY = LoadGraph("picture/verticalink.png");
	int laserX = LoadGraph("picture/horizonllaser.png");
	int laserY = LoadGraph("picture/verticallaser.png");

	//�M�̃��\�[�X
	int hudeTex = LoadGraph("picture/fude.png");

	//�^�C�g��
	int title = LoadGraph("picture/title.png");

	//�X�e�[�W�I���A���\�[�X
	int stageTex0 = LoadGraph("picture/moji1.png");
	int stageTex1 = LoadGraph("picture/senntaku1.png");
	int stageTex2 = LoadGraph("picture/moji2.png");
	int stageTex3 = LoadGraph("picture/moji3.png");
	int stageTex4 = LoadGraph("picture/moji4.png");
	int stageTex5 = LoadGraph("picture/moji5.png");
	int stageTex6 = LoadGraph("picture/moji6.png");
	int stageTex7 = LoadGraph("picture/moji7.png");
	int stageTex8 = LoadGraph("picture/moji8.png");

	int GoalTexBack = LoadGraph("picture/clear.png");

	//�v���C���[�A�j���[�V����
	int playerWaitTex[5];
	LoadDivGraph("picture/hito_wait.png", 5, 5, 1, 32, 32, playerWaitTex);

	int playerWalkRightTex[5];
	LoadDivGraph("picture/hito_walk2.png", 5, 5, 1, 32, 32, playerWalkRightTex);

	int playerWalkLeftTex[5];
	LoadDivGraph("picture/hito_walk_left.png", 5, 5, 1, 32, 32, playerWalkLeftTex);

	int backGround = LoadGraph("picture/ROTARY WHITE MAPLE.jpg");

	int hole = LoadGraph("picture/circle.png");

	int peraAnime[14];
	LoadDivGraph("picture/nextpage.png", 14, 14, 1, 1600, 960, peraAnime);

	//�h�A�A�S�[�����\�[�X
	int doorTex[7];
	LoadDivGraph("picture/open3.png", 7, 7, 1, 128, 128, doorTex);
	int goalTex = LoadGraph("picture/door_goal.png");

	//�`���[�g���A���e�L�X�g
	int tekisuto[2];
	LoadDivGraph("picture/memo.png", 2, 2, 1, 400, 400, tekisuto);

	int titlebgm;
	titlebgm = LoadSoundMem("music/m1.mp3");
	ChangeVolumeSoundMem(210, titlebgm);

	int gamebgm;
	gamebgm = LoadSoundMem("music/n57.mp3");
	ChangeVolumeSoundMem(120, gamebgm);

	int jumpse;
	jumpse = LoadSoundMem("music/jump06.mp3");
	ChangeVolumeSoundMem(150, jumpse);

	int doorse;
	doorse = LoadSoundMem("music/9ad3fb07d44fb37c.mp3");
	ChangeVolumeSoundMem(100, doorse);

	int clearse;
	clearse = LoadSoundMem("music/43db0965c1eb6b27.mp3");

	int nextpagese;
	nextpagese = LoadSoundMem("music/ada609dbdd34d26f.mp3");

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		//�X�s�[�h��0��
		player.speedX = 0;
		player.speedY = 0;

		//�}�E�X�|�C���^���W
		GetMousePoint(&mouseX, &mouseY);
		pointer.x = mouseX;
		pointer.y = mouseY;

		if ((GetMouseInput() & MOUSE_INPUT_RIGHT) && isEnemy == 1)
		{
			isEnemy = 0;
		}
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) && isEnemy == 0)
		{
			isEnemy = 1;
		}

		//�V�[��99(�^�C�g��)
		if (scene == 99)
		{
			//�^�C�g��
			if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0 ||
				keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
			{
				scene = 0;
				player.x = 80;
				player.y = 480;
			}
		}

		//�@�[�|�|�|�|�@�V�[��0(�X�e�[�W�I�����)�@�[�|�|�|�|�@
		if (scene == 0)
		{
			if (player.x - player.r > 0)
			{
				if (keys[KEY_INPUT_LEFT] == 1 || keys[KEY_INPUT_A] == 1)
				{
					leftTopX = ((player.x - provisionalSpeed) - player.r) / blockSize;
					leftBottomX = ((player.x - provisionalSpeed) - player.r) / blockSize;
					if (map0[leftTopY][leftTopX] == NONE && map0[leftBottomY][leftBottomX] == NONE)
					{
						player.speedX = -4;
					}
				}
			}
			if (player.x + player.r < WIN_WIDTH - 64)
			{
				if (keys[KEY_INPUT_RIGHT] == 1 || keys[KEY_INPUT_D] == 1)
				{
					rightTopX = ((player.x + provisionalSpeed) + player.r - 1) / blockSize;
					rightBottomX = ((player.x + provisionalSpeed) + player.r - 1) / blockSize;
					if (map0[rightTopY][rightTopX] == NONE && map0[rightBottomY][rightBottomX] == NONE)
					{
						player.speedX = 4;
					}
				}
			}

			//�@�[�|�|�|�|�@�[�|�|�|�|�@�W�����v�@�[�|�|�|�|�@�[�|�|�|�|�@

			//�d�͏��������邽�߁A�}�b�v�`�b�v���W�̎�����ς���B
			//�E��
			rightTopX = (player.x + player.r - 1) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			//����
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			//�E��
			rightBottomX = (player.x + player.r - 1) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;
			//����
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			//���Ƀu���b�N���Ȃ���Η������鏈��
			if (map0[leftBottomY][leftBottomX] == NONE && map0[rightBottomY][rightBottomX] == NONE && isGravity == 1)
			{
				if (player.y + player.r <= WIN_HEIGHT)
				{

					if (isJump == 0)
					{
						g--;

						player.y -= g;

						if (g < -10)
						{
							g = -10;
						}
					}
				}
			}

			//�v���C���[�̃W�����v
			if (jumpCount > 0)
			{
				if (map0[leftTopY][leftTopX] == NONE || map0[rightTopY][rightTopX] == NONE)
				{
					if (keys[KEY_INPUT_W] == 1 && oldkeys[KEY_INPUT_W] == 0 || keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
					{
						PlaySoundMem(jumpse, DX_PLAYTYPE_BACK, true);
						isJump = 1;
						g = 0;
						jumpCount -= 1;
						jumpHeight = 16;
					}
				}
			}

			//�W�����v�̎d�g��
			if (jumpCount < 2)
			{
				if (isJump == 1)
				{
					jumpHeight--;
					if (jumpHeight < -8)
					{
						jumpHeight = -8;
					}
					player.y -= jumpHeight;
				}
			}

			//�n�ʂɒ��n������ēx�W�����v�ł���悤�ɂ���
			if (jumpCount == 0)
			{
				if (map0[leftBottomY][leftBottomX] != NONE || map0[rightBottomY][rightBottomX] != NONE)
				{
					jumpCount = 2;
				}
			}

			//���݈ʒu�̒�ӂ̏��
			playerBottomYInfo = player.y + player.r - 1;

			//�����݈ʒu�̒�ӂ̃}�b�v�`�b�v���(��ӂ̏�񂩂�}�b�v�`�b�v��ł̂ǂ̐����ɂ��邩���v�Z����)
			playerBottomYMaptip = (player.y + player.r - 1) / blockSize;

			//���ݒn���P����y���W�B���@�̒�ӂ̍��W�͈���̍����y���W�ɂȂ邽�߁B(���2�s����}�b�v��̎��@�̐�������ꂽ�̂ŁA�Œ肷��ʒu���w�肵�ău���b�N�T�C�Y�������Ă�����)
			playerBottomYHeightPlus = (playerBottomYMaptip + 1) * blockSize;

			//���ݒn���P���̃}�b�v�`�b�v�̏��
			playerBottomYMaptipPlus = (playerBottomYHeightPlus / blockSize);

			//���݈ʒu�̒��_�̏�� 
			playerTopYInfo = player.y - player.r;

			//���݈ʒu�̒��_�̃}�b�v�`�b�v���
			playerTopYMaptip = (player.y - player.r) / blockSize;

			//���_�����l�ɌŒ肷�邽�߂�y���W���o�����߂�y���W�����߂�B
			playerTopYHeight = (playerTopYMaptip + 1) * blockSize;

			//���W���ړ��������̂ŁA������x�e�S�̊p�̍��W���v�Z����B
			//�E��
			rightTopX = (player.x + player.r - 1) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			//����
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			//�E��
			rightBottomX = (player.x + player.r - 1) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;
			//����
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			//���ł���Ƃ�
			if (jumpCount < 3)
			{
				//������Ńu���b�N�ɂԂ��������̏���
				if (player.y <= (playerBottomYHeightPlus - player.r))
				{
					if (map0[leftTopY][leftTopX] != NONE || map0[rightTopY][rightTopX] != NONE)
					{
						jumpHeight = 0;
						isJump = 0;
					}
				}
			}

			//�������Ńu���b�N�ɂԂ��������̏���
			if (map0[leftBottomY][leftBottomX] != NONE || map0[rightBottomY][rightBottomX] != NONE)
			{
				player.y = playerTopYHeight - player.r;

				g = 0;
				isJump = 0;
				jumpCount = 2;
				jumpHeight = 25;
			}
			if (player.y >= (WIN_HEIGHT - 1) * blockSize - player.r)
			{
				player.y = (WIN_HEIGHT - 1) * blockSize - player.r;
				jumpCount = 2;
				jumpHeight = 25;
				isJump = 0;
			}

			//�h�A(�X�e�[�W�I��)�̏���
			for (int i = 0; i < 5; i++)
			{
				if (player.y - player.r < doorEndY && doorStartY < player.y + player.r)
				{
					if (player.x - player.r < door[i].endX && door[i].startX < player.x + player.r)
					{
						PlaySoundMem(doorse, DX_PLAYTYPE_BACK, true);
						//�^�C�g����
						if (player.x - player.r < door[0].endX && door[0].startX < player.x + player.r)
						{
							if (keys[KEY_INPUT_E] == 1 && oldkeys[KEY_INPUT_E] == 0)
							{
								scene = 99;
								player.x = 80;
								player.y = 480;
							}
						}
						//�`���[�g���A����
						if (player.x - player.r < door[1].endX && door[1].startX < player.x + player.r)
						{
							if (keys[KEY_INPUT_E] == 1 && oldkeys[KEY_INPUT_E] == 0)
							{
								scene = 1;
								isReset = 1;
							}
						}
						//�X�e�[�W1��
						if (player.x - player.r < door[2].endX && door[2].startX < player.x + player.r)
						{
							if (keys[KEY_INPUT_E] == 1 && oldkeys[KEY_INPUT_E] == 0)
							{
								scene = 3;
								isReset = 1;
							}
						}
						//�X�e�[�W2��
						if (player.x - player.r < door[3].endX && door[3].startX < player.x + player.r)
						{
							if (keys[KEY_INPUT_E] == 1 && oldkeys[KEY_INPUT_E] == 0)
							{
								scene = 5;
								isReset = 1;
							}
						}
						//�X�e�[�W3��
						if (player.x - player.r < door[4].endX && door[4].startX < player.x + player.r)
						{
							if (keys[KEY_INPUT_E] == 1 && oldkeys[KEY_INPUT_E] == 0)
							{
								scene = 7;
								isReset = 1;
							}
						}
					}
				}
			}
		}


		for (int i = 0; i < 5; i++)
		{
			if (player.y - player.r < doorEndY && doorStartY < player.y + player.r)
			{
				if (player.x - player.r < door[i].endX && door[i].startX < player.x + player.r)
				{
					isDoorAnime[i] = 1;
				}
				else
				{
					isDoorAnime[i] = 0;
				}

				if (isDoorAnime[i] == 1)
				{
					doorAnimeTimer -= 1;
					if (doorAnimeTimer == 0)
					{
						isDoorAnime[i] = 0;
						doorAnimeTimer = 70;
					}
				}
			}
		}


		// ---------- ---------- �`���[�g���A���X�e�[�W_�n�� ---------- ---------- 
		//�V�[���P(�\)
		if (scene == 1)
		{
			//�G�A�}�E�X�Ǐ]
			if (isEnemy == 1)
			{
				if (pointer.x > 0 && pointer.x < WIN_WIDTH && pointer.y>0 && pointer.y < WIN_HEIGHT)
				{
					for (i = 0; i < MAX_BULLET; i++)
					{
						enemy.speedX = (int)(cos(enemy.angle) * 3.0);
						enemy.speedY = (int)(sin(enemy.angle) * 3.0);
						int a = enemy.x - pointer.x;
						int b = enemy.y - pointer.y;
						int c = pointer.r + enemy.r;
						if ((c * c) >= (a * a) + (b * b) && enemy.flag == 1)
						{
							if (enemy.flag == 1)
							{
								PEcollision = 1;
							}
						}

						//�ǔ�����
						double ax, ay, bx, by;
						bx = cos(enemy.angle);
						by = sin(enemy.angle);
						ax = pointer.x - (enemy.x);
						ay = pointer.y - (enemy.y);

						enemy.angle += (ax * by - ay * bx < 0.0) ? +PI / 180 * 8 : -PI / 180 * 8;

						// �ړ�����
						enemy.x += enemy.speedX;
						enemy.y += enemy.speedY;
					}
				}

				//�G
				int uy = enemy.y;
				int ux = enemy.x;
				if (map[uy / blockSize][ux / blockSize] == NONE)
				{
					map[uy / blockSize][ux / blockSize] = 2;
				}
				if (map2[uy / blockSize][49 - ux / blockSize] == NONE)
				{
					map2[uy / blockSize][49 - ux / blockSize] = 2;
				}
			}

			//�`���[�g���A���A�j���[�V����
			tekisutoTimer -= 1;
			if (tekisutoTimer == 0)
			{
				tekisutoTimer = 20;
			}

			//�}�b�v�`�b�v�̓����蔻��
			if (player.x - player.r > 0)
			{
				if (keys[KEY_INPUT_LEFT] == 1 || keys[KEY_INPUT_A] == 1)
				{
					leftTopX = ((player.x - provisionalSpeed) - player.r) / blockSize;
					leftBottomX = ((player.x - provisionalSpeed) - player.r) / blockSize;
					if (map[leftTopY][leftTopX] == NONE && map[leftBottomY][leftBottomX] == NONE)
					{
						player.speedX = -4;
					}
				}
			}
			if (player.x + player.r < WIN_WIDTH - 64)
			{
				if (keys[KEY_INPUT_RIGHT] == 1 || keys[KEY_INPUT_D] == 1)
				{
					rightTopX = ((player.x + provisionalSpeed) + player.r - 1) / blockSize;
					rightBottomX = ((player.x + provisionalSpeed) + player.r - 1) / blockSize;
					if (map[rightTopY][rightTopX] == NONE && map[rightBottomY][rightBottomX] == NONE)
					{
						player.speedX = 4;
					}
				}
			}

			//�W�����v
			//�d�͏��������邽�߁A�}�b�v�`�b�v���W�̎�����ς���B
			//�E��
			rightTopX = (player.x + player.r - 1) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			//����
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			//�E��
			rightBottomX = (player.x + player.r - 1) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;
			//����
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			//���Ƀu���b�N���Ȃ���Η������鏈��
			if (map[leftBottomY][leftBottomX] == NONE && map[rightBottomY][rightBottomX] == NONE && isGravity == 1)
			{
				if (player.y + player.r <= WIN_HEIGHT)
				{
					if (isJump == 0)
					{
						g--;
						player.y -= g;
						if (g < -10)
						{
							g = -10;
						}
					}
				}
			}

			//�v���C���[�̃W�����v
			if (jumpCount > 0)
			{
				if (map[leftTopY][leftTopX] == NONE || map[rightTopY][rightTopX] == NONE)
				{
					if (keys[KEY_INPUT_W] == 1 && oldkeys[KEY_INPUT_W] == 0 || keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
					{
						PlaySoundMem(jumpse, DX_PLAYTYPE_BACK, true);
						isJump = 1;
						g = 0;
						jumpCount -= 1;
						jumpHeight = 16;
					}
				}
			}
			//�W�����v�̎d�g��
			if (jumpCount < 2)
			{
				if (isJump == 1)
				{
					jumpHeight--;
					if (jumpHeight < -8)
					{
						jumpHeight = -8;
					}

					player.y -= jumpHeight;
				}
			}

			//�n�ʂɒ��n������ēx�W�����v�ł���悤�ɂ���
			if (jumpCount == 0)
			{
				if (map[leftBottomY][leftBottomX] != NONE || map[rightBottomY][rightBottomX] != NONE)
				{

					jumpCount = 2;
				}
			}

			//���݈ʒu�̒�ӂ̏��
			playerBottomYInfo = player.y + player.r - 1;
			//�����݈ʒu�̒�ӂ̃}�b�v�`�b�v���(��ӂ̏�񂩂�}�b�v�`�b�v��ł̂ǂ̐����ɂ��邩���v�Z����)
			playerBottomYMaptip = (player.y + player.r - 1) / blockSize;

			//���ݒn���P����y���W�B���@�̒�ӂ̍��W�͈���̍����y���W�ɂȂ邽�߁B(���2�s����}�b�v��̎��@�̐�������ꂽ�̂ŁA�Œ肷��ʒu���w�肵�ău���b�N�T�C�Y�������Ă�����)
			playerBottomYHeightPlus = (playerBottomYMaptip + 1) * blockSize;
			//���ݒn���P���̃}�b�v�`�b�v�̏��
			playerBottomYMaptipPlus = (playerBottomYHeightPlus / blockSize);

			//���݈ʒu�̒��_�̏�� 
			playerTopYInfo = player.y - player.r;
			//���݈ʒu�̒��_�̃}�b�v�`�b�v���
			playerTopYMaptip = (player.y - player.r) / blockSize;
			//���_�����l�ɌŒ肷�邽�߂�y���W���o�����߂�y���W�����߂�B
			playerTopYHeight = (playerTopYMaptip + 1) * blockSize;

			//���W���ړ��������̂ŁA������x�e�S�̊p�̍��W���v�Z����B
			//�E��
			rightTopX = (player.x + player.r - 1) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			//����
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			//�E��
			rightBottomX = (player.x + player.r - 1) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;
			//����
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			//���ł���Ƃ�
			if (jumpCount < 3)
			{
				//������Ńu���b�N�ɂԂ��������̏���
				if (player.y <= (playerBottomYHeightPlus - player.r))
				{
					if (map[leftTopY][leftTopX] != NONE || map[rightTopY][rightTopX] != NONE)
					{
						jumpHeight = 0;
						isJump = 0;
					}
				}
			}

			//�������Ńu���b�N�ɂԂ��������̏���
			if (map[leftBottomY][leftBottomX] != NONE || map[rightBottomY][rightBottomX] != NONE)
			{
				player.y = playerTopYHeight - player.r;
				g = 0;
				isJump = 0;
				jumpCount = 2;
				jumpHeight = 25;
			}

			if (player.y >= (WIN_HEIGHT - 1) * blockSize - player.r)
			{
				player.y = (WIN_HEIGHT - 1) * blockSize - player.r;
				jumpCount = 2;
				jumpHeight = 25;
				isJump = 0;
			}
		}

		//�V�[���؂�ւ�
		if (player.x >= 1500 && scene == 1)
		{
			if (keys[KEY_INPUT_E] == 1 && oldkeys[KEY_INPUT_E] == 0)
			{
				PlaySoundMem(nextpagese, DX_PLAYTYPE_BACK, true);
				isAnimation = 1;
				oldPlayerFront = player.y;
			}
		}

		if (isAnimation == 1 && scene == 1)
		{
			peraAnimeTimer -= 1;
			if (peraAnimeTimer == 0 && scene == 1)
			{
				isAnimation = 0;
				player.x = 48;
				player.y = oldPlayerFront;
				scene = 2;
				peraAnimeTimer = 42;
			}
		}

		if (player.x <= 16 && scene == 2)
		{
			if (keys[KEY_INPUT_E] == 1 && oldkeys[KEY_INPUT_E] == 0)
			{
				PlaySoundMem(nextpagese, DX_PLAYTYPE_BACK, true);
				isReverseAnimation = 1;
				oldPlayerBack = player.y;
			}
		}

		if (isReverseAnimation == 1 && scene == 2)
		{
			peraAnimeTimer -= 1;
			if (peraAnimeTimer == 0 && scene == 2)
			{
				isReverseAnimation = 0;
				player.x = 1550;
				player.y = oldPlayerBack;
				scene = 1;
				peraAnimeTimer = 42;
			}
		}

		//�V�[��2(��)
		if (scene == 2 && isGoal == 0)
		{
			int uy = enemy.y;
			int ux = enemy.x;
			//map2[uy / blockSize][49 - ux / blockSize] = 2;

			//�}�b�v�`�b�v�̓����蔻��
			if (player.x - player.r > 0)
			{
				if (keys[KEY_INPUT_LEFT] == 1 || keys[KEY_INPUT_A] == 1)
				{
					leftTopX = ((player.x - provisionalSpeed) - player.r) / blockSize;
					leftBottomX = ((player.x - provisionalSpeed) - player.r) / blockSize;
					if (map2[leftTopY][leftTopX] == NONE && map2[leftBottomY][leftBottomX] == NONE)
					{
						player.speedX = -4;
					}
				}
			}
			if (player.x + player.r < WIN_WIDTH - 64)
			{
				if (keys[KEY_INPUT_RIGHT] == 1 || keys[KEY_INPUT_D] == 1)
				{
					rightTopX = ((player.x + provisionalSpeed) + player.r - 1) / blockSize;
					rightBottomX = ((player.x + provisionalSpeed) + player.r - 1) / blockSize;
					if (map2[rightTopY][rightTopX] == NONE && map2[rightBottomY][rightBottomX] == NONE)
					{
						player.speedX = 4;
					}
				}
			}

			//�W�����v
			//�d�͏��������邽�߁A�}�b�v�`�b�v���W�̎�����ς���B
			//�E��
			rightTopX = (player.x + player.r - 1) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			//����
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			//�E��
			rightBottomX = (player.x + player.r - 1) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;
			//����
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			//���Ƀu���b�N���Ȃ���Η������鏈��
			if (map2[leftBottomY][leftBottomX] == NONE && map2[rightBottomY][rightBottomX] == NONE && isGravity == 1)
			{
				if (player.y + player.r <= WIN_HEIGHT)
				{
					if (isJump == 0)
					{
						g--;

						player.y -= g;

						if (g < -10)
						{
							g = -10;
						}
					}
				}
			}

			//�v���C���[�̃W�����v
			if (jumpCount > 0)
			{
				if (map2[leftTopY][leftTopX] == NONE || map2[rightTopY][rightTopX] == NONE)
				{
					if (keys[KEY_INPUT_W] == 1 && oldkeys[KEY_INPUT_W] == 0 || keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
					{
						PlaySoundMem(jumpse, DX_PLAYTYPE_BACK, true);
						isJump = 1;
						g = 0;
						jumpCount -= 1;
						jumpHeight = 16;
					}
				}
			}
			//�W�����v�̎d�g��
			if (jumpCount < 2)
			{
				if (isJump == 1)
				{
					jumpHeight--;
					if (jumpHeight < -8)
					{
						jumpHeight = -8;
					}

					player.y -= jumpHeight;
				}
			}

			//�n�ʂɒ��n������ēx�W�����v�ł���悤�ɂ���
			if (jumpCount == 0)
			{
				if (map2[leftBottomY][leftBottomX] != NONE || map2[rightBottomY][rightBottomX] != NONE)
				{
					jumpCount = 2;
				}
			}

			//���݈ʒu�̒�ӂ̏��
			playerBottomYInfo = player.y + player.r - 1;
			//�����݈ʒu�̒�ӂ̃}�b�v�`�b�v���(��ӂ̏�񂩂�}�b�v�`�b�v��ł̂ǂ̐����ɂ��邩���v�Z����)
			playerBottomYMaptip = (player.y + player.r - 1) / blockSize;

			//���ݒn���P����y���W�B���@�̒�ӂ̍��W�͈���̍����y���W�ɂȂ邽�߁B(���2�s����}�b�v��̎��@�̐�������ꂽ�̂ŁA�Œ肷��ʒu���w�肵�ău���b�N�T�C�Y�������Ă�����)
			playerBottomYHeightPlus = (playerBottomYMaptip + 1) * blockSize;
			//���ݒn���P���̃}�b�v�`�b�v�̏��
			playerBottomYMaptipPlus = (playerBottomYHeightPlus / blockSize);

			//���݈ʒu�̒��_�̏�� 
			playerTopYInfo = player.y - player.r;
			//���݈ʒu�̒��_�̃}�b�v�`�b�v���
			playerTopYMaptip = (player.y - player.r) / blockSize;
			//���_�����l�ɌŒ肷�邽�߂�y���W���o�����߂�y���W�����߂�B
			playerTopYHeight = (playerTopYMaptip + 1) * blockSize;

			//���W���ړ��������̂ŁA������x�e�S�̊p�̍��W���v�Z����B
			//�E��
			rightTopX = (player.x + player.r - 1) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			//����
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			//�E��
			rightBottomX = (player.x + player.r - 1) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;
			//����
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			//���ł���Ƃ�
			if (jumpCount < 3) {
				//������Ńu���b�N�ɂԂ��������̏���
				if (player.y <= (playerBottomYHeightPlus - player.r))
				{
					if (map2[leftTopY][leftTopX] != NONE || map2[rightTopY][rightTopX] != NONE)
					{
						jumpHeight = 0;
						isJump = 0;
					}
				}
			}

			//�������Ńu���b�N�ɂԂ��������̏���
			if (map2[leftBottomY][leftBottomX] != NONE || map2[rightBottomY][rightBottomX] != NONE)
			{
				player.y = playerTopYHeight - player.r;
				g = 0;
				isJump = 0;
				jumpCount = 2;
				jumpHeight = 25;
			}

			if (player.y >= (WIN_HEIGHT - 1) * blockSize - player.r)
			{
				player.y = (WIN_HEIGHT - 1) * blockSize - player.r;
				jumpCount = 2;
				jumpHeight = 25;
				isJump = 0;
			};

			//�S�[��
			GLcollision = GetGLcollision(cGoal, player);
			if (GLcollision)
			{
				PlaySoundMem(clearse, DX_PLAYTYPE_BACK, true);
				isGoal = 1;
			}
		}

		// ---------- ---------- �`���[�g���A���X�e�[�W_�I��� ---------- ---------- 

		// ---------- ---------- �X�e�[�W1_�n�� ---------- ---------- 
		//�V�[���R(�\)
		if (scene == 3)
		{
			//�G�A�}�E�X�Ǐ]
			if (isEnemy == 1)
			{
				if (pointer.x > 0 && pointer.x < WIN_WIDTH && pointer.y>0 && pointer.y < WIN_HEIGHT)
				{
					for (i = 0; i < MAX_BULLET; i++)
					{
						enemy.speedX = (int)(cos(enemy.angle) * 3.0);
						enemy.speedY = (int)(sin(enemy.angle) * 3.0);
						int a = enemy.x - pointer.x;
						int b = enemy.y - pointer.y;
						int c = pointer.r + enemy.r;
						if ((c * c) >= (a * a) + (b * b) && enemy.flag == 1)
						{
							if (enemy.flag == 1)
							{
								PEcollision = 1;
							}
						}

						//�ǔ�����
						double ax, ay, bx, by;
						bx = cos(enemy.angle);
						by = sin(enemy.angle);
						ax = pointer.x - (enemy.x);
						ay = pointer.y - (enemy.y);

						enemy.angle += (ax * by - ay * bx < 0.0) ? +PI / 180 * 8 : -PI / 180 * 8;

						// �ړ�����
						enemy.x += enemy.speedX;
						enemy.y += enemy.speedY;
					}
				}
				int uy = enemy.y;
				int ux = enemy.x;

				//�G�̃X�e�[�W��Z�H���Ȃ�����
				for (int y = 0; y < mapSizeY; y++)
				{
					for (int x = 0; x < mapSizeX; x++)
					{
						if (map3[uy / blockSize][ux / blockSize] == NONE)
						{
							map3[uy / blockSize][ux / blockSize] = 2;
						}

						if (map4[uy / blockSize][49 - ux / blockSize] == NONE)
						{
							map4[uy / blockSize][49 - ux / blockSize] = 2;
						}
					}
				}
			}

			//�}�b�v�`�b�v�̓����蔻��
			if (player.x - player.r > 0)
			{
				if (keys[KEY_INPUT_LEFT] == 1 || keys[KEY_INPUT_A] == 1)
				{
					leftTopX = ((player.x - provisionalSpeed) - player.r) / blockSize;
					leftBottomX = ((player.x - provisionalSpeed) - player.r) / blockSize;
					if (map3[leftTopY][leftTopX] == NONE && map3[leftBottomY][leftBottomX] == NONE)
					{
						player.speedX = -4;
					}
				}
			}
			if (player.x + player.r < WIN_WIDTH - 64)
			{
				if (keys[KEY_INPUT_RIGHT] == 1 || keys[KEY_INPUT_D] == 1)
				{
					rightTopX = ((player.x + provisionalSpeed) + player.r - 1) / blockSize;
					rightBottomX = ((player.x + provisionalSpeed) + player.r - 1) / blockSize;
					if (map3[rightTopY][rightTopX] == NONE && map3[rightBottomY][rightBottomX] == NONE)
					{
						player.speedX = 4;
					}
				}
			}

			//�W�����v
			//�d�͏��������邽�߁A�}�b�v�`�b�v���W�̎�����ς���B
			//�E��
			rightTopX = (player.x + player.r - 1) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			//����
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			//�E��
			rightBottomX = (player.x + player.r - 1) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;
			//����
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			//���Ƀu���b�N���Ȃ���Η������鏈��
			if (map3[leftBottomY][leftBottomX] == NONE && map3[rightBottomY][rightBottomX] == NONE && isGravity == 1)
			{
				if (player.y + player.r <= WIN_HEIGHT)
				{
					if (isJump == 0)
					{
						g--;
						player.y -= g;
						if (g < -10)
						{
							g = -10;
						}
					}
				}
			}

			//�v���C���[�̃W�����v
			if (jumpCount > 0)
			{
				if (map3[leftTopY][leftTopX] == NONE || map3[rightTopY][rightTopX] == NONE)
				{
					if (keys[KEY_INPUT_W] == 1 && oldkeys[KEY_INPUT_W] == 0 || keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
					{
						PlaySoundMem(jumpse, DX_PLAYTYPE_BACK, true);
						isJump = 1;
						g = 0;
						jumpCount -= 1;
						jumpHeight = 16;
					}
				}
			}
			//�W�����v�̎d�g��
			if (jumpCount < 2)
			{
				if (isJump == 1)
				{
					jumpHeight--;
					if (jumpHeight < -8)
					{
						jumpHeight = -8;
					}

					player.y -= jumpHeight;
				}
			}

			//�n�ʂɒ��n������ēx�W�����v�ł���悤�ɂ���
			if (jumpCount == 0)
			{
				if (map3[leftBottomY][leftBottomX] == BLOCK || map3[rightBottomY][rightBottomX] == BLOCK)
				{
					jumpCount = 2;
				}
			}

			//���݈ʒu�̒�ӂ̏��
			playerBottomYInfo = player.y + player.r - 1;
			//�����݈ʒu�̒�ӂ̃}�b�v�`�b�v���(��ӂ̏�񂩂�}�b�v�`�b�v��ł̂ǂ̐����ɂ��邩���v�Z����)
			playerBottomYMaptip = (player.y + player.r - 1) / blockSize;

			//���ݒn���P����y���W�B���@�̒�ӂ̍��W�͈���̍����y���W�ɂȂ邽�߁B(���2�s����}�b�v��̎��@�̐�������ꂽ�̂ŁA�Œ肷��ʒu���w�肵�ău���b�N�T�C�Y�������Ă�����)
			playerBottomYHeightPlus = (playerBottomYMaptip + 1) * blockSize;
			//���ݒn���P���̃}�b�v�`�b�v�̏��
			playerBottomYMaptipPlus = (playerBottomYHeightPlus / blockSize);

			//���݈ʒu�̒��_�̏�� 
			playerTopYInfo = player.y - player.r;
			//���݈ʒu�̒��_�̃}�b�v�`�b�v���
			playerTopYMaptip = (player.y - player.r) / blockSize;
			//���_�����l�ɌŒ肷�邽�߂�y���W���o�����߂�y���W�����߂�B
			playerTopYHeight = (playerTopYMaptip + 1) * blockSize;

			//���W���ړ��������̂ŁA������x�e�S�̊p�̍��W���v�Z����B
			//�E��
			rightTopX = (player.x + player.r - 1) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			//����
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			//�E��
			rightBottomX = (player.x + player.r - 1) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;
			//����
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			//���ł���Ƃ�
			if (jumpCount < 3)
			{
				//������Ńu���b�N�ɂԂ��������̏���
				if (player.y <= (playerBottomYHeightPlus - player.r))
				{
					if (map3[leftTopY][leftTopX] != NONE || map3[rightTopY][rightTopX] != NONE)
					{
						jumpHeight = 0;
						isJump = 0;
					}
				}
			}

			//�������Ńu���b�N�ɂԂ��������̏���
			if (map3[leftBottomY][leftBottomX] != NONE || map3[rightBottomY][rightBottomX] != NONE)
			{
				player.y = playerTopYHeight - player.r;
				g = 0;
				isJump = 0;
				jumpCount = 2;
				jumpHeight = 25;
			}

			if (player.y >= (WIN_HEIGHT - 1) * blockSize - player.r)
			{
				player.y = (WIN_HEIGHT - 1) * blockSize - player.r;
				jumpCount = 2;
				jumpHeight = 25;
				isJump = 0;
			}
		}

		//�V�[���؂�ւ�
		if (player.x >= 1500 && scene == 3)
		{
			if (keys[KEY_INPUT_E] == 1 && oldkeys[KEY_INPUT_E] == 0)
			{
				PlaySoundMem(nextpagese, DX_PLAYTYPE_BACK, true);
				isAnimation = 1;
				oldPlayerFront = player.y;
			}
		}

		if (isAnimation == 1 && scene == 3)
		{
			peraAnimeTimer -= 1;
			if (peraAnimeTimer == 0)
			{
				isAnimation = 0;
				player.x = 48;
				player.y = oldPlayerFront;
				scene = 4;
				peraAnimeTimer = 42;
			}
		}

		if (player.x <= 16 && scene == 4)
		{
			if (keys[KEY_INPUT_E] == 1 && oldkeys[KEY_INPUT_E] == 0)
			{
				PlaySoundMem(nextpagese, DX_PLAYTYPE_BACK, true);
				isReverseAnimation = 1;
				oldPlayerBack = player.y;
			}
		}

		if (isReverseAnimation == 1 && scene == 4)
		{
			peraAnimeTimer -= 1;
			if (peraAnimeTimer == 0)
			{
				isReverseAnimation = 0;
				player.x = 1550;
				player.y = oldPlayerBack;
				scene = 3;
				peraAnimeTimer = 42;
			}
		}

		//�V�[��4(��)
		if (scene == 4 && isGoal == 0)
		{
			int uy = enemy.y;
			int ux = enemy.x;

			//�}�b�v�`�b�v�̓����蔻��
			if (player.x - player.r > 0)
			{
				if (keys[KEY_INPUT_LEFT] == 1 || keys[KEY_INPUT_A] == 1)
				{
					leftTopX = ((player.x - provisionalSpeed) - player.r) / blockSize;
					leftBottomX = ((player.x - provisionalSpeed) - player.r) / blockSize;
					if (map4[leftTopY][leftTopX] == NONE && map4[leftBottomY][leftBottomX] == NONE)
					{
						player.speedX = -4;
					}
				}
			}
			if (player.x + player.r < WIN_WIDTH - 64)
			{
				if (keys[KEY_INPUT_RIGHT] == 1 || keys[KEY_INPUT_D] == 1)
				{
					rightTopX = ((player.x + provisionalSpeed) + player.r - 1) / blockSize;
					rightBottomX = ((player.x + provisionalSpeed) + player.r - 1) / blockSize;
					if (map4[rightTopY][rightTopX] == NONE && map4[rightBottomY][rightBottomX] == NONE)
					{
						player.speedX = 4;
					}
				}
			}

			//�W�����v
			//�d�͏��������邽�߁A�}�b�v�`�b�v���W�̎�����ς���B
			//�E��
			rightTopX = (player.x + player.r - 1) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			//����
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			//�E��
			rightBottomX = (player.x + player.r - 1) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;
			//����
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			//���Ƀu���b�N���Ȃ���Η������鏈��
			if (map4[leftBottomY][leftBottomX] == NONE && map4[rightBottomY][rightBottomX] == NONE && isGravity == 1)
			{
				if (player.y + player.r <= WIN_HEIGHT)
				{
					if (isJump == 0)
					{
						g--;
						player.y -= g;
						if (g < -10)
						{
							g = -10;
						}
					}
				}
			}

			//�v���C���[�̃W�����v
			if (jumpCount > 0)
			{
				if (map4[leftTopY][leftTopX] == NONE || map4[rightTopY][rightTopX] == NONE)
				{
					if (keys[KEY_INPUT_W] == 1 && oldkeys[KEY_INPUT_W] == 0 || keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
					{
						PlaySoundMem(jumpse, DX_PLAYTYPE_BACK, true);
						isJump = 1;
						g = 0;
						jumpCount -= 1;
						jumpHeight = 16;
					}
				}
			}
			//�W�����v�̎d�g��
			if (jumpCount < 2)
			{
				if (isJump == 1)
				{
					jumpHeight--;
					if (jumpHeight < -8)
					{
						jumpHeight = -8;
					}
					player.y -= jumpHeight;
				}
			}

			//�n�ʂɒ��n������ēx�W�����v�ł���悤�ɂ���
			if (jumpCount == 0)
			{
				if (map4[leftBottomY][leftBottomX] == BLOCK || map4[rightBottomY][rightBottomX] == BLOCK)
				{
					jumpCount = 2;
				}
			}

			//���݈ʒu�̒�ӂ̏��
			playerBottomYInfo = player.y + player.r - 1;
			//�����݈ʒu�̒�ӂ̃}�b�v�`�b�v���(��ӂ̏�񂩂�}�b�v�`�b�v��ł̂ǂ̐����ɂ��邩���v�Z����)
			playerBottomYMaptip = (player.y + player.r - 1) / blockSize;

			//���ݒn���P����y���W�B���@�̒�ӂ̍��W�͈���̍����y���W�ɂȂ邽�߁B(���2�s����}�b�v��̎��@�̐�������ꂽ�̂ŁA�Œ肷��ʒu���w�肵�ău���b�N�T�C�Y�������Ă�����)
			playerBottomYHeightPlus = (playerBottomYMaptip + 1) * blockSize;
			//���ݒn���P���̃}�b�v�`�b�v�̏��
			playerBottomYMaptipPlus = (playerBottomYHeightPlus / blockSize);

			//���݈ʒu�̒��_�̏�� 
			playerTopYInfo = player.y - player.r;
			//���݈ʒu�̒��_�̃}�b�v�`�b�v���
			playerTopYMaptip = (player.y - player.r) / blockSize;
			//���_�����l�ɌŒ肷�邽�߂�y���W���o�����߂�y���W�����߂�B
			playerTopYHeight = (playerTopYMaptip + 1) * blockSize;

			//���W���ړ��������̂ŁA������x�e�S�̊p�̍��W���v�Z����B
			//�E��
			rightTopX = (player.x + player.r - 1) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			//����
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			//�E��
			rightBottomX = (player.x + player.r - 1) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;
			//����
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			//���ł���Ƃ�
			if (jumpCount < 3)
			{
				//������Ńu���b�N�ɂԂ��������̏���
				if (player.y <= (playerBottomYHeightPlus - player.r))
				{
					if (map4[leftTopY][leftTopX] != NONE || map4[rightTopY][rightTopX] != NONE)
					{
						jumpHeight = 0;
						isJump = 0;
					}
				}
			}

			//�������Ńu���b�N�ɂԂ��������̏���
			if (map4[leftBottomY][leftBottomX] != NONE || map4[rightBottomY][rightBottomX] != NONE)
			{
				player.y = playerTopYHeight - player.r;
				g = 0;
				isJump = 0;
				jumpCount = 2;
				jumpHeight = 25;
			}

			if (player.y >= (WIN_HEIGHT - 1) * blockSize - player.r)
			{
				player.y = (WIN_HEIGHT - 1) * blockSize - player.r;
				jumpCount = 2;
				jumpHeight = 25;
				isJump = 0;
			}

			//�S�[��
			GLcollision = GetGLcollision(goal, player);
			if (GLcollision)
			{
				PlaySoundMem(clearse, DX_PLAYTYPE_BACK, true);
				isGoal = 1;
			}
		}

		// ---------- ---------- �X�e�[�W1_�I��� ---------- ---------- 

		// ---------- ---------- �X�e�[�W2_�n�� ---------- ---------- 
		//�V�[��5(�\)
		if (scene == 5)
		{
			//�G�A�}�E�X�Ǐ]
			if (isEnemy == 1)
			{
				if (pointer.x > 0 && pointer.x < WIN_WIDTH && pointer.y>0 && pointer.y < WIN_HEIGHT)
				{
					for (i = 0; i < MAX_BULLET; i++)
					{
						enemy.speedX = (int)(cos(enemy.angle) * 3.0);
						enemy.speedY = (int)(sin(enemy.angle) * 3.0);
						int a = enemy.x2 - pointer.x;
						int b = enemy.y2 - pointer.y;
						int c = pointer.r + enemy.r;
						if ((c * c) >= (a * a) + (b * b) && enemy.flag == 1)
						{
							if (enemy.flag == 1)
							{
								PEcollision = 1;
							}
						}

						//�ǔ�����
						double ax, ay, bx, by;
						bx = cos(enemy.angle);
						by = sin(enemy.angle);
						ax = pointer.x - (enemy.x2);
						ay = pointer.y - (enemy.y2);

						enemy.angle += (ax * by - ay * bx < 0.0) ? +PI / 180 * 8 : -PI / 180 * 8;

						// �ړ�����
						enemy.x2 += enemy.speedX;
						enemy.y2 += enemy.speedY;
					}
				}
				int uy = enemy.y2;
				int ux = enemy.x2;

				//�G�̃X�e�[�W��Z�H���Ȃ����� & ���[�U�[�̏���
				for (int y = 0; y < mapSizeY; y++)
				{
					for (int x = 0; x < mapSizeX; x++)
					{
						if (map5[uy / blockSize][ux / blockSize] == NONE || map5[uy / blockSize][ux / blockSize] == YOKOLASER)
						{
							map5[uy / blockSize][ux / blockSize] = 2;
							if (map5[uy / blockSize][0] == YOKOLASER || map5[uy / blockSize][0] == NONE || map5[uy / blockSize][0] == STAGE)
							{
								for (int x = 0; x < ux / blockSize; x++)
								{
									if (map5[uy / blockSize][x] == YOKOLASER)
									{
										map5[uy / blockSize][x] = NONE;
									}
								}
							}
						}

						if (map5[uy / blockSize][ux / blockSize] == NONE || map5[uy / blockSize][ux / blockSize] == TATELASER)
						{
							map5[uy / blockSize][ux / blockSize] = 2;
							if (map5[29][ux / blockSize] == TATELASER || map5[29][ux / blockSize] == NONE || map5[29][ux / blockSize] == STAGE || map5[29][ux / blockSize] == YOKOLASER)
							{
								for (int y = 29; y >= uy / blockSize; y--)
								{
									if (map5[y][ux / blockSize] == TATELASER)
									{
										map5[y][ux / blockSize] = NONE;
									}
								}
							}
						}

						if (map6[uy / blockSize][49 - ux / blockSize] == NONE || map6[uy / blockSize][49 - ux / blockSize] == TATELASER)
						{
							map6[uy / blockSize][49 - ux / blockSize] = 2;
							if (map6[29][49 - ux / blockSize] == TATELASER || map6[29][49 - ux / blockSize] == NONE || map6[29][49 - ux / blockSize] == STAGE || map6[29][49 - ux / blockSize] == YOKOLASER)
							{
								for (int y = 29; y >= uy / blockSize; y--)
								{
									if (map6[y][49 - ux / blockSize] == TATELASER)
									{
										map6[y][49 - ux / blockSize] = NONE;
									}
								}
							}
						}

						if (map6[uy / blockSize][49 - ux / blockSize] == NONE || map6[uy / blockSize][49 - ux / blockSize] == YOKOLASER)
						{
							map6[uy / blockSize][49 - ux / blockSize] = 2;
							if (map6[uy / blockSize][0] == YOKOLASER || map6[uy / blockSize][0] == NONE || map6[uy / blockSize][0] == STAGE || map6[uy / blockSize][0] == TATELASER)
							{
								for (int x = 0; x < 49 - ux / blockSize; x++)
								{
									if (map6[uy / blockSize][x] == YOKOLASER)
									{
										map6[uy / blockSize][x] = NONE;
									}
								}
							}
						}
					}
				}
			}

			//�}�b�v�`�b�v�̓����蔻��
			if (player.x - player.r > 0)
			{
				if (keys[KEY_INPUT_LEFT] == 1 || keys[KEY_INPUT_A] == 1)
				{
					leftTopX = ((player.x - provisionalSpeed) - player.r) / blockSize;
					leftBottomX = ((player.x - provisionalSpeed) - player.r) / blockSize;
					if (map5[leftTopY][leftTopX] == NONE && map5[leftBottomY][leftBottomX] == NONE)
					{
						player.speedX = -4;
					}
				}
			}

			if (player.x + player.r < WIN_WIDTH - 64)
			{
				if (keys[KEY_INPUT_RIGHT] == 1 || keys[KEY_INPUT_D] == 1)
				{
					rightTopX = ((player.x + provisionalSpeed) + player.r - 1) / blockSize;
					rightBottomX = ((player.x + provisionalSpeed) + player.r - 1) / blockSize;
					if (map5[rightTopY][rightTopX] == NONE && map5[rightBottomY][rightBottomX] == NONE)
					{
						player.speedX = 4;
					}
				}
			}

			//�W�����v
			//�d�͏��������邽�߁A�}�b�v�`�b�v���W�̎�����ς���B
			//�E��
			rightTopX = (player.x + player.r - 1) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			//����
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			//�E��
			rightBottomX = (player.x + player.r - 1) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;
			//����
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			//���Ƀu���b�N���Ȃ���Η������鏈��
			if (map5[leftBottomY][leftBottomX] == NONE && map5[rightBottomY][rightBottomX] == NONE && isGravity == 1)
			{
				if (player.y + player.r <= WIN_HEIGHT)
				{
					if (isJump == 0)
					{
						g--;
						player.y -= g;
						if (g < -10)
						{
							g = -10;
						}
					}
				}
			}

			//�v���C���[�̃W�����v
			if (jumpCount > 0)
			{
				if (map5[leftTopY][leftTopX] == NONE || map5[rightTopY][rightTopX] == NONE)
				{
					if (keys[KEY_INPUT_W] == 1 && oldkeys[KEY_INPUT_W] == 0 || keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
					{
						PlaySoundMem(jumpse, DX_PLAYTYPE_BACK, true);
						isJump = 1;
						g = 0;
						jumpCount -= 1;
						jumpHeight = 16;
					}
				}
			}
			//�W�����v�̎d�g��
			if (jumpCount < 2)
			{
				if (isJump == 1)
				{
					jumpHeight--;
					if (jumpHeight < -8)
					{
						jumpHeight = -8;
					}
					player.y -= jumpHeight;
				}
			}

			//�n�ʂɒ��n������ēx�W�����v�ł���悤�ɂ���
			if (jumpCount == 0)
			{
				if (map5[leftBottomY][leftBottomX] == BLOCK || map5[rightBottomY][rightBottomX] == BLOCK)
				{
					jumpCount = 2;
				}
			}

			//���݈ʒu�̒�ӂ̏��
			playerBottomYInfo = player.y + player.r - 1;
			//�����݈ʒu�̒�ӂ̃}�b�v�`�b�v���(��ӂ̏�񂩂�}�b�v�`�b�v��ł̂ǂ̐����ɂ��邩���v�Z����)
			playerBottomYMaptip = (player.y + player.r - 1) / blockSize;

			//���ݒn���P����y���W�B���@�̒�ӂ̍��W�͈���̍����y���W�ɂȂ邽�߁B(���2�s����}�b�v��̎��@�̐�������ꂽ�̂ŁA�Œ肷��ʒu���w�肵�ău���b�N�T�C�Y�������Ă�����)
			playerBottomYHeightPlus = (playerBottomYMaptip + 1) * blockSize;
			//���ݒn���P���̃}�b�v�`�b�v�̏��
			playerBottomYMaptipPlus = (playerBottomYHeightPlus / blockSize);

			//���݈ʒu�̒��_�̏�� 
			playerTopYInfo = player.y - player.r;
			//���݈ʒu�̒��_�̃}�b�v�`�b�v���
			playerTopYMaptip = (player.y - player.r) / blockSize;
			//���_�����l�ɌŒ肷�邽�߂�y���W���o�����߂�y���W�����߂�B
			playerTopYHeight = (playerTopYMaptip + 1) * blockSize;

			//���W���ړ��������̂ŁA������x�e�S�̊p�̍��W���v�Z����B
			//�E��
			rightTopX = (player.x + player.r - 1) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			//����
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			//�E��
			rightBottomX = (player.x + player.r - 1) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;
			//����
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			//���ł���Ƃ�
			if (jumpCount < 3)
			{
				//������Ńu���b�N�ɂԂ��������̏���
				if (player.y <= (playerBottomYHeightPlus - player.r))
				{
					if (map5[leftTopY][leftTopX] != NONE || map5[rightTopY][rightTopX] != NONE)
					{
						jumpHeight = 0;
						isJump = 0;
					}
				}
			}

			//�������Ńu���b�N�ɂԂ��������̏���
			if (map5[leftBottomY][leftBottomX] != NONE || map5[rightBottomY][rightBottomX] != NONE)
			{
				player.y = playerTopYHeight - player.r;
				g = 0;
				isJump = 0;
				jumpCount = 2;
				jumpHeight = 25;
			}

			if (player.y >= (WIN_HEIGHT - 1) * blockSize - player.r)
			{
				player.y = (WIN_HEIGHT - 1) * blockSize - player.r;
				jumpCount = 2;
				jumpHeight = 25;
				isJump = 0;
			}
		}

		// ---------- �V�[���؂�ւ� ---------- 
		if (player.x >= 1500 && scene == 5)
		{
			if (keys[KEY_INPUT_E] == 1 && oldkeys[KEY_INPUT_E] == 0)
			{
				PlaySoundMem(nextpagese, DX_PLAYTYPE_BACK, true);
				isAnimation = 1;
				oldPlayerFront = player.y;
			}
		}

		if (isAnimation == 1 && scene == 5)
		{
			peraAnimeTimer -= 1;
			if (peraAnimeTimer == 0)
			{
				isAnimation = 0;
				player.x = 48;
				player.y = oldPlayerFront;
				scene = 6;
				peraAnimeTimer = 42;
			}
		}

		if (player.x <= 16 && scene == 6)
		{
			if (keys[KEY_INPUT_E] == 1 && oldkeys[KEY_INPUT_E] == 0)
			{
				PlaySoundMem(nextpagese, DX_PLAYTYPE_BACK, true);
				isReverseAnimation = 1;
				oldPlayerBack = player.y;
			}
		}

		if (isReverseAnimation == 1 && scene == 6)
		{
			peraAnimeTimer -= 1;
			if (peraAnimeTimer == 0)
			{
				isReverseAnimation = 0;
				player.x = 1550;
				player.y = oldPlayerBack;
				scene = 5;
				peraAnimeTimer = 42;
			}
		}

		//�V�[��6(��)
		if (scene == 6 && isGoal == 0)
		{
			int uy = enemy.y;
			int ux = enemy.x;

			//�}�b�v�`�b�v�̓����蔻��
			if (player.x - player.r > 0)
			{
				if (keys[KEY_INPUT_LEFT] == 1 || keys[KEY_INPUT_A] == 1)
				{
					leftTopX = ((player.x - provisionalSpeed) - player.r) / blockSize;
					leftBottomX = ((player.x - provisionalSpeed) - player.r) / blockSize;
					if (map6[leftTopY][leftTopX] == NONE && map6[leftBottomY][leftBottomX] == NONE)
					{
						player.speedX = -4;
					}
				}
			}

			if (player.x + player.r < WIN_WIDTH - 64)
			{
				if (keys[KEY_INPUT_RIGHT] == 1 || keys[KEY_INPUT_D] == 1)
				{
					rightTopX = ((player.x + provisionalSpeed) + player.r - 1) / blockSize;
					rightBottomX = ((player.x + provisionalSpeed) + player.r - 1) / blockSize;
					if (map6[rightTopY][rightTopX] == NONE && map6[rightBottomY][rightBottomX] == NONE)
					{
						player.speedX = 4;
					}
				}
			}

			//�W�����v
			//�d�͏��������邽�߁A�}�b�v�`�b�v���W�̎�����ς���B
			//�E��
			rightTopX = (player.x + player.r - 1) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			//����
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			//�E��
			rightBottomX = (player.x + player.r - 1) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;
			//����
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			//���Ƀu���b�N���Ȃ���Η������鏈��
			if (map6[leftBottomY][leftBottomX] == NONE && map6[rightBottomY][rightBottomX] == NONE && isGravity == 1)
			{
				if (player.y + player.r <= WIN_HEIGHT)
				{
					if (isJump == 0)
					{
						g--;
						player.y -= g;
						if (g < -10)
						{
							g = -10;
						}
					}
				}
			}

			//�v���C���[�̃W�����v
			if (jumpCount > 0)
			{
				if (map6[leftTopY][leftTopX] == NONE || map6[rightTopY][rightTopX] == NONE)
				{
					if (keys[KEY_INPUT_W] == 1 && oldkeys[KEY_INPUT_W] == 0 || keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
					{
						PlaySoundMem(jumpse, DX_PLAYTYPE_BACK, true);
						isJump = 1;
						g = 0;
						jumpCount -= 1;
						jumpHeight = 16;
					}
				}
			}
			//�W�����v�̎d�g��
			if (jumpCount < 2)
			{
				if (isJump == 1)
				{
					jumpHeight--;
					if (jumpHeight < -8)
					{
						jumpHeight = -8;
					}
					player.y -= jumpHeight;
				}
			}

			//�n�ʂɒ��n������ēx�W�����v�ł���悤�ɂ���
			if (jumpCount == 0)
			{
				if (map6[leftBottomY][leftBottomX] == BLOCK || map6[rightBottomY][rightBottomX] == BLOCK)
				{
					jumpCount = 2;
				}
			}

			//���݈ʒu�̒�ӂ̏��
			playerBottomYInfo = player.y + player.r - 1;
			//�����݈ʒu�̒�ӂ̃}�b�v�`�b�v���(��ӂ̏�񂩂�}�b�v�`�b�v��ł̂ǂ̐����ɂ��邩���v�Z����)
			playerBottomYMaptip = (player.y + player.r - 1) / blockSize;

			//���ݒn���P����y���W�B���@�̒�ӂ̍��W�͈���̍����y���W�ɂȂ邽�߁B(���2�s����}�b�v��̎��@�̐�������ꂽ�̂ŁA�Œ肷��ʒu���w�肵�ău���b�N�T�C�Y�������Ă�����)
			playerBottomYHeightPlus = (playerBottomYMaptip + 1) * blockSize;
			//���ݒn���P���̃}�b�v�`�b�v�̏��
			playerBottomYMaptipPlus = (playerBottomYHeightPlus / blockSize);

			//���݈ʒu�̒��_�̏�� 
			playerTopYInfo = player.y - player.r;
			//���݈ʒu�̒��_�̃}�b�v�`�b�v���
			playerTopYMaptip = (player.y - player.r) / blockSize;
			//���_�����l�ɌŒ肷�邽�߂�y���W���o�����߂�y���W�����߂�B
			playerTopYHeight = (playerTopYMaptip + 1) * blockSize;

			//���W���ړ��������̂ŁA������x�e�S�̊p�̍��W���v�Z����B
			//�E��
			rightTopX = (player.x + player.r - 1) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			//����
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			//�E��
			rightBottomX = (player.x + player.r - 1) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;
			//����
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			//���ł���Ƃ�
			if (jumpCount < 3)
			{
				//������Ńu���b�N�ɂԂ��������̏���
				if (player.y <= (playerBottomYHeightPlus - player.r))
				{
					if (map6[leftTopY][leftTopX] != NONE || map6[rightTopY][rightTopX] != NONE)
					{
						jumpHeight = 0;
						isJump = 0;
					}
				}
			}

			//�������Ńu���b�N�ɂԂ��������̏���
			if (map6[leftBottomY][leftBottomX] != NONE || map6[rightBottomY][rightBottomX] != NONE)
			{
				player.y = playerTopYHeight - player.r;
				g = 0;
				isJump = 0;
				jumpCount = 2;
				jumpHeight = 25;
			}

			if (player.y >= (WIN_HEIGHT - 1) * blockSize - player.r)
			{
				player.y = (WIN_HEIGHT - 1) * blockSize - player.r;
				jumpCount = 2;
				jumpHeight = 25;
				isJump = 0;
			}

			//�S�[��
			GLcollision = GetGLcollision(goal, player);
			if (GLcollision)
			{
				PlaySoundMem(clearse, DX_PLAYTYPE_BACK, true);
				isGoal = 1;
			}
		}

		// ---------- ���[�U�[�����蔻�� ---------- 
		if (scene == 5 || scene == 6)
		{
			//�l�p�̍��W�A�X�V
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			rightTopX = (player.x + player.r) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			rightBottomX = (player.x + player.r) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;

			if (scene == 5)
			{
				if (map5[leftTopY][leftTopX] == YOKOLASER || map5[rightTopY][rightTopX] == YOKOLASER ||
					map5[leftBottomY][leftBottomX] == YOKOLASER || map5[rightBottomY][rightBottomX] == YOKOLASER)
				{
					player.isAllive = 0;
				}
			}
			if (scene == 6)
			{
				if (map6[leftTopY][leftTopX] == TATELASER || map6[rightTopY][rightTopX] == TATELASER ||
					map6[leftBottomY][leftBottomX] == TATELASER || map6[rightBottomY][rightBottomX] == TATELASER)
				{
					player.isAllive = 0;
				}
			}
		}

		if (player.isAllive == 0)
		{
			player.isAllive = 1;
			isReset = 1;
		}

		// ---------- ---------- �X�e�[�W2_�I��� ---------- ---------- 

		// ---------- ---------- �X�e�[�W3_�n�� ---------- ---------- 
		//�V�[��7(�\)
		if (scene == 7)
		{
			//�G�A�}�E�X�Ǐ]
			if (isEnemy == 1)
			{
				if (pointer.x > 0 && pointer.x < WIN_WIDTH && pointer.y>0 && pointer.y < WIN_HEIGHT)
				{
					for (i = 0; i < MAX_BULLET; i++)
					{
						enemy.speedX = (int)(cos(enemy.angle) * 3.0);
						enemy.speedY = (int)(sin(enemy.angle) * 3.0);
						int a = enemy.x2 - pointer.x;
						int b = enemy.y2 - pointer.y;
						int c = pointer.r + enemy.r;
						if ((c * c) >= (a * a) + (b * b) && enemy.flag == 1)
						{
							if (enemy.flag == 1)
							{
								PEcollision = 1;
							}
						}

						//�ǔ�����
						double ax, ay, bx, by;
						bx = cos(enemy.angle);
						by = sin(enemy.angle);
						ax = pointer.x - (enemy.x2);
						ay = pointer.y - (enemy.y2);

						enemy.angle += (ax * by - ay * bx < 0.0) ? +PI / 180 * 8 : -PI / 180 * 8;

						// �ړ�����
						enemy.x2 += enemy.speedX;
						enemy.y2 += enemy.speedY;
					}
				}
				int uy = enemy.y2;
				int ux = enemy.x2;

				//�G�̃X�e�[�W��Z�H���Ȃ����� & ���[�U�[�̏���
				for (int y = 0; y < mapSizeY; y++)
				{
					for (int x = 0; x < mapSizeX; x++)
					{
						if (map7[uy / blockSize][ux / blockSize] == NONE || map7[uy / blockSize][ux / blockSize] == YOKOLASER)
						{
							map7[uy / blockSize][ux / blockSize] = 2;
							if (map7[uy / blockSize][0] == YOKOLASER || map7[uy / blockSize][0] == NONE || map7[uy / blockSize][0] == STAGE)
							{
								for (int x = 0; x < ux / blockSize; x++)
								{
									if (map7[uy / blockSize][x] == YOKOLASER)
									{
										map7[uy / blockSize][x] = NONE;
									}
								}
							}
						}

						if (map7[uy / blockSize][ux / blockSize] == NONE || map7[uy / blockSize][ux / blockSize] == TATELASER)
						{
							map7[uy / blockSize][ux / blockSize] = 2;
							if (map7[29][ux / blockSize] == TATELASER || map7[29][ux / blockSize] == NONE || map7[29][ux / blockSize] == STAGE || map7[29][ux / blockSize] == YOKOLASER)
							{
								for (int y = 29; y >= uy / blockSize; y--)
								{
									if (map7[y][ux / blockSize] == TATELASER)
									{
										map7[y][ux / blockSize] = NONE;
									}
								}
							}
						}

						if (map8[uy / blockSize][49 - ux / blockSize] == NONE || map8[uy / blockSize][49 - ux / blockSize] == TATELASER)
						{
							map8[uy / blockSize][49 - ux / blockSize] = 2;
							if (map8[29][49 - ux / blockSize] == TATELASER || map8[29][49 - ux / blockSize] == NONE || map8[29][49 - ux / blockSize] == STAGE || map8[29][49 - ux / blockSize] == YOKOLASER)
							{
								for (int y = 29; y >= uy / blockSize; y--)
								{
									if (map8[y][49 - ux / blockSize] == TATELASER)
									{
										map8[y][49 - ux / blockSize] = NONE;
									}
								}
							}
						}

						if (map8[uy / blockSize][49 - ux / blockSize] == NONE || map8[uy / blockSize][49 - ux / blockSize] == YOKOLASER)
						{
							map8[uy / blockSize][49 - ux / blockSize] = 2;
							if (map8[uy / blockSize][0] == YOKOLASER || map8[uy / blockSize][0] == NONE || map8[uy / blockSize][0] == STAGE || map8[uy / blockSize][0] == TATELASER)
							{
								for (int x = 0; x < 49 - ux / blockSize; x++)
								{
									if (map8[uy / blockSize][x] == YOKOLASER)
									{
										map8[uy / blockSize][x] = NONE;
									}
								}
							}
						}
					}
				}
			}

			//�}�b�v�`�b�v�̓����蔻��
			if (player.x - player.r > 0)
			{
				if (keys[KEY_INPUT_LEFT] == 1 || keys[KEY_INPUT_A] == 1)
				{
					leftTopX = ((player.x - provisionalSpeed) - player.r) / blockSize;
					leftBottomX = ((player.x - provisionalSpeed) - player.r) / blockSize;
					if (map7[leftTopY][leftTopX] == NONE && map7[leftBottomY][leftBottomX] == NONE)
					{
						player.speedX = -4;
					}
				}
			}

			if (player.x + player.r < WIN_WIDTH - 64)
			{
				if (keys[KEY_INPUT_RIGHT] == 1 || keys[KEY_INPUT_D] == 1)
				{
					rightTopX = ((player.x + provisionalSpeed) + player.r - 1) / blockSize;
					rightBottomX = ((player.x + provisionalSpeed) + player.r - 1) / blockSize;
					if (map7[rightTopY][rightTopX] == NONE && map7[rightBottomY][rightBottomX] == NONE)
					{
						player.speedX = 4;
					}
				}
			}

			//�W�����v
			//�d�͏��������邽�߁A�}�b�v�`�b�v���W�̎�����ς���B
			//�E��
			rightTopX = (player.x + player.r - 1) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			//����
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			//�E��
			rightBottomX = (player.x + player.r - 1) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;
			//����
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			//���Ƀu���b�N���Ȃ���Η������鏈��
			if (map7[leftBottomY][leftBottomX] == NONE && map7[rightBottomY][rightBottomX] == NONE && isGravity == 1)
			{
				if (player.y + player.r <= WIN_HEIGHT)
				{
					if (isJump == 0)
					{
						g--;
						player.y -= g;
						if (g < -10)
						{
							g = -10;
						}
					}
				}
			}

			//�v���C���[�̃W�����v
			if (jumpCount > 0)
			{
				if (map7[leftTopY][leftTopX] == NONE || map7[rightTopY][rightTopX] == NONE)
				{
					if (keys[KEY_INPUT_W] == 1 && oldkeys[KEY_INPUT_W] == 0 || keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
					{
						PlaySoundMem(jumpse, DX_PLAYTYPE_BACK, true);
						isJump = 1;
						g = 0;
						jumpCount -= 1;
						jumpHeight = 16;
					}
				}
			}
			//�W�����v�̎d�g��
			if (jumpCount < 2)
			{
				if (isJump == 1)
				{
					jumpHeight--;
					if (jumpHeight < -8)
					{
						jumpHeight = -8;
					}
					player.y -= jumpHeight;
				}
			}

			//�n�ʂɒ��n������ēx�W�����v�ł���悤�ɂ���
			if (jumpCount == 0)
			{
				if (map7[leftBottomY][leftBottomX] == BLOCK || map7[rightBottomY][rightBottomX] == BLOCK)
				{
					jumpCount = 2;
				}
			}

			//���݈ʒu�̒�ӂ̏��
			playerBottomYInfo = player.y + player.r - 1;
			//�����݈ʒu�̒�ӂ̃}�b�v�`�b�v���(��ӂ̏�񂩂�}�b�v�`�b�v��ł̂ǂ̐����ɂ��邩���v�Z����)
			playerBottomYMaptip = (player.y + player.r - 1) / blockSize;

			//���ݒn���P����y���W�B���@�̒�ӂ̍��W�͈���̍����y���W�ɂȂ邽�߁B(���2�s����}�b�v��̎��@�̐�������ꂽ�̂ŁA�Œ肷��ʒu���w�肵�ău���b�N�T�C�Y�������Ă�����)
			playerBottomYHeightPlus = (playerBottomYMaptip + 1) * blockSize;
			//���ݒn���P���̃}�b�v�`�b�v�̏��
			playerBottomYMaptipPlus = (playerBottomYHeightPlus / blockSize);

			//���݈ʒu�̒��_�̏�� 
			playerTopYInfo = player.y - player.r;
			//���݈ʒu�̒��_�̃}�b�v�`�b�v���
			playerTopYMaptip = (player.y - player.r) / blockSize;
			//���_�����l�ɌŒ肷�邽�߂�y���W���o�����߂�y���W�����߂�B
			playerTopYHeight = (playerTopYMaptip + 1) * blockSize;

			//���W���ړ��������̂ŁA������x�e�S�̊p�̍��W���v�Z����B
			//�E��
			rightTopX = (player.x + player.r - 1) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			//����
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			//�E��
			rightBottomX = (player.x + player.r - 1) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;
			//����
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			//���ł���Ƃ�
			if (jumpCount < 3)
			{
				//������Ńu���b�N�ɂԂ��������̏���
				if (player.y <= (playerBottomYHeightPlus - player.r))
				{
					if (map7[leftTopY][leftTopX] != NONE || map7[rightTopY][rightTopX] != NONE)
					{
						jumpHeight = 0;
						isJump = 0;
					}
				}
			}

			//�������Ńu���b�N�ɂԂ��������̏���
			if (map7[leftBottomY][leftBottomX] != NONE || map7[rightBottomY][rightBottomX] != NONE)
			{
				player.y = playerTopYHeight - player.r;
				g = 0;
				isJump = 0;
				jumpCount = 2;
				jumpHeight = 25;
			}

			if (player.y >= (WIN_HEIGHT - 1) * blockSize - player.r)
			{
				player.y = (WIN_HEIGHT - 1) * blockSize - player.r;
				jumpCount = 2;
				jumpHeight = 25;
				isJump = 0;
			}
		}

		// ---------- �V�[���؂�ւ� ---------- 
		if (player.x >= 1580 && scene == 7)
		{
			if (keys[KEY_INPUT_E] == 1 && oldkeys[KEY_INPUT_E] == 0)
			{
				PlaySoundMem(nextpagese, DX_PLAYTYPE_BACK, true);
				isAnimation = 1;
				oldPlayerFront = player.y;
			}
		}

		if (isAnimation == 1 && scene == 7)
		{
			peraAnimeTimer -= 1;
			if (peraAnimeTimer == 0)
			{
				isAnimation = 0;
				player.x = 48;
				player.y = oldPlayerFront;
				scene = 8;
				peraAnimeTimer = 42;
			}
		}

		if (player.x <= 16 && scene == 8)
		{
			if (keys[KEY_INPUT_E] == 1 && oldkeys[KEY_INPUT_E] == 0)
			{
				PlaySoundMem(nextpagese, DX_PLAYTYPE_BACK, true);
				isReverseAnimation = 1;
				oldPlayerBack = player.y;
			}
		}

		if (isReverseAnimation == 1 && scene == 8)
		{
			peraAnimeTimer -= 1;
			if (peraAnimeTimer == 0)
			{
				isReverseAnimation = 0;
				player.x = 1550;
				player.y = oldPlayerBack;
				scene = 7;
				peraAnimeTimer = 42;
			}
		}

		//�V�[��8(��)
		if (scene == 8 && isGoal == 0)
		{
			int uy = enemy.y;
			int ux = enemy.x;

			//�}�b�v�`�b�v�̓����蔻��
			if (player.x - player.r > 0)
			{
				if (keys[KEY_INPUT_LEFT] == 1 || keys[KEY_INPUT_A] == 1)
				{
					leftTopX = ((player.x - provisionalSpeed) - player.r) / blockSize;
					leftBottomX = ((player.x - provisionalSpeed) - player.r) / blockSize;
					if (map8[leftTopY][leftTopX] == NONE && map8[leftBottomY][leftBottomX] == NONE)
					{
						player.speedX = -4;
					}
				}
			}

			if (player.x + player.r < WIN_WIDTH - 64)
			{
				if (keys[KEY_INPUT_RIGHT] == 1 || keys[KEY_INPUT_D] == 1)
				{
					rightTopX = ((player.x + provisionalSpeed) + player.r - 1) / blockSize;
					rightBottomX = ((player.x + provisionalSpeed) + player.r - 1) / blockSize;
					if (map8[rightTopY][rightTopX] == NONE && map8[rightBottomY][rightBottomX] == NONE)
					{
						player.speedX = 4;
					}
				}
			}

			//�W�����v
			//�d�͏��������邽�߁A�}�b�v�`�b�v���W�̎�����ς���B
			//�E��
			rightTopX = (player.x + player.r - 1) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			//����
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			//�E��
			rightBottomX = (player.x + player.r - 1) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;
			//����
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			//���Ƀu���b�N���Ȃ���Η������鏈��
			if (map8[leftBottomY][leftBottomX] == NONE && map8[rightBottomY][rightBottomX] == NONE && isGravity == 1)
			{
				if (player.y + player.r <= WIN_HEIGHT)
				{
					if (isJump == 0)
					{
						g--;
						player.y -= g;
						if (g < -10)
						{
							g = -10;
						}
					}
				}
			}

			//�v���C���[�̃W�����v
			if (jumpCount > 0)
			{
				if (map8[leftTopY][leftTopX] == NONE || map8[rightTopY][rightTopX] == NONE)
				{
					if (keys[KEY_INPUT_W] == 1 && oldkeys[KEY_INPUT_W] == 0 || keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
					{
						PlaySoundMem(jumpse, DX_PLAYTYPE_BACK, true);
						isJump = 1;
						g = 0;
						jumpCount -= 1;
						jumpHeight = 16;
					}
				}
			}
			//�W�����v�̎d�g��
			if (jumpCount < 2)
			{
				if (isJump == 1)
				{
					jumpHeight--;
					if (jumpHeight < -8)
					{
						jumpHeight = -8;
					}
					player.y -= jumpHeight;
				}
			}

			//�n�ʂɒ��n������ēx�W�����v�ł���悤�ɂ���
			if (jumpCount == 0)
			{
				if (map8[leftBottomY][leftBottomX] == BLOCK || map8[rightBottomY][rightBottomX] == BLOCK)
				{
					jumpCount = 2;
				}
			}

			//���݈ʒu�̒�ӂ̏��
			playerBottomYInfo = player.y + player.r - 1;
			//�����݈ʒu�̒�ӂ̃}�b�v�`�b�v���(��ӂ̏�񂩂�}�b�v�`�b�v��ł̂ǂ̐����ɂ��邩���v�Z����)
			playerBottomYMaptip = (player.y + player.r - 1) / blockSize;

			//���ݒn���P����y���W�B���@�̒�ӂ̍��W�͈���̍����y���W�ɂȂ邽�߁B(���2�s����}�b�v��̎��@�̐�������ꂽ�̂ŁA�Œ肷��ʒu���w�肵�ău���b�N�T�C�Y�������Ă�����)
			playerBottomYHeightPlus = (playerBottomYMaptip + 1) * blockSize;
			//���ݒn���P���̃}�b�v�`�b�v�̏��
			playerBottomYMaptipPlus = (playerBottomYHeightPlus / blockSize);

			//���݈ʒu�̒��_�̏�� 
			playerTopYInfo = player.y - player.r;
			//���݈ʒu�̒��_�̃}�b�v�`�b�v���
			playerTopYMaptip = (player.y - player.r) / blockSize;
			//���_�����l�ɌŒ肷�邽�߂�y���W���o�����߂�y���W�����߂�B
			playerTopYHeight = (playerTopYMaptip + 1) * blockSize;

			//���W���ړ��������̂ŁA������x�e�S�̊p�̍��W���v�Z����B
			//�E��
			rightTopX = (player.x + player.r - 1) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			//����
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			//�E��
			rightBottomX = (player.x + player.r - 1) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;
			//����
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			//���ł���Ƃ�
			if (jumpCount < 3)
			{
				//������Ńu���b�N�ɂԂ��������̏���
				if (player.y <= (playerBottomYHeightPlus - player.r))
				{
					if (map8[leftTopY][leftTopX] != NONE || map8[rightTopY][rightTopX] != NONE)
					{
						jumpHeight = 0;
						isJump = 0;
					}
				}
			}

			//�������Ńu���b�N�ɂԂ��������̏���
			if (map8[leftBottomY][leftBottomX] != NONE || map8[rightBottomY][rightBottomX] != NONE)
			{
				player.y = playerTopYHeight - player.r;
				g = 0;
				isJump = 0;
				jumpCount = 2;
				jumpHeight = 25;
			}

			if (player.y >= (WIN_HEIGHT - 1) * blockSize - player.r)
			{
				player.y = (WIN_HEIGHT - 1) * blockSize - player.r;
				jumpCount = 2;
				jumpHeight = 25;
				isJump = 0;
			}

			//�S�[��
			GLcollision = GetGLcollision(goal2, player);
			if (GLcollision)
			{
				PlaySoundMem(clearse, DX_PLAYTYPE_BACK, true);
				isGoal = 1;
			}
		}

		// ---------- ���[�U�[�����蔻�� ---------- 
		if (scene == 7 || scene == 8)
		{
			//�l�p�̍��W�A�X�V
			leftTopX = (player.x - player.r) / blockSize;
			leftTopY = (player.y - player.r) / blockSize;
			leftBottomX = (player.x - player.r) / blockSize;
			leftBottomY = (player.y + player.r) / blockSize;

			rightTopX = (player.x + player.r) / blockSize;
			rightTopY = (player.y - player.r) / blockSize;
			rightBottomX = (player.x + player.r) / blockSize;
			rightBottomY = (player.y + player.r) / blockSize;

			if (scene == 7)
			{
				if (map7[leftTopY][leftTopX] == YOKOLASER || map7[rightTopY][rightTopX] == YOKOLASER ||
					map7[leftBottomY][leftBottomX] == YOKOLASER || map7[rightBottomY][rightBottomX] == YOKOLASER)
				{
					player.isAllive = 0;
				}
			}
			if (scene == 8)
			{
				if (map8[leftTopY][leftTopX] == TATELASER || map8[rightTopY][rightTopX] == TATELASER ||
					map8[leftBottomY][leftBottomX] == TATELASER || map8[rightBottomY][rightBottomX] == TATELASER)
				{
					player.isAllive = 0;
				}
			}
		}

		if (player.isAllive == 0)
		{
			player.isAllive = 1;
			isReset = 1;
		}

		// ---------- ---------- �X�e�[�W3_�I��� ---------- ---------- 

		// ----- ----- ���Z�b�g ----- ----- 
		if (keys[KEY_INPUT_R] == 1)
		{
			isReset = 1;
		}

		if (isReset == 1)
		{
			if (scene == 1 || scene == 2)
			{
				scene = 1;
			}

			if (scene == 3 || scene == 4)
			{
				scene = 3;
			}

			if (scene == 5 || scene == 6)
			{
				scene = 5;
			}

			if (scene == 7 || scene == 8)
			{
				scene = 7;
			}

			player.x = 96;
			player.y = 480;
			player.isAllive = 1;
			enemy.x = 1450;
			enemy.y = 800;
			enemy.flag = 1;
			isEnemy = 0;

			if (scene == 5 || scene == 6 || scene == 7 || scene == 8)
			{
				enemy.x2 = 20;
				enemy.y2 = 20;
				enemy.flag = 1;
				isEnemy = 0;
			}

			int uy = enemy.y;
			int ux = enemy.x;
			int ux2 = 1600 - enemy.x;

			//BLOCK��NONE�ɁA���[�U�[���Ăѕ\��
			for (int y = 0; y < mapSizeY; y++)
			{
				for (int x = 0; x < mapSizeX; x++)
				{
					//�`���[�g���A��(�\)
					if (map[y][x] == BLOCK)
					{
						map[y][x] = NONE;
					}

					//�`���[�g���A��(��)
					if (map2[y][x] == BLOCK)
					{
						map2[y][x] = NONE;
					}

					//�X�e�[�W�P(�\)
					if (map3[y][x] == BLOCK)
					{
						map3[y][x] = NONE;
					}

					//�X�e�[�W�P(��)
					if (map4[y][x] == BLOCK)
					{
						map4[y][x] = NONE;
					}

					//�X�e�[�W2(�\)
					if (map5[y][x] == BLOCK)
					{
						map5[y][x] = NONE;
					}

					//���[�U�[���Z�b�g(�X�e�[�W2�A�\)
					if (map5[5][x] == NONE)
					{
						map5[5][x] = YOKOLASER;
					}

					//�X�e�[�W2(��)
					if (map6[y][x] == BLOCK)
					{
						map6[y][x] = NONE;
					}

					//���[�U�[���Z�b�g(�X�e�[�W2�A��)
					if (map6[y][10] == NONE)
					{
						map6[y][10] = TATELASER;
					}

					if (map6[y][23] == NONE)
					{
						map6[y][23] = TATELASER;
					}

					if (map6[y][40] == NONE)
					{
						map6[y][40] = TATELASER;
					}

					//�X�e�[�W3(�\)
					if (map7[y][x] == BLOCK)
					{
						map7[y][x] = NONE;
					}

					//���[�U�[���Z�b�g(�X�e�[�W3�A�\)
					if (map7[29][x] == NONE)
					{
						map7[29][x] = YOKOLASER;
					}
					if (map7[y][22] == NONE)
					{
						map7[y][22] = TATELASER;
					}
					if (map7[y][35] == NONE)
					{
						if (y < 20)
						{
							map7[y][35] = TATELASER;
						}
					}

					//�X�e�[�W3(��)
					if (map8[y][x] == BLOCK)
					{
						map8[y][x] = NONE;
					}

					//���[�U�[���Z�b�g(�X�e�[�W3�A��)
					if (map8[y][10] == NONE)
					{
						if (y < 21)
						{
							map8[y][10] = TATELASER;
						}
					}
					if (map8[y][23] == NONE)
					{
						if (y < 21)
						{
							map8[y][23] = TATELASER;
						}
					}
					if (map8[y][40] == NONE)
					{
						map8[y][40] = TATELASER;
					}
					if (map8[20][x] == NONE)
					{
						map8[20][x] = YOKOLASER;
					}
					if (map8[29][x] == NONE)
					{
						map8[29][x] = YOKOLASER;
					}
				}
			}

			isReset = 0;
		}

		//�X�e�[�W�I����ʂɖ߂�
		if (scene != 99 && scene != 0 && isGoal == 1)
		{
			if (keys[KEY_INPUT_Q] == 1)
			{
				scene = 0;
				player.x = 80;
				player.y = 480;
				isGoal = 0;
			}
		}

		//�v���C���[�A�j���[�V�����^�C�}�[
		playerAnimationTimer -= 1;
		if (playerAnimationTimer == 0)
		{
			playerAnimationTimer = 25;
		}

		//�X�s�[�h����
		player.x += player.speedX;
		player.y += player.speedY;

		//�l�p�̍��W�A�X�V
		leftTopX = (player.x - player.r) / blockSize;
		leftTopY = (player.y - player.r) / blockSize;
		leftBottomX = (player.x - player.r) / blockSize;
		leftBottomY = (player.y + player.r - 1) / blockSize;

		rightTopX = (player.x + player.r - 1) / blockSize;
		rightTopY = (player.y - player.r) / blockSize;
		rightBottomX = (player.x + player.r - 1) / blockSize;
		rightBottomY = (player.y + player.r - 1) / blockSize;

		//���y
		if (scene == 1 || scene == 3 || scene == 5 || scene == 7)
		{
			StopSoundMem(titlebgm);
		}
		if (scene == 0)
		{
			StopSoundMem(gamebgm);
		}

		//�@�[�|�|�|�|�@�`�揈���@�[�|�|�|�|�@

		//��
		DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, backGround, true);

		//�^�C�g��
		if (scene == 99)
		{
			PlaySoundMem(titlebgm, DX_PLAYTYPE_BACK, false);
			DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, title, true);
		}

		//�}�b�v�`�b�v�`��
		if (isAnimation == 0 && isReverseAnimation == 0)
		{
			for (int y = 0; y < mapSizeY; y++)
			{
				for (int x = 0; x < mapSizeX; x++)
				{
					if (scene == 0)
					{
						PlaySoundMem(titlebgm, DX_PLAYTYPE_BACK, false);
						if (map0[y][x] == NONE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block, TRUE);
						}
						if (map0[y][x] == STAGE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block2, TRUE);
						}
						if (map0[y][x] == 10)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, hole, TRUE);
						}
					}
					if (scene == 1)
					{
						PlaySoundMem(gamebgm, DX_PLAYTYPE_LOOP, false);
						if (map[y][x] == NONE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block, TRUE);
						}
						if (map2[y][49 - x] == STAGE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, uraBlock, TRUE);
						}
						if (map[y][x] == STAGE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block2, TRUE);
						}
						if (map[y][x] == BLOCK)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block3, TRUE);
						}
						if (map[y][x] == 10)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, hole, TRUE);
						}
					}
					if (scene == 2)
					{
						if (map2[y][x] == NONE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block, TRUE);
						}
						if (map[y][49 - x] == STAGE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, uraBlock, TRUE);
						}
						if (map2[y][x] == STAGE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block2, TRUE);
						}
						if (map2[y][x] == BLOCK)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block3, TRUE);
						}
						if (map2[y][x] == 10)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, hole, TRUE);
						}
					}
					if (scene == 3)
					{
						PlaySoundMem(gamebgm, DX_PLAYTYPE_LOOP, false);
						if (map3[y][x] == NONE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block, TRUE);
						}
						if (map4[y][49 - x] == STAGE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, uraBlock, TRUE);
						}
						if (map3[y][x] == STAGE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block2, TRUE);
						}
						if (map3[y][x] == BLOCK)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block3, TRUE);
						}
						if (map3[y][x] == 10)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, hole, TRUE);
						}
					}
					if (scene == 4)
					{
						if (map4[y][x] == NONE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block, TRUE);
						}
						if (map3[y][49 - x] == STAGE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, uraBlock, TRUE);
						}
						if (map4[y][x] == STAGE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block2, TRUE);
						}
						if (map4[y][x] == BLOCK)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block3, TRUE);
						}
						if (map4[y][x] == 10)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, hole, TRUE);
						}
					}
					if (scene == 5)
					{
						PlaySoundMem(gamebgm, DX_PLAYTYPE_LOOP, false);
						if (map5[y][x] == NONE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block, TRUE);
						}
						if (map6[y][49 - x] == STAGE || map6[y][49 - x] == YOKOLASER || map6[y][49 - x] == TATELASER)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, uraBlock, TRUE);
						}
						if (map5[y][x] == STAGE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block2, TRUE);
						}
						if (map5[y][x] == BLOCK)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block3, TRUE);
						}
						if (map5[y][x] == LASERPOINT_X)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, laserpointX, TRUE);
						}
						if (map5[y][x] == YOKOLASER)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, laserX, TRUE);
						}
						if (map5[y][x] == LASERPOINT_Y)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, laserpointY, TRUE);
						}
						if (map5[y][x] == TATELASER)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, laserY, TRUE);
						}
						if (map5[y][x] == 10)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, hole, TRUE);
						}
					}
					if (scene == 6)
					{
						if (map6[y][x] == NONE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block, TRUE);
						}
						if (map5[y][49 - x] == STAGE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, uraBlock, TRUE);
						}
						if (map6[y][x] == STAGE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block2, TRUE);
						}
						if (map6[y][x] == BLOCK)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block3, TRUE);
						}
						if (map6[y][x] == LASERPOINT_X)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, laserpointX, TRUE);
						}
						if (map6[y][x] == YOKOLASER)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, laserX, TRUE);
						}
						if (map6[y][x] == LASERPOINT_Y)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, laserpointY, TRUE);
						}
						if (map6[y][x] == TATELASER)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, laserY, TRUE);
						}
						if (map6[y][x] == 10)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, hole, TRUE);
						}
					}
					if (scene == 7)
					{
						PlaySoundMem(gamebgm, DX_PLAYTYPE_LOOP, false);
						if (map7[y][x] == NONE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block, TRUE);
						}
						if (map8[y][49 - x] == STAGE || map8[y][49 - x] == YOKOLASER || map8[y][49 - x] == TATELASER)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, uraBlock, TRUE);
						}
						if (map7[y][x] == STAGE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block2, TRUE);
						}
						if (map7[y][x] == BLOCK)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block3, TRUE);
						}
						if (map7[y][x] == LASERPOINT_X)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, laserpointX, TRUE);
						}
						if (map7[y][x] == YOKOLASER)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, laserX, TRUE);
						}
						if (map7[y][x] == LASERPOINT_Y)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, laserpointY, TRUE);
						}
						if (map7[y][x] == TATELASER)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, laserY, TRUE);
						}
						if (map7[y][x] == 10)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, hole, TRUE);
						}
					}
					if (scene == 8)
					{
						if (map8[y][x] == NONE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block, TRUE);
						}
						if (map7[y][49 - x] == STAGE || map7[y][49 - x] == YOKOLASER || map7[y][49 - x] == TATELASER)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, uraBlock, TRUE);
						}
						if (map8[y][x] == STAGE)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block2, TRUE);
						}
						if (map8[y][x] == BLOCK)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, block3, TRUE);
						}
						if (map8[y][x] == LASERPOINT_X)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, laserpointX, TRUE);
						}
						if (map8[y][x] == YOKOLASER)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, laserX, TRUE);
						}
						if (map8[y][x] == LASERPOINT_Y)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, laserpointY, TRUE);
						}
						if (map8[y][x] == TATELASER)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, laserY, TRUE);
						}
						if (map8[y][x] == 10)
						{
							DrawGraph(x * blockSize + blockSize, y * blockSize + blockSize, hole, TRUE);
						}
					}
				}
			}
		}

		//�@�[�|�|�|�|�@�X�e�[�W�I����ʂ̕`��@�[�|�|�|�|�@
		if (scene == 0)
		{
			DrawGraph(648, 64, stageTex8, true);
			DrawGraph(door[0].startX - 25 + blockSize, doorStartY + blockSize, doorTex[0], true);
			DrawGraph(door[1].startX - 25 + blockSize, doorStartY + blockSize, doorTex[0], true);
			DrawGraph(door[2].startX - 25 + blockSize, doorStartY + blockSize, doorTex[0], true);
			DrawGraph(door[3].startX - 25 + blockSize, doorStartY + blockSize, doorTex[0], true);
			DrawGraph(door[4].startX - 25 + blockSize, doorStartY + blockSize, doorTex[0], true);
			for (int i = 0; i < 5; i++)
			{
				if (player.y - player.r < doorEndY && doorStartY < player.y + player.r)
				{
					if (player.x - player.r < door[i].endX && door[i].startX < player.x + player.r)
					{
						DrawGraph(player.x - player.r - 80 + blockSize, player.y - 80 + blockSize, stageTex5, TRUE);

						if (player.x - player.r < door[0].endX && door[0].startX < player.x + player.r)
						{
							DrawGraph(door[0].startX - 40 + blockSize, doorStartY - 20 + blockSize, stageTex0, TRUE);
						}
						if (player.x - player.r < door[1].endX && door[1].startX < player.x + player.r)
						{
							DrawGraph(door[1].startX - 10 + blockSize, doorStartY - 40 + blockSize, stageTex1, TRUE);
						}
						if (player.x - player.r < door[2].endX && door[2].startX < player.x + player.r)
						{
							DrawGraph(door[2].startX - 50 + blockSize, doorStartY - 40 + blockSize, stageTex2, TRUE);
						}
						if (player.x - player.r < door[3].endX && door[3].startX < player.x + player.r)
						{
							DrawGraph(door[3].startX - 55 + blockSize, doorStartY - 40 + blockSize, stageTex3, TRUE);
						}
						if (player.x - player.r < door[4].endX && door[4].startX < player.x + player.r)
						{
							DrawGraph(door[4].startX - 50 + blockSize, doorStartY - 40 + blockSize, stageTex4, TRUE);
						}
					}
				}
				if (isDoorAnime[i] == 1)
				{
					if (doorAnimeTimer <= 70 && doorAnimeTimer > 60)
					{
						DrawGraph(door[i].startX - 25 + blockSize, doorStartY + blockSize, doorTex[0], true);
					}
					if (doorAnimeTimer <= 60 && doorAnimeTimer > 50)
					{
						DrawGraph(door[i].startX - 25 + blockSize, doorStartY + blockSize, doorTex[1], true);
					}
					if (doorAnimeTimer <= 50 && doorAnimeTimer > 40)
					{
						DrawGraph(door[i].startX - 25 + blockSize, doorStartY + blockSize, doorTex[2], true);
					}
					if (doorAnimeTimer <= 40 && doorAnimeTimer > 30)
					{
						DrawGraph(door[i].startX - 25 + blockSize, doorStartY + blockSize, doorTex[3], true);
					}
					if (doorAnimeTimer <= 30 && doorAnimeTimer > 20)
					{
						DrawGraph(door[i].startX - 25 + blockSize, doorStartY + blockSize, doorTex[4], true);
					}
					if (doorAnimeTimer <= 20 && doorAnimeTimer > 10)
					{
						DrawGraph(door[i].startX - 25 + blockSize, doorStartY + blockSize, doorTex[5], true);
					}
					if (doorAnimeTimer <= 10 && doorAnimeTimer > 0)
					{
						DrawGraph(door[i].startX - 25 + blockSize, doorStartY + blockSize, doorTex[6], true);
					}
				}
			}
		}

		//�@�[�|�|�|�|�@�G�l�~�[�`��@�[�|�|�|�|�@
		if (isAnimation == 0 && isReverseAnimation == 0)
		{
			//�V�[��1 & �V�[��3
			if (scene == 1 || scene == 3)
			{
				DrawGraph(enemy.x - enemy.r * 2 + blockSize, enemy.y - enemy.r * 2 + blockSize, hudeTex, true);
			}

			//�V�[��5
			if (scene == 5 || scene == 7)
			{
				DrawGraph(enemy.x2 - enemy.r * 2 + blockSize, enemy.y2 - enemy.r * 2 + blockSize, hudeTex, true);
			}
		}

		//�@�[�|�|�|�|�@�S�[���`��@�[�|�|�|�|�@
		if (isAnimation == 0 && isReverseAnimation == 0)
		{
			if (scene == 2)
			{
				DrawGraph(cGoal.x - 70 + blockSize, cGoal.y - 60 + blockSize, doorTex[0], true);
			}

			if (scene == 4)
			{
				DrawGraph(goal.x - 70 + blockSize, goal.y - 60 + blockSize, doorTex[0], true);
			}

			if (scene == 6)
			{
				DrawGraph(goal.x - 70 + blockSize, goal.y - 60 + blockSize, doorTex[0], true);
			}

			if (scene == 8)
			{
				DrawGraph(goal2.x - 70 + blockSize, goal2.y - 60 + blockSize, doorTex[0], true);
			}
		}

		//�v���C���[�`��(�A�j���[�V����)
		if (isAnimation == 0 && isReverseAnimation == 0)
		{
			if (player.isAllive == 1)
			{
				if (keys[KEY_INPUT_A] == 1)
				{
					if (playerAnimationTimer <= 25 && playerAnimationTimer > 20)
					{
						DrawGraph(player.x - player.r + blockSize, player.y - player.r + blockSize, playerWalkLeftTex[0], true);
					}
					if (playerAnimationTimer <= 20 && playerAnimationTimer > 15)
					{
						DrawGraph(player.x - player.r + blockSize, player.y - player.r + blockSize, playerWalkLeftTex[1], true);
					}
					if (playerAnimationTimer <= 15 && playerAnimationTimer > 10)
					{
						DrawGraph(player.x - player.r + blockSize, player.y - player.r + blockSize, playerWalkLeftTex[2], true);
					}
					if (playerAnimationTimer <= 10 && playerAnimationTimer > 5)
					{
						DrawGraph(player.x - player.r + blockSize, player.y - player.r + blockSize, playerWalkLeftTex[3], true);
					}
					if (playerAnimationTimer <= 5 && playerAnimationTimer >= 0)
					{
						DrawGraph(player.x - player.r + blockSize, player.y - player.r + blockSize, playerWalkLeftTex[4], true);
					}
				}
				else if (keys[KEY_INPUT_D] == 1)
				{
					if (playerAnimationTimer <= 25 && playerAnimationTimer > 20)
					{
						DrawGraph(player.x - player.r + 32, player.y - player.r + 32, playerWalkRightTex[0], true);
					}
					if (playerAnimationTimer <= 20 && playerAnimationTimer > 15)
					{
						DrawGraph(player.x - player.r + 32, player.y - player.r + 32, playerWalkRightTex[1], true);
					}
					if (playerAnimationTimer <= 15 && playerAnimationTimer > 10)
					{
						DrawGraph(player.x - player.r + 32, player.y - player.r + 32, playerWalkRightTex[2], true);
					}
					if (playerAnimationTimer <= 10 && playerAnimationTimer > 5)
					{
						DrawGraph(player.x - player.r + 32, player.y - player.r + 32, playerWalkRightTex[3], true);
					}
					if (playerAnimationTimer <= 5 && playerAnimationTimer >= 0)
					{
						DrawGraph(player.x - player.r + 32, player.y - player.r + 32, playerWalkRightTex[4], true);
					}
				}
				else
				{
					if (playerAnimationTimer <= 25 && playerAnimationTimer > 20)
					{
						DrawGraph(player.x - player.r + 32, player.y - player.r + 32, playerWaitTex[0], true);
					}
					if (playerAnimationTimer <= 20 && playerAnimationTimer > 15)
					{
						DrawGraph(player.x - player.r + 32, player.y - player.r + 32, playerWaitTex[1], true);
					}
					if (playerAnimationTimer <= 15 && playerAnimationTimer > 10)
					{
						DrawGraph(player.x - player.r + 32, player.y - player.r + 32, playerWaitTex[2], true);
					}
					if (playerAnimationTimer <= 10 && playerAnimationTimer > 5)
					{
						DrawGraph(player.x - player.r + 32, player.y - player.r + 32, playerWaitTex[3], true);
					}
					if (playerAnimationTimer <= 5 && playerAnimationTimer >= 0)
					{
						DrawGraph(player.x - player.r + 32, player.y - player.r + 32, playerWaitTex[4], true);
					}
				}
			}
		}

		//�@�[�|�|�|�|�@�V�[���؂�ւ��\���̕`��@�[�|�|�|�|�@
		if (isAnimation == 0 && isReverseAnimation == 0)
		{
			if (scene != 99 && scene != 0)
			{
				if (scene == 2 || scene == 4 || scene == 6 || scene == 8)
				{
					if (player.x <= 16)
					{
						DrawGraph(player.x - player.r, player.y - 80 + blockSize, stageTex6, TRUE);
					}
				}
				if (scene == 1 || scene == 3 || scene == 5 || scene == 7)
				{
					if (player.x >= 1500)
					{
						DrawGraph(player.x - player.r - 100 + blockSize, player.y - 80 + blockSize, stageTex7, TRUE);
					}
				}
			}
		}

		//�`���[�g���A���̃���
		if (scene == 1 && isAnimation == 0)
		{
			if (tekisutoTimer <= 20 && tekisutoTimer > 10)
			{
				DrawGraph(648, 64, tekisuto[0], true);
			}
			if (tekisutoTimer <= 10 && tekisutoTimer > 0)
			{
				DrawGraph(648, 64, tekisuto[1], true);
			}
		}

		//�߂���A�j���[�V����(�\)
		if (isAnimation == 1)
		{

			if (peraAnimeTimer <= 42 && peraAnimeTimer > 39)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[0], true);
			}
			if (peraAnimeTimer <= 39 && peraAnimeTimer > 36)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[1], true);
			}
			if (peraAnimeTimer <= 36 && peraAnimeTimer > 33)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[2], true);
			}
			if (peraAnimeTimer <= 33 && peraAnimeTimer > 30)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[3], true);
			}
			if (peraAnimeTimer <= 30 && peraAnimeTimer > 27)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[4], true);
			}
			if (peraAnimeTimer <= 27 && peraAnimeTimer > 24)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[5], true);
			}
			if (peraAnimeTimer <= 24 && peraAnimeTimer > 21)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[6], true);
			}
			if (peraAnimeTimer <= 21 && peraAnimeTimer > 18)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[7], true);
			}
			if (peraAnimeTimer <= 18 && peraAnimeTimer > 15)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[8], true);
			}
			if (peraAnimeTimer <= 15 && peraAnimeTimer > 12)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[9], true);
			}
			if (peraAnimeTimer <= 12 && peraAnimeTimer > 9)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[10], true);
			}
			if (peraAnimeTimer <= 9 && peraAnimeTimer > 6)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[11], true);
			}
			if (peraAnimeTimer <= 6 && peraAnimeTimer > 3)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[12], true);
			}
			if (peraAnimeTimer <= 3 && peraAnimeTimer > 0)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[13], true);
			}
		}

		//�߂���A�j���[�V����(��)
		if (isReverseAnimation == 1)
		{

			if (peraAnimeTimer <= 42 && peraAnimeTimer > 39)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[13], true);
			}
			if (peraAnimeTimer <= 39 && peraAnimeTimer > 36)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[12], true);
			}
			if (peraAnimeTimer <= 36 && peraAnimeTimer > 33)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[11], true);
			}
			if (peraAnimeTimer <= 33 && peraAnimeTimer > 30)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[10], true);
			}
			if (peraAnimeTimer <= 30 && peraAnimeTimer > 27)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[9], true);
			}
			if (peraAnimeTimer <= 27 && peraAnimeTimer > 24)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[8], true);
			}
			if (peraAnimeTimer <= 24 && peraAnimeTimer > 21)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[7], true);
			}
			if (peraAnimeTimer <= 21 && peraAnimeTimer > 18)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[6], true);
			}
			if (peraAnimeTimer <= 18 && peraAnimeTimer > 15)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[5], true);
			}
			if (peraAnimeTimer <= 15 && peraAnimeTimer > 12)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[4], true);
			}
			if (peraAnimeTimer <= 12 && peraAnimeTimer > 9)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[3], true);
			}
			if (peraAnimeTimer <= 9 && peraAnimeTimer > 6)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[2], true);
			}
			if (peraAnimeTimer <= 6 && peraAnimeTimer > 3)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[1], true);
			}
			if (peraAnimeTimer <= 3 && peraAnimeTimer > 0)
			{
				DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, peraAnime[0], true);
			}
		}

		//�S�[�����A(��)�`��
		if (isGoal == 1)
		{
			DrawGraph(32, 32, GoalTexBack, true);
		}

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}

void WindowSetteings()
{
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);
}