char int_length(long );
void Binary_to_PC(long );
void FNP_in_binary_to_PC(long );
long decimal_to_binary(long,char,char);
void binary_points_to_decimal(long, int, int);





/*********************************************************************************************************************************/
void Real_Num_to_FPN(void){

char LHS_length;                                                    //Number of binary characters on LHS of binary point
char num_leading_zeros;                                             //The number of zeros immediately following the dp.

char next_decimal_place;                                            //Location of decimal places comming after the decimal point
long binary_places;                                                 //Binary equivalent of decimal places
//char sign; 
int expt_2;                                                         //Exponent to which binary number is raised.
long LHS_of_dp, RHS_of_dp;



//sign = positive;                                                      //Default setting
//dp_location = Scientific_num_from_KBD(data_buff, &sign);              //Subroutine echoes keypresses to screen


/********Proces the integer part of the non-integer number*********************************************************************/
LHS_of_dp = atol(data_buff);                                          //Convert integer part to binary
LHS_length = int_length(LHS_of_dp);                                   //See below for this subroutine
expt_2 = 127 + (LHS_length - 1);                                      //Floating point format (exponent = length - 1)


/********Procces the fractional part of the number*********************************************************************/
if(dp_location == 14)                                                 //Set to 14 in the absence of any decimal places
binary_places = 0;                                                    //No binary places required.

else
{RHS_of_dp = atol(data_buff + dp_location + 1);                       //Convert the decimal places to an integer number
num_leading_zeros = 0;                                                //Check for the presence of leading zeros (i.e. 7.0005)
next_decimal_place = dp_location + 1;                                 //Location of first decimal place
while ((data_buff[next_decimal_place++]) == '0')
num_leading_zeros += 1;                                               //Count the number of leading zeros 
                                                       
binary_places = 
decimal_to_binary(RHS_of_dp,LHS_length,num_leading_zeros); }         //Convert the integer to the max allowed num of binary places 


/********Start assembly of the FPN****************************************************************/
if (LHS_length){FPN = LHS_of_dp << (25 - LHS_length);                  //Shift MSB to bit 24
FPN = FPN | binary_places;}                                            //Start building the FPN

else {FPN = binary_places;                                            //Special case: There are bits on the LHS of the binary point
while (!(FPN & (( 0x80000000 >> 7))))                                 //LHS_of_dp is zero                 
{FPN = (FPN << 1);expt_2 -= 1;}}                                      //Shift MS '1' of binary places to bit 24


/********Round up: Add one to LSB & vacate bit 23****************************************************************/
FPN += 1;     
FPN = FPN >> 1;                                                        //Vacate bit 24
if (FPN & (0x80000000 >> 7))                                           //Special case: round up caused bit 25 to be occupied 
{FPN = FPN >> 1; expt_2 += 1;LHS_length += 1;}


FPN = FPN & (~(0x800000));                                            //Clear bit 23: The MSB of the integer number
FPN = FPN | ((unsigned long)expt_2 << 23);                            //Copy in the exponent

if (sign == negative)FPN |= 0x80000000;  }                             //Add in the sign bit






