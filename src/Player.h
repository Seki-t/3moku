#ifndef PLAYER_H
#define PLAYER_H

#include"Chip.h"
#include"Position.h"

class Player{

	protected:
		ChipType player_type;

	public:
		virtual ~Player(){}
		Player(ChipType t) :
			player_type{t} {}

		virtual Point selectMove(Field& ban)=0;

		ChipType getPlayerType(){
			return player_type;
		}

};

#endif
