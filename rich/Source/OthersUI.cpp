#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "OthersUI.h"
namespace game_framework
{
	OthersUI::OthersUI()
	{
		ResetLotteryUI();
	}
	void OthersUI::ResetLotteryUI()
	{
		_optionTouch[0] = _isMOpen = _isLOpen = _LOKTouch = _once = false;
		for (int i = 0; i < 10; i++)
		{
			_lotteryTouch[i] = _lotteryChoose[i] = _lotteryRowSet[i] = _lotteryTempChoose[i] = false;
		}
	}
	void OthersUI::SetIsOpen()
	{
		if (_isMOpen)
			_isMOpen = false;
		else
			_isMOpen = true;
	}
	void OthersUI::SetIsOpen(bool flag)
	{
		_isMOpen = flag;
	}
	bool OthersUI::GetMenuIsOpen() {
		return _isMOpen;
	}
	bool OthersUI::GetOthersIsOpen()
	{
		if (_isLOpen)
			return true;
		return false;
	}
	void OthersUI::SetOnce(bool flag)
	{
		_once = flag;
	}
	void OthersUI::JudgeUI(int x, int y, bool mouseclick, vector<Role*> &roleList, Role* role, Station** station, Lottery& lottery)
	{
		if (_isMOpen && !_isLOpen)//MENU open
		{
			_menuMoney.SetInteger(role->GetMoney());
			int j = 0;
			for (int i = 0; i < 81; i++)
			{
				if (station[i]->house != nullptr)//避免站點是空的地方
				{
					if (station[i]->GetBuildingType() == "House"&&station[i]->house->GetOwner() == role->GetRoleNum())
					{
						j++;
					}
				}
			}
			_menuHouse.SetInteger(j);//設定個人的房地產
			for (int i = 0; i < 1; i++)
			{
				if (x > 100 && x < 100 + _option[0].Width() && y>60 + i * (_option[0].Height() + 20) && y < 60 + i * (_option[0].Height() + 20) + _option[0].Height())
				{
					_optionTouch[i] = true;
					if (mouseclick)
					{
						switch (i)
						{
						case(0):
							_isLOpen = true;
							Sleep(150);
							break;
						}
					}
				}
				else
					_optionTouch[i] = false;
			}
		}
		else if (_isLOpen)//樂透介面開啟
		{
			LotteryUI(x, y, mouseclick, roleList, role, lottery);
		}
	}
	void OthersUI::LotteryUI(int x, int y, bool mouseclick, vector<Role*> &roleList, Role* role, Lottery& lottery)
	{
		if (_isLOpen)
		{
			if (lottery.CanChoose(role))//沒超過3個號碼
			{
				for (int i = 0; i < 5; i++)
				{
					if (x > 50 + 90 * i&&x < 50 + 90 * i + _lotteryNum[i].Width() && y>50 && y < 50 + _lotteryNum[i].Height() && !_once)
					{
						_lotteryTouch[i] = true;
						if (mouseclick && !_lotteryChoose[i])
						{
							if (_lotteryTempChoose[i])
							{
								_lotteryTempChoose[i] = false;
								Sleep(150);
							}
							else
							{
								_lotteryTempChoose[i] = true;
								Sleep(150);
							}
							for (int j = 0; j < 10; j++)
							{
								if (i == j)
									continue;
								_lotteryTempChoose[j] = false;
							}
						}
					}
					else
						_lotteryTouch[i] = false;
					if (x > 120 + 90 * i&&x < 120 + 90 * i + _lotteryNum[i + 5].Width() && y>145 && y < 145 + _lotteryNum[i + 5].Height() && !_once)
					{
						_lotteryTouch[i + 5] = true;
						if (mouseclick && !_lotteryChoose[i + 5] && !_once)
						{
							if (_lotteryTempChoose[i + 5])
							{
								_lotteryTempChoose[i + 5] = false;
								Sleep(150);
							}
							else
							{
								_lotteryTempChoose[i + 5] = true;
								Sleep(150);
							}
							for (int j = 0; j < 10; j++)
							{
								if (i + 5 == j)
									continue;
								_lotteryTempChoose[j] = false;
							}
						}
					}
					else
						_lotteryTouch[i + 5] = false;
				}
			}
			if (x > 280 && x < 280 + _LOK.Width() && y>370 && y < 370 + _LOK.Height())//確認鍵
			{
				_LOKTouch = true;
				if (mouseclick)
				{
					Sleep(150);
					for (int i = 0; i < 10; i++)
					{
						if (_lotteryTempChoose[i])
						{
							lottery.SetNum(i, role);
							_lotteryChoose[i] = true;
							_lotteryTempChoose[i] = false;
							_once = true; //一回合只能簽一次
						}
					}
					_isLOpen = false;
					_isMOpen = true;
				}
			}
			else
				_LOKTouch = false;
		}
	}
	void OthersUI::LoadBitmap()
	{
		_menuBK.LoadBitmapA(IDB_menu_BK);
		_menuMoney.LoadBitmap();
		_menuHouse.LoadBitmap();
		_moneyLogo.LoadBitmap(IDB_logo_money, RGB(255, 255, 255));
		_houseLogo.LoadBitmap(IDB_logo_house, RGB(255, 255, 255));
		_menuPhoto[0].LoadBitmap(IDB_R101, RGB(0, 0, 100));
		_menuPhoto[1].LoadBitmap(IDB_R201, RGB(0, 0, 100));
		_menuPhoto[2].LoadBitmap(IDB_R301, RGB(0, 0, 100));
		_menuPhoto[3].LoadBitmap(IDB_R401, RGB(0, 0, 100));
		_option[0].LoadBitmap(IDB_lottery_option);
		_optionT[0].LoadBitmap(IDB_lottery_option_choosed);
		_option[1].LoadBitmap(IDB_bag_option);
		_optionT[1].LoadBitmap(IDB_bag_option_choosed);
		_LBK.LoadBitmap(IDB_L_BK);
		_LOK.LoadBitmap(IDB_L_OK);
		_LOKT.LoadBitmapA(IDB_L_OK_T);
		_lotteryNum[0].LoadBitmap(IDB_L1);
		_lotteryNumC[0].LoadBitmap(IDB_L1C);
		_lotteryNumT[0].LoadBitmap(IDB_L1T);
		_lotteryNum[1].LoadBitmap(IDB_L2);
		_lotteryNumC[1].LoadBitmap(IDB_L2C);
		_lotteryNumT[1].LoadBitmap(IDB_L2T);
		_lotteryNum[2].LoadBitmap(IDB_L3);
		_lotteryNumC[2].LoadBitmap(IDB_L3C);
		_lotteryNumT[2].LoadBitmap(IDB_L3T);
		_lotteryNum[3].LoadBitmap(IDB_L4);
		_lotteryNumC[3].LoadBitmap(IDB_L4C);
		_lotteryNumT[3].LoadBitmap(IDB_L4T);
		_lotteryNum[4].LoadBitmap(IDB_L5);
		_lotteryNumC[4].LoadBitmap(IDB_L5C);
		_lotteryNumT[4].LoadBitmap(IDB_L5T);
		_lotteryNum[5].LoadBitmap(IDB_L6);
		_lotteryNumC[5].LoadBitmap(IDB_L6C);
		_lotteryNumT[5].LoadBitmap(IDB_L6T);
		_lotteryNum[6].LoadBitmap(IDB_L7);
		_lotteryNumC[6].LoadBitmap(IDB_L7C);
		_lotteryNumT[6].LoadBitmap(IDB_L7T);
		_lotteryNum[7].LoadBitmap(IDB_L8);
		_lotteryNumC[7].LoadBitmap(IDB_L8C);
		_lotteryNumT[7].LoadBitmap(IDB_L8T);
		_lotteryNum[8].LoadBitmap(IDB_L9);
		_lotteryNumC[8].LoadBitmap(IDB_L9C);
		_lotteryNumT[8].LoadBitmap(IDB_L9T);
		_lotteryNum[9].LoadBitmap(IDB_L10);
		_lotteryNumC[9].LoadBitmap(IDB_L10C);
		_lotteryNumT[9].LoadBitmap(IDB_L10T);
		_lotteryRole[0].LoadBitmapA(IDB_L_R1, RGB(255, 255, 254));
		_lotteryRole[1].LoadBitmapA(IDB_L_R2, RGB(255, 255, 254));
		_lotteryRole[2].LoadBitmapA(IDB_L_R3, RGB(255, 255, 254));
		_lotteryRole[3].LoadBitmapA(IDB_L_R4, RGB(255, 255, 254));
	}
	void OthersUI::OnShow(vector<Role*> &roleList, Role* role, Lottery &lottery)
	{
		_menuBK.SetTopLeft(80, 40);
		_menuMoney.SetTopLeft(470, 250);
		_moneyLogo.SetTopLeft(375, 240);
		_menuHouse.SetTopLeft(470, 300);
		_houseLogo.SetTopLeft(375, 275);
		for (int i = 0; i < 2; i++)//---------------------------------------設定樂透按鈕位置
		{
			_option[i].SetTopLeft(100, 60 + i * (_option[0].Height() + 20));
			_optionT[i].SetTopLeft(100, 60 + i * (_option[0].Height() + 20));
		}
		for (int i = 0; i < 4; i++)//---------------------------------------設定角色欄位置
			_menuPhoto[i].SetTopLeft(500, 50);
		_LBK.SetTopLeft(40, 40);
		_LOK.SetTopLeft(280, 370);
		_LOKT.SetTopLeft(280, 370);
		for (int i = 0; i < 5; i++)//---------------------------------------樂透的數字
		{
			if (!_lotteryChoose[i])//---------------------------------------被選到就不排
				_lotteryNum[i].SetTopLeft(50 + 90 * i, 50);
			_lotteryNumC[i].SetTopLeft(50 + 90 * i, 50);
			_lotteryNumT[i].SetTopLeft(50 + 90 * i, 50);
		}
		for (int i = 5, j = 0; i < 10; i++, j++)//--------------------------樂透的數字
		{
			if (!_lotteryChoose[i])//---------------------------------------被選到就不排
				_lotteryNum[i].SetTopLeft(120 + 90 * j, 145);
			_lotteryNumC[i].SetTopLeft(120 + 90 * j, 145);
			_lotteryNumT[i].SetTopLeft(120 + 90 * j, 145);
		}
		for (unsigned int i = 0; i < roleList.size(); i++)//----------------判斷當前存活的角色
		{
			_lotteryRole[roleList[i]->GetRoleNum()].SetTopLeft(_roleLoc[static_cast<int> (i)][0], _roleLoc[static_cast<int>(i)][1]);
		}
		if (_isMOpen && !_isLOpen)//----------------------------------------Show 個人選單
		{
			_menuBK.ShowBitmap();
			if (_optionTouch[0])
				_optionT[0].ShowBitmap();
			else
				_option[0].ShowBitmap();
			_menuPhoto[role->GetRoleNum()].ShowBitmap();
			_menuMoney.ShowBitmap();
			_moneyLogo.ShowBitmap();
			_menuHouse.ShowBitmap();
			_houseLogo.ShowBitmap();
		}
		else if (_isLOpen)//------------------------------------------------Show 樂透的UI
		{
			_LBK.ShowBitmap();
			for (unsigned int i = 0; i < roleList.size(); i++)//------------角色欄
			{
				_lotteryRole[roleList[i]->GetRoleNum()].ShowBitmap();
			}
			if (_LOKTouch)//------------------------------------------------確認鍵
				_LOKT.ShowBitmap();
			else
				_LOK.ShowBitmap();
			for (int i = 0; i < 10; i++)//----------------------------------可選的樂透數字
			{
				if (!_lotteryTouch[i] && !_lotteryChoose[i] && !_lotteryTempChoose[i])
					_lotteryNum[i].ShowBitmap();
				else if ((_lotteryTouch[i] && !_lotteryChoose[i]) || _lotteryTempChoose[i])
					_lotteryNumT[i].ShowBitmap();
				else if (_lotteryChoose[i])
					_lotteryNumC[i].ShowBitmap();
			}
			for (unsigned int u_who = 0; u_who < roleList.size(); u_who++)//角色欄數字
			{
				int index = 2;
				int who = static_cast<int>(u_who);
				for (int i = 0; i < 10; i++)
				{
					if (lottery.GetOwner(i) == roleList[who]->GetRoleNum())
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