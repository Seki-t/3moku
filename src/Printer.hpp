#ifndef PRINTER_HPP
#define PRINTER_HPP
#include<vector>
#include"Chip.hpp"


class Printer{
	public:
		virtual void operator ()(vector<vector<Chip>>& ban) = 0;
		virtual ~Printer(){}

};

#endif
