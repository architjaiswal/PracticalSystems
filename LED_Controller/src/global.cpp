#include "global.h"

Gui_Window_AppWidgets *gui_app; //!< this will hold all the widget

int ser_dev=-1; //!< default value for the device serial number

char c_voltage_value[40]; //!< creates the array to hold the voltage value

int kill_all_threads; //!< basic variable to remove the threads

GMutex *mutex_to_protect_voltage_display; //!< mutex for the voltage 



  

