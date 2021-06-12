
/*
Explores steps required to enter real numbers
convert them to binary and then reconvert them to strings
Looks at the errors generated by this process.
*/



#include "Project_header.h"

int main (void){ 

unsigned long FPNumLF;                                              //Floating point num in unsigned long format
float FPNum;                                    
float* FPNum_ptr;                                                   //Pointer to the floating point number
long LHS, RHS;
char T_array[15];
char expt_10_string[6];
char E_ptr;
int expt_10;

setup_328_HW;                                                       //see header file"

//FPNum_ptr = (float *)&FPNumLF;
//FPNum = *FPNum_ptr;


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

itoa(expt_10, expt_10_string, 10);                                     //Echo the string prior to its conversion to a FPN
Serial.write(data_buff); Serial.write ('E');
Serial.write(expt_10_string);

Serial.write("\r\n");
FPNumLF = Real_Num_to_FPN(data_buff);
Serial.write("\r\nFPN equivalent\t");
FNP_in_binary_to_PC(FPNumLF);



/********Reverse the proces to recover the real number****************************************************************/

Serial.write ("\r\n\r\nReverse the process\r\n");
FPN_print_out(FPNumLF);
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
