#pragma once
#include"Role.h"
#include"Station.h"
#include"Lottery.h"
#include"Integer.h"
namespace game_framework
{
	class OthersUI
	{
	public:
		OthersUI();
		void SetIsOpen(bool flag);//---------------------------------------------------------------------------------------------- 設定個人選單關閉
		void SetIsOpen();//--------------------------------------------------------------------------------------------------------開關個人選單	
		bool GetMenuIsOpen();//----------------------------------------------------------------------------------------------------個人選歌是否開啟
		void JudgeUI(int x, int y, bool mouseclick, vector<Role*> &roleList, Role* role, Station** station, Lottery& lottery);//---判斷當前應該在什麼UI
		void LotteryUI(int x, int y, bool mouseclick, vector<Role*> &roleList, Role* role, Lottery& lottery);//--------------------進入樂透UI
		void ResetLotteryUI();//---------------------------------------------------------------------------------------------------開獎時清除所有人的樂透UI資料
		void LoadBitmap();
		void SetOnce(bool);//------------------------------------------------------------------------------------------------------該回合已經選過一次數字
		bool GetOthersIsOpen();//--------------------------------------------------------------------------------------------------是否有任何UI開啟中
		void OnShow(vector<Role*> &roleList, Role* role, Lottery &lottery);


	private:
		////////// menu part /////////
		Integer _menuMoney, _menuHouse;
		CMovingBitmap _option[2], _optionT[2], _menuBK, _menuPhoto[4], _moneyLogo, _houseLogo;
		bool _isMOpen, _optionTouch[2];
		////////// Lottery part /////////
		CMovingBitmap _LBK, _LOK, _LOKT, _lotteryNum[10], _lotteryNumT[10], _lotteryNumC[10], _lotteryRole[4];
		bool  _isLOpen, _isOK;
		bool  _lotteryTouch[10], _lotteryChoose[10], _lotteryTempChoose[10], _LOKTouch, _lotteryRowSet[10], _once;
		int _roleLoc[4][5] = {{50,225,100,160,220} ,//樂透數字的顯示位置
/*--------------------------*/{320,225,370,430,490},
/*--------------------------*/{50,300,100,160,220},
/*--------------------------*/{320,300,370,430,490}};
	};
}