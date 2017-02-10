#ifndef CUI_PRINTER_HPP
#define CUI_PRINTER_HPP
#include<iostream>
#include"Printer.hpp"
#include<algorithm>

class CUIPrinter : public Printer{
	protected:

		string game_type;
	public:
		
		CUIPrinter(string _game_type):game_type{_game_type}{}

		virtual void operator ()(vector<vector<Chip>>& ban){

			if(game_type == "OSERO"){

				for_each(ban.begin(),ban.end(),[&](vector<Chip>& line){
						for(size_t i = 0; i < line.size(); i++)cout<<" ---";
						cout<<endl;
						for_each(line.begin(),line.end(),[&](Chip& c){
								cout<<"| ";
								c.print();
								cout<<" ";
								});
						cout<<"|"<<endl;
						});

				for(size_t i=0;i<ban.size();i++)cout<<" ---";
				cout<<endl;
			}
			else if(game_type == "GOMOKU")
			{

				for(size_t j=0;j<ban.size();j++){

					for(size_t i=0;i<ban.size();i++){

						ban[j][i].print();
						if(i < ban.size()-1)cout<<"---";

					}
					if(j < ban.size()-1){
						cout<<" "<<endl;

						for(size_t i=0;i<ban.size() ;i++)cout<<"|   ";

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
