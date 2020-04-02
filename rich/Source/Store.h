#pragma once
#include "Building.h"
namespace game_framework
{
	class Store :public Building
	{
	public:
		Store();
		virtual string GetType();
		virtual void OnShow();
		virtual void LoadBitmap();
	protected:
		CMovingBitmap  _store;
	};
}
