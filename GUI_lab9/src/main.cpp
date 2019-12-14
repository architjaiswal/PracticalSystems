#include "global.h"
#include "string.h"

//********************************************************************
// to connect widgets with code
//********************************************************************
void ObtainGuiWidgets(GtkBuilder *p_builder)
{
  #define GuiappGET(xx) gui_app->xx=GTK_WIDGET(gtk_builder_get_object(p_builder,#xx))
  GuiappGET(Window1);
  GuiappGET(serial_device);
GuiappGET(serial_entry);
  GuiappGET(open_button);
  GuiappGET(close_button);
  GuiappGET(red_label);
  GuiappGET(red_entry);
  GuiappGET(green_label);
  GuiappGET(green_entry);
  GuiappGET(blue_label);
  GuiappGET(blue_entry);
  GuiappGET(send_button);
  GuiappGET(red_sli_label);
  GuiappGET(green_sli_label);
  GuiappGET(blue_sli_label);
  GuiappGET(return_pack_string);
  GuiappGET(output_str);
  GuiappGET(green_slider);
  GuiappGET(blue_slider);
  GuiappGET(red_slider);
  GuiappGET(vol_label);
  GuiappGET(vol_out_lab);
  GuiappGET(exit_button);
}


//********************************************************************
// GUI handlers
//********************************************************************


extern "C" void button_send_clicked(GtkWidget *p_wdgt, gpointer p_data ) 
{
  const char *a_cc_value;
  char c_cc_value[20];
  int a_d_value=0;
  if(!clear_f)// for red
    {
       a_cc_value = gtk_label_get_text(GTK_LABEL(gui_app->red_entry));
       a_d_value = atoi(a_cc_value);
       a_d_value*=10;
    }
    gtk_label_set_text(GTK_LABEL(gui_app->red_slider),c_cc_value);
    
    
  if(!clear_f)// for green
    {
       a_cc_value = gtk_label_get_text(GTK_LABEL(gui_app->green_entry));
       a_d_value = atoi(a_cc_value);
       a_d_value*=10;
    }
    gtk_label_set_text(GTK_LABEL(gui_app->green_slider),c_cc_value);
    
    
  if(!clear_f)// for blue
    {
       a_cc_value = gtk_label_get_text(GTK_LABEL(gui_app->blue_entry));
       a_d_value = atoi(a_cc_value);
       a_d_value*=10;
    }
  gtk_label_set_text(GTK_LABEL(gui_app->blue_slider),c_cc_value);
  
  
  clear_f=false;
  
  sprintf(c_cc_value,"%d",a_d_value);
  
  //gtk_label_set_text(GTK_LABEL(gui_app->label_result),c_cc_value);
}

extern "C" void button_exit_clicked(GtkWidget *p_wdgt, gpointer p_data ) 
{
  gtk_main_quit();

}

//********************************************************************
//********************************************************************
// 
//   Main loop
//
//********************************************************************
//********************************************************************

int main(int argc, char **argv)
{

  GtkBuilder *builder;
  GError *err = NULL;

  // Now we initialize GTK+ 
  gtk_init(&argc, &argv);
  
  //create gtk_instance for visualization
  gui_app = g_slice_new(Gui_Window_AppWidgets);

  //builder
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "Lab9.glade", &err);
  
  //error handling
  if(err)
    {
      g_error(err->message);
      g_error_free(err);
      g_slice_free(Gui_Window_AppWidgets, gui_app);
      exit(-1);
    }

  // Obtain widgets that we need
  ObtainGuiWidgets(builder);

  // Connect signals
  gtk_builder_connect_signals(builder, gui_app);

  // Destroy builder now that we created the infrastructure
  g_object_unref(G_OBJECT(builder));

  //display the gui
  gtk_widget_show(GTK_WIDGET(gui_app->Window1));

  //the main loop
  gtk_main();
 
  //destroy gui if it still exists
  if(gui_app)
    g_slice_free(Gui_Window_AppWidgets, gui_app);

  return 0;
}
