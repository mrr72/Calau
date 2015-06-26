/*
 * Control.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mrr
 */

#ifndef MVC_H_
#define MVC_H_

//-----------------------------------
#include <gtk/gtk.h>
#include "Control.h"

class View {
public:
	View(int*argc,char***argv,Control c);
	virtual ~View();
	static gboolean numberbtn_callback(GtkWidget *numbtn, gpointer callback_data);
	void add_button(GtkWidget *table, GtkWidget* Display);
	static gboolean delete_event(GtkWidget *widget, GdkEvent *event,gpointer data);
	static bool enter_callback(GtkEntry *entry, GdkEventKey *event, gpointer user_data);
//	static void enter_callback(GtkWidget *widget, GtkWidget *entry);

	// interface to entry
	void append_to_entry(char* text);
	void clear_entry();
	void entry_set_text(char* text);

private :
	GtkWidget *entry;
	Control control;
};
#endif /* MVC_H_ */

