/*
 * Control.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mrr
 */

#include "Mvc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

using namespace std;

Control::Control() {
	state = 0;
	first_num = "";
	second_num = "";
}
void Control::setview(View* view) {
	this->view = view;
}

Control::~Control() {
}

short int Control::whatis(char* i) {
	if ((i[0] >= '0') && (i[0] <= '9')) {
		return 0;
	}
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

char* Control::append(char* a, char* b) {
	size_t len = strlen(a);
	char* ret = new char[len + 2];
	strcpy(ret, a);
	ret[len] = b[0];
	ret[len + 1] = '\0';
	return ret;
}

int Control::eval() {
	view->add_to_history_command(first_num);
	char temp[3] = { ' ', opt, ' ' };
	view->add_to_history_command(temp);
	view->add_to_history_command(second_num);
	view->add_to_history_command(" \n");

	printf("eval %d \n", opt);
	switch (opt) {
	case '+':
//		printf("%s + %s \n", first_num, second_num);
		return atoi(first_num) + atoi(second_num);
		break;
	case '-':
//		printf("%s - %s \n", first_num, second_num);
		return atoi(first_num) - atoi(second_num);
		break;
	case '*':
//		printf("%s * %s \n", first_num, second_num);
		return atoi(first_num) * atoi(second_num);
		break;
	case '/':
//		printf("%s / %s \n", first_num, second_num);
		return atoi(first_num) / atoi(second_num);
		break;
	default:
		break;
	}
}
void Control::backspace() {
	if (state == 0) {
		first_num[strlen(first_num) - 1] = '\0';
		view->entry_set_text(first_num);
	} else {
		second_num[strlen(second_num) - 1] = '\0';
		view->entry_set_text(first_num);
		char temp[3] = { ' ', opt, ' ' };
		view->append_to_entry(temp);
		view->append_to_entry(second_num);
	}
}

void Control::reset() {
	state = 0;
	first_num = "";
	second_num = "";
	view->entry_set_text("");
}

void Control::save() {
	if (state == 0) {
		memory = first_num;
	} else if (state == 1) {
		memory = second_num;
	}
}

void Control::show_save() {
	if (state == 0) {
		first_num = memory;
		view->entry_set_text(first_num);
	} else if (state == 1) {
		second_num = memory;
		view->entry_set_text(first_num);
		char temp[3] = { ' ', opt, ' ' };
		view->append_to_entry(temp);
		view->append_to_entry(second_num);
	}
}
void Control::handle_entry(char* input) {
	short int instate = whatis(input);
	printf("%d\n", instate);
	if (instate != 100) {
		if (instate == 0) {
			if (state == 0) {
				first_num = append(first_num, input);
				view->append_to_entry(input);
			} else {
				second_num = append(second_num, input);
				view->append_to_entry(input);
			}
		} else if (state == 0 && instate != 5) {
			state = 1;
			opt = input[0];
			view->append_to_entry(" ");
			view->append_to_entry(input);
			view->append_to_entry(" ");
		} else if (state == 1 && instate == 5) {
			int result = eval();
			printf("resault: %d\n", result);
			char res[20];
			sprintf(res, "%d", result);
			strcpy(first_num, res);
			second_num = "";
			state = 0;
			view->entry_set_text(res);

		} else if (state == 1 && instate != 5) {
			int result = eval();
			printf("resault: %d\n", result);
			char res[20];
			sprintf(res, "%d", result);
			strcpy(first_num, res);
			second_num = "";
			state = 1;
			opt = input[0];
			view->entry_set_text(res);
			view->append_to_entry(" ");
			view->append_to_entry(input);
			view->append_to_entry(" ");
		}
	}
}

