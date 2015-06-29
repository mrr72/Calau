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
//	printf("a: %s\n", a);
//	printf("b: %s\n", b);
	size_t len = strlen(a);
	char* ret = new char[len + 2];
	strcpy(ret, a);
	ret[len] = b[0];
	ret[len + 1] = '\0';
	return ret;
//	strcat(a,b);
//return strcat(a, b);
}

int Control::eval() {
	printf("eval %d \n",opt);
	switch (opt) {
	case '+':
		printf("%s + %s \n", first_num,second_num);
		return atoi(first_num) + atoi(second_num);
		break;
	case '-':
		printf("%s - %s \n", first_num,second_num);
		return atoi(first_num) - atoi(second_num);
		break;
	case '*':
		printf("%s * %s \n", first_num,second_num);
		return atoi(first_num) * atoi(second_num);
		break;
	case '/':
		printf("%s / %s \n", first_num,second_num);
		return atoi(first_num) / atoi(second_num);
		break;
	default:
		break;
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
//			printf("elseif: %s\n", input[0]);
			state = 1;
			opt = input[0];
			view->append_to_entry(" ");
			view->append_to_entry(input);
			view->append_to_entry(" ");
		} else if (state == 1) {
			int result = eval();
			printf("resault: %d\n", result);
			char res[20];
			sprintf(res, "%d", result);
			strcpy(first_num, res);
			second_num = "";
			state = 0;
			view->entry_set_text(res);

		}
	}
}

