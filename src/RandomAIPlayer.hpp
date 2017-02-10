#ifndef RANDOM_AI_PLAYER_H
#define RANDOM_AI_PLAYER_H

#include"Player.hpp"
#include"Chip.hpp"
#include"Position.hpp"
#include"Field.hpp"
#include<iostream>
#include<random>
class RandomAIPlayer : public Player{

	protected:

		std::mt19937 mt;
		std::uniform_int_distribution<> rand1;
	public:

		RandomAIPlayer(ChipType t) :
			Player{t},
			rand1{0,1000}
		{
			random_device rnd;
			mt.seed(rnd());
		}


		virtual Point selectMove(Field& ban){
			Point selected_point;
			int selecting;

			while(1){

				vector<Point>* can_put_chip_positions = ban.getEnableSelects();

				int enable_select_num = can_put_chip_positions->size();

				if(enable_select_num == 0)return Point{-1,-1};	

				selecting = rand1(mt) % enable_select_num;

				selected_point = (*can_put_chip_positions)[selecting];
				cout<<"select player ";
				if(player_type == ChipType::maru)cout<<"maru ";
				else cout<<"batu ";

				cout<<selected_point.x<<" "<<selected_point.y<<endl;	
				if( ban.canPutChip(selected_point,player_type) )break;
				cout<<"cannot put chip"<<endl;	
			}

			return selected_point;
		} 

};

#endif
