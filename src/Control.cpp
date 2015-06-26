/*
 * Control.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mrr
 */

#include "Mvc.h"
#include "Control.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Control::Control(View v) {
	view = v;
	state = 0;
	first_num = "";
	second_num = "";
}

Control::~Control() {
}

short int Control::whatis(char* i) {
	if ((i[0] >= '0') && (i[0] <= '9')) {
		return 0;
		switch (i[0]) {
		case '+':
			return 1;
			break;
		case '-':
			return 2;
			break;
		case '*':
			return 3;
			break;
		case '/':
			return 4;
			break;
		case '=':
			return 5;
			break;
		default:
			return 100;
			break;
		}
	}
}

char* Control::append(char* a, char* b) {
	return strcat(a, b);
}

int Control::eval() {
	switch (opt) {
	case '+':
		return atoi(first_num) + atoi(second_num);
		break;
	case '-':
		return atoi(first_num) - atoi(second_num);
		break;
	case '*':
		return atoi(first_num) * atoi(second_num);
		break;
	case '/':
		return atoi(first_num) / atoi(second_num);
		break;
	default:
		break;
	}
}

void Control::handle_entry(char* input) {
	short int instate = whatis(input);
	if (instate != 100) {
		if (instate == 4) {
			if (state == 0) {
				first_num = append(first_num, input);
				gint tmp_pos = view.append_to_entry(input);
			} else {
				second_num = append(second_num, input);
				gint tmp_pos = view.append_to_entry(input);
			}
		} else if (state == 0 && instate != 5) {
			state = 1;
			opt = input;
			view.append_to_entry(" ");
			view.append_to_entry(input);
		} else if (state == 1) {
			int result = eval();
////			first_num =;
//			state = 0;
//			sprintf(first_num, "%s", result);
////			view.entry_set_text(result);

		}
	}
}

