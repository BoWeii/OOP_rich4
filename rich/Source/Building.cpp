#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include"Building.h"
namespace game_framework
{
	Building::Building() :_referenceX(0), _referenceY(0), _isEmpty(false) 
	{ 
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		_type = "Building";
	}
	Building::Building(string type) : _referenceX(0), _referenceY(0), _isEmpty(false)
	{
		_type = type;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false; 
	}
	void Building::OnShow()
	{
		if (_x<639 && _x>-639 && _y<479 && _y>-479)
		{
			building.SetTopLeft(_x, _y);
			building.ShowBitmap();
		}
	}
	int Building::GetX()
	{
		return _x;
	}
	int Building::GetY()
	{
		return _y;
	}
	void Building::SetXY(int nx, int ny)
	{
		_x = nx; _y = ny;
	}
	void Building::LoadBitmap()
	{
	}
	string Building::GetType()
	{
		return _type;
	}
	void Building::OnMove()
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
	void Building::OnMove(int camerax, int cameray)
	{
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
	void Building::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}
	void Building::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}
	void Building::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}
	void Building::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}
}
