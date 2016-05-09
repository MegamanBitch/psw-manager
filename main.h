#include <iostream>
#include <gtk/gtk.h>

#ifndef MAIN_H
#define MAIN_H

/*
* builder:
* Puntatore a GtkBuilder per accedere ai widget dell'interfaccia grafica
*/
static GtkBuilder* builder;

void initGUI(int argc, char* argv[]);
extern "C" void freezeAll_handler(GtkWidget *widget, GdkEvent *event, gpointer user_data);
extern "C" void add_user_handler(GtkWidget *widget, GdkEvent *event, gpointer user_data);











#endif
