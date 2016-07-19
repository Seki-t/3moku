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

		Chip(){
			type = ChipType::none;
		}

		Chip(ChipType t) :
			type{t} {}

		void print(){
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
};

#endif
