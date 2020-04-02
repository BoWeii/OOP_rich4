#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "StartMenu.h"
namespace game_framework {
	StartMenu::StartMenu() : _playerAmount(2) , _isDone(false) {
	}
	bool StartMenu::GetDone() {
		return _isDone;
	}
	void StartMenu::SetDone(bool flag) {
		_isDone = flag;
	}
	unsigned int StartMenu::GetPlayerAmount() {
		return _playerAmount;
	}
	void StartMenu::OnChoose(int posx, int posy, bool mouseclick) {
		if (posx > 85 && posx < 185 && posy > 190 && posy < 290 && mouseclick)
			_playerAmount = 2;
		else if (posx > 270 && posx < 370 && posy > 190 && posy < 290 && mouseclick)
			_playerAmount = 3;
		else if (posx > 455 && posx < 555 && posy > 190 && posy < 290 && mouseclick)
			_playerAmount = 4;
	}
	void StartMenu::LoadBitmap() {
		_playerChoosed[0][0].LoadBitmap(IDB_P2);
		_playerChoosed[0][1].LoadBitmap(IDB_P3);
		_playerChoosed[0][2].LoadBitmap(IDB_P4);
		_playerChoosed[1][0].LoadBitmap(IDB_CP2);
		_playerChoosed[1][1].LoadBitmap(IDB_CP3);
		_playerChoosed[1][2].LoadBitmap(IDB_CP4);
	}
	void StartMenu::OnShow() {
		_playerChoosed[0][0].SetTopLeft(85, 190);
		_playerChoosed[0][1].SetTopLeft(270, 190);
		_playerChoosed[0][2].SetTopLeft(455, 190);
		_playerChoosed[1][0].SetTopLeft(85, 190);
		_playerChoosed[1][1].SetTopLeft(270, 190);
		_playerChoosed[1][2].SetTopLeft(455, 190);
		switch (_playerAmount) {
		case 2:
			_playerChoosed[1][0].ShowBitmap();
			_playerChoosed[0][1].ShowBitmap();
			_playerChoosed[0][2].ShowBitmap();
			break;
		case 3:
			_playerChoosed[0][0].ShowBitmap();
			_playerChoosed[1][1].ShowBitmap();
			_playerChoosed[0][2].ShowBitmap();
			break;
		case 4:
			_playerChoosed[0][0].ShowBitmap();
			_playerChoosed[0][1].ShowBitmap();
			_playerChoosed[1][2].ShowBitmap();
			break;
		default:
			break;
		}
	}
}