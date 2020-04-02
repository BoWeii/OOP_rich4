#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Store.h"
namespace game_framework
{
	Store::Store() : Building("Store") {
	}
	string Store::GetType()
	{
		return _type;
	}
	void Store::LoadBitmap()
	{
		_store.LoadBitmap(IDB_store, RGB(0, 0, 100));
	}
	void Store::OnShow()
	{
		_store.SetTopLeft(_x, _y - 20);
		if (_x<690 && _x>-50 && _y<530 && _y>-50)
		{
			_store.ShowBitmap();
		}
	}
}