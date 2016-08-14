#ifndef OSERO_FIELD_HPP
#define OSERO_FIELD_HPP
#include"Field.h"


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
		
		void updataChipSides(Point selectted_point){
			

			const vector<Point> SurroundingPoints = {{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};
			
			for_each(SurroundingPoints.begin(), SurroundingPoints.end(), [&](auto&& orient){

				bool opponent_chip_existing = false;	//相手のチップが置いたチップの周囲にあるか

				Point scanning_point = selected_point;	
				
				int linking_number = 0;
				while( isPointInBan(scanning_point) ){
					scanning_point.first += orient.first;
					scanning_point.second += orient.second;
	
					if( !isPointInBan(scanning_point) )break;

					if(ban[scanning_point.first][scanning_point.second] != ban[selected_point.first][selected_point.second]){
						opponent_chip_existing = true;
					}

					if(opponent_chip_existing && ( ban[scanning_point.first][scanning_point.second] == ban[selected_point.first][selected_point.second] ) ){
						while(linking_number > 0){
							linking_number--;

							scanning_point.first -= orient.first;
							scanning_point.second -= orient.second;
							ban[scanning_point.first][scanning_point.second] =ban[selected_point.first][selected_point.second];
						}
					}
					linking_number++;
				}
			});

		}

	public:

		virtual bool checkVictory(Point selected_point){
			
			//maru_numとbatu_numが更新	
			updateChipNum();
			return (maru_num + batu_num) == ban.size() * ban.size() ;
		}
		
		
		virtual int evaluteBan(Point selected_point){

			const ChipType now_putted_chip = ban[selected_point.first][selected_point.second];

			if(now_putted_chip == ChipType::maru){
				return maru_num;
			}else if(now_putted_chip == ChipType::batu){
				return batu_num;
			}
		
			//ERROR
			return -1;
		}

		virtual bool canPutChip(Point selected_point)const{

			const vector<Point> SurroundingPoints = {{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};

			for(auto& orient:SurroundingPoints){

				bool opponent_chip_existing = false;	//相手のチップが置いたチップの周囲にあるか

				Point scanning_point = selected_point;	

				while( isPointInBan(scanning_point) ){
					scanning_point.first += orient.first;
					scanning_point.second += orient.second;

					if( !isPointInBan(scanning_point) )break;

					if(ban[scanning_point.first][scanning_point.second] != ban[selected_point.first][selected_point.second]){
						opponent_chip_existing = true;
					}

					if(opponent_chip_existing && ( ban[scanning_point.first][scanning_point.second] == ban[selected_point.first][selected_point.second] ) ){
						return true;
					}
				}

			}
			
			//
			virtual void setChip(Point selectted_point,ChipType c_type){
				ban.[selectted_point.first][selectted_point.second] = c_type;

				//盤の白黒の更新
	



#endif

