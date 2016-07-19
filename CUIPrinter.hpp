#ifndef CUI_PRINTER_HPP
#define CUI_PRINTER_HPP
#include<iostream>
#include"Printer.h"
#include<algorithm>

class CUIPrinter : public Printer{
	protected:

		string game_type;
	public:
		
		CUIPrinter(string _game_type):game_type{_game_type}{}

		virtual void operator ()(vector<vector<Chip>>& ban){

			if(game_type == "OSERO"){

				for_each(ban.begin(),ban.end(),[&](vector<Chip>& line){
						for(int i=0;i<size;i++)cout<<" ---";
						cout<<endl;
						for_each(line.begin(),line.end(),[&](Chip& c){
								cout<<"| ";
								c.print();
								cout<<" ";
								});
						cout<<"|"<<endl;
						});
				for(int i=0;i<size;i++)cout<<" ---";
				cout<<endl;
			}
			else if(game_type == "GOMOKU"){

				for(int j=0;j<size;j++){

					for(int i=0;i<size;i++){

						ban[j][i].print();
						if(i < size-1)cout<<"---";

					}
					if(j < size-1){
						cout<<" "<<endl;

						for(int i=0;i<size ;i++)cout<<"|   ";

						cout<<endl;
					}
				}
				cout<<endl;
			}
			else{
				cout<<"NOT KNOWN GAME"<<endl;
			}
		}

};

#endif
