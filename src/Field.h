#ifndef FIELD_H
#define FIELD_H

#include"Chip.h"
#include<vector>
#include<algorithm>
#include"Position.h"
#include"CUIPrinter.hpp"
class Field{
	protected:

		vector<Point> can_put_chip_positions;
		vector<vector<Chip>> ban;
		int size;
		ChipType victory_user_type;

		Printer* printer;

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

	public:

		Field(int field_size,Printer* p){
			ban.resize(field_size);
			for(auto &s:ban){
				s.resize(field_size);
			}

			size = field_size;
			printer = p;

			maru_num = 0;
			batu_num = 0;
		}

		virtual ~Field(){
			cout<<"de"<<endl;
			delete printer;
		}

		vector<Point>* getEnableSelects(){
			return &can_put_chip_positions;
		}

		virtual bool checkVictory(Point selected_point) = 0;
		virtual int evaluteBan(Point selected_point) = 0;

		void print(){
			(*printer)(ban);
		}

		virtual void setChip(Point selected_point, ChipType type){
			ban[selected_point.x][selected_point.y] = Chip{type};
		}

		Chip getChip(Point selected_point){
			return ban[selected_point.x][selected_point.y] ;
		}

		bool isPointInBan(Point selected_point)const{
			return (selected_point.x < size && selected_point.y < size && selected_point.x >= 0 && selected_point.y >= 0);
		}


		virtual bool canPutChip(Point selected_point,ChipType c_type)const{
			return (ban[selected_point.x][selected_point.y] == Chip{ChipType::none} ) && isPointInBan(selected_point);
		}


		int checkLinkingNumber(Point selected_point,Point check_direction){

			int link_count = 0;
			const Chip selecting_chip = ban[selected_point.x][selected_point.y];

			Point checking_point = selected_point;
			while(1){
				link_count++;

				checking_point += check_direction;
				if( !isPointInBan(checking_point) ) break;
				if(selecting_chip != ban[checking_point.x][checking_point.y] )break;
			}

			return link_count;
		}


		string victoryUser(){
			//to do:make game manager class
			//set player
			//and show player name.

			switch(victory_user_type){
				case ChipType::maru : 
					return "Player1 ";
					break;
				case ChipType::batu :
					return "Player2 ";
					break;
				default :
					return "Drow ";
					break;
			}
			return "Error";
		}

		Point getResult(){
			return Point{maru_num,batu_num};
		}


		vector<vector<Chip>>* getBan(){
			return &ban;
		}
};


#endif
