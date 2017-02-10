#ifndef CHIP_H
#define CHIP_H

#include<iostream>
using namespace std;

enum class ChipType{
	maru,
	batu,
	none
};

class Chip{
public:
		ChipType type;	//maru or batu
		//もしおいた時に周囲８方向の、反転できるチップの数
		unsigned char enable_revers_chips_num[8];
		Chip(){
			type = ChipType::none;
		}

		Chip(ChipType t) :
			type{t} {}
	

		void clear(){
			type = ChipType::none;
			for(int i = 0; i < 8; i++)enable_revers_chips_num[i]=0;
		}

		void print(){
			int a = 0;
			for(int i = 0; i < 8; i++){
				a |= enable_revers_chips_num[i];
			}
			switch(type){
				case ChipType::maru :
					cout<<"o";
					break;
				case ChipType::batu :
					cout<<"x";
					break;
				case ChipType::none :
					cout<<" ";
					break;
			}

		}

		bool operator == (const Chip& c)const{
			return type == c.type;
		}
		bool operator != (const Chip& c)const{
			return type != c.type;
		}
		
			
		ChipType opType()const{
			if(type == ChipType::maru)return ChipType::batu;
			if(type == ChipType::batu)return ChipType::maru;
			return ChipType::none;
		}


		void setType(ChipType s_type){
			type = s_type;
		}
};
ChipType opType(ChipType type){
	if(type == ChipType::maru)return ChipType::batu;
	if(type == ChipType::batu)return ChipType::maru;
	return ChipType::none;
}

#endif
