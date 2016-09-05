#include<iostream>
#include<random>


int main(){
	std::random_device rnd;
	std::mt19937 mt{rnd()};
	std::uniform_int_distribution<> rand1{0,9};
	int i=0;
	while(1){
		i++;
		if(i>1000)break;
		std::cout<<rand1(mt)<<std::endl;
	}
	return 0;
}

