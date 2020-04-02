#include "stdafx.h"
#include"Round.h"
namespace game_framework
{
	Round::Round()
	{
		_round = 0;
	}
	void Round::AddRound(int whoturn, int playamount)
	{
		if (whoturn == playamount - 1)
			_round++;
	}
	int Round::GetRound()
	{
		return  _round;
	}
	void Round::SetRound(int i) {
		_round = i;
	}
}