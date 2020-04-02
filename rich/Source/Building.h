#pragma once
namespace game_framework
{
	class Building
	{
	public:
		Building(string);
		Building();
		int GetX();
		int GetY();
		void SetXY(int nx, int ny);     //設定房子的位置
		virtual void LoadBitmap();
		virtual void OnShow();
		void OnMove();
		void OnMove(int camerax, int cameray);
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		virtual string GetType();       // 得取該建築物的類型
	protected:
		string _type;					// 該建築物的類型
		int _x, _y;
		bool _isEmpty;
		int _referenceX, _referenceY;   // 座標參考點
		bool isMovingDown;				// 是否正在往下移動
		bool isMovingLeft;				// 是否正在往左移動
		bool isMovingRight;				// 是否正在往右移動
		bool isMovingUp;				// 是否正在往上移動
		CMovingBitmap building;
	};
}
