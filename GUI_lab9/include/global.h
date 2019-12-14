#include <gtk/gtk.h>
#include <stdlib.h>
#include <iostream>
#define __STDC_FORMAT_MACROS


#ifndef _MY__GLOBAL__H
#define _MY__GLOBAL__H

using namespace std;

/**************************************************************
 * GUI window stuff
 **************************************************************/

typedef struct 
{
  GtkWidget *Window1; //visualization window
  GtkWidget *serial_entry;  //the entry for the device
  GtkWidget *open_button; //the open button
  GtkWidget *close_button; //the close button
  GtkWidget *red_entry; //the red entry
  GtkWidget *green_entry; //the green entry
  GtkWidget *blue_entry; //the blue entry
  GtkWidget *send_button; //the send button	
  GtkWidget *output_str; //the return packet output
  GtkWidget *green_slider; //the green slider
  GtkWidget *blue_slider;  //the blue slider
  GtkWidget *red_slider;   //the red slider
  GtkWidget *vol_out_lab;  //the voltage output
  GtkWidget *exit_button; //the exit button

} Gui_Window_AppWidgets;

extern Gui_Window_AppWidgets *gui_app;

extern int operand;
extern int last_function;
extern int clear_f;

#endif
