#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Role.h"

namespace game_framework
{
	Role::Role()
		:_referenceX(0), _referenceY(0), _stepNum(0), _x(560), _y(280) ,_mystate(0), _money(5){
		_roleTurn = _isMovingLeft = _isMovingRight = _isMovingUp = _isMovingDown = false;
		_showRole = true;
		_money.SetInteger(10000);
	}
	Role::Role(int roleNumber) : _referenceX(0), _referenceY(0), _stepNum(0), _money(5),_roleNumber(roleNumber) {
		switch (roleNumber) {
		case 0:
			_x = 560;
			_y = 280;
			_mystate = 0;
			break;
		case 1:
			_x = 224;
			_y = 960;
			_mystate = 10;
			break;
		case 2:
			_x = 704;
			_y = 1944;
			_mystate = 30;
			break;

		case 3:
			_x = 1388;
			_y = 228;
			_mystate = 60;
			break;
		default:
			_x = 560;
			_y = 280;
			_mystate = 0;
		}
		_showRole = true;
		_roleTurn = _isMovingLeft = _isMovingRight = _isMovingUp = _isMovingDown = false;
		_money.SetInteger(10000);
	}
	void Role::SetShowRole(bool flag) {
		_showRole = flag;
	}
	int Role::GetCameraX()
	{
		if (320 != _x ) {
			return 320 - _x;
		}
		else {
			return  0;
		}
	}
	int Role::GetCameraY()
	{
		if (240 != _y) {
			return 240 - _y;
		}
		else {
			return  0;
		}
	}
	int Role::GetX() {
		return _x;
	}
	int Role::GetY() {
		return _y;
	}
	void Role::AddMoney(int price) {
		_money.Add(price);
	}
	int Role::GetMoney() {
		return _money.GetInteger();
	}
	int Role::GetRoleNum() {
		return _roleNumber;
	}
	int Role::GetRoleState() {
		return _mystate;
	}
	bool Role::SetRoleMove(Station* state,int direction) {
		int stepSize = 4;
		if (_x != state->GetX()) {
			if (_x < state->GetX()) {
				_x += stepSize;
			}
			if (_x > state->GetX()) {
				_x -= stepSize;
			}
		}
		if (_y != state->GetY()) {
			if (_y < state->GetY()) {
				_y += stepSize;
			}
			if (_y > state->GetY()) {
				_y -= stepSize;
			}
		}

		if (_x == state->GetX() && _y == state->GetY()) {
			if (direction > 0) {
				_mystate++;
				if (_mystate == 81) {
					_mystate = 0;
				}
			}
			else if(direction<0){
				_mystate--;
				if (_mystate == -1) {
					_mystate = 80;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}
	int Role::RoleMove(int diceNum, Station **state) {
		int stepSize = 4;
		int nextstate = _mystate + 1;
		if (_mystate == 80) {
			nextstate = 0;
		}
		if (diceNum > 0) {
			if (_x != state[nextstate]->GetX()) {
 				if (_x < state[nextstate]->GetX()) {
 					_x += stepSize;
				}
				if (_x > state[nextstate]->GetX()) {
					_x -= stepSize;
				}
			}
			if (_y != state[nextstate]->GetY()) {
				if (_y < state[nextstate]->GetY()) {
					_y += stepSize;
				}
				if (_y > state[nextstate]->GetY()) {
					_y -= stepSize;
				}
			}

			if (_x == state[nextstate]->GetX() && _y == state[nextstate]->GetY()) {
				++_mystate;
				if (_mystate > 80) {
					_mystate = 0;
				}
				return diceNum-1;
			}
		}
		if (_roleNumber == 0) {
			_roleOneDown.OnMove();
			_roleOneUp.OnMove();
			_roleOneLeft.OnMove();
			_roleOneRight.OnMove();
		}
		else if (_roleNumber == 1) {
			_roleTwoDown.OnMove();
			_roleTwoUp.OnMove();
			_roleTwoLeft.OnMove();
			_roleTwoRight.OnMove();
		}
		else if (_roleNumber == 2) {
			_roleThreeDown.OnMove();
			_roleThreeUp.OnMove();
			_roleThreeLeft.OnMove();
			_roleThreeRight.OnMove();
		}
		else if (_roleNumber == 3) {
			_roleFourDown.OnMove();
			_roleFourUp.OnMove();
			_roleFourLeft.OnMove();
			_roleFourRight.OnMove();
		}
		
		return diceNum;
	}

	void Role::SetRoleTurn(bool flag)
	{
		_roleTurn = flag;
	}
	void Role::OnMove()
	{
		const int STEP_SIZE = 10;
		if (_referenceX + STEP_SIZE <= 0 && _isMovingLeft) {
			_x += STEP_SIZE;
			_referenceX += STEP_SIZE;
		}
		if (_referenceX - STEP_SIZE >= -1280 && _isMovingRight) {
			_x -= STEP_SIZE;
			_referenceX -= STEP_SIZE;
		}
		if (_referenceY + STEP_SIZE <= 0 && _isMovingUp) {
			_y += STEP_SIZE;
			_referenceY += STEP_SIZE;
		}
		if (_referenceY - STEP_SIZE >= -1920 && _isMovingDown) {
			_y -= STEP_SIZE;
			_referenceY -= STEP_SIZE;
		}

	}
	void Role::OnMove(int camerax, int cameray) {
		if (_referenceX + camerax <= 0 && _referenceX + camerax >= -1280) {
			_referenceX += camerax;
			_x += camerax;
		}
		else if (camerax > 0) {
			_x = _x - _referenceX;
			_referenceX = 0;
			_x = _referenceX + _x;
		}
		else if (camerax < 0) {
			_x = _x - _referenceX;
			_referenceX = -1280;
			_x = _referenceX + _x;
		}
		if (_referenceY + cameray <= 0 && _referenceY + cameray >= -1920) {
			_referenceY += cameray;
			_y += cameray;
		}
		else if (cameray > 0) {
			_y = _y - _referenceY;
			_referenceY = 0;
			_y = _referenceY + _y;
		}
		else if (cameray < 0) {
			_y = _y - _referenceY;
			_referenceY = -1920;
			_y = _referenceY + _y;
		}
	}

	void Role::LoadBitmap() {
		_money.LoadBitmap();
		if (_roleNumber==0) {
			_roleOneDown.AddBitmap(IDB_R101, RGB(0, 0, 100));
			_roleOneDown.AddBitmap(IDB_R102, RGB(0, 0, 100));
			_roleOneDown.AddBitmap(IDB_R103, RGB(0, 0, 100));
			_roleOneDown.AddBitmap(IDB_R104, RGB(0, 0, 100));
			_roleOneUp.AddBitmap(IDB_R113, RGB(0, 0, 100));
			_roleOneUp.AddBitmap(IDB_R114, RGB(0, 0, 100));
			_roleOneUp.AddBitmap(IDB_R115, RGB(0, 0, 100));
			_roleOneUp.AddBitmap(IDB_R116, RGB(0, 0, 100));
			_roleOneLeft.AddBitmap(IDB_R105, RGB(0, 0, 100));
			_roleOneLeft.AddBitmap(IDB_R106, RGB(0, 0, 100));
			_roleOneLeft.AddBitmap(IDB_R107, RGB(0, 0, 100));
			_roleOneLeft.AddBitmap(IDB_R108, RGB(0, 0, 100));
			_roleOneRight.AddBitmap(IDB_R109, RGB(0, 0, 100));
			_roleOneRight.AddBitmap(IDB_R110, RGB(0, 0, 100));
			_roleOneRight.AddBitmap(IDB_R111, RGB(0, 0, 100));
			_roleOneRight.AddBitmap(IDB_R112, RGB(0, 0, 100));
		}
		else if (_roleNumber == 1) {
			_roleTwoDown.AddBitmap(IDB_R201, RGB(0, 0, 100));
			_roleTwoDown.AddBitmap(IDB_R202, RGB(0, 0, 100));
			_roleTwoDown.AddBitmap(IDB_R203, RGB(0, 0, 100));
			_roleTwoDown.AddBitmap(IDB_R204, RGB(0, 0, 100));
			_roleTwoUp.AddBitmap(IDB_R213, RGB(0, 0, 100));
			_roleTwoUp.AddBitmap(IDB_R214, RGB(0, 0, 100));
			_roleTwoUp.AddBitmap(IDB_R215, RGB(0, 0, 100));
			_roleTwoUp.AddBitmap(IDB_R216, RGB(0, 0, 100));
			_roleTwoLeft.AddBitmap(IDB_R205, RGB(0, 0, 100));
			_roleTwoLeft.AddBitmap(IDB_R206, RGB(0, 0, 100));
			_roleTwoLeft.AddBitmap(IDB_R207, RGB(0, 0, 100));
			_roleTwoLeft.AddBitmap(IDB_R208, RGB(0, 0, 100));
			_roleTwoRight.AddBitmap(IDB_R209, RGB(0, 0, 100));
			_roleTwoRight.AddBitmap(IDB_R210, RGB(0, 0, 100));
			_roleTwoRight.AddBitmap(IDB_R211, RGB(0, 0, 100));
			_roleTwoRight.AddBitmap(IDB_R212, RGB(0, 0, 100));
		}
		else if (_roleNumber == 2) {
			_roleThreeDown.AddBitmap(IDB_R301, RGB(0, 0, 100));
			_roleThreeDown.AddBitmap(IDB_R302, RGB(0, 0, 100));
			_roleThreeDown.AddBitmap(IDB_R303, RGB(0, 0, 100));
			_roleThreeDown.AddBitmap(IDB_R304, RGB(0, 0, 100));
			_roleThreeUp.AddBitmap(IDB_R313, RGB(0, 0, 100));
			_roleThreeUp.AddBitmap(IDB_R314, RGB(0, 0, 100));
			_roleThreeUp.AddBitmap(IDB_R315, RGB(0, 0, 100));
			_roleThreeUp.AddBitmap(IDB_R316, RGB(0, 0, 100));
			_roleThreeLeft.AddBitmap(IDB_R305, RGB(0, 0, 100));
			_roleThreeLeft.AddBitmap(IDB_R306, RGB(0, 0, 100));
			_roleThreeLeft.AddBitmap(IDB_R307, RGB(0, 0, 100));
			_roleThreeLeft.AddBitmap(IDB_R308, RGB(0, 0, 100));
			_roleThreeRight.AddBitmap(IDB_R309, RGB(0, 0, 100));
			_roleThreeRight.AddBitmap(IDB_R310, RGB(0, 0, 100));
			_roleThreeRight.AddBitmap(IDB_R311, RGB(0, 0, 100));
			_roleThreeRight.AddBitmap(IDB_R312, RGB(0, 0, 100));
		}
		else if (_roleNumber == 3) {
			_roleFourDown.AddBitmap(IDB_R401, RGB(0, 0, 100));
			_roleFourDown.AddBitmap(IDB_R402, RGB(0, 0, 100));
			_roleFourDown.AddBitmap(IDB_R403, RGB(0, 0, 100));
			_roleFourDown.AddBitmap(IDB_R404, RGB(0, 0, 100));
			_roleFourUp.AddBitmap(IDB_R413, RGB(0, 0, 100));
			_roleFourUp.AddBitmap(IDB_R414, RGB(0, 0, 100));
			_roleFourUp.AddBitmap(IDB_R415, RGB(0, 0, 100));
			_roleFourUp.AddBitmap(IDB_R416, RGB(0, 0, 100));
			_roleFourLeft.AddBitmap(IDB_R405, RGB(0, 0, 100));
			_roleFourLeft.AddBitmap(IDB_R406, RGB(0, 0, 100));
			_roleFourLeft.AddBitmap(IDB_R407, RGB(0, 0, 100));
			_roleFourLeft.AddBitmap(IDB_R408, RGB(0, 0, 100));
			_roleFourRight.AddBitmap(IDB_R409, RGB(0, 0, 100));
			_roleFourRight.AddBitmap(IDB_R410, RGB(0, 0, 100));
			_roleFourRight.AddBitmap(IDB_R411, RGB(0, 0, 100));
			_roleFourRight.AddBitmap(IDB_R412, RGB(0, 0, 100));
		}
	}
	void Role::SetMovingDown(bool flag)
	{
		_isMovingDown = flag;
	}

	void Role::SetMovingLeft(bool flag)
	{
		_isMovingLeft = flag;
	}

	void Role::SetMovingRight(bool flag)
	{
		_isMovingRight = flag;
	}

	void Role::SetMovingUp(bool flag)
	{
		_isMovingUp = flag;
	}
	void Role::OnShow(Station **state) {
		int nextstate = _mystate + 1;
		if (_mystate == 80) {
			nextstate = 0;
		}
		if (_showRole) {
			if (_x <= 690 && _x >= -50 && _y >= -50 && _y <= 530) {
				if (_roleNumber == 0) {
					if (_y < state[nextstate]->GetY()) {
						_roleOneDown.SetTopLeft(_x + 5, _y - 45);
						_roleOneDown.OnShow();
					}
					else if (_y > state[nextstate]->GetY()) {
						_roleOneUp.SetTopLeft(_x + 5, _y - 45);
						_roleOneUp.OnShow();
					}
					else if (_x > state[nextstate]->GetX()) {
						_roleOneLeft.SetTopLeft(_x + 5, _y - 45);
						_roleOneLeft.OnShow();
					}
					else if (_x < state[nextstate]->GetX()) {
						_roleOneRight.SetTopLeft(_x + 5, _y - 45);
						_roleOneRight.OnShow();
					}
					else {
						_roleOneDown.SetTopLeft(_x + 5, _y - 45);
						_roleOneDown.OnShow();
					}
				}
				else if (_roleNumber == 1) {
					if (_y < state[nextstate]->GetY()) {
						_roleTwoDown.SetTopLeft(_x + 2, _y - 55);
						_roleTwoDown.OnShow();
					}
					else if (_y > state[nextstate]->GetY()) {
						_roleTwoUp.SetTopLeft(_x + 2, _y - 55);
						_roleTwoUp.OnShow();
					}
					else if (_x > state[nextstate]->GetX()) {
						_roleTwoLeft.SetTopLeft(_x + 2, _y - 55);
						_roleTwoLeft.OnShow();
					}
					else if (_x < state[nextstate]->GetX()) {
						_roleTwoRight.SetTopLeft(_x + 2, _y - 55);
						_roleTwoRight.OnShow();
					}
					else {
						_roleTwoDown.SetTopLeft(_x + 2, _y - 55);
						_roleTwoDown.OnShow();
					}
				}
				else if (_roleNumber == 2) {
					if (_y < state[nextstate]->GetY()) {
						_roleThreeDown.SetTopLeft(_x + 5, _y - 45);
						_roleThreeDown.OnShow();
					}
					else if (_y > state[nextstate]->GetY()) {
						_roleThreeUp.SetTopLeft(_x + 5, _y - 45);
						_roleThreeUp.OnShow();
					}
					else if (_x > state[nextstate]->GetX()) {
						_roleThreeLeft.SetTopLeft(_x + 5, _y - 45);
						_roleThreeLeft.OnShow();
					}
					else if (_x < state[nextstate]->GetX()) {
						_roleThreeRight.SetTopLeft(_x + 5, _y - 45);
						_roleThreeRight.OnShow();
					}
					else {
						_roleThreeDown.SetTopLeft(_x + 5, _y - 45);
						_roleThreeDown.OnShow();
					}
				}
				else if (_roleNumber == 3) {
					if (_y < state[nextstate]->GetY()) {
						_roleFourDown.SetTopLeft(_x + 5, _y - 55);
						_roleFourDown.OnShow();
					}
					else if (_y > state[nextstate]->GetY()) {
						_roleFourUp.SetTopLeft(_x + 5, _y - 55);
						_roleFourUp.OnShow();
					}
					else if (_x > state[nextstate]->GetX()) {
						_roleFourLeft.SetTopLeft(_x + 5, _y - 55);
						_roleFourLeft.OnShow();
					}
					else if (_x < state[nextstate]->GetX()) {
						_roleFourRight.SetTopLeft(_x + 5, _y - 55);
						_roleFourRight.OnShow();
					}
					else {
						_roleFourDown.SetTopLeft(_x + 5, _y - 55);
						_roleFourDown.OnShow();
					}
				}
			}
		}
	}
}