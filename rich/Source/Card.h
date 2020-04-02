#pragma once
#include "Dice.h"
#include "Station.h"
#include "GameMap.h"
#include "Role.h"
namespace game_framework
{
	enum class CardName {
		toNext,
		burnHouse,
		steal
	};
	class Card
	{
	public:
		Card();
		Card(CardName cardKind);
		int GetCardKind();
		void SetCardIsUsing(bool flag);
		bool GetCardIsUsing();
		void JudgeCard(vector<Role*> &roleList, Role* role, Station** station, bool mouseclick, int posx, int posy, GameMap *map, Building** building);
		void TossAgain(vector<Role*> &roleList, Role* role, Station** station, Station* rolestation, int direction, GameMap *map, Building** building); //往前後n站
		void ChooseHouse(vector<Role*> &roleList, Station** station, bool mouseclick, int posx, int posy, GameMap *map, Building** building);
		void StealMoney(vector<Role*> &roleList, Station** station, Role* role, bool mouseclick, int posx, int posy, GameMap *map, Building** building);
		void LoadBitmap();
		void OnShow(vector<Role*> &roleLList, Role* role, Station** station, Station* rolestation);
	private:
		bool _cardIsUsing; // true 使用中
		Role* _roleBeSteal;
		bool _targetConfirm;
		int _targetx, _targety;
		CMovingBitmap _card ;
		CAnimation  _carDown, _carUp, _carLeft, _carRight;
		CAnimation _bomb, _steal;
		Dice _dice[3];
		CardName _cardKind;
	};
}