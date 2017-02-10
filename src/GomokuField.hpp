#ifndef FIELD_H
#define FIELD_H

#include"Chip.h"
#include<iostream>
#include<vector>
#include<algorithm>

class GomokuField : public Field{

	protected:
		int victory_condition;
	public:

		GomokuField(int field_size,int v_c,Printer* p) :Field{field_size,p},victory_condition{v_c}{}


		virtual bool checkVictory(Point selectted_point){

			const vector<Point> SurroundingPoints = {{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};
			
			bool is_victory =  any_of(SurroundingPoints.begin(), SurroundingPoints.end(), [&](auto&& p){
					return ( this->checkLinkingNumber(selectted_point,p) >= 5 );
					});

			if(is_victory)victory_user_type = ban[selectted_point.x][selectted_point.y].type;

			return is_victory;
		}

		virtual int evaluteBan(Chip checked_chip){

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
			return sum_val;
		}
