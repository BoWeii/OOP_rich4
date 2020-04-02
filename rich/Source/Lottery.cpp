#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <random>
#include "Lottery.h"
namespace game_framework
{
	Lottery::Lottery()
	{
		Reset();
	}
	bool Lottery::GetIsOK()
	{
		return _isOK;
	}
	void Lottery::SetIsOK(bool flag)
	{
		_isOK = flag;
	}
	int Lottery::GetOwner(int num)
	{
		return _numberOwner[num];
	}
	void Lottery::SetNum(int num, Role *player)
	{
		_numberOwner[num] = player->GetRoleNum();
		player->AddMoney(-VALUE);
	}
	bool Lottery::GetIsOpen() {
		return _isDrawing;
	}
	void Lottery::Reset()
	{
		for (int i = 0; i < 10; i++)
		{
			_lotteryRowSet[i] = false;
			_numberOwner[i] = -1;
		}
		_randomCount = 0;
		std::random_device rd;
		std::default_random_engine gen = std::default_random_engine(rd());
		std::uniform_int_distribution<int> dis(1, 10);
		_openNum = dis(gen);
		_isSendMoney = false;
		_isOK = true;
		_isDrawing = false;
	}
	bool Lottery::CanChoose(Role *role)
	{
		int times = 0;
		for (int i = 0; i < 10; i++)
			if (role->GetRoleNum() == _numberOwner[i])
				times++;
		if (times >= 3)
			return false;
		else
			return true;
	}
	void Lottery::DrawTheNumber(int x, int y, bool mouseclick, vector<Role*> &roleList)
	{
		if (!_isOK)
		{
			_isDrawing = true;
			if (!_isSendMoney)
			{
				for (unsigned int i = 0; i < roleList.size(); i++)
				{
					if (_numberOwner[_openNum - 1] != -1 && roleList[i]->GetRoleNum() == _numberOwner[_openNum - 1])//該數字有人抽，且得獎者得存活才發錢
						roleList[_numberOwner[_openNum - 1]]->AddMoney(AWARD_1);
					else
						break;
				}
			}
			_isSendMoney = true;
			if (x > 280 && x < 280 + _OK.Width() && y>370 && y < 370 + _OK.Height())
			{
				_isOKTouch = true;
				if (mouseclick)
				{
					Reset();
				}
			}
			else
				_isOKTouch = false;
		}
	}
	void Lottery::LoadBitmap()
	{
		_BK.LoadBitmap(IDB_L_BK);
		_OKT.LoadBitmap(IDB_L_OK_T);
		_OK.LoadBitmap(IDB_L_OK);
		for (int i = 0; i < 10; i++)
		{
			_openRandom[i].AddBitmap(IDB_random1, RGB(255, 255, 255));
			_openRandom[i].AddBitmap(IDB_random2, RGB(255, 255, 255));
			_openRandom[i].AddBitmap(IDB_random3, RGB(255, 255, 255));
			_openRandom[i].AddBitmap(IDB_random4, RGB(255, 255, 255));
			_openRandom[i].AddBitmap(IDB_random5, RGB(255, 255, 255));
			_openRandom[i].AddBitmap(IDB_random6, RGB(255, 255, 255));
			_openRandom[i].AddBitmap(IDB_random7, RGB(255, 255, 255));
		}
		_openRandom[0].AddBitmap(IDB_open1, RGB(255, 255, 255));
		_openRandom[1].AddBitmap(IDB_open2, RGB(255, 255, 255));
		_openRandom[2].AddBitmap(IDB_open3, RGB(255, 255, 255));
		_openRandom[3].AddBitmap(IDB_open4, RGB(255, 255, 255));
		_openRandom[4].AddBitmap(IDB_open5, RGB(255, 255, 255));
		_openRandom[5].AddBitmap(IDB_open6, RGB(255, 255, 255));
		_openRandom[6].AddBitmap(IDB_open7, RGB(255, 255, 255));
		_openRandom[7].AddBitmap(IDB_open8, RGB(255, 255, 255));
		_openRandom[8].AddBitmap(IDB_open9, RGB(255, 255, 255));
		_openRandom[9].AddBitmap(IDB_open10, RGB(255, 255, 255));
		_lotteryNum[0].LoadBitmap(IDB_L1);
		_lotteryNum[1].LoadBitmap(IDB_L2);
		_lotteryNum[2].LoadBitmap(IDB_L3);
		_lotteryNum[3].LoadBitmap(IDB_L4);
		_lotteryNum[4].LoadBitmap(IDB_L5);
		_lotteryNum[5].LoadBitmap(IDB_L6);
		_lotteryNum[6].LoadBitmap(IDB_L7);
		_lotteryNum[7].LoadBitmap(IDB_L8);
		_lotteryNum[8].LoadBitmap(IDB_L9);
		_lotteryNum[9].LoadBitmap(IDB_L10);
		_lotteryRole[0].LoadBitmapA(IDB_L_R1, RGB(255, 255, 254));
		_lotteryRole[1].LoadBitmapA(IDB_L_R2, RGB(255, 255, 254));
		_lotteryRole[2].LoadBitmapA(IDB_L_R3, RGB(255, 255, 254));
		_lotteryRole[3].LoadBitmapA(IDB_L_R4, RGB(255, 255, 254));
	}
	void Lottery::OnShow(vector<Role*> &roleList, Role* role)
	{
		if (_isDrawing)
		{
			_BK.SetTopLeft(40, 40);
			_BK.ShowBitmap();
			_openRandom[_openNum - 1].SetTopLeft(240, 90);
			_openRandom[_openNum - 1].OnShow();
			if (!_openRandom[_openNum - 1].IsFinalBitmap())//---------------開獎的七彩數字
			{
				_openRandom[_openNum - 1].OnMove();
			}
			if (_randomCount < 7)
			{
				_randomCount++;
			}
			_OK.SetTopLeft(280, 370);
			_OKT.SetTopLeft(280, 370);
			if (_isOKTouch)
				_OKT.ShowBitmap();
			else
				_OK.ShowBitmap();
			//--------------------------------------------------------------腳色欄
			for (unsigned int i = 0; i < roleList.size(); i++)//------------判斷當前存活的角色
			{
				_lotteryRole[roleList[i]->GetRoleNum()].SetTopLeft(_roleLoc[static_cast<int> (i)][0], _roleLoc[static_cast<int>(i)][1]);
			}
			for (unsigned int i = 0; i < roleList.size(); i++)//------------Show出所有存活的角色
			{
				_lotteryRole[roleList[i]->GetRoleNum()].ShowBitmap();
			}
			for (unsigned int u_who = 0; u_who < roleList.size(); u_who++)//每個角色所選的樂透數字	
			{
				int index = 2;
				int who = static_cast<int>(u_who);
				for (int i = 0; i < 10; i++)
				{
					if (_numberOwner[i] == roleList[who]->GetRoleNum())
					{
						_lotteryNum[i].SetTopLeft(_roleLoc[static_cast<int> (who)][index], _roleLoc[static_cast<int>(who)][1] + 5);
						_lotteryNum[i].ShowBitmap();
						index++;
					}
				}
			}
		}
	}
}