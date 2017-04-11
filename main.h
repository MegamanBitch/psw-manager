#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <stdio.h>
#include <gtk/gtk.h>
#include "struttura_dati.h"
#include "funzioni.h"
#include "debug.h"
#include "crittografia.h"
#include "entropy.h"
#include "gen_psw.h"

/*
* builder:
* Puntatore a GtkBuilder per accedere ai widget dell'interfaccia grafica
*/
static GtkBuilder* builder;

static GtkListStore* fileListModel;

void initGUI(int argc, char* argv[]);
int getOptions();

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
extern "C" void handler_show_login (GtkWidget *widget, GdkEvent *event, gpointer user_data);
extern "C" void handler_get_login (GtkWidget *widget, GdkEvent *event, gpointer user_data);
extern "C" void handler_entropy (GtkWidget *widget, GdkEvent *event, gpointer user_data);
extern "C" void handler_chooseFile (GtkWidget *widget, GdkEvent *event, gpointer user_data);
extern "C" void handler_spinButton (GtkWidget *widget, GdkEvent *event, gpointer user_data);
extern "C" void handler_generatePassword (GtkWidget *widget, GdkEvent *event, gpointer user_data);
extern "C" void handler_show_credits_window (GtkWidget *widget, GdkEvent *event, gpointer user_data);

void addToFileView(entry_t &values);


void clearFileView();

/**
* @brief Rimuove tutte le righe da ::fileListModel e reinserisce tutti i dati presenti in ::fileList
*/
void reloadFileView();

/**
*	@brief Ritorna l'indice della riga correntemente selezionata nella fileListView
*
* @return Indice della riga selezionata o -1 se nessuna riga è selezionata
*/
int getFileViewSelectedRow();



#endif
