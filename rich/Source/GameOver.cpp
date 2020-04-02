#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameOver.h"
namespace game_framework {
	GameOver::GameOver()
	{
		_isOpen = _isOK = _isTouch = false;
	}
	bool GameOver::IsOK()
	{
		return _isOK;
	}
	void GameOver::SetIsOK(bool flag)
	{
		_isOK = flag;
	}
	void GameOver::bankrupt(Role *role, int x, int y,bool mouseclick) 
	{	
		_isOpen = true;
		if (x > 300 && x < _OK.Width() + 300 && y>350 && y < 350 + _OK.Height())
		{
			_isTouch = true;
			if (mouseclick)
			{
				_isOK = true;
				_isOpen = false;
				Sleep(150);
			}		
		}
		else
			_isTouch = false;
	}
	void GameOver::LoadBitmap()
	{
		_winBK.LoadBitmap(IDB_win);
		_bankruptBK.LoadBitmap(IDB_bankrupt);
		_OK.LoadBitmap(IDB_L_OK);
		_OKT.LoadBitmap(IDB_L_OK_T);
		_r1.LoadBitmap(IDB_R101);
		_r2.LoadBitmap(IDB_R201);
		_r3.LoadBitmap(IDB_R301);
		_r4.LoadBitmap(IDB_R401);
	}
	void GameOver::OnShow(Role *role,int size)
	{
		_bankruptBK.SetTopLeft(80, 100);
		_winBK.SetTopLeft(80, 100);
		_OK.SetTopLeft(300, 350);
		_OKT.SetTopLeft(300, 350);
		_r1.SetTopLeft(300, 250);
		_r2.SetTopLeft(300, 250);
		_r3.SetTopLeft(300, 250);
		_r4.SetTopLeft(300, 250);
		if (_isOpen)
		{
			if (size >= 2)//------------------破產的畫面
				_bankruptBK.ShowBitmap();
			else//----------------------------勝利者的畫面
				_winBK.ShowBitmap();
			if (role->GetRoleNum() == 0)
				_r1.ShowBitmap();
			else if (role->GetRoleNum() == 1)
				_r2.ShowBitmap();
			else if (role->GetRoleNum() == 2)
				_r3.ShowBitmap();
			else if (role->GetRoleNum() == 3)
				_r4.ShowBitmap();
			if(_isTouch)
				_OKT.ShowBitmap();
			else
				_OK.ShowBitmap();
		}
	}
}