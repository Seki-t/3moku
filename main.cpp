#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<sstream>
#include<cassert>
using namespace std;

enum class ChipType{
	maru,
	batu,
	none
};

class Chip{

private:

	 ChipType type;	//maru or batu

public:
	
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

	bool operator == (const Chip& c){
		return type == c.type;
	}


};



class Field{
private:
	vector<vector<Chip>> ban;
	int size;
public:

	Field(int field_size){
		ban.resize(field_size);
		for(auto &s:ban){
			s.resize(field_size);
		}
		size = field_size;
	}	

	void print(){
		for_each(ban.begin(),ban.end(),[&](vector<Chip>& line){
			for(int i=0;i<size;i++)cout<<" -";
			cout<<endl;
			for_each(line.begin(),line.end(),[&](Chip& c){
				cout<<"|";
				c.print();
			});
			cout<<"|"<<endl;
		});
		for(int i=0;i<size;i++)cout<<" -";
		cout<<endl;
	}

	void setChip(pair<int,int> selectted_point, ChipType type){
		ban[selectted_point.first][selectted_point.second] = Chip{type};
	}

	Chip getChip(pair<int,int> selectted_point){
		return ban[selectted_point.first][selectted_point.second] ;
	}

	bool CanPutChip(pair<int,int> selectted_point){
		if(selectted_point.first >= size || selectted_point.second >= size)return false;
		return (ban[selectted_point.first][selectted_point.second] == Chip{ChipType::none} );
	}
};




class Player{

protected:
	ChipType player_type;

public:
	virtual ~Player(){}
	Player(ChipType t) :
		player_type{t} {}

	virtual pair<int,int> selectMove(Field& ban)=0;
	
	ChipType getPlayerType(){
		return player_type;
	}
	
};


class HumanPlayer : public Player{

protected:

	pair<int,int> getKeyInput(){
		cout<<"Input>>";
		string str;
		getline(cin,str);
		if(str == "exit"){
			cout<<"exit"<<endl;
			return pair<int,int>{-1,-1};
		}
		else{
			stringstream ss;
			ss.write(str.c_str(),str.length());
			int row,col;
			ss>>row>>col;
			row-=1;
			col-=1;
			return pair<int,int>{row,col};
		}
		return pair<int,int>{-1,-1};
	}

public:
	
	HumanPlayer(ChipType t) :
		Player{t} {}

	
	virtual pair<int,int> selectMove(Field& ban){
		
		pair<int,int> selectted_point;
	
		while(1){
			selectted_point = getKeyInput();
			if( ban.CanPutChip(selectted_point) )break;
			
			cout<<"You Can't put chip on that point! Once again!"<<endl;

		}
		return selectted_point;
	} 

};

int main(){
 	Field f{5};
	Player* player1 = new HumanPlayer(ChipType::maru);
	Player* player2 = new HumanPlayer(ChipType::batu);
	
	bool available = true;
		f.print();
	while(available){
 		pair<int,int> selectted_point;
		
		selectted_point = player1->selectMove(f);
		if(selectted_point == pair<int,int>{-1,-1})available = false;

		f.setChip(selectted_point,player1->getPlayerType() );
		
		f.print();
		
		selectted_point = player2->selectMove(f);
		if(selectted_point == pair<int,int>{-1,-1})available = false;
		
		f.setChip(selectted_point,player2->getPlayerType() );

		f.print();
	}
	return 0;
}
