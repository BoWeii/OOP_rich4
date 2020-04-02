#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Card.h"


namespace game_framework
{
	Card::Card() {}
	Card::Card(CardName cardKind): _cardKind(cardKind), _cardIsUsing(false), _targetConfirm(false){}
	int Card::GetCardKind() {
		switch (_cardKind) {
		case CardName::toNext:
			break;
		case CardName::burnHouse:
			break;
		case CardName::steal:
			break;
		}
		return 0;
	}
	void Card::SetCardIsUsing(bool flag) {
		_cardIsUsing = flag;
	}
	bool Card::GetCardIsUsing() {
		return _cardIsUsing;
	}
	void Card::JudgeCard(vector<Role*> &roleList, Role* role, Station** station, bool mouseclick, int posx, int posy, GameMap *map, Building** building) {
		int nextstate=0;
		switch (_cardKind) {
		case CardName::toNext:
			nextstate = role->GetRoleState() + 1;
			if (nextstate == 81) {
				nextstate = 0;
			}
			TossAgain(roleList,role, station,station[nextstate], 1,map,building);
			break;
		case CardName::burnHouse:
			ChooseHouse(roleList,station,mouseclick, posx, posy, map, building);
			break;
		case CardName::steal:
			StealMoney(roleList, station, role, mouseclick, posx, posy, map, building);
			break;
		}
	}
	void Card::TossAgain(vector<Role*> &roleList, Role* role, Station** station, Station* rolestation, int direction, GameMap *map, Building** building){
		if (_dice[2].IsToss() && _dice[0].IsToss()) {
			role->SetShowRole(false);
			_dice[2].setXY(460, 420);
			_dice[2].TossDice(0);
		}
		if (_dice[1].IsToss() && _dice[0].IsToss()) {
			_dice[1].setXY(520, 420);
			_dice[1].TossDice(0);
		}
		if (_dice[0].IsToss()) {	
			_dice[0].setXY(580, 420);
			_dice[0].TossDice(0);
			CAudio::Instance()->Play(AUDIO_CAR, true);
		}

		int camerax, cameray;
		camerax = role->GetCameraX();
		cameray = role->GetCameraY();
		map->OnMove(camerax, cameray);
		for (int i = 0; i < 81; i++)
			station[i]->OnMove(camerax, cameray);
		for (unsigned int i = 0; i < roleList.size(); i++) {
			roleList[i]->OnMove(camerax, cameray);
		}
		for (int i = 0; i < 49; i++)
			building[i]->OnMove(camerax, cameray);

		_carDown.OnMove();
		_carUp.OnMove();
		_carLeft.OnMove();
		_carRight.OnMove();
		if (_dice[2].GetDiceNumber() > 0){
			if (role->SetRoleMove(rolestation, direction)) {
				_dice[2].SetDiceNumber(_dice[2].GetDiceNumber() - 1);
			}
		}
		else if (_dice[1].GetDiceNumber()>0){
			if (role->SetRoleMove(rolestation, direction)) {
				_dice[1].SetDiceNumber(_dice[1].GetDiceNumber() - 1);
			}
		}
		else if (_dice[0].GetDiceNumber() > 0) {
			if (role->SetRoleMove(rolestation, direction)) {
				_dice[0].SetDiceNumber(_dice[0].GetDiceNumber() - 1);
			}
		}
		else if (_dice[0].GetDiceNumber() == 0){
			role->SetShowRole(true);
			_dice[0].SetDiceIsToss(true);
			_dice[1].SetDiceIsToss(true);
			_dice[2].SetDiceIsToss(true);
			_cardIsUsing = false;
			CAudio::Instance()->Stop(AUDIO_CAR);
		}
	}
	void Card::ChooseHouse(vector<Role*> &roleList ,Station** station, bool mouseclick, int posx, int posy, GameMap *map, Building** building) {
		if (!_targetConfirm) {
			map->OnMove();
			for (int i = 0; i < 81; i++) {
				station[i]->OnMove();
			}
			for (int i = 0; i < 49; i++) {
				building[i]->OnMove();
			}
			for (unsigned int i = 0; i < roleList.size(); i++) {
				roleList[i]->OnMove();
			}
		}
		if (mouseclick&&!_targetConfirm) {
			for (int i = 0; i < 81; i++) {
				if (station[i]->GetBuildingType() == "House") {
					if (station[i]->house->GetX() + 50 >= posx && station[i]->house->GetX() <= posx && station[i]->house->GetY() + 50 >= posy && station[i]->house->GetY() <= posy) {
						_targetx = station[i]->house->GetX();
						_targety = station[i]->house->GetY();
						station[i]->house->SetLevel(-1);
						station[i]->house->SetOwner(4);
						_targetConfirm = true;
						CAudio::Instance()->Play(AUDIO_BOMB, false);
					}
				}
			}
		}
		else if (_targetConfirm) {
			
			if (_bomb.IsFinalBitmap()) {
				_bomb.Reset();
				_targetConfirm = false;
				_cardIsUsing = false;
			}
			_bomb.OnMove();
		}
	}
	void Card::StealMoney(vector<Role*> &roleList, Station** station, Role* role, bool mouseclick, int posx, int posy, GameMap *map, Building** building) {
		if (!_targetConfirm) {
			map->OnMove();
			for (int i = 0; i < 81; i++) {
				station[i]->OnMove();
			}
			for (int i = 0; i < 49; i++) {
				building[i]->OnMove();
			}
			for (unsigned int i = 0; i < roleList.size(); i++) {
				roleList[i]->OnMove();
			}
		}
		if (mouseclick && !_targetConfirm) {
			for (unsigned int i = 0; i < roleList.size(); i++) {
				if (roleList[i]->GetX() + 50 >= posx && roleList[i]->GetX() <= posx && roleList[i]->GetY() + 10 >= posy && roleList[i]->GetY() - 50 <= posy) {
					_targetx = roleList[i]->GetX() - 50;
					_targety = roleList[i]->GetY();
					_roleBeSteal = roleList[i];
					role->AddMoney(2000);
					_targetConfirm = true;
					CAudio::Instance()->Play(AUDIO_STEAL, false);
					break;
				}
			}
		}
		else if (_targetConfirm) {
			if (_steal.IsFinalBitmap()) {
				_roleBeSteal->AddMoney(-2000);
				_steal.Reset();
				_targetConfirm = false;
				_cardIsUsing = false;
				CAudio::Instance()->Stop(AUDIO_STEAL);
			}
			_targetx += 3;
			_steal.OnMove();
		}
	}
	void Card::LoadBitmap() {

		switch (_cardKind) {
		case CardName::toNext:
			_card.LoadBitmap(IDB_carCard, RGB(0, 0, 100));
			_dice[0].LoadBitmap();
			_dice[1].LoadBitmap();
			_dice[2].LoadBitmap();
			_carDown.AddBitmap(IDB_Car_1, RGB(255, 255, 255));
			_carDown.AddBitmap(IDB_Car_2, RGB(255, 255, 255));
			_carDown.AddBitmap(IDB_Car_3, RGB(255, 255, 255));
			_carDown.AddBitmap(IDB_Car_4, RGB(255, 255, 255));
			_carLeft.AddBitmap(IDB_Car_5, RGB(255, 255, 255));
			_carLeft.AddBitmap(IDB_Car_6, RGB(255, 255, 255));
			_carLeft.AddBitmap(IDB_Car_7, RGB(255, 255, 255));
			_carLeft.AddBitmap(IDB_Car_8, RGB(255, 255, 255));
			_carRight.AddBitmap(IDB_Car_9, RGB(255, 255, 255));
			_carRight.AddBitmap(IDB_Car_10, RGB(255, 255, 255));
			_carRight.AddBitmap(IDB_Car_11, RGB(255, 255, 255));
			_carRight.AddBitmap(IDB_Car_12, RGB(255, 255, 255));
			_carUp.AddBitmap(IDB_Car_13, RGB(255, 255, 255));
			_carUp.AddBitmap(IDB_Car_14, RGB(255, 255, 255));
			_carUp.AddBitmap(IDB_Car_15, RGB(255, 255, 255));
			_carUp.AddBitmap(IDB_Car_16, RGB(255, 255, 255));		
			CAudio::Instance()->Load(AUDIO_CAR, "sounds\\car.mp3");

			break;
		case CardName::burnHouse:
			_card.LoadBitmap(IDB_bombCard, RGB(0, 0, 100));
			_bomb.AddBitmap(IDB_bomb1, RGB(0, 0, 100));
			_bomb.AddBitmap(IDB_bomb2, RGB(0, 0, 100));
			_bomb.AddBitmap(IDB_bomb3, RGB(0, 0, 100));
			_bomb.AddBitmap(IDB_bomb4, RGB(0, 0, 100));
			_bomb.AddBitmap(IDB_bomb5, RGB(0, 0, 100));
			_bomb.AddBitmap(IDB_bomb6, RGB(0, 0, 100));
			_bomb.AddBitmap(IDB_bomb7, RGB(0, 0, 100));
			_bomb.AddBitmap(IDB_bomb8, RGB(0, 0, 100));
			_bomb.AddBitmap(IDB_bomb9, RGB(0, 0, 100));
			_bomb.AddBitmap(IDB_bomb10, RGB(0, 0, 100));
			_bomb.AddBitmap(IDB_bomb11, RGB(0, 0, 100));
			_bomb.AddBitmap(IDB_bomb12, RGB(0, 0, 100));
			_bomb.AddBitmap(IDB_bomb13, RGB(0, 0, 100));
			_bomb.AddBitmap(IDB_bomb14, RGB(0, 0, 100));
			_bomb.AddBitmap(IDB_bomb15, RGB(0, 0, 100));
			CAudio::Instance()->Load(AUDIO_BOMB, "sounds\\bomb.mp3");

			break;
		case CardName::steal:	
			_card.LoadBitmap(IDB_stealCard, RGB(0, 0, 100));
			_steal.AddBitmap(IDB_steal1, RGB(0, 0, 100));
			_steal.AddBitmap(IDB_steal2, RGB(0, 0, 100));
			_steal.AddBitmap(IDB_steal3, RGB(0, 0, 100));
			_steal.AddBitmap(IDB_steal4, RGB(0, 0, 100));
			_steal.AddBitmap(IDB_steal5, RGB(0, 0, 100));
			_steal.AddBitmap(IDB_steal6, RGB(0, 0, 100));
			CAudio::Instance()->Load(AUDIO_STEAL, "sounds\\steal.mp3");
			break;
		}
	}
	void Card::OnShow(vector<Role*> &roleLList, Role* role, Station** station, Station* rolestation) {
		if (_cardIsUsing) {
			if (_cardKind == CardName::toNext) {
				_dice[0].OnShow();
				_dice[1].OnShow();
				_dice[2].OnShow();
				int rolestate=role->GetRoleState() + 1;
				if (rolestate == 81) {
					rolestate = 0;
				}
				if (role->GetY() < station[rolestate]->GetY()) {
					_carDown.SetTopLeft(role->GetX(), role->GetY() - 45);
					_carDown.OnShow();
				}
				else if (role->GetY() > station[rolestate]->GetY()) {
					_carUp.SetTopLeft(role->GetX(), role->GetY() - 45);
					_carUp.OnShow();
				}
				else if (role->GetX() > station[rolestate]->GetX()) {
					_carLeft.SetTopLeft(role->GetX(), role->GetY() - 45);
					_carLeft.OnShow();
				}
				else if (role->GetX() < station[rolestate]->GetX()) {
					_carRight.SetTopLeft(role->GetX(), role->GetY() - 45);
					_carRight.OnShow();
				}
				else {
					_carDown.SetTopLeft(role->GetX(), role->GetY() - 45);
					_carDown.OnShow();
				}
			}
			else if (_cardKind == CardName::burnHouse) {
				if (_targetConfirm) {
					_bomb.SetTopLeft(_targetx, _targety - 30);
					_bomb.OnShow();
				}
			}
			else if (_cardKind == CardName::steal) {
				if (_targetConfirm) {
					_steal.SetTopLeft(_targetx, _targety - 40);
					_steal.OnShow();
				}
			}

		}
		else {
			_card.SetTopLeft(90, 90);
			_card.ShowBitmap();
		}
	}
	
}