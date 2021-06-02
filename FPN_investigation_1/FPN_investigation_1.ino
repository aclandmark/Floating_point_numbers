

#include "Project_header.h"

int main (void){ 

char keypress;                                               
char dp_location;
long LHS_of_dp, RHS_of_dp;
long binary_places;
int precision;
int num_decimal_places;


setup_328_HW;                                                     //see header file"
sei();

while(1){
do{Serial.write("F/f    ");}                                       //User prompt; press F or f to escape
while((isCharavailable(127) == 0));                                //Waits 1 sec for user response; then resends prompt    
keypress = Serial.read();
if ((keypress  == 'F')||
(keypress  == 'f'))break;}


Serial.write("\r\n\r\nFPN from keyboard\
\r\n\r\nEcho keypresses ");                                        //User enters floating point number (FPN)
dp_location = Float_from_KBD(data_buff);                          //Subroutine echoes keypresses to screen

LHS_of_dp = atol(data_buff);                                      //Convert integer part to binary

Serial.write("\r\nReal number in binary form\r\n");

Binary_to_PC(LHS_of_dp);                                          //Echo binary part to the screen

RHS_of_dp = atol(data_buff + dp_location + 1);                    //Convert the decimal places to an integer number
binary_places = decimal_to_binary(RHS_of_dp, 32);                 //Convert the integer number to binary places                                 
Serial.write(" . ");
Binary_to_PC(binary_places);                                      //Echo the binary places to the screen

Serial.write("\r\n\r\nShift significant binary places to \
LHS of binary point\r\nand set the number of decimal places\r\n");

Serial.write ("No. binary places (Enter 1 - 26)?   ");
Float_from_KBD(data_buff);
precision = atol(data_buff);

Serial.write ("\r\nNo. decimal places (Enter 0 - 32)?    ");
Float_from_KBD(data_buff);
num_decimal_places = atol(data_buff);

Serial.write ("\r\nSignificant Binary places as integer number");
binary_points_to_decimal(binary_places, precision, num_decimal_places);

Serial.write("\r\n"); 


while(1);
SW_reset;}

 

/********************************************************************************************************/
void Binary_to_PC(long num){
  int HB, LB;
  long temp;
  temp = num >> 16;
  HB = temp;
  LB = num;
for (int m = 0; m <= 15; m++){if ((m) && !(m%4))Serial.write(' ');
  if (HB & (1 << (15 - m)))Serial.write('1'); else Serial.write('0');}
  Serial.write(' ');
  for (int m = 0; m <= 15; m++){if ((m) && !(m%4))Serial.write(' ');
  if (LB & (1 << (15 - m)))Serial.write('1'); else Serial.write('0');}}
 


/********************************************************************************************************/
long decimal_to_binary(long num, int precision){
long denominator = 1;
long result = 0;
long remainder;
while(denominator < num) denominator *= 10;
remainder = num;
for (int m = 0; m < precision; m++){
result = (result << 1) | ((remainder * 2)/ denominator);
remainder = (remainder * 2) % denominator;}
return result;}



/********************************************************************************************************/
void binary_points_to_decimal(long binary_points, int precision, int Num_dps){
long denominator = 1;
char result;
long remainder;

binary_points = (unsigned long)binary_points >> (32 - precision);

while (denominator <= binary_points)denominator *= 2; 

Serial.write("\r\n");
Binary_to_PC(binary_points);Serial.write("  which converts to 0.");

remainder = binary_points;
for (int m = 0; m < Num_dps; m++){
  result = ((remainder * 10)/ denominator);
remainder = (remainder * 10) % denominator;
//array[array_ptr++] = result + '0';
Serial.write(result + '0');}}
  


/********************************************************************************************************/
char data_from_KBD(void){
while (!(Serial.available()));
return Serial.read();}
