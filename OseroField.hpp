#ifndef OSERO_FIELD_HPP
#define OSERO_FIELD_HPP
#include"Field.h"
#include<cassert>

class OseroField : public Field{
	private:

		int batu_num,maru_num;

		void updateChipNum(){

			maru_num = 0;
			batu_num = 0;

			for(auto& line:ban){
				for(auto& s:line){

					if(s == ChipType::maru){
						maru_num++;
					}else if(s == ChipType::batu){
						batu_num++;
					}
				}
			}
		}

		void updateChipSides(Point selected_point){
			cout<<"updateChipSides"<<endl;	

			const vector<Point> surrounding_points = {{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};

			for_each(surrounding_points.begin(), surrounding_points.end(), [&](Point orient){


					Point scanning_point = selected_point;	

					int linking_number = 0;
					
					scanning_point.x += orient.x;
					scanning_point.y += orient.y;
					cout<<"scanning_point = "<<scanning_point.x<<","<<scanning_point.y<<endl;	
					
					if( isPointInBan(scanning_point) ){

					if(ban[scanning_point.x][scanning_point.y] != ban[selected_point.x][selected_point.y]){
						cout<<"op_true"<<endl;

						while(1){
							scanning_point.x += orient.x;
							scanning_point.y += orient.y;
							if( !isPointInBan(scanning_point) )break;
							cout<<"scanning_point = "<<scanning_point.x<<","<<scanning_point.y<<endl;	

							if( ban[scanning_point.x][scanning_point.y] == ban[selected_point.x][selected_point.y] ){
								while(linking_number > 0){
									linking_number--;

									scanning_point.x -= orient.x;
									scanning_point.y -= orient.y;
									ban[scanning_point.x][scanning_point.y] =ban[selected_point.x][selected_point.y];
								}
								break;
							}
							linking_number++;
						}
					}
					}

			});

		}

	public:

		OseroField(Printer* p):Field(8,p){

			ban[3][4] = ChipType::batu;
			ban[4][4] = ChipType::maru;
			ban[3][3] = ChipType::maru;
			ban[4][3] = ChipType::batu;


		}

		virtual bool checkVictory(Point selected_point){

			//maru_numとbatu_numが更新	
			updateChipNum();
			return (maru_num + batu_num) == ban.size() * ban.size() ;
		}


		virtual int evaluteBan(Point selected_point){

			const ChipType now_putted_chip = ban[selected_point.x][selected_point.y].type;

			if(now_putted_chip == ChipType::maru){
				return maru_num;
			}else if(now_putted_chip == ChipType::batu){
				return batu_num;
			}

			//ERROR
			return -1;
		}

		virtual bool canPutChip(Point selected_point)const{
			cout<<"canPutChip"<<endl;
			const vector<Point> SurroundingPoints = {{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};

			for(auto& orient:SurroundingPoints){

				bool opponent_chip_existing = false;	//相手のチップが置いたチップの周囲にあるか

				Point scanning_point = selected_point;	

				while(1){
					scanning_point.x += orient.x;
					scanning_point.y += orient.y;
					cout<<"scanning_point = "<<scanning_point.x<<","<<scanning_point.y<<endl;	
					if( !isPointInBan(scanning_point) )break;

					if(ban[scanning_point.x][scanning_point.y] != ban[selected_point.x][selected_point.y]){
						opponent_chip_existing = true;
					}

					if(opponent_chip_existing && ( ban[scanning_point.x][scanning_point.y] == ban[selected_point.x][selected_point.y] ) ){
						return true;
					}
				}

			}
			return false;
		}

		//
		virtual void setChip(Point selected_point,ChipType c_type){
			ban[selected_point.x][selected_point.y] = c_type;

			//盤の白黒の更新
			updateChipSides(selected_point);
		}


};
#endif

