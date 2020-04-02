#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Integer.h"

namespace game_framework
{
	Integer::Integer(int digits)
		: NUMDIGITS(digits)
	{
		isBmpLoaded = false;
	}

	void Integer::Add(int x)
	{
		n += x;
	}

	int Integer::GetInteger()
	{
		return n;
	}

	void Integer::LoadBitmap()
	{
		int d[11] = { IDB_000,IDB_001,IDB_002,IDB_003,IDB_004,IDB_005,IDB_006,IDB_007,IDB_008,IDB_009,IDB_MINUS };
		for (int i = 0; i < 11; i++)
			digit[i].LoadBitmap(d[i]);
	}

	void Integer::SetInteger(int i)
	{
		n = i;
	}

	void Integer::SetTopLeft(int nx, int ny)		// �N�ʵe�����W���y�в��� (x,y)
	{
		x = nx; y = ny;
	}

	void Integer::ShowBitmap()
	{
		int nx;		// ����ܦ�ƪ� x �y��
		int MSB;	// �̥���(�t�Ÿ�)����ƪ��ƭ�
		if (n >= 0) {
			MSB = n;
			nx = x + digit[0].Width()*(NUMDIGITS - 1);
		}/*
		else {
			MSB = -n;
			nx = x + digit[0].Width()*NUMDIGITS;
		}*/
		for (int i = 0; i < NUMDIGITS; i++) {
			int d = MSB % 10;
			MSB /= 10;
			digit[d].SetTopLeft(nx, y);
			digit[d].ShowBitmap();
			nx -= digit[d].Width();
		}/*
		if (n < 0) { // �p�G�p��0�A�h��ܭt��
			digit[10].SetTopLeft(nx, y);
			digit[10].ShowBitmap();
		}*/
	}
}
