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

View::View(int*argc, char***argv,IControl* c) {
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
	g_signal_connect(entry, "key_press_event", G_CALLBACK (enter_callback), icontrol);
	gtk_table_attach_defaults(GTK_TABLE(table), entry, 1, 12, 1, 3);

	gtk_widget_show(entry);
	add_button(table, entry);

	/* Put the table in the main window */
	gtk_container_add(GTK_CONTAINER(window), table);
	gtk_widget_show(table);
	gtk_widget_show(window);

//	gtk_main();

}
void View::runview(){
	gtk_main();

}

View::~View() {
}

gboolean View::delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {

	gtk_main_quit();
	return FALSE;
}
bool View::enter_callback(GtkEntry *entry,GdkEventKey *event, gpointer user_data) {

	Control* iii = (Control*)user_data;
		iii->handle_entry(event->string);
		printf("Entry contents: %s\n", event->string);
	return true;
}

gboolean View::numberbtn_callback(GtkWidget *numbtn, gpointer callback_data) {

	char* a = (char*) gtk_button_get_label((GtkButton*) numbtn);
	int num = atoi(a);
//	GtkEntry* entry = GTK_ENTRY(callback_data);
	Control* iii = (Control*)callback_data;
	iii->handle_entry(a);
//	printf("Entry contents: %s\n", a);

	// TODO : bug here
//	GtkEntry* entry = GTK_ENTRY(callback_data);
//	gint tmp_pos = gtk_entry_get_text_length(entry);
//	gint tmp_pos = gtk_entry_get_text_length((GtkEntry*)entry);
//	gtk_editable_insert_text(GTK_EDITABLE(callback_data), a, -1, &tmp_pos);
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
//	TODO : complete button adding
}

void View::entry_set_text(char* text){
	GtkEntry* entryyy = GTK_ENTRY(entry);
	gtk_entry_set_text(entryyy,text);
 }
void View::append_to_entry(char* text){
	GtkEntry* entryyy = GTK_ENTRY(entry);
	gint tmp_pos = gtk_entry_get_text_length(entryyy);
	gtk_editable_insert_text(GTK_EDITABLE(entryyy), text, -1, &tmp_pos);
}
