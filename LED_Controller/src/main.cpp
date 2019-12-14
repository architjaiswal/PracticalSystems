/*!
 * \author Chris Socolich
 * \author Archit Jaiswal
 * \version 1.0
 * \date 2018-11-15
 * \copyright GNU Pulbic License
 * 
 * \mainpage The Teeesy LED Controller
 * \section intro_sec Introduction
 * This code is supposed to allow the user to adjust a slide to increase or decrease an LED light. Similarly, the user can type in a value which will change the brightness. Finally, if the user adjusts the potentiometer, the voltage will also change
 */

#include "global.h"
#include "string.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#define VOLTAGE_DISPLAY_UPDATE_MS 100

//********************************************************************
// to connect widgets with code
//********************************************************************
void ObtainGuiWidgets(GtkBuilder *p_builder) //!< this will get the GUI widgets
{
  #define GuiappGET(xx) gui_app->xx=GTK_WIDGET(gtk_builder_get_object(p_builder,#xx))
  GuiappGET(Window1); //!< gets the window
  GuiappGET(serial_entry); //!< gets the entry box
  GuiappGET(vol_out_lab); //!< gets the voltage label
  GuiappGET(open_button); //!<
  GuiappGET(close_button);//!<
  GuiappGET(red_entry);//!<
  GuiappGET(green_entry);//!<
  GuiappGET(blue_entry);//!<
  GuiappGET(send_button);//!<
  GuiappGET(output_str);//!<
  GuiappGET(green_slider);//!<
  GuiappGET(blue_slider);//!<
  GuiappGET(red_slider);//!<
  GuiappGET(exit_button);//!<
    
}


//********************************************************************
// GUI handlers
//********************************************************************
gboolean  Voltage_Display_Displayer(gpointer p_gptr) //!< this will display the voltage
{
  // do not change this function
  g_mutex_lock(mutex_to_protect_voltage_display); //!< locks the mutex
  gtk_label_set_text(GTK_LABEL(gui_app->vol_out_lab),c_voltage_value); //!< sets the label text
  g_mutex_unlock(mutex_to_protect_voltage_display);//!<unlocks the mutex
  return true;
}

extern "C" void button_opendevice_clicked(GtkWidget *p_wdgt, gpointer p_data ) //!< open device button
{
  //do not change  the next few lines
  //they contain the mambo-jumbo to open a serial port
  
  const char *t_device_value; //!< pointer to device ID
  struct termios my_serial; //!< the serial number

  t_device_value = gtk_entry_get_text(GTK_ENTRY(gui_app->serial_entry)); //!< gets the text from the entry box
  //open serial port with read and write, no controling terminal (we don't
  //want to get killed if serial sends CTRL-C), non-blocking 
  ser_dev = open(t_device_value, O_RDWR | O_NOCTTY ); //!< opens device communication
  
  bzero(&my_serial, sizeof(my_serial)); //!< clears the struct 
        
  //B9600: set baud rate to 9600
  //   CS8     : 8n1 (8bit,no parity,1 stopbit)
  //   CLOCAL  : local connection, no modem contol
  //   CREAD   : enable receiving characters  */
  my_serial.c_cflag = B9600 | CS8 | CLOCAL | CREAD; 
         
  tcflush(ser_dev, TCIFLUSH); //!< clears device
  tcsetattr(ser_dev,TCSANOW,&my_serial); 

  //You can add code beyond this line but do not change anything above this line
  
}

extern "C" void button_closedevice_clicked(GtkWidget *p_wdgt, gpointer p_data ) //!< close device button
{
  //this is how you disable a button:
  //gtk_widget_set_sensitive (gui_app->button_closedevice,FALSE);
  //this is how you enable a button:
  //gtk_widget_set_sensitive (gui_app->button_opendevice,TRUE);

  //do not change the next two lines; they close the serial port
  close(ser_dev); //!< closes device
  ser_dev=-1;//!< sets device number to -1

}

