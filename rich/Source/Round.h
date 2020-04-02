#pragma once
namespace game_framework
{
	class Round
	{
	public:
		Round();
		void AddRound(int, int);
		void SetRound(int i);
		int GetRound();
	protected:
		int _round = 0;
	};
}