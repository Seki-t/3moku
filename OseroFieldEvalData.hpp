#pragma once
#include"Chip.hpp"
#include<vector>

static const int zyoban_value_data[8][8] = { 30,-10, 0,-1,-1, 0,-10, 30,
	-10,-15,-3,-3,-3,-3,-15,-10,
	0, -3,-2,-2,-2,-2, -3,  0,
	-1, -3,-2,-2,-2,-2, -3, -1,
	-1, -3,-2,-2,-2,-2, -3, -1,
	0, -3,-2,-2,-2,-2, -3,  0,
	-10,-15,-3,-3,-3,-3,-15,-10,
	30,-10, 0,-1,-1, 0,-10, 30,
};

class OseroFieldEvalData{
	protected:


	public:

		OseroFieldEvalData(){}


		static int evalBan(vector<vector<Chip>>* ban,ChipType player_type){
			int sum = 0;	

			for(int i = 0; i < 8; i++){
				for(int j = 0; j < 8; j++){

					if((*ban)[i][j] == player_type){
						sum += zyoban_value_data[j][i];
					}
				}
			}
			return sum;
		}
};
