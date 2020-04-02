#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include <random>
#include "gamelib.h"
#include "Dice.h"
namespace game_framework
{
	Dice::Dice(): _diceNumber(0) ,_isToss(true), _x(580), _y(420){}

	int Dice::GetDiceNumber() {
		return _diceNumber;
	}
	void Dice::setXY(int x, int y) {
		_x = x;
		_y = y;
	}
	void Dice::SetDiceIsToss(bool flag) {
		_isToss = flag;
	}

	bool Dice::IsToss() {
		return _isToss;
	}
	void Dice::SetDiceNumber(int diceNum) {
		_diceNumber = diceNum;
	}
	void Dice::TossDice(int diceNum) {
		if (_isToss) {
			if (diceNum == 0) {
				std::random_device rd;
				std::default_random_engine gen = std::default_random_engine(rd());
				std::uniform_int_distribution<int> dis(1, 6);
				_diceNumber = dis(gen);
			}
			else {
				_diceNumber = diceNum;
			}
			_isToss = false;
		}
	}

	void Dice::LoadBitmap() {
		_zero.LoadBitmap(IDB_Question);
		_one.LoadBitmap(IDB_DICEONE);
		_two.LoadBitmap(IDB_DICETWO);
		_three.LoadBitmap(IDB_DICETHREE);
		_four.LoadBitmap(IDB_DICEFOUR);
		_five.LoadBitmap(IDB_DICEFIVE);
		_six.LoadBitmap(IDB_DICESIX);
		
	}
	void Dice::OnShow() {
		switch (_diceNumber) {
		case 0:
			_zero.SetTopLeft(_x, _y);
			_zero.ShowBitmap();
			break;
		case 1:
			_one.SetTopLeft(_x, _y);
			_one.ShowBitmap();
			break;
		case 2:
			_two.SetTopLeft(_x, _y);
			_two.ShowBitmap();
			break;
		case 3:
			_three.SetTopLeft(_x, _y);
			_three.ShowBitmap();
			break;
		case 4:
			_four.SetTopLeft(_x, _y);
			_four.ShowBitmap();
			break;
		case 5:
			_five.SetTopLeft(_x, _y);
			_five.ShowBitmap();
			break;
		case 6:
			_six.SetTopLeft(_x, _y);
			_six.ShowBitmap();
			break;
		}

	}
}