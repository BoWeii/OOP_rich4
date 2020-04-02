#pragma once
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include"House.h"
namespace game_framework
{
	House::House() : Building("House"), _level(0) , _owner(4) {
		_price[0]= 1000;
		_price[1] = 3000;
		_price[2] = 6000;
		_price[3] = 1000;
		_tolls[0] = 400;
		_tolls[1] = 900;
		_tolls[2] = 1800;
	} 
	unsigned int House::GetOwner()
	{
		return _owner;
	}
	int House::GetPrice(int level) {
		if (level == 1){
			return _price[0];
		}
		else if (level == 2) {
			return _price[1];
		}
		else if (level == 3) {
			return _price[2];
		}
		else if (level == -1) {
			return _price[3];
		}
		return 0;
	}
	int House::GetTolls() {
		if (_level == 1) {
			return _tolls[0];
		}
		else if (_level == 2) {
			return _tolls[1];
		}
		else if (_level == 3) {
			return _tolls[2];
		}
		return 0;
	}
	void House::SetLevel(int level) {
		if (level == -1) {
			_level = 0;
		}
		else {
			_level = level;
		}
	}
	void House::SetOwner(unsigned int who)
	{
		_owner = who;
	}
	string House::GetType()
	{
		return _type;
	}
	void House::LoadBitmap()
	{
		land.LoadBitmap(IDB_LAND, RGB(255, 255, 255));
		house_1.LoadBitmap(IDB_HOUSE_1, RGB(255, 255, 255));
		house_2.LoadBitmap(IDB_HOUSE_2, RGB(255, 255, 255));
		house_3.LoadBitmap(IDB_HOUSE_3, RGB(255, 255, 255));
	}
	void House::OnShow()
	{
		land.SetTopLeft(_x, _y);
		house_1.SetTopLeft(_x, _y - 10);
		house_2.SetTopLeft(_x, _y - 20);
		house_3.SetTopLeft(_x, _y - 20);
		if (_x<690 && _x>-50 && _y<530 && _y>-50)
		{
			if (_level == 0)
			{
				land.ShowBitmap();
			}
			else if (_level == 1)
			{
				house_1.ShowBitmap();
			}
			else if (_level == 2)
			{
				house_2.ShowBitmap();
			}
			else if (_level == 3)
			{
				house_3.ShowBitmap();
			}
		}
	}
}