/*********************************************************************************************************************************/
void FPN_print_out(void){
int num_decimal_places;                                         //Entered by user prior to the binary to askii conversion
long binary_places;                                             //Binary equivalent of decimal places
long binary_digits;                                             //Includes binary digits on both sides of the binary point
//char sign; 
int expt_2;                                                     //Exponent to which binary number is raised.
long LHS_of_dp, RHS_of_dp;




if (FPN & (0x80000000)) {sign = negative;                        //Check for a negative sign                  
FPN &= (~(0x80000000));}                                         //Clear sign bit

Serial.write ("\r\nNo. decimal places (Enter 0 - 32)?    ");
Scientific_num_from_KBD(data_buff,&sign);                       //Enter number of decimal places required
num_decimal_places = atol(data_buff);

expt_2 = ((FPN >> 23) & 0x1FF) - 127;                             //Recover the exponent
ltoa(expt_2, data_buff, 10);
Serial.write("\r\nTwo's exponent is  ");
Serial.write(data_buff);

binary_digits = FPN & (~(0xFF800000));                          //Mask of exponent and sign, leaving bits on both the LHS & RHS of the point.
binary_digits |= 0x800000;                                      //Reinstate the missing 1 (the most significant bit)

LHS_of_dp = binary_digits >> (23 - expt_2);                     //Remove binary places leaving just the LHS of the binary point

Serial.write("\r\n\r\nLHS bits are\t");
Binary_to_PC(LHS_of_dp);
Serial.write("  which converts to ");
if(sign == negative) Serial.write('-');
ltoa(LHS_of_dp, data_buff, 10);
Serial.write(data_buff);

binary_places = 
binary_digits  & (~(LHS_of_dp << (23 - expt_2)));               //Remove bits on the LHS of the binary point 

Serial.write("\r\nRHS bits are\t");
Binary_to_PC(binary_places);
Serial.write("  which converts to 0.");
binary_points_to_decimal(binary_places, expt_2, num_decimal_places);}





/********************************************************************************************************/
char int_length(long num){
char len = 1;

if (!(num))return 0;
while (num = (num >> 1)) len += 1;
return len;}



 

/********************************************************************************************************/
void Binary_to_PC(long num){                                              //Sends a binary number to the screen as ones and zeros
  int HB, LB;                                                             //High byte and low byte
  
  HB = num >> 16;
  LB = num;
for (int m = 0; m <= 15; m++){if ((m) && !(m%4))Serial.write(' ');
  if (HB & (1 << (15 - m)))Serial.write('1'); else Serial.write('0');}
  Serial.write(' ');
  for (int m = 0; m <= 15; m++){if ((m) && !(m%4))Serial.write(' ');
  if (LB & (1 << (15 - m)))Serial.write('1'); else Serial.write('0');}}



/********************************************************************************************************/
void FNP_in_binary_to_PC(long num){                                  
char counter = 0;
for (unsigned long m = 0x80000000; m >= 1; m = m >> 1){
  if (num & m)Serial.write('1'); else Serial.write('0');counter += 1;
  if ((counter == 1) || (counter == 9) || (counter == 12)
  || (counter == 16) || (counter == 20) || (counter == 24)
  || (counter == 28))  Serial.write(' ');}}



/********************************************************************************************************/
long decimal_to_binary(long num,char LHS_length,char num_leading_zeros){       //Takes decimal points as integer number
long denominator = 1;                                                          //converts it to a fraction
long result = 0;                                                               //and converts the fraction to binary places
long remainder;

if (!(num))return 0;
while(denominator <= num) denominator *= 10;
while (num_leading_zeros--)denominator *= 10;


remainder = num;
for (int m = 0; m <= (24 - LHS_length); m++){                                 //Maximum num binary places + 1 for rounding
result = (result << 1) | ((remainder * 2)/ denominator);
remainder = (remainder * 2) % denominator;}

return result;}                                                               //Returns one additional binary place


                                           



/********************************************************************************************************/
void binary_points_to_decimal(long binary_points, int expt, int Num_dps){
long denominator = 1;                                                       
char result;                                                                //Takes the binary places as an integer number
long remainder;                                                             //converts it to a fraction and
                                                                            //converts this to decimal places
if (expt >= -4)                                                           
{denominator = (unsigned long)0x80000000 >> (8 + expt);                     //Fails for shifts of less than 4
remainder = binary_points;}
else
{denominator = (unsigned long)0x80000000 >> (4);                            //If the exponent is less than -4
remainder = binary_points >> -expt - 4;}                                    //we must also shift the binary points

for (int m = 0; m < Num_dps; m++){
result = ((remainder * 10)/ denominator);
remainder = (remainder * 10) % denominator;
Serial.write(result + '0');}}
  


/********************************************************************************************************/
char data_from_KBD(void){
while (!(Serial.available()));
return Serial.read();}