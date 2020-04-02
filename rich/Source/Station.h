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
		void SetMovingDown(bool flag);//--�]�w�O�_���b���U����
		void SetMovingLeft(bool flag);//--�]�w�O�_���b��������
		void SetMovingRight(bool flag);//-�]�w�O�_���b���k����
		void SetMovingUp(bool flag);//----�]�w�O�_���b���W����
		House *house;
		Store *store;
		string GetBuildingType();
		void SetBuildingType(string buildingType);
	protected:
		int _x, _y;
		int _referenceX, _referenceY;
		string _buildingType;
		bool isMovingDown;//----------�O�_���b���U����
		bool isMovingLeft;//----------�O�_���b��������
		bool isMovingRight;//---------�O�_���b���k����
		bool isMovingUp;//------------�O�_���b���W����
		CMovingBitmap station;
	};
}