// mygame.cpp: 本檔案儲遊戲本身的class的implementation 
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////
	CGameStateInit::CGameStateInit(CGame *g): CGameState(g)
	{
	}
	void CGameStateInit::OnInit()
	{
		ShowInitProgress(0);	// 一開始的loading進度為0%
		_start.LoadBitmap(IDB_INT);
		_explainLogo.LoadBitmap(IDB_explainIcon);
		_explain.LoadBitmap(IDB_explain);
		_about.LoadBitmap(IDB_about);
		_aboutLogo.LoadBitmap(IDB_aboutIcon);
	}
	void CGameStateInit::OnBeginState()
	{
	}
	void CGameStateInit::OnMove()
	{
	}
	void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
	}
	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC = 27;
		const char KEY_SPACE = 0x20;
		if (nChar == KEY_SPACE)
			GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
		else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
	}
	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
	}
	void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		pos = point;
	}
	void CGameStateInit::OnShow()
	{
		_start.SetTopLeft(0, 0);
		_start.ShowBitmap();
		_explainLogo.SetTopLeft(250, 360);
		_explainLogo.ShowBitmap();
		_explain.SetTopLeft(150, 20);
		_about.SetTopLeft(200, 20);
		_aboutLogo.SetTopLeft(350, 360);
		_aboutLogo.ShowBitmap();
		if (pos.x > 250 && pos.x < _explainLogo.Width() + 250 && pos.y>360 && pos.y < _explainLogo.Height() + 360)
			_explain.ShowBitmap();
		if (pos.x > 350 && pos.x < _aboutLogo.Width() + 350 && pos.y>360 && pos.y < _aboutLogo.Height() + 360)
			_about.ShowBitmap();
	}
	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
	}
	void CGameStateOver::OnMove()
	{
		counter--;
		if (counter < 0) {
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
		}
	}
	void CGameStateOver::OnBeginState()
	{
		counter = 30 * 5; // 5 seconds
	}

	void CGameStateOver::OnInit()
	{
		ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
		Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		ShowInitProgress(100);
	}
	void CGameStateOver::OnShow()
	{
	}
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////
	CGameStateRun::CGameStateRun(CGame *g)
		: CGameState(g), STATION(81), _whoTurn(0), _playerAmount(4), mouseclick(false), BUILDING(49), HOUSE(41), STORE(8), LOTTERY_OPEN_ROUND(3), _isShowGameOver(false), _isbankrupt(false), _buyUIOnce(false), _isDelete(false)
	{  
		Role* role;
		for (unsigned int i = 0; i < _playerAmount;i++) {
			role = new Role(i);
			players.push_back(role);
		}
		for (int i = 0; i < STATION; i++)
			station[i] = new Station;
		for (int i = 0; i < HOUSE; i++) {
			house[i] = new House;
		}
		for (int i = 0; i < STORE; i++) {
			store[i] = new Store;
		}
		int houseNum=0, storeNum=0;
		for (int i = 0; i < BUILDING; i++)
		{
			if (i == 9 || i == 12 || i == 23 || i == 21 || i == 31 || i == 36 || i == 2 || i == 4)
			{
				building[i] = store[storeNum++];
			}
			else
			{
				building[i] = house[houseNum++];
			}
		}
	}
	CGameStateRun::~CGameStateRun()
	{
		_buyUI.~BuyUI();
		players.clear();
		for(int i=0;i<BUILDING;i++)
			delete [] building[i];
		for(int i=0;i<STATION;i++)
			delete [] station[i];
	}
	void CGameStateRun::OnBeginState()
	{
		const int BALL_GAP = 90;
		const int BALL_XY_OFFSET = 45;
		const int BALL_PER_ROW = 7;
		const int HITS_LEFT = 10;
		const int HITS_LEFT_X = 590;
		const int HITS_LEFT_Y = 0;
		const int BACKGROUND_X = 60;
		const int ANIMATION_SPEED = 15;
		//----------at map[0]-----------------------------------------at map[1] -------------------------------at map[2]
		station[0]->SetXY(560, 280);/*-----------------*/station[76]->SetXY(1128, 292);/*-----------------*/station[58]->SetXY(1592, 376);
			building[46]->SetXY(1193, 292);/*------------*/building[36]->SetXY(1527, 376);
		station[1]->SetXY(496, 332);/*-----------------*/station[77]->SetXY(1040, 200);/*-----------------*/station[59]->SetXY(1480, 276);
			building[0]->SetXY(429, 332);/*-----------------------------------------------------------------*/building[37]->SetXY(1490, 241);
		station[2]->SetXY(552, 416);/*-----------------*/station[78]->SetXY(944, 272);/*------------------*/station[60]->SetXY(1388, 228);
			building[1]->SetXY(485, 416);
		station[80]->SetXY(692, 280);/*----------------*/station[61]->SetXY(1428, 412);
				building[48]->SetXY(692, 245);/*---------*/building[38]->SetXY(1363, 412);
		//----------at map[3]-----------------------------------------at map[4] -------------------------------at map[5]
		station[3]->SetXY(560, 560);/*-----------------*/station[72]->SetXY(1156, 872);/*-----------------*/station[55]->SetXY(1740, 864);
				building[43]->SetXY(1221, 872);				building[34]->SetXY(1805, 864);
		station[4]->SetXY(436, 572);/*-----------------*/station[73]->SetXY(904, 776);/*-----------------*/station[56]->SetXY(1692, 660);
			building[2]->SetXY(436, 537);/*----------------------------------------------------------------*/building[35]->SetXY(1757, 660);
		station[5]->SetXY(344, 552);/*-----------------*/station[74]->SetXY(992, 676);/*-----------------*/station[57]->SetXY(1692, 660);
			building[3]->SetXY(344, 517);/*----------------*/building[44]->SetXY(1059, 677);
		station[6]->SetXY(284, 620);/*-----------------*/station[75]->SetXY(1064, 528);/*-----------------*/station[62]->SetXY(1324, 636);
			building[4]->SetXY(219, 620);/*----------------*/building[45]->SetXY(1130, 528);/*---------------*/building[39]->SetXY(1259, 636);
		station[7]->SetXY(252, 680);/*-----------------*/station[79]->SetXY(852, 500);/*------------------*/station[63]->SetXY(1428, 704);
			building[5]->SetXY(185, 680);/*----------------*/building[47]->SetXY(789, 500);/*-----------------*/building[40]->SetXY(1493, 680);
		station[8]->SetXY(400, 760);/*--------------------------------------------------------------------*/station[64]->SetXY(1312, 768);
			building[6]->SetXY(400, 725);/*---------------------------------------------------------------*/station[65]->SetXY(1416, 840);
		station[9]->SetXY(456, 872);/*--------------------------------------------------------------------*/station[66]->SetXY(1512, 908);
		//----------at map[6]-----------------------------------------at map[7] -------------------------------at map[8]
		station[10]->SetXY(224, 960);/*-----------------*/station[68]->SetXY(1064, 1108);/*-----------------*/station[50]->SetXY(1684, 1364);
			building[41]->SetXY(1064, 1073);
		station[11]->SetXY(368, 1000);/*----------------*/station[69]->SetXY(940, 1120);/*-----------------*/station[51]->SetXY(1516, 1324);
			building[42]->SetXY(875, 1120);
		station[12]->SetXY(380, 1080);/*----------------*/station[70]->SetXY(896, 1020);/*-----------------*/station[52]->SetXY(1556, 1220);
		station[13]->SetXY(252, 1136);/*----------------*/station[71]->SetXY(1040, 980);/*-------------------*/building[31]->SetXY(1620, 1220);
		/*-------------------------------------------------------------------------------------------------*/station[53]->SetXY(1668, 1140);
		station[14]->SetXY(212, 1236);/*---------------------------------------------------------------------*/building[32]->SetXY(1732, 1140);
		/*-------------------------------------------------------------------------------------------------*/station[54]->SetXY(1724, 988);
		station[15]->SetXY(168, 1352);/*---------------------------------------------------------------------*/building[33]->SetXY(1789, 988);
		station[67]->SetXY(1312, 1012);
			building[34]->SetXY(1312, 977);
		//----------at map[9]-----------------------------------------at map[10] -------------------------------at map[11]
		station[16]->SetXY(152, 1508);/*-----------------*/station[31]->SetXY(744, 1840);/*-----------------*/station[42]->SetXY(1664, 1852);
			building[18]->SetXY(744, 1805);/*---------------*/building[27]->SetXY(1729, 1822);
		station[17]->SetXY(172, 1592);/*-----------------*/station[32]->SetXY(868, 1788);/*-----------------*/station[43]->SetXY(1500, 1852);
			building[19]->SetXY(868, 1753);/*----------------*/building[28]->SetXY(1500, 1817);
		station[18]->SetXY(128, 1696);/*-----------------*/station[33]->SetXY(1020, 1784);/*-----------------*/station[44]->SetXY(1344, 1784);
			building[20]->SetXY(1020, 1749);/*--------------*/building[29]->SetXY(1279, 1784);
		station[19]->SetXY(128, 1824);/*-----------------*/station[34]->SetXY(1156, 1760);/*-----------------*/station[45]->SetXY(1436, 1712);
			building[21]->SetXY(1210, 1725);/*--------------*/building[30]->SetXY(1501, 1712);
		station[20]->SetXY(320, 1832);/*-----------------*/station[35]->SetXY(1108, 1844);/*-----------------*/station[46]->SetXY(1352, 1632);
			building[7]->SetXY(320, 1798);/*----------------*/building[22]->SetXY(1173, 1844);
		station[21]->SetXY(424, 1832);/*---------------------------------------------------------------------*/station[47]->SetXY(1460, 1580);
			building[8]->SetXY(410, 1798);
		station[22]->SetXY(532, 1856);/*---------------------------------------------------------------------*/station[48]->SetXY(1576, 1560);
			building[9]->SetXY(597, 1856);/*-----------------------------------------------------------------*/station[49]->SetXY(1788, 1500);
		//----------at map[12]-----------------------------------------at map[13] -------------------------------at map[14]
		station[23]->SetXY(504, 1968);/*-----------------*/station[28]->SetXY(704, 2112);/*-----------------*/station[37]->SetXY(1320, 2016);
			building[10]->SetXY(569, 1968);/*--------------*/building[15]->SetXY(769, 2112);/*-----------------*/building[24]->SetXY(1320, 1981);
		station[24]->SetXY(368, 2000);/*-----------------*/station[29]->SetXY(704, 2040);/*-----------------*/station[38]->SetXY(1412, 2092);
			building[11]->SetXY(368, 1965);/*--------------*/building[16]->SetXY(769, 2040);
		station[25]->SetXY(272, 2072);/*-----------------*/station[30]->SetXY(704, 1944);/*-----------------*/station[39]->SetXY(1496, 2016);
			building[12]->SetXY(207, 2072);/*-----------------*/building[17]->SetXY(769, 1944);/*--------------*/building[25]->SetXY(1496, 1981);
		station[26]->SetXY(428, 2108);/*-----------------*/station[36]->SetXY(1176, 1960);/*----------------*/station[40]->SetXY(1640, 1964);
			building[13]->SetXY(428, 2073);/*--------------*/building[23]->SetXY(1111, 1960);
		station[27]->SetXY(544, 2108);/*--------------------------------------------------------------------*/station[41]->SetXY(1736, 1960);
			building[14]->SetXY(544, 2073);/*-----------------------------------------------------------------*/building[26]->SetXY(1801, 1960);
		for (int i = 0; i < STATION; i++)
		{
			int stationX = station[i]->GetX(), stationY = station[i]->GetY();
			for (int j = 0; j < BUILDING; j++)
			{
				if (stationX + 70 > building[j]->GetX() && stationX - 70 < building[j]->GetX() &&
					stationY + 10 > building[j]->GetY() && stationY - 40 < building[j]->GetY() && building[j]->GetType() == "House")
				{
					station[i]->house = (House *)building[j];
					station[i]->store = nullptr;
					station[i]->SetBuildingType("House");
					break;
				}
				else if (stationX + 70 > building[j]->GetX() && stationX - 70 < building[j]->GetX() &&
					stationY + 10 > building[j]->GetY() && stationY - 40 < building[j]->GetY() && building[j]->GetType() == "Store")
				{
					station[i]->house = nullptr;
					station[i]->store = (Store *)building[j];
					station[i]->SetBuildingType("Store");
				}
			}
		}
		gamemap.Initialize();
		help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
		CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
		CAudio::Instance()->Play(AUDIO_BM, true);			// 撥放 MIDI
	}
	void CGameStateRun::GoRoleScene()
	{
		int camerax, cameray;
		camerax = players[_whoTurn]->GetCameraX();
		cameray = players[_whoTurn]->GetCameraY();
		gamemap.OnMove(camerax, cameray);
		for (int i = 0; i < STATION; i++)
			station[i]->OnMove(camerax, cameray);
		for (unsigned int i = 0; i < _playerAmount; i++) {
			players[i]->OnMove(camerax, cameray);
		}
		for (int i = 0; i < BUILDING; i++)
			building[i]->OnMove(camerax, cameray);
	}
	void CGameStateRun::DoAction()
	{
		if (!_buyUIOnce)
		{
			JudgeBankrupt();
			_buyUI.JudgeHS(pos.x, pos.y, mouseclick, players, players[_whoTurn], station, station[players[_whoTurn]->GetRoleState()], &gamemap, building, _isbankrupt);//打開UI 如果沒建築將不做事
			if (_buyUI.GetIsOK()) {
				for (vector<Role*>::iterator i = players.begin(); i != players.end(); i++) {  //檢查角色金額是否小於0  刪除 剩一人刪除角色及reset房子
					if ((*i)->GetMoney() <= 0)
					{
						_isbankrupt = true;
					}
				}
				if (!_isbankrupt)
				{
					lottery.SetIsOK(false);
					_othersUI.SetOnce(false);
					_round.AddRound(_whoTurn, _playerAmount);
					_whoTurn++;
					dice.SetDiceIsToss(true);
				}
				if (_whoTurn == _playerAmount) {
					_whoTurn = 0;
				}
				_buyUI.SetIsOK(false);//重設UI狀態
				_buyUIOnce = true;
				GoRoleScene();
			}
		}
	}
	void CGameStateRun::DoLottery()
	{
		if (_round.GetRound() % LOTTERY_OPEN_ROUND == 0 && _round.GetRound() != 0 && !lottery.GetIsOK())//樂透判斷是否開獎
		{
			lottery.DrawTheNumber(pos.x, pos.y, mouseclick, players);
			if (lottery.GetIsOK())
			{
				_othersUI.ResetLotteryUI();
				_round.SetRound(0);
			}
		}
	}
	void CGameStateRun::JudgeBankrupt()
	{
		if (players.size() < 2) {
			if (gameover.IsOK())
			{
				CAudio::Instance()->Stop(AUDIO_BM);
				PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
			}
			else
				gameover.bankrupt(players[0], pos.x, pos.y, mouseclick);
		}
		else {
			unsigned int index = 0;
			for (vector<Role*>::iterator i = players.begin(); i != players.end(); i++, index++) {  //檢查角色金額是否小於0  刪除 剩一人刪除角色及reset房子
				if ((*i)->GetMoney() <= 0)
				{
					if(!_isDelete)
						_isbankrupt = true;
					roleDelet = (*i)->GetRoleNum();
					gameover.bankrupt(*i, pos.x, pos.y, mouseclick);
					if (gameover.IsOK())
					{
						_isDelete = true;
						_isbankrupt = false;
						gameover.SetIsOK(false);
						_othersUI.SetOnce(false);
						_othersUI.SetIsOpen(false);
						for (int j = 0; j < STATION; j++) {
							if (station[j]->GetBuildingType() == "House") {
								if (station[j]->house->GetOwner() == (*i)->GetRoleNum()) {
									station[j]->house->SetLevel(-1);
									station[j]->house->SetOwner(4);
								}
							}
						}
						if (_whoTurn == _playerAmount - 1) {
							_whoTurn = 0;
						}
						else if (index > _whoTurn)
						{
							_whoTurn++;
							if (_whoTurn == _playerAmount - 1) {//注意whoturn不能超過playerAmount
								_whoTurn = 0;
							}
						}
						i = players.erase(i);
						_playerAmount -= 1;
						GoRoleScene();
						break;
					}			
				}
			}
		}
		if (_isDelete){ //角色以刪除
			lottery.SetIsOK(false);
			_othersUI.SetOnce(false);
			_round.AddRound(_whoTurn, _playerAmount);
			_isDelete = false;
			dice.SetDiceIsToss(true);
		}
	}
	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		if (!_menu.GetDone()) {
			_menu.OnChoose(pos.x, pos.y, mouseclick);
		}
		if (_menu.GetDone()) {
			JudgeBankrupt();
			if (!dice.IsToss()) {
				if (dice.GetDiceNumber() != 0) {
					_buyUIOnce = false;
					GoRoleScene();
				}
				dice.SetDiceNumber(players[_whoTurn]->RoleMove(dice.GetDiceNumber(), station)); 
				if (dice.GetDiceNumber() == 0) {//到達最終位置
					DoAction();
				}
			}
			else {
				DoLottery();
				if (_othersUI.GetMenuIsOpen())
					_othersUI.JudgeUI(pos.x, pos.y, mouseclick, players, players[_whoTurn], station, lottery);
				gamemap.OnMove();
				for (int i = 0; i < STATION; i++)
					station[i]->OnMove();
				for (unsigned int i = 0; i < _playerAmount; i++) {
					players[i]->OnMove();
				}
				for (int i = 0; i < BUILDING; i++)
					building[i]->OnMove();
			}
		}	
	}
	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		ShowInitProgress(33);	
		gamemap.LoadBitmap();
		_menu.LoadBitmap();
		for (unsigned int i = 0; i < _playerAmount; i++) {
			players[i]->LoadBitmap();
		}
		for (int i = 0; i < STATION; i++)
			station[i]->LoadBitmap();
		for (int i = 0; i < BUILDING; i++)
			building[i]->LoadBitmap();
		dice.LoadBitmap();
		_buyUI.LoadBitmap();
		_othersUI.LoadBitmap();
		lottery.LoadBitmap();
		gameover.LoadBitmap();
		ShowInitProgress(50);
		Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		help.LoadBitmap(IDB_HELP, RGB(255, 255, 255));				// 載入說明的圖形
		corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
		CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
		CAudio::Instance()->Load(AUDIO_BM, "sounds\\backmusic.mp3");	// 載入編號2的聲音ntut.mid
	}
	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_SPACE = 0x20;
		const char KEY_Q = 81;
		const char KEY1 = 49, KEY2 = 50, KEY3 = 51, KEY4 = 52, KEY5 = 53, KEY6 = 54;
		bool tossdice = false;
		int diceNum = 0;
		if (nChar == KEY1 || nChar == KEY2 || nChar == KEY3 || nChar == KEY4 || nChar == KEY5 || nChar == KEY6 || nChar == KEY_SPACE) {
			tossdice = true;
		}
		if (nChar == KEY_LEFT ) {
			gamemap.SetMovingLeft(true);
			for (int i = 0; i < STATION; i++)
				station[i]->SetMovingLeft(true);
			for (unsigned int i = 0; i < _playerAmount; i++) {
				players[i]->SetMovingLeft(true);
			}
			for (int i = 0; i < BUILDING; i++)
				building[i]->SetMovingLeft(true);
		}
		//////////////////////////////////////////////////////
		if (nChar == KEY_RIGHT) {
			gamemap.SetMovingRight(true);
			for (int i = 0; i < STATION; i++)
				station[i]->SetMovingRight(true);
			for (unsigned int i = 0 ;i < _playerAmount; i++) {
				players[i]->SetMovingRight(true);
			}
			for (int i = 0; i < BUILDING; i++)
				building[i]->SetMovingRight(true);
		}
		//////////////////////////////////////////////////////
		if (nChar == KEY_UP ) {
			gamemap.SetMovingUp(true);
			for (int i = 0; i < STATION; i++)
				station[i]->SetMovingUp(true);
			for (unsigned int i = 0; i < _playerAmount; i++) {
				players[i]->SetMovingUp(true);
			}
			for (int i = 0; i < BUILDING; i++)
				building[i]->SetMovingUp(true);
		}
		//////////////////////////////////////////////////////
		if (nChar == KEY_DOWN) {
			gamemap.SetMovingDown(true);
			for (int i = 0; i < STATION; i++)
				station[i]->SetMovingDown(true);
			for (unsigned int i = 0; i < _playerAmount; i++) {
				players[i]->SetMovingDown(true);
			}
			for (int i = 0; i < BUILDING; i++)
				building[i]->SetMovingDown(true);
		}
		if (tossdice && dice.IsToss() && _menu.GetDone() && !_othersUI.GetMenuIsOpen() && !_othersUI.GetOthersIsOpen() && !lottery.GetIsOpen())
		{
			switch (nChar) {
			case KEY1:
				diceNum = 1;
				break;
			case KEY2:
				diceNum = 2;
				break;
			case KEY3:
				diceNum = 3;
				break;
			case KEY4:
				diceNum = 4;
				break;
			case KEY5:
				diceNum = 5;
				break;
			case KEY6:
				diceNum = 6;
				break;
			case KEY_SPACE:
				diceNum = 0;
				break;
			}
			dice.TossDice(diceNum);
		}
		if (nChar == KEY_Q && _menu.GetDone() && dice.IsToss() && !_othersUI.GetOthersIsOpen() && !lottery.GetIsOpen())
		{
			_othersUI.SetIsOpen();
		}
	}
	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)  
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_SPACE = 0x20;
		const char KEY1 = 49, KEY2 = 50, KEY3 = 51, KEY4 = 52, KEY5 = 53, KEY6 = 54;
		bool tossdice = false;
		if (nChar == KEY1 || nChar == KEY2 || nChar == KEY3 || nChar == KEY4 || nChar == KEY5 || nChar == KEY6 || nChar == KEY_SPACE) {
			tossdice = true;
		}
		Role* rmrole;
		if (nChar == KEY_LEFT)
		{
			gamemap.SetMovingLeft(false);
			for (int i = 0; i < STATION; i++)
				station[i]->SetMovingLeft(false);
			for (unsigned int i = 0; i < _playerAmount; i++) {
				players[i]->SetMovingLeft(false);
			}
			for (int i = 0; i < BUILDING; i++)
				building[i]->SetMovingLeft(false);
		}
		//////////////////////////////////////////////////////
		if (nChar == KEY_RIGHT)
		{
			gamemap.SetMovingRight(false);
			for (int i = 0; i < STATION; i++)
				station[i]->SetMovingRight(false);
			for (unsigned int i = 0; i < _playerAmount; i++) {
				players[i]->SetMovingRight(false);
			}
			for (int i = 0; i < BUILDING; i++)
				building[i]->SetMovingRight(false);
		}
		//////////////////////////////////////////////////////
		if (nChar == KEY_UP)
		{
			gamemap.SetMovingUp(false);
			for (int i = 0; i < STATION; i++)
				station[i]->SetMovingUp(false);
			for (unsigned int i = 0; i < _playerAmount; i++) {
				players[i]->SetMovingUp(false);
			}
			for (int i = 0; i < BUILDING; i++)
				building[i]->SetMovingUp(false);
		}
		//////////////////////////////////////////////////////	
		if (nChar == KEY_DOWN)
		{
			gamemap.SetMovingDown(false);
			for (int i = 0; i < STATION; i++)
				station[i]->SetMovingDown(false);
			for (unsigned int i = 0; i < _playerAmount; i++) {
				players[i]->SetMovingDown(false);
			}
			for (int i = 0; i < BUILDING; i++)
				building[i]->SetMovingDown(false);
		}
		//////////////////////////////////////////////////////
		if (tossdice && !_menu.GetDone()) {
			_menu.SetDone(true);
			_playerAmount = _menu.GetPlayerAmount();
			for (int i = 0; i != 4 - _playerAmount; i++) {
				rmrole=players.back();
				players.pop_back();
				delete rmrole;
			}
		}
	}
	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		mouseclick = true;
	}
	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		mouseclick = false;
	}
	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		pos = point;
	}
	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
	}
	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
	}
	void CGameStateRun::OnShow()
	{
		help.ShowBitmap();				
		if (!_menu.GetDone()) {
			_menu.OnShow();
		}
		if (_menu.GetDone()) {
			gamemap.OnShow();
			for (int i = 0; i < STATION; i++)
				station[i]->OnShow();
			for (int i = 0; i < BUILDING; i++) {
				building[i]->OnShow();
			}
			for (unsigned int i = 0; i < _playerAmount; i++) {
				players[i]->OnShow(station);
			}
			dice.OnShow();
			_buyUI.OnShow(players, players[_whoTurn], station, station[players[_whoTurn]->GetRoleState()]);
			_othersUI.OnShow(players, players[_whoTurn], lottery);
			lottery.OnShow(players, players[_whoTurn]);
			for (vector<Role *>::iterator i = players.begin(); i != players.end(); i++) {
				if ((*i)->GetRoleNum() == roleDelet) {
					gameover.OnShow((*i), players.size());
				}
				else if (players.size() < 2) {
					gameover.OnShow(players[0], players.size());
				}
			}
		
		}
		corner.SetTopLeft(0, 0);
		corner.ShowBitmap();
		corner.SetTopLeft(SIZE_X - corner.Width(), SIZE_Y - corner.Height());
		corner.ShowBitmap();
	}
}