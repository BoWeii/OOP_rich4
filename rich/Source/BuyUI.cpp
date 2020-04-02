#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <random>
#include "BuyUI.h"

namespace game_framework
{
	BuyUI::BuyUI(): _isOpen(false), _showHouseUI(false), _showStoreUI(false),_isUIOK(false), _isOK(false), _level (0), _cardIndex(-1), _dothing("doNothing")
	{
		_dollar[0].SetInteger(0);
		_dollar[1].SetInteger(0);
		_dollar[2].SetInteger(0);
		_dollar[3].SetInteger(0);
		_cardPrice = 1000;
		_isDraw = false;
		for (int i = 0;i < 3 ; i++) {
			CardName cardname = (CardName)i;
			Card* card = new Card(cardname);
			_card.push_back(card);
		}
	}
	BuyUI::~BuyUI(){
		_card.clear();
	}
	void BuyUI::SetIsOK(bool flag) {
		_isOK = flag;
	}
	bool BuyUI::GetIsOK() {
		return _isOK;
	}
	bool BuyUI::GetIsOpen() {
		return _isOpen;
	}
	void BuyUI::JudgeHS(int x, int y, bool mouseclick,vector<Role*> &roleList, Role* role, Station** station, Station* rolestation, GameMap *map, Building** building, bool &isbankrupt) {
		if(!_isUIOK){
			if (rolestation->GetBuildingType() == "House") {
				_dollar[0].SetInteger(rolestation->house->GetPrice(1)); //house1價格
				_dollar[1].SetInteger(rolestation->house->GetPrice(2)); //house2價格
				_dollar[2].SetInteger(rolestation->house->GetPrice(3)); //house3價格
				_dollar[3].SetInteger(rolestation->house->GetPrice(-1)); //賣house價格
				if (role->GetRoleNum() == rolestation->house->GetOwner() || rolestation->house->GetOwner() == 4) {//土地為role的或無人土地
					_isOpen = true;
					_showHouseUI = true;
					_dothing = "doHouse";
					HouseUI(x, y, mouseclick, role, rolestation);
				}
				else{
					for (unsigned int i  = 0; i < roleList.size(); i++) {
						if (rolestation->house->GetOwner() == roleList[i]->GetRoleNum()) {
							TollsTransaction(roleList[i], role, rolestation->house->GetTolls());
							_dothing == "doTolls";
						}
					}
					_isUIOK = true;
				}
			}
			else if (rolestation->GetBuildingType() == "Store") {
				_isOpen = true;
				_showStoreUI = true;
				_dothing = "doStore";
				StoreUI(x, y, mouseclick, role);
			}
			else {
				_isUIOK = true;
			}
		}
		if (_isUIOK) {
			if (_dothing == "doHouse") {
				HouseTransaction(role, rolestation);
			}
			else if (_dothing == "doTolls") {
			}
			else if (_dothing == "doStore") {
				UseCard(roleList, role ,station, rolestation, mouseclick , x, y, map, building);
			}
			else if (_dothing == "doNothing") {
				_isOK = true;
			}
			if (_isOK) {
				ResetUI();
				Sleep(200);
			}
		}
	}
	void BuyUI::ResetUI() { //重設選單
		_level = 0;
		_dothing = "doNothing";
		_isUIOK = false;
		_isDraw = false;
		_cardIndex = -1;
	}
	void BuyUI::HouseUI(int x, int y, bool mouseclick, Role* role, Station* rolestation) {
		if (mouseclick) {
			if (x > 180 && x < 260 && y>180 && y < 220 && _level != 1 && role->GetMoney() >= rolestation->house->GetPrice(1)) {  //選level 如果重複點選=取消
				_level = 1;
			}
			else if (x > 320 && x < 400 && y>180 && y < 220 && _level != 2 && role->GetMoney() >= rolestation->house->GetPrice(2)) {
				_level = 2;
			}
			else if (x > 460 && x < 540 && y>180 && y < 220 && _level != 3 && role->GetMoney() >= rolestation->house->GetPrice(3)) {
				_level = 3;
			}
			else if (x > 180 && x < 260 && y>180 && y < 220 && _level == 1) {
				_level = 0;
			}
			else if (x > 320 && x < 400 && y>180 && y < 220 && _level == 2) {
				_level = 0;
			}
			else if (x > 460 && x < 540 && y>180 && y < 220 && _level == 3) {
				_level = 0;
			}
			else if (x > 180 && x < 260 && y>280 && y < 320 && _level != -1 &&  role->GetRoleNum()== rolestation->house->GetOwner()) { //sellhouse
				_level = -1;
			}
			else if (x > 180 && x < 260 && y>280 && y < 320 && _level != 0) {
				_level = 0;
			}
			else if (x > 290 && x < 370 && y>360 && y < 400) {
				_isUIOK = true;
				_showHouseUI = false;
				_isOpen = false;
			}
			Sleep(70);
		}
	}

