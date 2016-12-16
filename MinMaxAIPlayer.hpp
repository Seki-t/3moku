#ifndef MINMAX_AI_PLAYER_H
#define MINMAX_AI_PLAYER_H

#include"Player.hpp"
#include"Chip.hpp"
#include"Position.hpp"
#include"Field.hpp"
#include<iostream>

using namespace std;

class MinMaxAIPlayer : public Player{

	protected:
	
	public:

		MinMaxAIPlayer(ChipType t) :
			Player{t},
		{
		}


		virtual Point selectMove(Field& ban){
			Point selectted_point;
			while(1){
				
				
				if( ban.canPutChip(selectted_point) )break;
			}
			return selectted_point;
		} 

};
#endif
