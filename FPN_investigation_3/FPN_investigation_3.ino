
/*
Explores steps required to enter real numbers
convert them to binary and then reconvert them to strings
Looks at the errors generated by this process.
*/



#include "Project_header.h"

int main (void){ 

long LHS, RHS;
char T_array[15];
char dp_ptr;
char expt_10;
char E_ptr;


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
E_ptr = Scientific_num_from_KBD(data_buff, &sign);              //Subroutine echoes keypresses to screen

Serial.write("\r\n");
Serial.write(data_buff);


dp_ptr = 0;
while (data_buff[dp_ptr] != '.')                                    //Scann the numerical string looking for the dp.
{if(data_buff[dp_ptr++] > '0')                                      //Is a non zero digit encountered first

{dp_ptr = 0;                                                        //If yes 
while (data_buff[dp_ptr++] != '.');                                 //continue untill the dp has been located
for (int m = dp_ptr-1; m >= 2; m--)                                 //Shift all digits bar the first one space right 
data_buff[m] = data_buff[m - 1];                                    //to occuppy the space originally occupied by the dp
data_buff [1] = '.';                                                //Place the dp in the vacated space
dp_location = 1;                                                    //Sett the dp location for the RN to FPN subroutine
expt_10 = dp_ptr - 2;                                               //Shifing the dp requires an adjustment to the tens exponent

Serial.write("\r\n");
Serial.write(data_buff); Serial.write ('E'); Serial.write (expt_10 + '0');break;}}

if (data_buff[dp_ptr] == '.')                                       //There are no non zero digits to the left of the dp  
{expt_10 = 0;
while ((data_buff[dp_ptr + 1])  == '0'){                            //Check for the presence of a non zero digit immediately to the left of the dp                           
{for(int m = dp_ptr + 1; m < 13; m++)                               //Shift all digits comming after the dp one place to the left
data_buff[m] = data_buff[m + 1];}
data_buff[14] = 0;                                                  //Clear the least significant digit
expt_10 -= 1;}                                                       //Adjust the tens exponent

data_buff[dp_ptr] = data_buff[dp_ptr + 1];                          //Move the dp one place to the right allong the string                           
data_buff[dp_ptr + 1] = '.';
dp_location = dp_ptr + 1;                                           //Required by the RN to FPN subroutine
expt_10 -= 1;
Serial.write("\r\n");
Serial.write(data_buff);Serial.write ("E-"); Serial.write (expt_10 * -1 + '0');

}


/*LHS = atol(data_buff); 
RHS = atol(data_buff + dp_location + 1);

Serial.write("\r\n");
ltoa(LHS, T_array, 10);Serial.write(T_array);Serial.write('\t');
ltoa(RHS, T_array, 10);Serial.write(T_array);*/
Serial.write("\r\n");

Real_Num_to_FPN();
Serial.write("FPN equivalent\t");







FNP_in_binary_to_PC(FPN);



/********Reverse the proces to recover the real number****************************************************************/

Serial.write ("\r\n\r\nReverse the process\r\n");

FPN_print_out();




Serial.write("\r\n"); }}
