// mygame.h: 本檔案儲遊戲本身的class的interface
#include "GameMap.h"
#include "Station.h"
#include "Role.h"
#include "Dice.h"
#include "StartMenu.h"
#include "Building.h"
#include "House.h"
#include "Store.h"
#include "Station.h"
#include "OthersUI.h"
#include "BuyUI.h"
#include "Card.h"
#include"Round.h"
#include "GameOver.h"
namespace game_framework {
	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnKeyDown(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
	protected:
		void OnMove();
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap _start, _explainLogo, _explain,_about,_aboutLogo;
		bool _isShowExplain;
		POINT pos;
	};
	//////////////////////////////////////////////////////
	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		vector <Role*> players;
	protected:
		void JudgeBankrupt();
		void GoRoleScene();
		void DoLottery();
		void DoAction();
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		const int		STATION, BUILDING, HOUSE,STORE, LOTTERY_OPEN_ROUND;	// 站點的總數
		unsigned int _whoTurn , _playerAmount;
		CMovingBitmap	help;		// 說明圖
		CMovingBitmap	corner;		// 角落圖
		StartMenu _menu;
		GameMap gamemap;
		Station *station[81];
		Building *building[49];
		House *house[41];
		Store *store[8];
		//////////////////////////
		Lottery lottery;
		OthersUI _othersUI;
		BuyUI _buyUI;
		Dice dice;
		int screenposx, screenposy, roleDelet;
		POINT pos;
		Round _round;
		bool mouseclick,_isShowGameOver, _isbankrupt,_buyUIOnce,_isDelete;
		int picX, picY ,x=0,y=0;
		GameOver gameover;
	};
	//////////////////////////////////////////////////////
	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
	};
}