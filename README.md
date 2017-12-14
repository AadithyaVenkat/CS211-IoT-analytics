# CS211-IoT-analytics
Provides a way to obtain low level network informtion to the user and their impact on performance metrics of an application.The repository contains the applications that can be run on AT&amp;T IoT starter kit along with their AT command trace logs. Also included are two tool, one in c++ to extract network parameters from the logs and dispaly in a user readable text based format. Another tool is written in python and can extract the relevant metrics and provide a visual representation of performance metrics and their variation with signal strength
The following applications are used for collecting AT Command traces
                       * small HTTP Request
                       * HTTPS Request
                       * Sensor data acquisition and transfer to cloud
                       * PDF download to board
                       * large HTTP request/Web browsing
Debug mode must be enabled in each of these files in order to collect the AT command traces 
SENSOR DATA APPLICATIONS:
The original application can be found here:

https://os.mbed.com/teams/Avnet/code/Avnet_ATT_Cellular_IOT/

The steps to set up the starter kit and run the application can be found here:

http://cloudconnectkits.org/sites/default/files/GettingStartedGuide-ATT-IOT-rv1-4.pdf

The following changes are made to the Avnet_ATT_Cellular_IOT application
   In cellular_modem.cpp
         timer module is called to calculate the time taken to load sensor data to cloud. timer start, stop and read functions are used in the  sendreceive module

In WNC_Control.cpp, the following AT commands are added
        "AT%MEAS=\"8\""
        "AT+CGEQOS?"
        "AT%PCONI"
The final version that can be run as such to collect traces is included in the repository
  https://os.mbed.com/users/nrithya/code/Avnet_ATT_Cellular_IOT_modified/

HTTP APPLICATIONS
 The modified HTTP application can be found here
 https://os.mbed.com/users/nrithya/code/easy-connect-httpmodified/

The easy connect WNC library is added to http request file and the debug mode is turned on in mbed_app.json. The above mentioned AT commands are added to
http-example-wnc-modified/easy-connect/WNC14A2AInterface/WncControllerK64F/WncController/WncController.cpp

The repository contains source files for both HTTP and HTTPS requests and the changes are made in the shared library file. Web browsing and PDF
download applications can be run by modifying the HTTP request URL.

The AT command trace can be viewed through a serial emulator like puTTY, by specifying the correct serial port and baud rate. The outputs can be logged to a separate text file by enabling 'Logging' under the 'session' tab and specifying the target file name.

The logs obtained for the different applications are saved to a common directory. 
The parser and mapper tool must be present in the same directory

The parser and mapper extracts the Signal Quality, Bandwidth, Transmission mode, Loading time and error rate from the raw output traces and displays it in a user-readable format

The log files are given as input to the 'cpp_parser-revised.cc' file which can be compiled and run using g++ compiler. the output can be viewed on the console or redirected to a file

A more visually powerful tool is developed in python to plot the variation of the performance metric, i.e loading time, against the network parameters like RSSI,RSRP, SINR, RSRQ

The log file is given as input to 'visualization.py' and the program is run to generate the plots.

