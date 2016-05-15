#include <iostream>
#include <gtk/gtk.h>
#include <cryptopp/integer.h>
#include "struttura_dati.h"
#include "funzioni.h"
#include "debug.h"
#include "crittografia.h"

#ifndef MAIN_H
#define MAIN_H

/*
* builder:
* Puntatore a GtkBuilder per accedere ai widget dell'interfaccia grafica
*/
static GtkBuilder* builder;

void initGUI(int argc, char* argv[]);
extern "C" gboolean handler_delete_event (GtkWidget *widget, GdkEvent *event, gpointer user_data);
extern "C" void handler_freezeAll (GtkWidget *widget, GdkEvent *event, gpointer user_data);
extern "C" void handler_add_user (GtkWidget *widget, GdkEvent *event, gpointer user_data);
extern "C" void handler_get_masterPassword (GtkWidget *widget, GdkEvent *event, gpointer user_data);
extern "C" void handler_show_welcome_window (GtkWidget *widget, GdkEvent *event, gpointer user_data);
extern "C" void handler_get_username (GtkWidget *widget, GdkEvent *event, gpointer user_data);
extern "C" void handler_show_main_window (GtkWidget *widget, GdkEvent *event, gpointer user_data);
extern "C" void handler_show_website (GtkWidget *widget, GdkEvent *event, gpointer user_data);
extern "C" void handler_get_website (GtkWidget *widget, GdkEvent *event, gpointer user_data);
extern "C" void handler_freeze_generatePassword (GtkWidget *widget, GdkEvent *event, gpointer user_data);







#endif
