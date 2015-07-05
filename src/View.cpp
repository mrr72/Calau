/*
 * View.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mrr
 */

#include "Mvc.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include<iostream>

View::View(int*argc, char***argv, IControl* c) {
	GtkWidget *window;
	GtkWidget *table;
	icontrol = c;
	gtk_init(argc, argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Calculator");
	g_signal_connect(window, "delete-event", G_CALLBACK (&View::delete_event),
			NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	/* Create a 2x2 table */
	table = gtk_table_new(17, 13, TRUE);
	entry = gtk_entry_new();
	g_signal_connect(entry, "key_press_event", G_CALLBACK (enter_callback),
			icontrol);
	gtk_table_attach_defaults(GTK_TABLE(table), entry, 1, 12, 1, 3);
	gtk_widget_show(entry);
	add_button(table, entry);
//------------
	textArea = gtk_text_view_new();
	GtkWidget* scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(scrolledwindow), textArea);
	gtk_table_attach_defaults(GTK_TABLE(table), scrolledwindow, 1, 12, 13, 17);
	gtk_widget_show(scrolledwindow);
	gtk_widget_show(textArea);
	gtk_container_add(GTK_CONTAINER(window), table);
	gtk_widget_show(table);
	gtk_widget_show(window);

}
void View::add_to_history_command(char* text) {
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textArea));
	gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
	gtk_text_buffer_insert(buffer, &iter, text, -1);

}
void View::runview() {
	gtk_main();

}

View::~View() {
}

gboolean View::delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {

	gtk_main_quit();
	return FALSE;
}
bool View::enter_callback(GtkEntry *entry, GdkEventKey *event,
		gpointer user_data) {

	Control* iii = (Control*) user_data;
	iii->handle_entry(event->string);
	if (event->keyval == 65288) {
		iii->backspace();
	}
	printf("Entry contents: %d -- %s \n", event->keyval, event->string);
	return true;
}

gboolean View::numberbtn_callback(GtkWidget *numbtn, gpointer callback_data) {

	char* a = (char*) gtk_button_get_label((GtkButton*) numbtn);
	int num = atoi(a);
	Control* iii = (Control*) callback_data;
	iii->handle_entry(a);
}
gboolean View::reset_callback(GtkWidget *numbtn, gpointer callback_data) {

	Control* iii = (Control*) callback_data;
	iii->reset();
}
gboolean View::memo_callback(GtkWidget *numbtn, gpointer callback_data) {

	Control* iii = (Control*) callback_data;
	iii->save();
}
gboolean View::showmemo_callback(GtkWidget *numbtn, gpointer callback_data) {

	Control* iii = (Control*) callback_data;
	iii->show_save();
}

void View::add_button(GtkWidget *table, GtkWidget* Display) {

	char aa[] = "0";
	for (int i = 0; i <= 8; i++) {
		aa[0] += 1;
		GtkWidget *numbtn = gtk_button_new_with_label(aa);
		g_signal_connect(numbtn, "clicked", G_CALLBACK (numberbtn_callback),
				icontrol);
		gtk_table_attach_defaults(GTK_TABLE(table), numbtn, 1 + ((i * 2) % 6),
				3 + ((i * 2) % 6), 4 + ((i / 3) * 2), 6 + ((i / 3) * 2));
		gtk_widget_show(numbtn);
	}

	GtkWidget *numbtn = gtk_button_new_with_label("0");
	g_signal_connect(numbtn, "clicked", G_CALLBACK (numberbtn_callback),
			icontrol);
	gtk_table_attach_defaults(GTK_TABLE(table), numbtn, 3, 5, 10, 12);
	gtk_widget_show(numbtn);
//------------------------------------------ End of number btn
	GtkWidget *optbtn = gtk_button_new_with_label("+");
	g_signal_connect(optbtn, "clicked", G_CALLBACK (numberbtn_callback),
			icontrol);
	gtk_table_attach_defaults(GTK_TABLE(table), optbtn, 8, 10, 4, 6);
	gtk_widget_show(optbtn);

	optbtn = gtk_button_new_with_label("-");
	g_signal_connect(optbtn, "clicked", G_CALLBACK (numberbtn_callback),
			icontrol);
	gtk_table_attach_defaults(GTK_TABLE(table), optbtn, 8, 10, 6, 8);
	gtk_widget_show(optbtn);

	optbtn = gtk_button_new_with_label("*");
	g_signal_connect(optbtn, "clicked", G_CALLBACK (numberbtn_callback),
			icontrol);
	gtk_table_attach_defaults(GTK_TABLE(table), optbtn, 8, 10, 8, 10);
	gtk_widget_show(optbtn);

	optbtn = gtk_button_new_with_label("/");
	g_signal_connect(optbtn, "clicked", G_CALLBACK (numberbtn_callback),
			icontrol);
	gtk_table_attach_defaults(GTK_TABLE(table), optbtn, 8, 10, 10, 12);
	gtk_widget_show(optbtn);

	optbtn = gtk_button_new_with_label("=");
	g_signal_connect(optbtn, "clicked", G_CALLBACK (numberbtn_callback),
			icontrol);
	gtk_table_attach_defaults(GTK_TABLE(table), optbtn, 10, 13, 10, 12);
	gtk_widget_show(optbtn);


	GtkWidget *func = gtk_button_new_with_label("C");
	g_signal_connect(func, "clicked", G_CALLBACK (reset_callback), icontrol);
	gtk_table_attach_defaults(GTK_TABLE(table), func, 10, 13, 4, 6);
	gtk_widget_show(func);

	func = gtk_button_new_with_label("M");
	g_signal_connect(func, "clicked", G_CALLBACK (memo_callback), icontrol);
	gtk_table_attach_defaults(GTK_TABLE(table), func, 10, 13, 6, 8);
	gtk_widget_show(func);

	func = gtk_button_new_with_label("sM");
	g_signal_connect(func, "clicked", G_CALLBACK (showmemo_callback), icontrol);
	gtk_table_attach_defaults(GTK_TABLE(table), func, 10, 13, 8, 10);
	gtk_widget_show(func);
}

void View::entry_set_text(char* text) {
	GtkEntry* entryyy = GTK_ENTRY(entry);
	gtk_entry_set_text(entryyy, text);
}
void View::append_to_entry(char* text) {
	GtkEntry* entryyy = GTK_ENTRY(entry);
	gint tmp_pos = gtk_entry_get_text_length(entryyy);
	gtk_editable_insert_text(GTK_EDITABLE(entryyy), text, -1, &tmp_pos);
}
