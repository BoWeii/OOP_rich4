#pragma once
#include"Role.h"
namespace game_framework
{
	class GameOver {
	public:
		GameOver();
		void bankrupt(Role *role,int x,int y,bool mouseclick); //-破產和遊戲結束的畫面
		void LoadBitmap();
		void OnShow(Role *role,  int size);
		void SetIsOK(bool);//------------------------------------ 設定確定的值
		bool IsOK();//------------------------------------------- 是否已按確定
	private:
		CMovingBitmap _winBK,_bankruptBK, _OK, _OKT,_r1, _r2, _r3, _r4 ;
		bool _isOK,_isOpen,_isTouch;//----------------------------是否已確認、打開
	};
}