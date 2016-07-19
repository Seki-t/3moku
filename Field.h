#ifndef FIELD_H
#define FIELD_H

#include"Chip.h"
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Field{
	private:
		vector<vector<Chip>> ban;
		int size;
		int victory_condition;

		ChipType victory_user_type;
	public:

		Field(int field_size,int v_c){
			ban.resize(field_size);
			for(auto &s:ban){
				s.resize(field_size);
			}
			size = field_size;
			victory_condition = v_c;
		}	

		void print(){
			//Osero Shougi narabe Ban
			// for_each(ban.begin(),ban.end(),[&](vector<Chip>& line){
			// 		for(int i=0;i<size;i++)cout<<" ---";
			// 		cout<<endl;
			// 		for_each(line.begin(),line.end(),[&](Chip& c){
			// 				cout<<"| ";
			// 				c.print();
			// 				cout<<" ";
			// 				});
			// 		cout<<"|"<<endl;
			// 		});
			// for(int i=0;i<size;i++)cout<<" ---";
			// cout<<endl;

			//Igo Gomoku Ban
			for(int j=0;j<size;j++){

				for(int i=0;i<size;i++){

					ban[j][i].print();
					if(i < size-1)cout<<"---";

				}
				if(j < size-1){
					cout<<" "<<endl;

					for(int i=0;i<size ;i++)cout<<"|   ";

					cout<<endl;
				}
			}
			cout<<endl;
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

		bool checkVictory(Point selectted_point){

			const vector<Point> SurroundingPoints = {{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};
			bool is_victory =  any_of(SurroundingPoints.begin(), SurroundingPoints.end(), [&](auto&& p){
					return ( this->checkLinkingNumber(selectted_point,p) >= 5 );
					});

			if(is_victory)victory_user_type = ban[selectted_point.x][selectted_point.y].type;

			return is_victory;
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

int Field::evaluteBan(Chip checked_chip){

	for(int i=0;i<ban.size();i++){
		for(int j = 0;j<ban[i].size();j++){

			if(ban[i][j] == checked_chip){
				Point checking_point = Point{i,j};

				const vector<Point> SurroundingPoints = {{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};

				int sum_val = 0;

				for_each(SurroundingPoints.begin(), SurroundingPoints.end(), [&sum_val](auto&& p){
						sum_val +=  this->checkLinkingNumber(checking_point,p);
						});
			}
		}
	}
}

#endif
