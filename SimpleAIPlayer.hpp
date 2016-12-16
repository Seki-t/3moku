#ifndef SIMPLE_AI_PLAYER_H
#define SIMPLE_AI_PLAYER_H

#include"Player.hpp"
#include"Chip.hpp"
#include"Position.hpp"
#include"Field.hpp"
#include<iostream>
#include<random>
#include"OseroFieldEvalData.hpp"
//おける位置の中で、一番良い盤位置を選んで石を打つ
class SimpleAIPlayer : public Player{

	protected:

		std::mt19937 mt;
		std::uniform_int_distribution<> rand1;
	public:

		SimpleAIPlayer(ChipType t) :
			Player{t},
			rand1{0,1000}
		{
			random_device rnd;
			mt.seed(rnd());
		}


		virtual Point selectMove(Field& field){
			
			Point selected_point;
			int selecting;

			while(1){
				
				//置くことが可能な座標列を取得
				vector<Point>* can_put_chip_positions = field.getEnableSelects();
				
				int enable_select_num = can_put_chip_positions->size();
				
				//おける数ゼロなら関数を抜けて、手渡しする
				if(enable_select_num == 0)return Point{-1,-1};	
				
				int max_banmen_value = 1000;
				int max_banmen_index = 0;
				
				//最小評価値の位置を選択
				for(int i = 0; i < enable_select_num; i++){
					
					int banmen_value = OseroFieldEvalData::evalBan(field.getBan(), player_type );
					
					if(max_banmen_value > banmen_value){
						max_banmen_value = banmen_value;
						max_banmen_index = i;
					}
				}
			
				selected_point = (*can_put_chip_positions)[max_banmen_index];

				cout<<"select player ";
				if(player_type == ChipType::maru)cout<<"maru ";
				else cout<<"batu ";

				cout<<selected_point.x<<" "<<selected_point.y<<endl;	
				if( field.canPutChip(selected_point,player_type) )break;
				cout<<"cannot put chip"<<endl;	
			}

			return selected_point;
		} 

};

#endif
