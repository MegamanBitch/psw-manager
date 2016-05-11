#include <iostream>
#include <gtk/gtk.h>
#include "struttura_dati.h"
#include "funzioni.h"

#ifndef MAIN_H
#define MAIN_H

/*
* builder:
* Puntatore a GtkBuilder per accedere ai widget dell'interfaccia grafica
*/
static GtkBuilder* builder;

void initGUI(int argc, char* argv[]);
extern "C" void freezeAll_handler(GtkWidget *widget, GdkEvent *event, gpointer user_data);
extern "C" void handler_add_user(GtkWidget *widget, GdkEvent *event, gpointer user_data);
extern "C" void setup_masterPassword_handler(GtkWidget *widget, GdkEvent *event, gpointer user_data);











#endif
