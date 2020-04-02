#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameMap.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	GameMap::GameMap()
		:_referenceX(0), _referenceY(0), MW(640), MH(480)
	{
		Initialize();
	}
	
	int GameMap::GetX1()
	{
		return _referenceX;
	}

	int GameMap::GetY1()
	{
		return _referenceY;
	}
	

	void GameMap::Initialize()
	{
		int map_init[5][3] = { {0,1,2},
							   {3,4,5},
							   {6,7,8},
						       {9,10,11},
						       {12,13,14} };
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 3; j++)
				map[i][j] = map_init[i][j];
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void GameMap::LoadBitmap()
	{
		zero.LoadBitmap(IDB_zero);
		one.LoadBitmap(IDB_one);
		two.LoadBitmap(IDB_two);
		three.LoadBitmap(IDB_three);
		four.LoadBitmap(IDB_four);
		five.LoadBitmap(IDB_five);
		six.LoadBitmap(IDB_six);
		seven.LoadBitmap(IDB_seven);
		eight.LoadBitmap(IDB_eight);
		nine.LoadBitmap(IDB_nine);
		ten.LoadBitmap(IDB_ten);
		eleven.LoadBitmap(IDB_eleven);
		twelve.LoadBitmap(IDB_twelve);
		thirsteen.LoadBitmapA(IDB_thirsteen);
		fourteen.LoadBitmapA(IDB_fourteen);

	}

	void GameMap::OnMove()
	{
		const int STEP_SIZE = 10;
		//animation.OnMove();
		if(_referenceX + STEP_SIZE <= 0){
			if (isMovingLeft)
				_referenceX += STEP_SIZE;
		}
		if(_referenceX - STEP_SIZE >= -1280){
			if (isMovingRight)
				_referenceX -= STEP_SIZE;
		}
		if(_referenceY + STEP_SIZE <= 0){
			if (isMovingUp)
				_referenceY += STEP_SIZE;
		}
		if(_referenceY - STEP_SIZE >= -1920){
			if (isMovingDown)
				_referenceY -= STEP_SIZE;
		}
	}
	void GameMap::OnMove(int camerax, int cameray) {
		if (_referenceX + camerax <= 0 && _referenceX + camerax >= -1280) {
			_referenceX += camerax;
		}
		else if (camerax > 0) {
			_referenceX = 0;
		}
		else if (camerax < 0) {
			_referenceX = -1280;
		}
		if (_referenceY + cameray <= 0 && _referenceY + cameray >= -1920) {
			_referenceY += cameray;
		}
		else if (cameray > 0) {
			_referenceY = 0;
		}
		else if (cameray < 0) {
			_referenceY = -1920;
		}
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
		_referenceX = nx; _referenceY = ny;
	}

	void GameMap::OnShow()
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 5; j++)
			{
				if (_referenceX + (MW*i) < 641 && _referenceX + (MW*i) > -641 && _referenceY + (MH*j) < 481 && _referenceY + (MH*j) > -481) {
					switch (map[j][i])
					{
					case 0:
						zero.SetTopLeft(_referenceX + (MW*i), _referenceY + (MH*j));//
						zero.ShowBitmap();
						break;
					case 1:
						one.SetTopLeft(_referenceX + (MW*i), _referenceY + (MH*j));//
						one.ShowBitmap();
						break;
					case 2:
						two.SetTopLeft(_referenceX + (MW*i), _referenceY + (MH*j));
						two.ShowBitmap();
						break;
					case 3:
						three.SetTopLeft(_referenceX + (MW*i), _referenceY + (MH*j));//
						three.ShowBitmap();
						break;
					case 4:
						four.SetTopLeft(_referenceX + (MW*i), _referenceY + (MH*j));//
						four.ShowBitmap();
						break;
					case 5:
						five.SetTopLeft(_referenceX + (MW*i), _referenceY + (MH*j));//
						five.ShowBitmap();
						break;
					case 6:
						six.SetTopLeft(_referenceX + (MW*i), _referenceY + (MH*j));//
						six.ShowBitmap();
						break;
					case 7:
						seven.SetTopLeft(_referenceX + (MW*i), _referenceY + (MH*j));//
						seven.ShowBitmap();
						break;
					case 8:
						eight.SetTopLeft(_referenceX + (MW*i), _referenceY + (MH*j));//
						eight.ShowBitmap();
						break;
					case 9:
						nine.SetTopLeft(_referenceX + (MW*i), _referenceY + (MH*j));//
						nine.ShowBitmap();
						break;
					case 10:
						ten.SetTopLeft(_referenceX + (MW*i), _referenceY + (MH*j));//
						ten.ShowBitmap();
						break;
					case 11:
						eleven.SetTopLeft(_referenceX + (MW*i), _referenceY + (MH*j));//
						eleven.ShowBitmap();
						break;
					case 12:
						twelve.SetTopLeft(_referenceX + (MW*i), _referenceY + (MH*j));//
						twelve.ShowBitmap();
						break;
					case 13:
						thirsteen.SetTopLeft(_referenceX + (MW*i), _referenceY + (MH*j));//
						thirsteen.ShowBitmap();
						break;
					case 14:
						fourteen.SetTopLeft(_referenceX + (MW*i), _referenceY + (MH*j));//
						fourteen.ShowBitmap();
						break;
					default:
						ASSERT(0);
					}
				}
			}
	}
}