//A C++ program to take 4 log files as inputs and output an easy to read interpretation of the AT command trace
//can be extended to any number of files by opening the file in the main function
//and calling the operate_on_file function with filename as argument
//the output can be displayed on console or redirected to a file


#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <locale>
#include <sstream>

using namespace std;


string line;                                             //stores the line at whicch the string to be found is present
string newline,newline0,newline1,newline2,newline3,newline4;
string newline5,newline6,newline7;                       //stores the final substring to be displayed
size_t pos,pos1,pos2,pos3,pos4,pos5,pos6,pos7,pos8,pos9; // stores the positions at which the specified string is found in the file
size_t pos10,pos11,pos12;
stringstream compare_string;
stringstream compare_string_1;
int compare_integer=0;
int compare_integer_1=0;
string str = "Signal";                                    //to find signal quality metrics from AT%MEAS
string str1 = "loading";                                  //to find the loading time
/* various parameters stripped from AT%PCONI- eNB parameters */
string str2 = "duplexing";                                //duplexing mode
string str3 = "HNBN";
string str4 = "Transmission";                             // transmission mode
string str5 = "MIMO";                                     //MIMO Bandwidth
string str6 = "EARFCN";
string str7 = "Global";                                   //Global cell ID
string str8 = "Physical";                                 //Physical Cell ID
string str9 = "Bandwidth: ";                              //to extract Bandwidth value alone from AT%PCONI output
/* following strings used to extract BER from AT+CSQ response */
string str10 = "AT+CSQ+CSQ";  
string str11 = ",";
string str12 = "OK";
/* length calculation required for Bandwidth and BER mapping*/
int length= strlen("Bandwidth: ");
int length1= strlen(",");

/* the bandwidth outputs of AT%PCONI are mapped to their interpreted physical values. e.g: MIMOBandwidth :3 actually means the measured bandwidth is 10Mhz*/

void map_bandwidth( int value) 
{
  switch(value)
   {
     case(0):
     {
      cout<< "bandwidth is 1.4Mhz "<< endl;
      break;
      }
     case(1):
     {
      cout<< "bandwidth is 3Mhz "<< endl;
      break;
      }
     case(2):
     {
      cout<< "bandwidth is 5Mhz "<< endl;
      break;
      }
     case(3):
      {
      cout<< "bandwidth is 10Mhz "<< endl;
      break;
      }
     case(4):
      {
      cout<< "bandwidth is 15Mhz "<< endl;
      break;
      }
     case(5):
      {
      cout<< "bandwidth is 20Mhz "<< endl;
      break;
      }
      default:
      {
      cout<< "value not identified "<< endl;
      break;
      }

   }

}


/* the bit error rate outputs of AT+CSQ are mapped to their interpreted physical values. e.g: AT+CSQ+CSQ 12,0ok actually means the measured BER(second value alone) is .14%*/

void map_BER( int value)
{
  switch(value)
   {
     case(0):
     {
      cout<< "error rate is assumed to be .14% "<< endl;
      break;
      }
     case(1):
     {
      cout<< "error rate is assumed to be .28% "<< endl;
      break;
      }
     case(2):
     {
      cout<< "error rate is assumed to be .57% "<< endl;
      break;
      }
     case(3):
      {
      cout<< "error rate is assumed to be 1.13% "<< endl;
      break;
      }
     case(4):
      {
      cout<< "error rate is assumed to be 2.26% "<< endl;
      break;
      }
     case(5):
      {
      cout<< "error rate is assumed to be 4.53% "<< endl;
      break;
      }
     case(6):
      {
      cout<< "error rate is assumed to be 9.05% "<< endl;
      break;
      }
     case(7):
      {
      cout<< "error rate is assumed to be 18.10% "<< endl;
      break;
      }
     default:
     {
     cout<<"error"<<endl;
     break;
     }


   }

}


/*Signal quality values RSSI,RSRQ,SINR,RSRP values are stripped from AT%MEAS by finding the last instance of the keyword 'Signal' in the trace*/
void  find_Signal_Quality(){

         
            pos= line.find(str,0); 
            
            }
/* keyword 'Loading' is used to search for the loading time*/
void  find_Loading_time(){ 

            pos= line.find(str1,0);
            newline=line.substr(pos);
            
             }
 void find_base_station_parameters(){
   
            pos= line.find(str2,0); //find the positions of the various strings in the trace
            pos3= line.find(str3,0);
            pos4= line.find(str4,0);
            pos5= line.find(str5,0);
            pos6= line.find(str6,0);
            pos7= line.find(str7,0);
            pos8= line.find(str8,0);
            pos9= line.find(str9,0);       
            newline0=line.substr(pos,(pos4-pos));  //split the output of AT%PCONI by extracting the values between two strings       
            newline1=line.substr(pos4,(pos5-pos4));           
            newline6=line.substr((pos9+length),(pos6-(pos9+length)));
            /*conversion of string value to integer value to enable mapping*/
            compare_string << newline6;
            compare_string >> compare_integer;

            newline3=line.substr(pos6,(pos7-pos6));//split the output of AT%PCONI by extracting the values between two strings
	    newline4=line.substr(pos7,(pos8-pos7));
	    newline5=line.substr(pos8,(pos3-pos8));
          
            }
  

void find_BER(){
    
            pos10= line.find(str10,0);
            pos12= line.find(str12);
            newline6=line.substr(pos10);
            pos11=newline6.find(str11);
            newline7=newline6.substr(pos11+length1,length1);// strip the BER value alone from AT+CSQ output
            /*conversion of string value to integer value to enable mapping*/
            compare_string_1 << newline7;
            compare_string_1 >> compare_integer_1;
            
              }

void print_values(){
    cout << newline << endl;
    cout << newline0 << endl;    
    cout << newline1 << endl;
    map_bandwidth(compare_integer);    
    cout << newline3 << endl;
    cout << newline4 << endl;
    cout << newline5 << endl;
    map_BER(compare_integer_1);
    cout<<"_________________"<< endl;
    cout<<""<<endl;

}
 /* the various strings are found within each file*/
void operate_on_file(ifstream& file_name){
    while(getline(file_name, line)) {                   //fetch the file line by line
        
        if (line.find(str, 0) != string::npos){    /*line.find returns the pos at which the string was found.It is checked against last    pos*/

           find_Signal_Quality();

             }
	if (line.find(str1, 0) != string::npos){

            find_Loading_time();
            
             }
	if (line.find(str2, 0) != string::npos){
            
            find_base_station_parameters();

             }
        if (line.find(str10, 0) != string::npos){

            find_BER();

             }
      }
    print_values();

    }

int main()
{
    ifstream file;
    ifstream file1;
    ifstream file2;
    ifstream file3;
    
    
    file.open("putty10.log"); //Sensor upload to cloud AT command trace
    file1.open("putty8.log"); //basic HTTP request AT command trace
    file2.open("http_ucla_log.txt"); //large HTTP request AT command trace
    file3.open("pdf_bedroom.txt"); // PDF downlaod AT command trace
  
    cout<<"IoT application"<<endl;
    cout<<""<<endl;
    operate_on_file(file);  
    cout<<"HTTP Request"<<endl;
    cout<<""<<endl;
    operate_on_file(file1);
    cout<<"Web Browsing application"<<endl;
    cout<<""<<endl;
    operate_on_file(file2);
    cout<<"PDF download"<<endl;
    cout<<""<<endl;
    operate_on_file(file3);


    return 0;
}
