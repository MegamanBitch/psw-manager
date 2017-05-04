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
* @var builder:
* @brief pointer to access graphical user interface widgets
*/
static GtkBuilder* builder;

/**
* @var fileListModel
* @brief pointer to GtkListStore which contains the fileListView model
*/
static GtkListStore* fileListModel;

/**
* @brief initialize graphical user interface
*
* @param[in] argc number of arguments
* @param[in] argv array of arguments
*/
void initGUI(int argc, char* argv[]);

/**
* @brief program closing handler
*/
extern "C" gboolean handler_delete_event (GtkWidget *widget, GdkEvent *event, gpointer user_data);

/**
* @brief add user button handler
*/
extern "C" void handler_add_user (GtkWidget *widget, GdkEvent *event, gpointer user_data);

/**
* @brief get master password handler
*/
extern "C" void handler_get_masterPassword (GtkWidget *widget, GdkEvent *event, gpointer user_data);

/**
* @brief show welcome window handler
*/
extern "C" void handler_show_welcome_window (GtkWidget *widget, GdkEvent *event, gpointer user_data);

/**
* @brief get username handler
*/
extern "C" void handler_get_username (GtkWidget *widget, GdkEvent *event, gpointer user_data);

/**
* @brief show main window handler
*/
extern "C" void handler_show_main_window (GtkWidget *widget, GdkEvent *event, gpointer user_data);

/**
* @brief show entry window handler
*/
extern "C" void handler_show_entry (GtkWidget *widget, GdkEvent *event, gpointer user_data);

/**
* @brief ok button in entry window handler
*/
extern "C" void handler_get_entry (GtkWidget *widget, GdkEvent *event, gpointer user_data);

/**
* @brief GtkSwitch in entry window handler
*/
extern "C" void handler_freeze_generatePassword (GtkWidget *widget, GdkEvent *event, gpointer user_data);

/**
* @brief login button handler
*/
extern "C" void handler_show_login (GtkWidget *widget, GdkEvent *event, gpointer user_data);

/**
* @brief ok button in login window handler
*/
extern "C" void handler_get_login (GtkWidget *widget, GdkEvent *event, gpointer user_data);

/**
* GtkLevelBar in master password handler
*/
extern "C" void handler_entropy (GtkWidget *widget, GdkEvent *event, gpointer user_data);

/**
* @brief choose file handler
*/
extern "C" void handler_chooseFile (GtkWidget *widget, GdkEvent *event, gpointer user_data);

/**
* @brief set increment of GtkSpinButton handler
*/
extern "C" void handler_spinButton (GtkWidget *widget, GdkEvent *event, gpointer user_data);

/**
* @brief generate password button handler
*/
extern "C" void handler_generatePassword (GtkWidget *widget, GdkEvent *event, gpointer user_data);

/**
* @brief info button handler
*/
extern "C" void handler_show_credits_window (GtkWidget *widget, GdkEvent *event, gpointer user_data);


/**
* @brief add instance of ::FileInfo to ::fileListModel
*
* @param[in] info pointer to the instance of ::FileInfo to add
*/
void addToFileView(entry_t &values);

/**
* @brief removes all rows from ::fileListModel
*/
void clearFileView();

/**
* @brief removes all rows from ::fileListModel and reinsert data in ::fileList
*/
void reloadFileView();

/**
*	@brief Ritorna l'indice della riga correntemente selezionata nella fileListView
*
* @return Indice della riga selezionata o -1 se nessuna riga è selezionata
*/
int getFileViewSelectedRow();



#endif