	void BuyUI::HouseTransaction(Role* role, Station* rolestation) {
		if (_level != 0) {
			rolestation->house->SetLevel(_level);
			rolestation->house->SetOwner(role->GetRoleNum());
			role->AddMoney(-rolestation->house->GetPrice(_level));
		}
		_isOK = true;
	}
	void BuyUI::TollsTransaction(Role* owner, Role* payer, int cash) {
		owner->AddMoney(cash);
		payer->AddMoney(-cash);
		_isOK = true;
	}
	//-----------------------------------------------------------------
	void BuyUI::StoreUI(int x, int y, bool mouseclick, Role* role)
	{
		if (mouseclick)
		{
			if (x > 470 && x < 550 && y>90 && y < 130 && role->GetMoney() > _cardPrice)
			{
				std::random_device rd;
				std::default_random_engine gen = std::default_random_engine(rd());
				std::uniform_int_distribution<int> dis(0, 2);
				_cardIndex = dis(gen);
				_isDraw = true;
				role->AddMoney(-_cardPrice);
				Sleep(100);
			}
			else if (x > 470 && x < 550 && y>350 && y < 390)
			{
				_isUIOK = true;
				_showStoreUI = false;
				_isOpen = false;
			}
		}
	}
	void BuyUI::UseCard(vector<Role*> &roleList, Role* role, Station** station , Station* rolestation, bool mouseclick, int posx, int posy, GameMap *map, Building** building) {
		if (_cardIndex >= 0) {  //有抽卡才做
			_card[_cardIndex]->SetCardIsUsing(true);
			_card[_cardIndex]->JudgeCard(roleList, role, station, mouseclick, posx, posy, map, building);
			if (!_card[_cardIndex]->GetCardIsUsing()) {  //卡片用完
				_isOK = true;
			}
		}
		else {
			_isOK = true;
		}
	}
	//-----------------------------------------------------------------------------------
	void BuyUI::LoadBitmap() {
		_UIBK.LoadBitmap(IDB_UI);
		_title[0].LoadBitmap(IDB_buytitle, RGB(0, 0, 100));
		_title[1].LoadBitmap(IDB_buy, RGB(0, 0, 100));
		_title[2].LoadBitmap(IDB_sell, RGB(0, 0, 100));
		_levelp[0][0].LoadBitmap(IDB_level1, RGB(0, 0, 100));
		_levelp[0][1].LoadBitmap(IDB_level2, RGB(0, 0, 100));
		_levelp[0][2].LoadBitmap(IDB_level3, RGB(0, 0, 100));
		_levelp[1][0].LoadBitmap(IDB_level1c, RGB(0, 0, 100));
		_levelp[1][1].LoadBitmap(IDB_level2c, RGB(0, 0, 100));
		_levelp[1][2].LoadBitmap(IDB_level3c, RGB(0, 0, 100));
		_dollar[0].LoadBitmap();
		_dollar[1].LoadBitmap();
		_dollar[2].LoadBitmap();
		_sell[0].LoadBitmap(IDB_btnsell, RGB(0, 0, 100));
		_sell[1].LoadBitmap(IDB_btnsellc, RGB(0, 0, 100));
		_dollar[3].LoadBitmap();
//----------------------------------------------
		_cardRandom.LoadBitmap(IDB_cardRandom, RGB(0, 0, 100));
		for (int i = 0; i < 3;i++) {
			_card[i]->LoadBitmap();
		}
		_draw.LoadBitmap(IDB_draw, RGB(0, 0, 100));
		_noDraw.LoadBitmap(IDB_poor, RGB(0, 0, 100));
		_OK.LoadBitmap(IDB_OK, RGB(0, 0, 100));
		for(int i=0;i<4;i++)
			_poor[i].LoadBitmap(IDB_poor, RGB(0, 0, 100));
	}
	void BuyUI::OnShow(vector<Role*> &roleList, Role* role, Station** station, Station* rolestation) {
		_UIBK.SetTopLeft(50, 50);
		_title[0].SetTopLeft(80,80);
		_title[1].SetTopLeft(80,170);
		_title[2].SetTopLeft(80,270);
		_levelp[0][0].SetTopLeft(180, 180);
		_levelp[0][1].SetTopLeft(320, 180);
		_levelp[0][2].SetTopLeft(460, 180);
		_levelp[1][0].SetTopLeft(180, 180);
		_levelp[1][1].SetTopLeft(320, 180);
		_levelp[1][2].SetTopLeft(460, 180);
		_dollar[0].SetTopLeft(170, 240);
		_dollar[1].SetTopLeft(310, 240);
		_dollar[2].SetTopLeft(450, 240);
		_poor[0].SetTopLeft(180,180);
		_poor[1].SetTopLeft(320,180);
		_poor[2].SetTopLeft(460,180);
		_sell[0].SetTopLeft(180,280);
		_sell[1].SetTopLeft(180,280);
		_dollar[3].SetTopLeft(170,340);
		_poor[3].SetTopLeft(180,280);
//-----------------------------------------------------card
		_cardRandom.SetTopLeft(90, 90);
		_draw.SetTopLeft(470, 90);
		_noDraw.SetTopLeft(470, 90);
		_OK.SetTopLeft(290, 360);
		role->_money.SetTopLeft(450,360);
		if (_isOpen ) {
			if (!_isUIOK) {
				_UIBK.ShowBitmap();
				if (_showHouseUI) {
					_title[0].ShowBitmap();
					_title[1].ShowBitmap();
					_title[2].ShowBitmap();
					switch (_level) {
					case 0:
						_levelp[0][0].ShowBitmap();
						_levelp[0][1].ShowBitmap();
						_levelp[0][2].ShowBitmap();
						break;
					case 1:
						_levelp[1][0].ShowBitmap();
						_levelp[0][1].ShowBitmap();
						_levelp[0][2].ShowBitmap();
						break;
					case 2:
						_levelp[0][0].ShowBitmap();
						_levelp[1][1].ShowBitmap();
						_levelp[0][2].ShowBitmap();
						break;
					case 3:
						_levelp[0][0].ShowBitmap();
						_levelp[0][1].ShowBitmap();
						_levelp[1][2].ShowBitmap();
						break;
					default:
						break;
					}
					_dollar[0].ShowBitmap();
					_dollar[1].ShowBitmap();
					_dollar[2].ShowBitmap();
					_dollar[3].ShowBitmap();
					role->_money.ShowBitmap();

					if (_level == 0) {
						_sell[0].ShowBitmap();
					}
					else if (_level == -1) {
						_sell[1].ShowBitmap();
					}
					if (rolestation->GetBuildingType() =="House")
					{
						if (role->GetMoney() < rolestation->house->GetPrice(3)) {
							_poor[2].ShowBitmap();
						}
						if (role->GetMoney() < rolestation->house->GetPrice(2)) {
							_poor[1].ShowBitmap();
						}
						if (role->GetMoney() < rolestation->house->GetPrice(1)) {
							_poor[0].ShowBitmap();
						}
						if (rolestation->house->GetOwner() != role->GetRoleNum()) {
							_poor[3].ShowBitmap();
						}
					}
					
					_OK.ShowBitmap();
				}
				else if (_showStoreUI) {
					_OK.SetTopLeft(470, 350);
					_OK.ShowBitmap();
					if (!_isDraw)
					{
						_cardRandom.ShowBitmap();
					}
					else
					{
						_card[_cardIndex]->OnShow(roleList, role, station, rolestation);
					}
					if (role->GetMoney() <= _cardPrice)//錢不夠
					{
						_noDraw.ShowBitmap();
					}
					else if (role->GetMoney() > _cardPrice)//錢夠
					{
						_draw.ShowBitmap();
					}
				}
			}
		}
		if (_isDraw) {
			_card[_cardIndex]->OnShow(roleList, role, station, rolestation);
		}
	}
}