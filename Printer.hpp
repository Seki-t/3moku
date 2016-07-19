#ifndef PRINTER_HPP
#define PRINTER_HPP
#include<vector>
#include"Chip.h"


class Printer{
	public:
		virtual void operator ()(vector<vector<Chip>>& ban) = 0;

}

#endif
