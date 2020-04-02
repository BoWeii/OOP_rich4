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
		void SetIsOpen(bool flag);//---------------------------------------------------------------------------------------------- �]�w�ӤH�������
		void SetIsOpen();//--------------------------------------------------------------------------------------------------------�}���ӤH���	
		bool GetMenuIsOpen();//----------------------------------------------------------------------------------------------------�ӤH��q�O�_�}��
		void JudgeUI(int x, int y, bool mouseclick, vector<Role*> &roleList, Role* role, Station** station, Lottery& lottery);//---�P�_��e���Ӧb����UI
		void LotteryUI(int x, int y, bool mouseclick, vector<Role*> &roleList, Role* role, Lottery& lottery);//--------------------�i�J�ֳzUI
		void ResetLotteryUI();//---------------------------------------------------------------------------------------------------�}���ɲM���Ҧ��H���ֳzUI���
		void LoadBitmap();
		void SetOnce(bool);//------------------------------------------------------------------------------------------------------�Ӧ^�X�w�g��L�@���Ʀr
		bool GetOthersIsOpen();//--------------------------------------------------------------------------------------------------�O�_������UI�}�Ҥ�
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
		int _roleLoc[4][5] = {{50,225,100,160,220} ,//�ֳz�Ʀr����ܦ�m
/*--------------------------*/{320,225,370,430,490},
/*--------------------------*/{50,300,100,160,220},
/*--------------------------*/{320,300,370,430,490}};
	};
}