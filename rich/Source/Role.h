#pragma once
#include "Integer.h"
#include "Station.h"
namespace game_framework
{
	class Role
	{
	public:
		Role();
		Role(int roleNumber);
		int GetCameraX();
		int GetCameraY();
		int GetX();
		int GetY();
		void SetShowRole(bool flag);
		void AddMoney(int price);
		int GetMoney();
		int GetRoleNum();
		int GetRoleState();
		void SetRoleTurn(bool flag);
		virtual void OnMove();  
		virtual void OnMove(int camerax, int cameray);//視角切換
		bool SetRoleMove(Station *state,int direction); //外部移動腳色 directoin>0正向 <0反向
		int RoleMove(int diceNum, Station **state);
		void OnShow(Station **state);
		void SetMovingDown(bool flag);
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void LoadBitmap();
		Integer _money;

	private:
		CAnimation _roleOneDown, _roleOneUp, _roleOneLeft, _roleOneRight, _roleTwoDown, _roleTwoUp, _roleTwoLeft, _roleTwoRight, _roleThreeDown, _roleThreeUp, _roleThreeLeft, _roleThreeRight, _roleFourDown, _roleFourUp, _roleFourLeft, _roleFourRight;
		int _x, _y, _stepNum, _referenceX, _referenceY, _mystate;
		unsigned int _roleNumber;
		bool _roleTurn, _showRole;
		bool _isMovingDown;
		bool _isMovingLeft;
		bool _isMovingRight;
		bool _isMovingUp;
	};

}
