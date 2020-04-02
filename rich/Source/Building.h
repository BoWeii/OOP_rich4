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
		void SetXY(int nx, int ny);     //�]�w�Фl����m
		virtual void LoadBitmap();
		virtual void OnShow();
		void OnMove();
		void OnMove(int camerax, int cameray);
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		virtual string GetType();       // �o���ӫؿv��������
	protected:
		string _type;					// �ӫؿv��������
		int _x, _y;
		bool _isEmpty;
		int _referenceX, _referenceY;   // �y�аѦ��I
		bool isMovingDown;				// �O�_���b���U����
		bool isMovingLeft;				// �O�_���b��������
		bool isMovingRight;				// �O�_���b���k����
		bool isMovingUp;				// �O�_���b���W����
		CMovingBitmap building;
	};
}
