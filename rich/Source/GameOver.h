#pragma once
#include"Role.h"
namespace game_framework
{
	class GameOver {
	public:
		GameOver();
		void bankrupt(Role *role,int x,int y,bool mouseclick); //-�}���M�C���������e��
		void LoadBitmap();
		void OnShow(Role *role,  int size);
		void SetIsOK(bool);//------------------------------------ �]�w�T�w����
		bool IsOK();//------------------------------------------- �O�_�w���T�w
	private:
		CMovingBitmap _winBK,_bankruptBK, _OK, _OKT,_r1, _r2, _r3, _r4 ;
		bool _isOK,_isOpen,_isTouch;//----------------------------�O�_�w�T�{�B���}
	};
}