extern "C" void button_send_clicked(GtkWidget *p_wdgt, gpointer p_data ) //!< send button
{
  const char *t_red_value;
  const char *t_green_value;
  const char *t_blue_value;
  double uc_red_value;
  double uc_green_value;
  double uc_blue_value;
  char c_cc_value[40]; 
  char send_buff[7];
  int length_send_buff = 7;



  //getting text from widget:
  t_red_value = gtk_entry_get_text(GTK_ENTRY(gui_app->red_entry));
  uc_red_value = stod(t_red_value);
  
    t_green_value = gtk_entry_get_text(GTK_ENTRY(gui_app->green_entry));
  uc_green_value = stod(t_green_value);

  //getting text from widget:
  t_blue_value = gtk_entry_get_text(GTK_ENTRY(gui_app->blue_entry));
  uc_blue_value = stod(t_blue_value);


  //setting range on scale slider to uc_red_value 
  gtk_range_set_value(GTK_RANGE(gui_app->red_slider),uc_red_value);


 
  //Green
  //getting text from widget:
  //setting range on scale slider to uc_red_value 
  gtk_range_set_value(GTK_RANGE(gui_app->green_slider),uc_green_value);

  
  //BLUE
  //setting range on scale slider to uc_red_value 
  gtk_range_set_value(GTK_RANGE(gui_app->blue_slider),uc_blue_value);

send_buff[0]=0xAA;
send_buff[1]=7;
send_buff[2]='L';
send_buff[3]=uc_red_value;
send_buff[4]=uc_green_value;
send_buff[5]=uc_blue_value;
send_buff[6]=send_buff[0] ^ send_buff[1] ^ send_buff[2] ^ send_buff[3] ^ send_buff[4] ^ send_buff[5];

sprintf(c_cc_value, "%X%X%X%X%X%X%X", send_buff[0], send_buff[1], send_buff[2], send_buff[3], send_buff[4],send_buff[5], send_buff[6]);
  gtk_label_set_text(GTK_LABEL(gui_app->output_str),c_cc_value);
  //this is how you send an array out on the serial port:
  write(ser_dev,send_buff,length_send_buff);
  
  
}

extern "C" void scale_rgb_value_changed(GtkWidget *p_wdgt, gpointer p_data ) //!< scale for rgb value
{
	int length_send_buff = 7;
	char send_buff[7];
	
	// for red
	//char uc_red_value;
	double g_red_value;
  char c_cc_value[40];
  //getting the value of the scale slider 
   g_red_value = gtk_range_get_value(GTK_RANGE(gui_app->red_slider));
	 sprintf(c_cc_value, "%d", (int)g_red_value);
	 gtk_entry_set_text(GTK_ENTRY(gui_app->red_entry),c_cc_value);
	 
	 //THIS IS FOR GREEN
	 //char uc_red_value;
	double g_green_value;
  char c_cd_value[40];
  //getting the value of the scale slider 
   g_green_value = gtk_range_get_value(GTK_RANGE(gui_app->green_slider));
	 sprintf(c_cd_value, "%d", (int)g_green_value);
	 gtk_entry_set_text(GTK_ENTRY(gui_app->green_entry),c_cd_value);
	 
	 
	 //THIS IS FOR BLUE
	 //char uc_red_value;
	double g_blue_value;
  char c_ce_value[40];
  //getting the value of the scale slider 
   g_blue_value = gtk_range_get_value(GTK_RANGE(gui_app->blue_slider));
	 sprintf(c_ce_value, "%d", (int)g_blue_value);
	 gtk_entry_set_text(GTK_ENTRY(gui_app->blue_entry),c_ce_value);

  
    
    send_buff[0]=0xAA;
	send_buff[1]=7;
	send_buff[2]='L';
	send_buff[3]= (unsigned char)g_red_value;
	send_buff[4]=(unsigned char)g_green_value;
	send_buff[5]=(unsigned char)g_blue_value;
	send_buff[6]=send_buff[0] ^ send_buff[1] ^ send_buff[2] ^ send_buff[3] ^ send_buff[4] ^ send_buff[5];

	sprintf(c_cc_value, "%X%X%X%X%X%X%X", send_buff[0], send_buff[1], send_buff[2], send_buff[3], send_buff[4],send_buff[5], send_buff[6]);
  gtk_label_set_text(GTK_LABEL(gui_app->output_str),c_cc_value);
  //this is how you send an array out on the serial port:
  write(ser_dev,send_buff,length_send_buff);
}


extern "C" void button_exit_clicked(GtkWidget *p_wdgt, gpointer p_data ) //!< exit button
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

  GThread *read_thread;

  //this is how you allocate a Glib mutex
  g_assert(mutex_to_protect_voltage_display == NULL); 
  mutex_to_protect_voltage_display = new GMutex;
  g_mutex_init(mutex_to_protect_voltage_display);

  // this is used to signal all threads to exit
  kill_all_threads=false;
  
  //spawn the serial read thread
  read_thread = g_thread_new(NULL,(GThreadFunc)Serial_Read_Thread,NULL);
  
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

  //this is going to call the Voltage_Display_Displayer function periodically
  gdk_threads_add_timeout(VOLTAGE_DISPLAY_UPDATE_MS,Voltage_Display_Displayer,NULL);

  //the main loop
  gtk_main();

  //signal all threads to die and wait for them (only one child thread)
  kill_all_threads=true;
  g_thread_join(read_thread);
  
  //destroy gui if it still exists
  if(gui_app)
    g_slice_free(Gui_Window_AppWidgets, gui_app);

  return 0;
}
