#ifndef FIELD_H
#define FIELD_H

#include"Chip.h"
#include<vector>
#include<algorithm>
#include"Printer.hpp"
class Field{
	protected:

		vector<vector<Chip>> ban;
		int size;
		ChipType victory_user_type;
		
		Printer* printer;
	public:
		
		Field(int field_size,Printer* p){
			ban.resize(field_size);
			for(auto &s:ban){
				s.resize(field_size);
			}
			size = field_size;
			printer = p;
		}

		virtual ~Field(){
			delete printer;
		}

		virtual bool checkVictory(Point selectted_point) = 0;
		virtual int evaluteBan(Point selectted_point) = 0;

		void print(){
			(*printer)(ban);
		}

		void setChip(Point selectted_point, ChipType type){
			ban[selectted_point.x][selectted_point.y] = Chip{type};
		}

		Chip getChip(Point selectted_point){
			return ban[selectted_point.x][selectted_point.y] ;
		}

		bool isPointInBan(Point selectted_point)const{
			return (selectted_point.x < size && selectted_point.y < size && selectted_point.x >= 0 && selectted_point.y >= 0);
		}


		bool canPutChip(Point selectted_point)const{
			return (ban[selectted_point.x][selectted_point.y] == Chip{ChipType::none} ) && isPointInBan(selectted_point);
		}


		int checkLinkingNumber(Point selectted_point,Point check_direction){

			int link_count = 0;
			const Chip selecting_chip = ban[selectted_point.x][selectted_point.y];
			
			Point checking_point = selectted_point;
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

};


#endif
