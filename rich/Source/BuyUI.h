#pragma once
#include "Integer.h"
#include "GameMap.h"
#include "Building.h"
#include "Station.h"
#include "Role.h"
#include "Card.h"
namespace game_framework
{
	class BuyUI {
	public:
		BuyUI();
		~BuyUI();
		void SetIsOK(bool flag);
		bool GetIsOK();
		bool GetIsOpen();
		void ResetUI();
		void JudgeHS(int x, int y, bool mouseclick, vector<Role*> &roleLList, Role* role, Station** station, Station* rolestation, GameMap *map, Building** building, bool &isbankrupt);
		void HouseUI(int x,int y, bool mouseclick,Role* role, Station* rolestation);
		void StoreUI(int x, int y, bool mouseclick, Role* role);
		void HouseTransaction(Role* role, Station* rolestation);
		void TollsTransaction(Role* owner, Role* payer, int cash);
		void UseCard(vector<Role*> &roleLList, Role* role, Station** station, Station* rolestation, bool mouseclick, int posx, int posy, GameMap *map, Building** building);
		void LoadBitmap();
		void OnShow(vector<Role*> &roleLList, Role* role, Station** station, Station* rolestation);
	private:
		CMovingBitmap _UIBK, _title[3], _levelp[2][3], _sell[2], _poor[4] , _OK, _cardRandom, _draw, _noDraw;;
		bool _isOpen, _showHouseUI, _showStoreUI, _isUIOK, _isDraw, _isOK; //isopen 是否顯示UI isOK是否做完
		Integer _dollar[4]; //房子買賣價格 role存款
		string _dothing; //doHouse, doTolls,doStore,doNothing
		int _level, _cardIndex, _cardPrice; // -1=sell 1~3==buy 0= donothing// _cardIndex -1 =donothing
		vector<Card*> _card;
	};
}