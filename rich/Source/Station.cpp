#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Station.h"
namespace game_framework
{
	Station::Station():_referenceX(0), _referenceY(0), _buildingType("none") { isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false; }
	int Station::GetX() {
		return _x;
	}
	int Station::GetY(){
		return _y;
	}
	void Station::SetXY(int nx, int ny)
	{
		_x = nx; _y = ny;
	}
	string Station::GetBuildingType()
	{
		return _buildingType;
	}
	void Station::SetBuildingType(string buildingType) {
		_buildingType = buildingType;
	}
	void Station::OnMove()
	{
		const int STEP_SIZE = 10;
		if (_referenceX + STEP_SIZE <= 0) {
			if (isMovingLeft)
			{
				_x += STEP_SIZE;
				_referenceX += STEP_SIZE;
			}
		}
		if (_referenceX - STEP_SIZE >= -1280) {
			if (isMovingRight)
			{
				_x -= STEP_SIZE;
				_referenceX -= STEP_SIZE;
			}
		}
		if (_referenceY + STEP_SIZE <= 0) {
			if (isMovingUp)
			{
				_y += STEP_SIZE;
				_referenceY += STEP_SIZE;

			}	
		}
		if (_referenceY - STEP_SIZE >= -1920) {
			if (isMovingDown)
			{
				_y -= STEP_SIZE;
				_referenceY -= STEP_SIZE;
			}	
		}
	}
	void Station::OnMove(int camerax, int cameray) {
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
	void Station::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}
	void Station::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}
	void Station::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}
	void Station::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}
	void Station::LoadBitmap()
	{
		station.LoadBitmap(IDB_dot, RGB(255, 255, 255));
	}
	void Station::OnShow()
	{
		if (_x<690 && _x>-50 && _y<530 && _y>-50)
		{
			station.SetTopLeft(_x, _y);
			station.ShowBitmap();
		}
	}
}
