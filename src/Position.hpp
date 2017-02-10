#ifndef POSITION_H
#define POSITION_H
#include<math.h>

template<typename T>
struct Position{
	T x, y;
	
	Position(T _x, T _y) :x{ _x }, y{ _y }{}
	Position(){}

	Position operator +(const Position& pos){
		return Position(x + pos.x, y + pos.y);
	}

	Position operator -(const Position& pos){
		return Position(x - pos.x, y - pos.y);
	}


	Position& operator += (const Position& pos){
		this->x += pos.x;
		this->y += pos.y;
		return *this;
	}

	Position& operator -= (const Position& pos){
		this->x -= pos.x;
		this->y -= pos.y;
		return *this;
	}

	Position& operator =(const Position& pos){
		x = pos.x;
		y = pos.y;
		return *this;
	}

	bool operator !=(const Position& pos){
		return ((x != pos.x) || (y != pos.y) );
	}
	T Get_Norm(){
		return sqrt(x*x + y*y);
	}

};

#define Point Position<int>


#endif
