#ifndef OSERO_FIELD_HPP
#define OSERO_FIELD_HPP
#include"Field.hpp"
#include<cassert>

class OseroField : public Field{
	private:


	public:

		OseroField(Printer* p):Field(8,p){

			for(auto& one_line:board){
				for(auto& chip:one_line){
					chip.clear();
				}
			}

			board[3][4] = ChipType::batu;
			board[4][4] = ChipType::maru;
			board[3][3] = ChipType::maru;
			board[4][3] = ChipType::batu;

			BanStateUpdate(ChipType::maru);

		}

		virtual bool checkVictory(Point selected_point){

			//maru_numとbatu_numが更新	
			updateChipNum();
			if(maru_num > batu_num){
				victory_user_type = ChipType::maru;
			}
			if(maru_num < batu_num){
				victory_user_type = ChipType::batu;
			}
			if(maru_num == batu_num){
				victory_user_type = ChipType::none;
			}
			return (maru_num + batu_num) == static_cast<int>(board.size() * board.size()) ;
		}


		virtual int evaluteBan(Point selected_point){

			const ChipType now_putted_chip = board[selected_point.x][selected_point.y].type;

			if(now_putted_chip == ChipType::maru){
				return maru_num;
			}else if(now_putted_chip == ChipType::batu){
				return batu_num;
			}

			//ERROR
			return -1;
		}


		void ReverseChips(Point selected_point,ChipType c_type){
//			cout<<"Start Reverse"<<endl;	
			const vector<Point> surrounding_points = {{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};
			
//			cout<<"dbg num"<<endl;
			// for(int i = 0; i < 8; i++){
			// 	cout<<static_cast<int>(board[selected_point.x][selected_point.y].enable_revers_chips_num[i])<<endl;
			// }
//			cout<<"ok"<<endl;
			//おける場所におく & 石を反転
			for(int i = 0; i < 8; i++){

				Point scanning_point = selected_point;	
				int reverse_chip_num = static_cast<int>(board[selected_point.x][selected_point.y].enable_revers_chips_num[i]); 	

				// cout<<"sur "<<surrounding_points[i].x<<","<<surrounding_points[i].y<<endl;
				// cout<<"rev_chip = "<<reverse_chip_num<<endl;

				for(int j = 0; j < reverse_chip_num; j++){

					scanning_point.x += surrounding_points[i].x;
					scanning_point.y += surrounding_points[i].y;

					board[scanning_point.x][scanning_point.y] = board[selected_point.x][selected_point.y];
				}	
			}

		}

		//Banのおける　場所とかのじょうほうを全部アップデート
		void BanStateUpdate(ChipType c_type){
	
			const vector<Point> surrounding_points = {{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};
			
			can_put_chip_positions.clear();

			//おいた時の変化個数情報更新	
			for(int i = 0; i < size; i++){
				for(int j = 0; j < size; j++){
				//	cout<<"check "<<i<<","<<j<<endl;

					if(board[i][j] != ChipType::none)continue;

					for(int k = 0; k < 8; k++){
						int scanning_point_x = i;
						int scanning_point_y = j;

						// cout<<"sur "<<surrounding_points[k].x<<","<<surrounding_points[k].y<<endl;	
						// cout<<"board("<<i<<","<<j<<") serch start."<<endl;

						int linking_number = 0;
						scanning_point_x += surrounding_points[k].x;
						scanning_point_y += surrounding_points[k].y;

						// cout<<"serch "<<scanning_point_x<<","<<scanning_point_y<<endl;

						if( !isPointInBan(Point{scanning_point_x,scanning_point_y}) )continue;

						if(board[scanning_point_x][scanning_point_y].type == opType(c_type) ){

							while(1){
								linking_number++;

								scanning_point_x += surrounding_points[k].x;
								scanning_point_y += surrounding_points[k].y;

								if( !isPointInBan(Point{scanning_point_x,scanning_point_y}) || board[scanning_point_x][scanning_point_y] == ChipType::none ){
									board[i][j].enable_revers_chips_num[k] = 0;
									break;
								}

								if( board[scanning_point_x][scanning_point_y] == c_type ){

									board[i][j].enable_revers_chips_num[k] = linking_number;
									can_put_chip_positions.push_back(Point{i,j});
				//					cout<<"point "<<i<<","<<j<<" can"<<endl;
									// cout<<"sur "<<surrounding_points[k].x<<","<<surrounding_points[k].y<<endl;	
									// cout<<"board("<<i<<","<<j<<") can put."<<endl;
									break;
								}
							}
						}
					}
				}
			}

		}

		virtual bool canPutChip(Point selected_point,ChipType c_type)const{
			if(board[selected_point.x][selected_point.y] != ChipType::none)return false;
			for(int i = 0; i < 8; i++){
//				cout<<(int)(board[selected_point.x][selected_point.y].enable_revers_chips_num[i])<<endl;
				if(board[selected_point.x][selected_point.y].enable_revers_chips_num[i] > 0)return true;
			}
			return false;
		}

		//
		virtual void setChip(Point selected_point,ChipType c_type){
			board[selected_point.x][selected_point.y].setType(c_type);

			//盤の白黒の更新
			ReverseChips(selected_point,c_type);
			BanStateUpdate(opType(c_type));
		}


};
#endif

