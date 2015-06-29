/*
 * Control.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mrr
 */
#ifndef MVC_H_
#define MVC_H_

class IControl {
public:
	virtual void handle_entry(char* input)=0;
//	virtual void reset()=0;
//	virtual void save()=0;
//	virtual void show_save()=0;
//	virtual void memory_dump()=0;
};


//-----------------------------------
#include <gtk/gtk.h>

class View {
public:
	View(int*argc, char***argv, IControl* ic);
	virtual ~View();
	void runview();
	static gboolean numberbtn_callback(GtkWidget *numbtn,
			gpointer callback_data);
	gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);
	static bool enter_callback(GtkEntry *entry, GdkEventKey *event,
			gpointer user_data);
	void add_button(GtkWidget *table, GtkWidget* Display);

	void append_to_entry(char* text);
	void clear_entry();
	void entry_set_text(char* text);

private:
	GtkWidget *entry;
	IControl* icontrol;
};

class Control : public IControl {
public:
	Control();
	virtual ~Control();
	void setview(View* view);
	void handle_entry(char* input);
//	void reset();
//	void save();
//	void show_save();
//	void memory_dump();

private:
	View* view;
	short int whatis(char* i);
	char* append(char* a, char* b);
	int eval();
	short int state;
	char opt;
	char* first_num;
	char* second_num;
};

#endif /* MVC_H_ */

