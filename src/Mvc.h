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
	static gboolean reset_callback(GtkWidget *numbtn,
			gpointer callback_data);
	static gboolean memo_callback(GtkWidget *numbtn,
			gpointer callback_data);
	static gboolean showmemo_callback(GtkWidget *numbtn,
			gpointer callback_data);

	gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);
	static bool enter_callback(GtkEntry *entry, GdkEventKey *event,
			gpointer user_data);
	void add_button(GtkWidget *table, GtkWidget* Display);

	void append_to_entry(char* text);
	void clear_entry();
	void entry_set_text(char* text);
	void add_to_history_command(char* texr);

private:
	GtkWidget *entry;
	IControl* icontrol;

	//	text view control

	GtkWidget* textArea;
	GtkTextBuffer *buffer;
	GtkTextIter iter;


};

class Control : public IControl {
public:
	Control();
	virtual ~Control();
	void setview(View* view);
	void handle_entry(char* input);
	void backspace();
	void reset();
	void save();
	void show_save();

private:
	View* view;
	short int whatis(char* i);
	char* append(char* a, char* b);
	int eval();
	short int state;
	char opt;
	char* first_num;
	char* second_num;
	char* memory;
};

#endif /* MVC_H_ */

