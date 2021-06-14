
/*
FPN_investigation_1 converted numbers of the type 1234.567 to floating point format
This investigation puts matarial from the previous investigation into a subroutine "Real_Num_to_FPN()"
It takes numbers of the type 1234.567e-15.
Real_Num_to_FPN() is used to convert 1234.567 to floating point format.
Repeated multiplication or division by 10 is then used to amalgamate the exponent.
*/



#include "Project_header.h"

int main (void){ 
  
float FPNum; 
float num2 = 1.5e3;

char T_array[15];
char expt_10_string[6];
char E_ptr;
int expt_10;
char sign; 


setup_328_HW;                                                       //see header file"

sei();

while(1){
do{Serial.write("F/f    ");}                                        //User prompt; press F or f to escape
while((isCharavailable(127) == 0));                                 //Waits 1 sec for user response; then resends prompt    
keypress = Serial.read();
if ((keypress  == 'F')||
(keypress  == 'f'))break;}


while(1){

Serial.write("\r\n\r\nFPN from keyboard\t");                          //User enters floating point number (FPN)

sign = positive;                                                      //Default setting
E_ptr = Scientific_num_from_KBD(data_buff, &sign);                    //Subroutine echoes keypresses to screen

if(E_ptr){expt_10 = atoi(data_buff + E_ptr + 1);                      //Read the exponent if there is one 
data_buff[E_ptr] = 0;}                                                //Ensure the number string is terminated in a zero
else expt_10 = 0;                                                     //Set to zero if no exponent was enntered.

expt_10 += Justify_Num_string(data_buff);                             //Shift the dp so that there is only one digit on its LHS
Serial.write('\t');

itoa(expt_10, expt_10_string, 10);                                    //Echo the string prior to its conversion to a FPN
if (sign == negative)Serial.write ('-');
Serial.write(data_buff); Serial.write ('E');
Serial.write(expt_10_string);



/*********Almalmagate the exponent and real number********************************************************************/

Serial.write("\r\n");
FPNum = Real_Num_to_FPN(data_buff, sign);                           //Reads data_buff and converts the string to a floating point number

if (expt_10 > 0){                                                   //Repeatedly multiply FPNum untill its exponent is zero
while (expt_10){FPNum *= 10; expt_10 -= 1;}}

if (expt_10 < 0){                                                    //Repeatedly divide FPNum untill its exponent is zero
while (expt_10){FPNum /= 10; expt_10 += 1;}}


Serial.write("\r\nFPN equivalent\t");
FNP_in_binary_to_PC(FPNum);




/********Reverse the proces to recover the real number****************************************************************/

Serial.write ("\r\n\r\nReverse the process");

expt_10 = 0;
while((FPNum > 10) || (FPNum < -10))                               //For numbers greater than +/- 10
{FPNum /= 10; expt_10 += 1;}                                       //repeatedly divide them by 10


while((FPNum < 1) && (FPNum > -1))                                 //For numbers smaller than +/- 1
{FPNum *= 10; expt_10 -= 1;}                                       //repeatedly multiply them by 10

itoa(expt_10, expt_10_string, 10);                                //Convert the exponent to a string
FPN_print_out(FPNum);                                             //Print out the number
Serial.write(" E ");                                              //plus exponent
Serial.write (expt_10_string);

Serial.write("\r\n"); }}



/***************************************************************************************************************************/
int Justify_Num_string(char * data_buff ){
char dp_ptr;
char expt_10;
char dp_location;                                                   //Location of decimal point in real number string

dp_ptr = 0;
while (data_buff[dp_ptr] != '.')                                    //Scann the numerical string looking for the dp.
{if(data_buff[dp_ptr++] > '0')                                      //Is a non zero digit encountered first

{dp_ptr = 0;                                                        //If yes 
while (data_buff[dp_ptr++] != '.');                                 //continue untill the dp has been located
for (int m = dp_ptr-1; m >= 2; m--)                                 //Shift all digits bar the first one space right 
data_buff[m] = data_buff[m - 1];                                    //to occuppy the space originally occupied by the dp
data_buff [1] = '.';                                                //Place the dp in the vacated space
expt_10 = dp_ptr - 2;                                               //Shifing the dp requires an adjustment to the tens exponent
break;}}

if (data_buff[dp_ptr] == '.')                                       //There are no non zero digits to the left of the dp  
{expt_10 = 0;
while ((data_buff[dp_ptr + 1])  == '0'){                            //Check for the presence of a non zero digit immediately to the left of the dp                           
{for(int m = dp_ptr + 1; m < 13; m++)                               //Shift all digits comming after the dp one place to the left
data_buff[m] = data_buff[m + 1];}
data_buff[14] = 0;                                                  //Clear the least significant digit
expt_10 -= 1;}                                                       //Adjust the tens exponent

data_buff[dp_ptr] = data_buff[dp_ptr + 1];                          //Move the dp one place to the right allong the string                           
data_buff[dp_ptr + 1] = '.';
expt_10 -= 1;

dp_ptr = 0;
while ((data_buff[dp_ptr++])  == '0'){                              //Check for unwanted zeros at the start of the numeric string                            
{for(int m = 0; m < 13; m++)                                        //Shift all digits left to remove them
data_buff[m] = data_buff[m + 1];}
data_buff[14] = 0;                                                  //Clear the vacated digit
dp_ptr = 0;}}

return expt_10;}
