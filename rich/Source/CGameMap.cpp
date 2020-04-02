#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameMap.h"


namespace game_framework {
	
	GameMap::CGameMap()
		:X(20), Y(40), MW(120), MH(100)
	{
		int map_init[5][3] = { {0,0,1},
							   {0,1,2},
							   {1,2,1},
							   {2,1,2},
							   {1,2,1} };
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 5; j++)
				map[i][j] = map_init[i][j];
	}

	void GameMap::LoadBitmap()
	{
		blue.LoadBitmap(IDB_BLUE);
		green.LoadBitmap(IDB_GREEN);
	}
	void GameMap::OnShow()
	{
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 4; j++)
			{
				switch (map[j][i])
				{
				case 0:
					break;
				case 1:
					blue.SetTopLeft(X + (MW*i), Y + (MH*j));
					blue.ShowBitmap();
					break;
				case 2:
					green.SetTopLeft(X + (MW*i), Y + (MH*j));
					green.ShowBitmap();
					break;
				default:
					ASSERT(0);
				}
			}
	
	}

	void GameMap::OnKeyDown(UINT nChar)
	{
		const int KEY_SPACE = 0x20;
		if (nChar == KEY_SPACE)
		{
		}
	}
	void GameMap::OnMove()
	{
		const int STEP_SIZE = 2;
		animation.OnMove();
		if (isMovingLeft)
			x -= STEP_SIZE;
		if (isMovingRight)
			x += STEP_SIZE;
		if (isMovingUp)
			y -= STEP_SIZE;
		if (isMovingDown)
			y += STEP_SIZE;*/
	}
	void GameMap::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void GameMap::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void GameMap::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void GameMap::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void GameMap::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void GameMap::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}

}