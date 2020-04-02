#pragma once
#include"Role.h"
#include"Station.h"
namespace game_framework
{
	class Lottery
	{
	public:
		Lottery();
		void SetNum(int, Role *);//----------------------------------------------------�x�s����ñ���Ʀr
		void SetIsOK(bool flag);//-----------------------------------------------------�]�w�O�_�T�{
		bool GetIsOK();//--------------------------------------------------------------�O�_�w�g�T�{���G
		bool GetIsOpen();//------------------------------------------------------------�O�_UI�����٬O���}��
		int  GetOwner(int);//----------------------------------------------------------�o���ӬO�ֿ�F�o�ӼƦr
		void Reset();//----------------------------------------------------------------�}����M���Ҧ����
		void LoadBitmap();
		void OnShow(vector<Role*> &roleLList, Role* role);
		bool CanChoose(Role* player);//------------------------------------------------�O�_�٦�����~���Ʀr
		void DrawTheNumber(int x, int y, bool mouseclick, vector<Role*> &roleList); //-�}��
	private:
		CMovingBitmap _BK, Large, _OK, _OKT, _lotteryNum[10], _lotteryRole[4];
		CAnimation _openRandom[10];//--------------------------------------------------10�ӼƦr
		int _roleLoc[4][5] = { {50,225,100,160,220} ,//--------------------------------�ֳz�Ʀr����ܦ�m
			/*---------------------------*/{320,225,370,430,490},
			/*---------------------------*/{50,300,100,160,220},
			/*---------------------------*/{320,300,370,430,490} };
		bool _isDrawing, _isOK, _isOKTouch, _lotteryRowSet[10];	//---------------------isopen �O�_���UI�BisOK�O�_�����B_lotteryRowSet�O�_�w�Ʀn�C�H��ܪ��Ʀr
		int _numberOwner[10], _openNum;//----------------------------------------------��ñ���Ʀr�B�}���Ʀr
		bool _isSendMoney;//-----------------------------------------------------------�O�_�w�o��
		int  _randomCount;//-----------------------------------------------------------�����ֳz���{�{�Ʀr
		const int AWARD_1 = 3000, VALUE = 1000;//--------------------------------------�����Bñ�@��������
	};
}