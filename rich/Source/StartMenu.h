#pragma once
namespace game_framework {

	class StartMenu {
	public:
		StartMenu();
		bool GetDone();
		void SetDone(bool flag);
		unsigned int GetPlayerAmount();
		void OnChoose(int posx,int posy, bool mouseclick);
		//void OnChoose(POINT pos);
		void OnShow();
		void LoadBitmap();
	private:
		int _playerAmount;
		CMovingBitmap _playerChoosed[2][3];
		bool _isDone;//true為已完成
		bool _choosePlayerAmount;
	};
}