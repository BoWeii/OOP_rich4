#pragma once
#include "House.h"
#include "Store.h"
namespace game_framework
{
	class Station  
	{
	public:
		Station();
		int GetX();
		int GetY();
		void SetXY(int nx, int ny);
		void LoadBitmap();
		void OnShow();
		virtual void OnMove();
		virtual void OnMove(int camerax, int cameray);
		void SetMovingDown(bool flag);//--設定是否正在往下移動
		void SetMovingLeft(bool flag);//--設定是否正在往左移動
		void SetMovingRight(bool flag);//-設定是否正在往右移動
		void SetMovingUp(bool flag);//----設定是否正在往上移動
		House *house;
		Store *store;
		string GetBuildingType();
		void SetBuildingType(string buildingType);
	protected:
		int _x, _y;
		int _referenceX, _referenceY;
		string _buildingType;
		bool isMovingDown;//----------是否正在往下移動
		bool isMovingLeft;//----------是否正在往左移動
		bool isMovingRight;//---------是否正在往右移動
		bool isMovingUp;//------------是否正在往上移動
		CMovingBitmap station;
	};
}