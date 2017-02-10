#ifndef MINMAX_AI_PLAYER_H
#define MINMAX_AI_PLAYER_H

#include"Player.h"
#include"Chip.h"
#include"Position.h"
#include"Field.h"
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
