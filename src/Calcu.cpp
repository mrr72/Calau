#include <gtk/gtk.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include "Mvc.h"

using namespace std;

int main(int argc, char *argv[]) {
	Control c;
	IControl* ic = &c;
	View v(&argc, &argv,ic);
	c.setview(&v);
	v.runview();
	return 0;
//	View* view;
//	Control a(view);
//
	//
//
}
