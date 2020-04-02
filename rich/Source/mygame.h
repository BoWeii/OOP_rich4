// mygame.h: ���ɮ��x�C��������class��interface
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
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnKeyDown(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
	protected:
		void OnMove();
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
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
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		vector <Role*> players;
	protected:
		void JudgeBankrupt();
		void GoRoleScene();
		void DoLottery();
		void DoAction();
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		const int		STATION, BUILDING, HOUSE,STORE, LOTTERY_OPEN_ROUND;	// ���I���`��
		unsigned int _whoTurn , _playerAmount;
		CMovingBitmap	help;		// ������
		CMovingBitmap	corner;		// ������
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
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
	};
}