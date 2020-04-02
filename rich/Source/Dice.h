#pragma once
namespace game_framework
{
	class Dice {
	public:
		Dice();
		int GetDiceNumber();
		void setXY(int x, int y);
		void TossDice(int diceNum);
		void SetDiceNumber(int diceNum);
		void SetDiceIsToss(bool flag);
		bool IsToss();
		void OnShow();
		void LoadBitmap();

	private:
		CMovingBitmap _one, _two, _three, _four, _five, _six, _zero;
		bool _isToss; //預設為true(可丟)  丟之後會成false 直到腳色到點變回true
		int _diceNumber, _x, _y;
	};
}