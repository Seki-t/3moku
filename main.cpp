#include<iostream>
#include"Position.h"
#include"OseroField.hpp"
#include"RandomAIPlayer.h"
#include"HumanPlayer.h"
#include"Chip.h"
#include"CUIPrinter.hpp"
#include"SimpleAIPlayer.hpp"
//#define Point Position<int>


int main(){
	int v1_num = 0,v2_num = 0;
	
	for(int i = 0; i < 1;i++){
		cout<<"battle "<<i<<endl;
		OseroField f(new CUIPrinter("OSERO"));
		Player* player1 = new RandomAIPlayer(ChipType::maru);
		Player* player2 = new SimpleAIPlayer(ChipType::batu);

		f.print();

		while(1){
			Point selectted_point;

			selectted_point = player1->selectMove(f);
			//このselectted_pointはおける位置である事がselectMove内で確認済み

			if(selectted_point != Point{-1,-1} ){
				f.setChip(selectted_point,player1->getPlayerType() );
			}else{
				cout<<"Pass"<<endl;
				f.BanStateUpdate(opType(player1->getPlayerType()));
			}

			if(f.checkVictory(selectted_point))break;
					f.print();

			selectted_point = player2->selectMove(f);
			//このselectted_pointはおける位置である事がselectMove内で確認済み

			if(selectted_point != Point{-1,-1}){
				f.setChip(selectted_point,player2->getPlayerType() );
			}else{
				cout<<"Pass"<<endl;
				f.BanStateUpdate(opType(player2->getPlayerType()));
			}

			if(f.checkVictory(selectted_point))break;
					f.print();
		}
		f.print();
		cout<<"Game Set!"<<endl;
		Point result = f.getResult();
		cout<<"Player1 vs Player2"<<endl;
		cout<<result.x<<" : "<<result.y<<endl;
		if(result.x > result.y )v1_num++;
		if(result.x < result.y)v2_num++;
		cout<<f.victoryUser()<<" Win!"<<endl;
		delete player1;
		delete player2;
	}

	cout<<v1_num<<" : "<<v2_num<<" : "<<(1000 - v1_num - v2_num)<<endl;
	return 0;
}
