#pragma once
#include"Building.h"
namespace game_framework
{
	class House :public Building
	{
	public:
		House();
		void SetLevel(int level);
		void SetOwner(unsigned int);
		unsigned int GetOwner();
		int GetPrice(int level);
		int GetTolls();
		virtual string GetType();
		virtual void OnShow();
		virtual void LoadBitmap();
	protected:
		unsigned int _owner;//--擁有者,owner=4 代表沒人
		int _level;//-----------土地等級 ,0為空地
		int _price[4];
		int _tolls[3];
		CMovingBitmap land, house_1, house_2, house_3;
	};
}
