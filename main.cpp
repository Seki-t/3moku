#include<iostream>
#include"Position.h"
#include"OseroField.hpp"
#include"RandomAIPlayer.h"
#include"HumanPlayer.h"
#include"Chip.h"
#include"CUIPrinter.hpp"

//#define Point Position<int>


int main(){
	OseroField f(new CUIPrinter("OSERO"));
	Player* player1 = new HumanPlayer(ChipType::maru);
	Player* player2 = new HumanPlayer(ChipType::batu);

	f.print();

	while(1){
		Point selectted_point;

		selectted_point = player1->selectMove(f);
		//このselectted_pointはおける位置である事がselectMove内で確認済み

		f.setChip(selectted_point,player1->getPlayerType() );

		if(f.checkVictory(selectted_point))break;
		f.print();

		selectted_point = player2->selectMove(f);
		//このselectted_pointはおける位置である事がselectMove内で確認済み

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
