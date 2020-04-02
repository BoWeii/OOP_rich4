#pragma once
#include"Role.h"
#include"Station.h"
namespace game_framework
{
	class Lottery
	{
	public:
		Lottery();
		void SetNum(int, Role *);//----------------------------------------------------儲存角色簽的數字
		void SetIsOK(bool flag);//-----------------------------------------------------設定是否確認
		bool GetIsOK();//--------------------------------------------------------------是否已經確認結果
		bool GetIsOpen();//------------------------------------------------------------是否UI介面還是打開的
		int  GetOwner(int);//----------------------------------------------------------得知該是誰選了這個數字
		void Reset();//----------------------------------------------------------------開獎後清除所有資料
		void LoadBitmap();
		void OnShow(vector<Role*> &roleLList, Role* role);
		bool CanChoose(Role* player);//------------------------------------------------是否還有資格繼續選數字
		void DrawTheNumber(int x, int y, bool mouseclick, vector<Role*> &roleList); //-開獎
	private:
		CMovingBitmap _BK, Large, _OK, _OKT, _lotteryNum[10], _lotteryRole[4];
		CAnimation _openRandom[10];//--------------------------------------------------10個數字
		int _roleLoc[4][5] = { {50,225,100,160,220} ,//--------------------------------樂透數字的顯示位置
			/*---------------------------*/{320,225,370,430,490},
			/*---------------------------*/{50,300,100,160,220},
			/*---------------------------*/{320,300,370,430,490} };
		bool _isDrawing, _isOK, _isOKTouch, _lotteryRowSet[10];	//---------------------isopen 是否顯示UI、isOK是否做完、_lotteryRowSet是否已排好每人顯示的數字
		int _numberOwner[10], _openNum;//----------------------------------------------誰簽的數字、開獎數字
		bool _isSendMoney;//-----------------------------------------------------------是否已發錢
		int  _randomCount;//-----------------------------------------------------------公布樂透的閃爍數字
		const int AWARD_1 = 3000, VALUE = 1000;//--------------------------------------獎金、簽一次的價格
	};
}