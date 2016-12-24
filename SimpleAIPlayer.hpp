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
		
		//このboard_bufは探索深さが必要数となるSimpleは探索深さ1なので1つで良い
		vector<vector<Chip>> board_buf;



	public:

		SimpleAIPlayer(ChipType t) :
			Player{t},
			rand1{0,1000}
		{
			random_device rnd;
			mt.seed(rnd());
		}


		virtual Point selectMove(Field& field){
				
				//盤面計算の流れ
				//現在のボードのアドレスを入手
				//現在のボードに一個新しく石を置いた時の盤面を、board_bufに作成する
				//board_bufをEvalする
			
			Point selected_point;

			while(1){
				
				//置くことが可能な座標列を取得
				vector<Point>* can_put_chip_positions = field.getEnableSelects();
				int enable_select_num = can_put_chip_positions->size();
				
				//現在のboardのポインタを取得
				vector<vector<Chip>> *now_board_state = field.getBan();

				//おける数ゼロなら関数を抜けて、手渡しする
				if(enable_select_num == 0)return Point{-1,-1};	
				
				
				int max_banmen_value = 1000;
				int max_banmen_index = 0;
				
				//最大評価値の位置を探索するループ
				for(int i = 0; i < enable_select_num; i++){
						
					board_buf = *now_board_state;

					int banmen_value = OseroFieldEvalData::evalBan(field.getBan(), player_type );
					
					if(max_banmen_value < banmen_value){
						max_banmen_value = banmen_value;
						max_banmen_index = i;
					}
				}

				//評価値最大のものを選ぶ	
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
