/*
 * Control.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mrr
 */

#ifndef CONTROL_H_
#define CONTROL_H_
#include "Mvc.h"


class Control {
public:
	Control(View v);
	virtual ~Control();
	void handle_entry(char* input);
	void reset();
	void save();
	void show_save();
	void memory_dump();

private:
	View view;
	short int whatis(char* i);
	char* append(char* a,char* b);
	int eval();
	short int state;
	char* opt;
	char* first_num;
	char* second_num;
};



#endif /* CONTROL_H_ */
