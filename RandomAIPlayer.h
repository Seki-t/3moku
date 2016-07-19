#ifndef RANDOM_AI_PLAYER_H
#define RANDOM_AI_PLAYER_H

#include"Player.h"
#include"Chip.h"
#include"Position.h"
#include"Field.h"
#include<iostream>
#include<random>

using namespace std;

class RandomAIPlayer : public Player{

	protected:
	
	std::mt19937 mt;
	std::uniform_int_distribution<> rand1;
	public:

		RandomAIPlayer(ChipType t) :
			Player{t},
			rand1{0,8}
		{
	random_device rnd;
			mt.seed(rnd());
		}


		virtual Point selectMove(Field& ban){
			Point selectted_point;
			while(1){
				selectted_point = Point{rand1(mt),rand1(mt)};
				if( ban.canPutChip(selectted_point) )break;
			}
			return selectted_point;
		} 

};

#endif
