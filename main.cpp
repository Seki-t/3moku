#include<iostream>
#include"Position.h"
#include"Field.h"
#include"RandomAIPlayer.h"
#include"HumanPlayer.h"
#include"Chip.h"

using namespace std;

#define Point Position<int>


int main(){
	Field f{9,5};
	Player* player1 = new RandomAIPlayer(ChipType::maru);
	Player* player2 = new RandomAIPlayer(ChipType::batu);

	f.print();
	
	while(1){
		Point selectted_point;

		selectted_point = player1->selectMove(f);

	//	cout<<"k0"<<endl;
		f.setChip(selectted_point,player1->getPlayerType() );
	//	cout<<"k1"<<endl;

		if(f.checkVictory(selectted_point))break;
	//	cout<<"k2"<<endl;
		f.print();

		selectted_point = player2->selectMove(f);

		f.setChip(selectted_point,player2->getPlayerType() );

		if(f.checkVictory(selectted_point))break;
		f.print();
	}
	f.print();
	cout<<"Game Set!"<<endl;
	cout<<f.victoryUser()<<" Win!"<<endl;
	delete player1;
	delete player2;
	return 0;
}
