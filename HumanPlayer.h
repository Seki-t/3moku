#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include"Player.h"
#include"Position.h"
#include"Field.h"
#include"Chip.h"
#include<string>
#include<iostream>
#include<sstream>

class HumanPlayer : public Player{

	protected:

		Point getKeyInput(){
			cout<<"Input>>";
			string str;
			getline(cin,str);
			if(str == "exit"){
				cout<<"exit"<<endl;
				return Point{-1,-1};
			}
			else{
				stringstream ss;
				ss.write(str.c_str(),str.length());
				int row,col;
				ss>>row>>col;
				row-=1;
				col-=1;
				return Point{row,col};
			}
			return Point{-1,-1};
		}

	public:

		HumanPlayer(ChipType t) :
			Player{t} {}

		virtual Point selectMove(Field& ban){

			Point selectted_point;

			while(1){
				selectted_point = getKeyInput();
				cout<<"select"<<endl;
				if( ban.canPutChip(selectted_point) )break;

				cout<<"You Can't put chip on that point! Once again!"<<endl;

			}
			return selectted_point;
		} 

};

#endif
